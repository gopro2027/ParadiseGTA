//Sessions list: lists the public sessions the game's matchmaking finds and joins the one you pick
//
//Ported from the 1.12 menu, which hooked the sceNpMatching2GetEventData import (1.12 0x2394154), copied every event's
//data and guessed from fixed offsets (+0x2C, 0xD4 per room) whether it was a room search. Those offsets are the
//firmware's SceNpMatching2SearchRoomResponse: { SceNpMatching2Range range (startIndex, total, size);
//SceNpMatching2RoomDataExternal *roomDataExternal; }, a linked list of rooms, each with its owner's SceNpUserInfo2.
//1.12 never got the join itself working (its networkJoinSession hook was "need more research").
//
//1.27 EBOOT:
//  0x18080E4 sceNpMatching2GetEventData import stub (slot 0x1C10784), only called by 0xD2B430, which copies an event
//            into a queued event object (data pointer at +0x1C, error code at +0x28).
//  0x16BECCC the room search task's update, the only sceNpMatching2SearchRoom caller (0x16BF348). Max 20 rooms.
//  0x16BF3F0 the room search task's event handler (vtable 0x1909764 +0x28 = slot 0x190978C, OPD 0x1C5B4D0, no direct
//            callers). On the response it walks the room list and turns each room into an rlSessionInfo with
//            0xD2B210, skipping your own room (0xD0C660). The rlSessionFindTask (0xD5B084) then queries each host for
//            details (0xD4BDD0) and the game joins one of them.
//  rlSessionInfo (0x40 bytes, same layout the gsinfo string import 0xD20D94 / 0xD3D7BC fills): +0x00 u64 token = the
//            room id, +0x08 u8 0, +0x10 the host's peer address = SceNpId (0x24 bytes) + 8 zero bytes, rest zero.
//So the event handler is hooked (its OPD) instead of GetEventData: it only ever sees room search responses, on the
//game's own thread, while the data is still valid. A room is joined by building its rlSessionInfo and going through the same
//self-invite path as Met Players > Join Them (HandleJoinPlayerWithSessionInfo in Mods.h).
//The list fills when the game matchmakes (going online, Find New Session) and from the menu's Search For Sessions,
//which runs the game's own session find (0xD597B4) with the filter the game built on its last attempt to go online.

namespace SessionBrowser {

	const unsigned int SEARCH_TASK_EVENT_SLOT = 0x190978C;//vtable 0x1909764 +0x28
	const unsigned int SEARCH_TASK_EVENT_OPD = 0x1C5B4D0;
	const unsigned int SEARCH_TASK_EVENT_FUNC = 0x16BF3F0;

	//SceNpMatching2SearchRoomResponse / SceNpMatching2RoomDataExternal offsets
	const int RESPONSE_ROOM_COUNT = 0x8;//range.size
	const int RESPONSE_FIRST_ROOM = 0xC;
	const int ROOM_NEXT = 0x0;
	const int ROOM_ID = 0x18;//u64
	const int ROOM_MAX_SLOT = 0x22;//u16
	const int ROOM_MEMBER_COUNT = 0x26;//u16 curMemberNum
	const int ROOM_OWNER = 0x30;//SceNpUserInfo2*, starts with the owner's SceNpId
	const int NPID_SIZE = 0x24;//SceNpId: online id (16 chars + term + 3), opt[8], reserved[8]

	const int MAX_ROOMS = 16;//16 * 48 bytes. The game asks for at most 20 rooms per search

	struct Room {
		uint64_t roomId;
		char npId[NPID_SIZE];//the host; the first 16 bytes are the PSN name
		unsigned short players;
		unsigned short maxPlayers;
	};

	Room rooms[MAX_ROOMS];
	int roomCount = 0;
	int nextReplace = 0;
	bool installed = false;

	opd_s searchTaskEvent_t = { SEARCH_TASK_EVENT_FUNC, TOC };
	int(*searchTaskEvent)(unsigned int task, unsigned int evt) = (int(*)(unsigned int, unsigned int))&searchTaskEvent_t;

	//debug log, read over FTP. Fsynced so the last lines before a crash are on disk
	void logLine(const char *fmt, ...) {
#if SESSIONS_LOG == 1
		char buf[200];
		int len = snprintf(buf, sizeof(buf), "[%u] ", (unsigned int)time(0));
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf + len, sizeof(buf) - len, fmt, args);
		va_end(args);
		int fd;
		uint64_t written;
		if (cellFsOpen("/dev_hdd0/tmp/gopro_2027/sessions_log.txt", CELL_FS_O_RDWR | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
			return;
		cellFsWrite(fd, (const void*)buf, (uint64_t)strlen(buf), &written);
		cellFsFsync(fd);
		cellFsClose(fd);
#endif
	}

	unsigned int hashText(const char *s) {//FNV-1a, to log a repeated line only when it changes
		unsigned int h = 2166136261u;
		while (*s)
			h = (h ^ (unsigned char)*s++) * 16777619u;
		return h;
	}

	//shown in the menu, to tell an empty search from no search at all
	int handlerCalls = 0;//every event the room search task got
	int searchesSeen = 0;//search responses read
	int lastSearchRooms = -1;//rooms in the last response

	//Search button: the same rlSessionManager find the game's matchmaking starts (CNetworkSession 0x138A184):
	//  0xD597B4(localGamer = *0x1CF7308, 1, 7, 1, filter, results, 15, *(session+0xA784), &resultCount, &status)
	//It creates an rlSessionFindTask (0x860 bytes, update 0xD5B084): mode 1 (PSN; mode 2 is LAN broadcast) starts the
	//room search task (0xD2A8DC), whose response goes through searchTaskEvent_hook like any other search, then asks
	//each host for its session details (0xD4BDD0) into results (0x240 bytes each).
	//  filter: the game's matchmaking filter (0x238 bytes), which DoMatchmakingCommon (0x138A770) builds and keeps at
	//          session+0xA0C8 (the matchmaking config is session+0xA09C, the filter its +0x2C) every time the game tries
	//          to go online, before any search starts. Before each search the game also calls
	//          0xD4AB18(filter, *(config+0xC), 0x135840C(config)), so we do too.
	//          As ints: [0] != -1, [1] condition count (<= 32), [2] [3] != -1 (the 2-byte bin attribute 0x54 value).
	//  results: the session's own result array (session+0xF098, 15 * 0x240 bytes), so the SPRX doesn't need 8.6 KB.
	//           Only used while the game's own regular search isn't running (session+0x112A4).
	//0xD597B4 fails right away if the gate at its start fails (gateCheck), if its 0x860-byte task can't be allocated or
	//queued. After that, status says how the find ended. The room search task needs the PSN matching context
	//(0x2031490) state +0x44 to be 2 (started); 0xD29484 starts it.
	const unsigned int NETWORK_SESSION_PTR = 0x1CF72C4;//CNetworkSession*
	const unsigned int LOCAL_GAMER_INDEX = 0x1CF7308;
	const unsigned int SESSION_FIND = 0xD597B4;
	const unsigned int MATCHING_CONTEXT = 0x2031490;
	const unsigned int MATCHING_READY = 0xD29484;//also starts the context
	const int SESSION_MM_CONFIG = 0xA09C;
	const int SESSION_FILTER = 0xA0C8;
	const int SESSION_RESULTS = 0xF098;
	const int SESSION_FIND_ARG = 0xA784;
	const int SESSION_REGULAR_SEARCH_BUSY = 0x112A4;//byte, set while the game's own regular search runs

	int findResultCount = 0;
	int findStatus[2] = { 0, 0 };//rage status: [0] 0 none, 1 pending, 2 failed, 3 succeeded
	int lastFindReturn = -1;//0xD597B4's return, -1 not called yet
	int lastGate = -1;
	int lastStartError = 0;

	unsigned int session() {
		return *(unsigned int*)NETWORK_SESSION_PTR;
	}

	int *gameFilter() {
		unsigned int s = session();
		return VALID_ADDR(s) ? (int*)(s + SESSION_FILTER) : 0;
	}

	bool filterValid() {
		int *f = gameFilter();
		return f && f[0] != -1 && f[2] != -1 && f[3] != -1 && f[1] >= 0 && f[1] <= 32;
	}

	//the check at the start of 0xD597B4 (0xD597FC..0xD5984C)
	int gateCheck() {
		int gamer = *(int*)LOCAL_GAMER_INDEX;
		if (gamer != 0)
			return 0;
		unsigned int base = 0x2051598 + gamer * 0xC88;
		if (*(int*)(base + 0x2B0) != 0)
			return call<int>(0xD2D398)(base + 0x30, 3);
		return *(unsigned char*)0x184FE97;
	}

	int matchingContextState() {
		return *(int*)(MATCHING_CONTEXT + 0x44);
	}

	void clear() {
		roomCount = 0;
		nextReplace = 0;
	}

	void copyName(char *dst, const Room &room) {//dst: 17 bytes
		strncpy(dst, room.npId, 16);
		dst[16] = 0;
	}

	void addRoom(uint64_t roomId, const char *npId, unsigned short players, unsigned short maxPlayers) {
		int i;
		for (i = 0; i < roomCount; i++)
			if (rooms[i].roomId == roomId)
				break;
		if (i == roomCount) {
			if (roomCount < MAX_ROOMS) {
				roomCount++;
			}
			else {//full: replace the oldest
				i = nextReplace;
				nextReplace = (nextReplace + 1) % MAX_ROOMS;
			}
		}
		rooms[i].roomId = roomId;
		memcpy(rooms[i].npId, npId, NPID_SIZE);
		rooms[i].players = players;
		rooms[i].maxPlayers = maxPlayers;
	}

	//response: the SceNpMatching2SearchRoomResponse the game got from sceNpMatching2GetEventData
	void readSearchResponse(unsigned int response) {
		if (!VALID_ADDR(response))
			return;
		int count = *(int*)(response + RESPONSE_ROOM_COUNT);
		unsigned int room = *(unsigned int*)(response + RESPONSE_FIRST_ROOM);
		int added = 0;
		for (int n = 0; n < count && n < 20 && VALID_ADDR(room); n++) {
			uint64_t roomId = *(uint64_t*)(room + ROOM_ID);
			unsigned int owner = *(unsigned int*)(room + ROOM_OWNER);
			unsigned short players = *(unsigned short*)(room + ROOM_MEMBER_COUNT);
			unsigned short maxPlayers = *(unsigned short*)(room + ROOM_MAX_SLOT);
			if (roomId != 0 && VALID_ADDR(owner) && players > 0 && *(char*)owner != 0) {
				addRoom(roomId, (const char*)owner, players, maxPlayers);
				added++;
			}
			room = *(unsigned int*)(room + ROOM_NEXT);
		}
		searchesSeen++;
		lastSearchRooms = count;
		logLine("room search: %i rooms, %i listed, %i in list\n", count, added, roomCount);
	}

	int searchErrors = 0;//search events that came back with an error
	int lastSearchError = 0;//its SCE error code

	//replaces the room search task's event handler (0x16BF3F0). It returns 1 when it used a search response
	int searchTaskEvent_hook(unsigned int task, unsigned int evt) {
		handlerCalls++;
		if (VALID_ADDR(evt) && *(int*)(evt + 0x28) < 0) {
			searchErrors++;
			lastSearchError = *(int*)(evt + 0x28);
			logLine("room search event error 0x%08X\n", lastSearchError);
		}
		int ret = searchTaskEvent(task, evt);
		if (ret && VALID_ADDR(evt))
			readSearchResponse(*(unsigned int*)(evt + 0x1C));
		return ret;
	}

	opd_s sessionFind_t = { SESSION_FIND, TOC };
	int(*sessionFind)(int localGamer, int a2, int a3, int a4, int *filter, unsigned int results, int maxResults, int a8,
		int *resultCount, int *status) = (int(*)(int, int, int, int, int*, unsigned int, int, int, int*, int*))&sessionFind_t;

	bool isSearching() {
		return findStatus[0] == 1;
	}

	//0 started, 1 no filter yet (the game hasn't tried to go online), 2 already searching, 3 the game's own search
	//is running, 4 0xD597B4 refused (see lastGate), 5 no network session
	int startSearchImpl() {
		unsigned int s = session();
		if (!VALID_ADDR(s))
			return lastStartError = 5;
		if (!filterValid())
			return lastStartError = 1;
		if (isSearching())
			return lastStartError = 2;
		if (*(unsigned char*)(s + SESSION_REGULAR_SEARCH_BUSY) != 0)
			return lastStartError = 3;
		call<int>(MATCHING_READY)(MATCHING_CONTEXT);//starts the PSN matching context if it isn't yet, like DoMatchmakingCommon
		unsigned int config = s + SESSION_MM_CONFIG;
		call<int>(0xD4AB18)(s + SESSION_FILTER, *(int*)(config + 0xC), call<int>(0x135840C)(config));
		lastGate = gateCheck();
		findStatus[0] = 0;
		findStatus[1] = 0;
		findResultCount = 0;
		lastFindReturn = sessionFind(*(int*)LOCAL_GAMER_INDEX, 1, 7, 1, gameFilter(), s + SESSION_RESULTS, 15,
			*(int*)(s + SESSION_FIND_ARG), &findResultCount, findStatus);
		if (lastFindReturn == 0)
			return lastStartError = 4;
		return lastStartError = 0;
	}

	void matchmakingStatusText(char *buf, int size);

	int startSearch() {
		int result = startSearchImpl();
		char mm[100];
		matchmakingStatusText(mm, sizeof(mm));
		logLine("search button: %i (0xD597B4 %i, gate %i, matching context %i) | %s\n", result, lastFindReturn, lastGate,
			matchingContextState(), mm);
		return result;
	}

	//One line for the menu with everything DoMatchmakingCommon (0x138A770) checks before it writes the filter. Going online
	//(NETWORK_SESSION_ENTER -> 0x138ADD4(session, gamemode, 1, 18, ...)) only searches if all of these pass; otherwise it
	//returns 0 before the filter is written:
	//  st   session state +0xA098: must not be 1 (and < 5 for 0x138ADD4)
	//  chk  0x1389540 (signed in / privileges), 0x1389D98 access check (reason code in brackets, see
	//       research/temp-character-mode.md), 0x1389CD4
	//  grp  current matchmaking group +0xAA50 (NETWORK_SESSION_SET_MATCHMAKING_GROUP 0x3C3E2AB6), must not be -1 and must
	//       be in the active list [count +0xAA68: +0xAA6C, +0xAA70] (0x5BE529F7). maintransition func_2410 sets group
	//       0 or 4 and adds 4 and 0
	//  f    filter ints 0..3 at +0xA0C8 (0 and 2, 3 must not be -1 for a search)
	void matchmakingStatusText(char *buf, int size) {
		unsigned int s = session();
		if (!VALID_ADDR(s)) {
			snprintf(buf, size, "No network session object");
			return;
		}
		int code = -1;
		int checkSignedIn = call<int>(0x1389540)(s, "SessionBrowser", 1) != 0;
		int checkAccess = call<int>(0x1389D98)(s, &code) != 0;
		int checkOther = call<int>(0x1389CD4)(s) != 0;
		int *f = (int*)(s + SESSION_FILTER);
		snprintf(buf, size, "MM st %i chk %i%i(%i)%i grp %i [%i:%i,%i] f %i,%i,%i,%i", *(int*)(s + 0xA098), checkSignedIn,
			checkAccess, code, checkOther, *(int*)(s + 0xAA50), *(int*)(s + 0xAA68), *(int*)(s + 0xAA6C), *(int*)(s + 0xAA70),
			f[0], f[1], f[2], f[3]);
	}

	//one line for the menu about the last search button press
	void findStatusText(char *buf, int size) {
		if (lastFindReturn == -1) {
			snprintf(buf, size, "~c~Search: not used yet, filter %s", filterValid() ? "ok" : "missing");
			return;
		}
		const char *state = "?";
		switch (findStatus[0]) {
		case 0: state = "not started"; break;
		case 1: state = "searching"; break;
		case 2: state = "failed"; break;
		case 3: state = "done"; break;
		}
		snprintf(buf, size, "~c~Find %i, gate %i, ctx %i: %s, %i found", lastFindReturn, lastGate, matchingContextState(),
			state, findResultCount);
	}

	//Logging hooks on the session natives maintransition uses to go online (func_2407). Native handlers take a context:
	//[0] pointer to the return value, [8] pointer to the arguments (4 bytes each). Handler OPDs are in the native table
	//registration (0x3F4354 for NETWORK_SESSION_ENTER). The script retries every frame until a call succeeds, so a line is
	//only written when it differs from the previous one for that native.
	//  NETWORK_SESSION_ENTER 0x543CD2BE: OPD 0x1C28B40, handler 0x1586B08 -> 0x3E3E08 -> 0x12F6ED8 -> 0x138ADD4
	//  NETWORK_SESSION_HOST  0x6716460F: OPD 0x1C28B60, handler 0x1586C70 -> 0x3E3FBC -> 0x12F6FEC -> 0x1389F84
	const unsigned int SESSION_ENTER_OPD = 0x1C28B40;
	const unsigned int SESSION_ENTER_HANDLER = 0x1586B08;
	const unsigned int SESSION_HOST_OPD = 0x1C28B60;
	const unsigned int SESSION_HOST_HANDLER = 0x1586C70;

	opd_s sessionEnterNative_t = { SESSION_ENTER_HANDLER, TOC };
	void(*sessionEnterNative)(unsigned int ctx) = (void(*)(unsigned int))&sessionEnterNative_t;
	opd_s sessionHostNative_t = { SESSION_HOST_HANDLER, TOC };
	void(*sessionHostNative)(unsigned int ctx) = (void(*)(unsigned int))&sessionHostNative_t;
	int enterCalls = 0;
	int hostCalls = 0;
	unsigned int lastEnterHash = 0;
	unsigned int lastHostHash = 0;

	//mm: the matchmaking checks before the call, what DoMatchmakingCommon sees
	void logNativeCall(const char *name, unsigned int ctx, int argCount, const char *mm, int calls, unsigned int *lastHash) {
		int *args = *(int**)(ctx + 8);
		int ret = **(int**)ctx;
		char line[180];
		int len = snprintf(line, sizeof(line), "%s(", name);
		for (int i = 0; i < argCount && len < (int)sizeof(line); i++)
			len += snprintf(line + len, sizeof(line) - len, i ? ",%i" : "%i", args[i]);
		int *f = gameFilter();
		if (len < (int)sizeof(line))
			snprintf(line + len, sizeof(line) - len, ") = %i | before: %s | filter after %i,%i,%i,%i\n", ret, mm,
				f ? f[0] : 0, f ? f[1] : 0, f ? f[2] : 0, f ? f[3] : 0);
		unsigned int h = hashText(line);
		if (h != *lastHash) {
			*lastHash = h;
			logLine("call %i: %s", calls, line);
		}
	}

	void sessionEnterNative_hook(unsigned int ctx) {
		char mm[100];
		matchmakingStatusText(mm, sizeof(mm));
		sessionEnterNative(ctx);
		logNativeCall("NETWORK_SESSION_ENTER", ctx, 6, mm, ++enterCalls, &lastEnterHash);
	}

	void sessionHostNative_hook(unsigned int ctx) {
		char mm[100];
		matchmakingStatusText(mm, sizeof(mm));
		sessionHostNative(ctx);
		logNativeCall("NETWORK_SESSION_HOST", ctx, 3, mm, ++hostCalls, &lastHostHash);
	}

	//Overwrites the game's OPD for the handler (only the vtable slot points to it), like the GtaThread run hook does with
	//0x1C2F0E0. The original is still called through searchTaskEvent_t. The native hooks overwrite the native table OPDs
	//the same way
	void install() {
		if (installed)
			return;
		bool nativesHooked = false;
		if (*(unsigned int*)SESSION_ENTER_OPD == SESSION_ENTER_HANDLER && *(unsigned int*)SESSION_HOST_OPD == SESSION_HOST_HANDLER) {
			*(uint64_t*)SESSION_ENTER_OPD = *(uint64_t*)sessionEnterNative_hook;
			*(uint64_t*)SESSION_HOST_OPD = *(uint64_t*)sessionHostNative_hook;
			nativesHooked = true;
		}
		if (*(unsigned int*)SEARCH_TASK_EVENT_SLOT == SEARCH_TASK_EVENT_OPD && *(unsigned int*)SEARCH_TASK_EVENT_OPD == SEARCH_TASK_EVENT_FUNC) {
			*(uint64_t*)SEARCH_TASK_EVENT_OPD = *(uint64_t*)searchTaskEvent_hook;
			installed = true;
		}
		logLine("=== boot: room search hook %i, session native hooks %i\n", installed ? 1 : 0, nativesHooked ? 1 : 0);
	}

	bool isMe(const Room &room) {
		char *me = getMyPSNName();
		return VALID_ADDR(me) && strncmp(me, room.npId, 16) == 0;
	}

	void join(int index) {
		if (index < 0 || index >= roomCount)
			return;
		Room room = rooms[index];
		GsSession info;
		memset(&info, 0, sizeof(info));
		//the rlSessionInfo 0xD2B210 builds for a search result
		info.m_peerToken = room.roomId;
		memcpy((char*)&info + 0x10, room.npId, NPID_SIZE);
		char name[17];
		copyName(name, room);
		HandleJoinPlayerWithSessionInfo(&info, name);
	}
}
