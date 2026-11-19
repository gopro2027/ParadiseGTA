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
//The list only fills while the game matchmakes (joining GTA Online, Find New Session, ...); the menu can't start a
//search by itself.

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
#if TEMPCHAR_DEBUG == 1
		tempcharLog("[sessions] room search: %i rooms, %i listed, %i in list\n", count, added, roomCount);
#endif
	}

	//replaces the room search task's event handler (0x16BF3F0). It returns 1 when it used a search response
	int searchTaskEvent_hook(unsigned int task, unsigned int evt) {
		int ret = searchTaskEvent(task, evt);
		if (ret && VALID_ADDR(evt))
			readSearchResponse(*(unsigned int*)(evt + 0x1C));
		return ret;
	}

	//Overwrites the game's OPD for the handler (only the vtable slot points to it), like the GtaThread run hook does with
	//0x1C2F0E0. The original is still called through searchTaskEvent_t
	void install() {
		if (installed)
			return;
		if (*(unsigned int*)SEARCH_TASK_EVENT_SLOT != SEARCH_TASK_EVENT_OPD || *(unsigned int*)SEARCH_TASK_EVENT_OPD != SEARCH_TASK_EVENT_FUNC)
			return;//not the 1.27 EBOOT this was made for
		*(uint64_t*)SEARCH_TASK_EVENT_OPD = *(uint64_t*)searchTaskEvent_hook;
		installed = true;
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
