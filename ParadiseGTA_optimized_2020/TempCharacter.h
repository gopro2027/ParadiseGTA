//Temporary character mode (restored from 1.12)
//
//In 1.12, when the Rockstar cloud was unavailable, maintransition offered a temporary character that plays
//GTA Online over PSN only. 1.13+ turned that screen (transition state 21) into a "return to story mode" dead end
//and removed the setup function (1.12 maintransition func_186 / func_189), but 1.27 still honours every flag it
//set. Since the PS3 cloud is gone for good, this always does what 1.12 did: as soon as maintransition enters
//state 21 because of the cloud, set up the temporary character and continue the join (state 3, substate 4).
//Global numbers are 1.27. Arrays have a size header, so element i of Global_X[] is X + 1 + i.
//Research notes: research/temp-character-mode.md

namespace TempCharacter {

	const unsigned int MAINTRANSITION_HASH = 0x5FF2841F;//joaat("maintransition")

	const int G_TRANSITION_STATE = 1315298;//func_2706 / func_59
	const int G_TRANSITION_SUBSTATE = 1315299;//func_2714
	const int G_TRANSITION_REASON = 1315326;//func_2736 / func_74
	const int G_OFFLINE_CONTENT = 2403346;//func_1258
	const int G_TEMP_CHARACTER = 1315352;//func_54 / func_194 (1.12 Global_1344090)
	const int G_WARNING_ACCEPTED = 1315353;//func_57, skips the connection warning check (1.12 Global_1344091)
	const int G_CLOUD_DOWN_SESSION = 1315354;//func_56 / func_50 (1.12 Global_1344092)
	const int G_SKIP_TUTORIAL = 1312399;//(1.12 Global_1332465)
	const int G_SLOT_LOADED = 1312341;//array of 3, func_55 (1.12 Global_1332383)
	const int G_SLOT_EXISTS = 1315392;//array of 3, func_244 (1.12 Global_1344312)

	const int STATE_CONNECTION_PROBLEM = 21;
	const int STAT_SLOT_COUNT = 3;//1.27 has 3 stat slots, 1.12 had 6

	//1.27 maintransition func_2749() == 0, which is what makes the state 21 screen show HUD_CLOUDOFFLIN
	bool isCloudFailure() {
		if (Read_Global(G_OFFLINE_CONTENT) != 0)
			return true;
		return !NETWORK::NETWORK_IS_CLOUD_AVAILABLE();
	}

	//1.27 maintransition func_202, run before continuing past a connection warning.
	//The Global_2428598[i <6>][j] part is left out.
	void resetConnectionWarnings() {
		for (int g = 1330639; g <= 1330656; g++)
			Write_Global(g, 0);
		for (int k = 0; k <= 18; k++) {
			Write_Global(1330657 + 3 * k + 1, 0);
			Write_Global(1330657 + 3 * k + 2, 0);
		}
		for (int k = 0; k <= 3; k++) {
			Write_Global(1330714 + 3 * k + 1, 0);
			Write_Global(1330714 + 3 * k + 2, 0);
		}
	}

	//The multiplayer access check in the game code (EBOOT 0x1389D98, behind NETWORK_CAN_ACCESS_MULTIPLAYER and the gate that
	//NETWORK_SESSION_ENTER / NETWORK_SESSION_HOST go through, 0x3E3D04) returns a reason code. 1.27 added two that 1.12
	//(0x1304110) doesn't have:
	//  11: CTunables (atSingleton at 0x1CFB0B8) +0x4D == 0, the cloud tunables were never downloaded (check at 0x1389F1C)
	//  12: bgScriptData (0x1CFB100) +0x1019 == 0, the cloud background script was never loaded (check at 0x1389F3C)
	//Without the cloud both always fail, so every session native returns false and the join waits in transition sub-state 18
	//forever. Same trick as the 0x387 bypass in prologueBypass (0x1389EA4): change "cmpwi r3,0" to "cmpwi r3,5" so the
	//following bne (skip the failure) is always taken. Returns how many of the two checks are patched.
	const unsigned int ACCESS_CHECK_TUNABLES = 0x1389F20;//cmpwi r3,0 / bne 0x1389F3C
	const unsigned int ACCESS_CHECK_BG_SCRIPT = 0x1389F48;//cmpwi r3,0 / bne 0x1389F68
	const unsigned int CMPWI_R3_0 = 0x2C030000;
	const unsigned int CMPWI_R3_5 = 0x2C030005;

	int allowSessionsWithoutCloud() {
		int patched = 0;
		const unsigned int checks[] = {ACCESS_CHECK_TUNABLES, ACCESS_CHECK_BG_SCRIPT};
		for (int i = 0; i < 2; i++) {
			volatile unsigned int* ins = (volatile unsigned int*)checks[i];
			if (*ins == CMPWI_R3_0)
				*(volatile char*)(checks[i] + 3) = 5;
			if (*ins == CMPWI_R3_5)
				patched++;
		}
		return patched;
	}

	//1.12 maintransition func_186 (cloud branch) + func_189(1)
	void create() {
		allowSessionsWithoutCloud();
		resetConnectionWarnings();
		Write_Global(G_WARNING_ACCEPTED, 1);
		STATS::_0xCE7A2411(1);//block saves ("autosave disabled")
		STATS::_0x395D18B1(-1);//STAT_CLEAR_PENDING_SAVES
		for (int slot = 0; slot < STAT_SLOT_COUNT; slot++)
			STATS::STAT_DELETE_SLOT(slot);
		for (int i = 0; i <= 6; i++)
			STATS::_0xE3247582(i);//local reset of the online character stats, same range 1.27 func_2577 uses
		Write_Global(G_SKIP_TUTORIAL, 1);
		for (int slot = 0; slot < STAT_SLOT_COUNT; slot++)
			Write_Global(G_SLOT_LOADED + 1 + slot, 1);
		Write_Global(G_TEMP_CHARACTER, 1);
		Write_Global(G_SLOT_EXISTS + 1 + 0, 1);
		Write_Global(G_CLOUD_DOWN_SESSION, 1);
		Write_Global(G_TRANSITION_REASON, 0);
		Write_Global(G_TRANSITION_SUBSTATE, 4);
		Write_Global(G_TRANSITION_STATE, 3);//continue the join
		print2("~b~Rockstar cloud unavailable: playing with a temporary character", 8000);
	}

#if TEMPCHAR_DEBUG == 1
	//debug log for testing on hardware. Written next to the other Paradise files, a game can't create files in the /dev_hdd0 root
	#define TEMPCHAR_LOG_FILE "/dev_hdd0/tmp/gopro_2027/tempchar_log.txt"

	//like appendToFile, but fsyncs so the last lines before a freeze or crash are on disk
	void debugLog(const char *fmt, ...) {
		char buf[200];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, sizeof(buf), fmt, args);
		va_end(args);
		int fd;
		uint64_t written;
		if (cellFsOpen(TEMPCHAR_LOG_FILE, CELL_FS_O_RDWR | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
			return;
		cellFsWrite(fd, (const void*)buf, (uint64_t)strlen(buf), &written);
		cellFsFsync(fd);
		cellFsClose(fd);
	}
#endif

	//Transition sub-state 18 (1.27 maintransition func_2428, maintransition.c:160394). First test: the temp character got this
	//far, then hung on "Loading GTA Online" in state 32 / sub-state 18. Once the player is set up, 1.27 added a wait that 1.12
	//doesn't have (func_893): it calls ON_ENTER_MP (0xC65586A9) once (func_894, Global_2403951 = 1), which starts applying the
	//multiplayer content changesets, then waits until HAVE_ALL_STREAMING_REQUESTS_COMPLETED(PLAYER_PED_ID()) (0xF9FB4B71) is true
	//and ARE_ANY_CCS_PENDING (0x0AF83036) is false. ON_ENTER_MP / ON_ENTER_SP (0x8BF60FC3) and ARE_ANY_CCS_PENDING appear nowhere
	//else in the 1.27 scripts and not at all in 1.12. If the changesets never finish for a temporary character, the join never
	//continues. This hooks ARE_ANY_CCS_PENDING through its OPD and makes it report "nothing pending" to scripts in exactly that
	//case, after it has been pending for FORCE_IDLE_AFTER_MS. The game then continues while the changesets may still be applying.
	const int SUBSTATE_ENTER_MP = 18;
	const int G_ON_ENTER_MP_CALLED = 2403951;//func_894
	const int G_ENTER_MP_DONE = 2403952;//func_893
	const int G_NEW_CHARACTER = 1312437 + 6;//Global_1312437.imm_6[slot], array of 2, skips the player setup call when set
	const unsigned int NATIVE_ARE_ANY_CCS_PENDING = 0x0AF83036;
	const int FORCE_IDLE_AFTER_MS = 10000;

	//PED::_0xF9FB4B71 in Natives.h
	bool haveAllStreamingRequestsCompleted(int ped) {
		return PED::_0xF9FB4B71(ped) != 0;
	}

	//the original native's OPD, kept as plain words and called through call<> (which builds the OPD on the stack).
	//Calling through the address of a global opd_s makes the compiler emit a direct call to a code symbol that doesn't exist.
	unsigned int originalAreAnyCcsPendingFunc = 0;
	unsigned int originalAreAnyCcsPendingToc = 0;
	bool triedHookCcsPending = false;
	bool hookedCcsPending = false;
	bool forceCcsIdle = false;
	int ccsPendingSince = 0;

	void ARE_ANY_CCS_PENDING_hook(NativeArg_s* args) {
		call<int>(originalAreAnyCcsPendingFunc, originalAreAnyCcsPendingToc)(args);
		if (forceCcsIdle && args != NativeArg)//only for script calls; Paradise's own invoke (NativeArg) still gets the real value
			*args->ReturnValue = 0;
	}

	//swaps the native's OPD contents, so scripts that already resolved the native go through the hook too
	void hookAreAnyCcsPending() {
		triedHookCcsPending = true;
		int opd = getOPDOfNative(NATIVE_ARE_ANY_CCS_PENDING);
		if (opd == -1)
			return;
		originalAreAnyCcsPendingFunc = *(unsigned int*)opd;
		originalAreAnyCcsPendingToc = *(unsigned int*)(opd + 4);
		*(uint64_t*)opd = *(uint64_t*)((int)ARE_ANY_CCS_PENDING_hook);
		hookedCcsPending = true;
	}

	//runs after each maintransition tick; the hook uses the decision on the next tick
	void updateCcsWorkaround() {
		bool waiting = Read_Global(G_TEMP_CHARACTER) == 1 && Read_Global(G_TRANSITION_SUBSTATE) == SUBSTATE_ENTER_MP && Read_Global(G_ON_ENTER_MP_CALLED) != 0;
		if (!waiting) {
			forceCcsIdle = false;
			ccsPendingSince = 0;
			return;
		}
		int busy = invoke<int>(NATIVE_ARE_ANY_CCS_PENDING);//real value, the hook passes Paradise's calls through
		if (busy == 0) {
			forceCcsIdle = false;
			ccsPendingSince = 0;
			return;
		}
		int now = GAMEPLAY::GET_GAME_TIMER();
		if (ccsPendingSince == 0)
			ccsPendingSince = now;
		if (!forceCcsIdle && now - ccsPendingSince >= FORCE_IDLE_AFTER_MS && haveAllStreamingRequestsCompleted(PLAYER::PLAYER_PED_ID())) {
			forceCcsIdle = true;
#if TEMPCHAR_DEBUG == 1
			debugLog("[tempchar] ARE_ANY_CCS_PENDING busy for %ims, forcing idle\n", now - ccsPendingSince);
#endif
		}
	}

	//Second test: ON_ENTER_MP and the changesets finished on their own, but the join still sat in sub-state 18 with no
	//session. Once its waits pass, sub-state 18 calls func_2407 (1.27 maintransition.c:159695), which starts the session and
	//only moves on to sub-state 21 when the session native returns true; otherwise it retries every frame. The native depends
	//on the session type (Global_1315323): the default 0 matchmakes into a public session (NETWORK_SESSION_ENTER), 1 hosts a
	//public session (NETWORK_SESSION_HOST(gamemode, 18, 0)). This part of the script is unchanged since 1.12, so if the native
	//keeps failing it's the 1.27 game code refusing without Rockstar's servers. Fallback: if a temporary character has been in
	//sub-state 18 for HOST_FALLBACK_AFTER_MS with session type 0 and no session, switch to hosting.
	const int G_SESSION_TYPE = 1315323;//func_307
	const int G_GAMEMODE = 19940;//func_2713 / func_51, 0 = freemode
	const int SESSION_TYPE_MATCHMAKE = 0;
	const int SESSION_TYPE_HOST_PUBLIC = 1;
	const int HOST_FALLBACK_AFTER_MS = 15000;

	int substateEnterMpSince = 0;

	void updateSessionFallback() {
		bool waiting = Read_Global(G_TEMP_CHARACTER) == 1 && Read_Global(G_TRANSITION_SUBSTATE) == SUBSTATE_ENTER_MP && Read_Global(G_ENTER_MP_DONE) != 0;
		if (!waiting) {
			substateEnterMpSince = 0;
			return;
		}
		if (NETWORK::NETWORK_IS_SESSION_STARTED() || NETWORK::NETWORK_IS_SESSION_ACTIVE() || NETWORK::NETWORK_IS_SESSION_BUSY())
			return;
		int now = GAMEPLAY::GET_GAME_TIMER();
		if (substateEnterMpSince == 0)
			substateEnterMpSince = now;
		if (Read_Global(G_SESSION_TYPE) == SESSION_TYPE_MATCHMAKE && now - substateEnterMpSince >= HOST_FALLBACK_AFTER_MS) {
			Write_Global(G_SESSION_TYPE, SESSION_TYPE_HOST_PUBLIC);
#if TEMPCHAR_DEBUG == 1
			debugLog("[tempchar] no session after %ims in sub-state 18, switching session type 0 -> 1 (host)\n", now - substateEnterMpSince);
#endif
		}
	}

#if TEMPCHAR_DEBUG == 1
	//logs the result of every session native func_2407 can call, when maintransition calls it: the first call, every change
	//of result, and every 600th call (func_2407 retries every frame)
	struct LoggedNative {
		unsigned int hash;
		const char* name;
		unsigned int func;
		unsigned int toc;
		int lastResult;
		int calls;
	};
	LoggedNative sessionNatives[] = {
		{0x543CD2BE, "NETWORK_SESSION_ENTER", 0, 0, -1, 0},
		{0x4E53202A, "NETWORK_SESSION_FRIEND_MATCHMAKING", 0, 0, -1, 0},
		{0xD7624E6B, "NETWORK_SESSION_CREW_MATCHMAKING", 0, 0, -1, 0},
		{0x3F75CC38, "NETWORK_SESSION_ACTIVITY_QUICKMATCH", 0, 0, -1, 0},
		{0x6716460F, "NETWORK_SESSION_HOST", 0, 0, -1, 0},
		{0x8AC9EA19, "NETWORK_SESSION_HOST_CLOSED", 0, 0, -1, 0},
		{0x26864403, "NETWORK_SESSION_HOST_FRIENDS_ONLY", 0, 0, -1, 0},
	};
	const int SESSION_NATIVE_COUNT = sizeof(sessionNatives) / sizeof(sessionNatives[0]);

	void callLoggedSessionNative(int i, NativeArg_s* args) {
		LoggedNative* n = &sessionNatives[i];
		call<int>(n->func, n->toc)(args);
		if (args == NativeArg)
			return;
		GtaThread* current = getCurrentGtaThread();
		if (!VALID_ADDR(current) || current->nameHash != MAINTRANSITION_HASH)
			return;
		int result = *args->ReturnValue;
		n->calls++;
		if (n->calls == 1 || result != n->lastResult || n->calls % 600 == 0)
			debugLog("[tempchar] %s(%i, ...) = %i, call %i, session type %i\n", n->name, args->ArgValues[0].i, result, n->calls, Read_Global(G_SESSION_TYPE));
		n->lastResult = result;
	}

	#define SESSION_NATIVE_HOOK(i) void sessionNativeHook##i(NativeArg_s* args) { callLoggedSessionNative(i, args); }
	SESSION_NATIVE_HOOK(0)
	SESSION_NATIVE_HOOK(1)
	SESSION_NATIVE_HOOK(2)
	SESSION_NATIVE_HOOK(3)
	SESSION_NATIVE_HOOK(4)
	SESSION_NATIVE_HOOK(5)
	SESSION_NATIVE_HOOK(6)
	void (*sessionNativeHooks[])(NativeArg_s*) = {
		sessionNativeHook0, sessionNativeHook1, sessionNativeHook2, sessionNativeHook3,
		sessionNativeHook4, sessionNativeHook5, sessionNativeHook6,
	};

	int hookSessionNatives() {
		int hooked = 0;
		for (int i = 0; i < SESSION_NATIVE_COUNT; i++) {
			int opd = getOPDOfNative(sessionNatives[i].hash);
			if (opd == -1)
				continue;
			sessionNatives[i].func = *(unsigned int*)opd;
			sessionNatives[i].toc = *(unsigned int*)(opd + 4);
			*(uint64_t*)opd = *(uint64_t*)((int)sessionNativeHooks[i]);
			hooked++;
		}
		return hooked;
	}

	const int G_CHAR_CHANGE_STEP = 1325170 + 600;//func_2445 step, the last step of the load-into-freemode sequence (func_2440)
	const int SUBSTATE_SESSION_STARTING = 21;//func_2417, waits for NETWORK_IS_GAME_IN_PROGRESS
	const int SUBSTATE_LOAD_FREEMODE = 23;//func_2385, requests and launches the freemode script

	//once a temporary character's session is starting, logs the first tick of every script thread, to see what was running
	//when the game froze
	void logScriptStart(GtaThread* thread) {
		static unsigned int seen[128];
		static int seenCount = 0;
		if (Read_Global(G_TEMP_CHARACTER) != 1 || Read_Global(G_TRANSITION_SUBSTATE) < SUBSTATE_SESSION_STARTING)
			return;
		for (int i = 0; i < seenCount; i++)
			if (seen[i] == thread->nameHash)
				return;
		if (seenCount < 128)
			seen[seenCount++] = thread->nameHash;
		char name[sizeof(thread->threadName) + 1];
		memcpy(name, thread->threadName, sizeof(thread->threadName));
		name[sizeof(thread->threadName)] = 0;
		debugLog("[tempchar] script running: %s (0x%08X), sub-state %i\n", name, thread->nameHash, Read_Global(G_TRANSITION_SUBSTATE));
	}

	//logs every change of the transition state, plus a heartbeat every 5 seconds outside state 0, so a hang shows what
	//the transition is waiting on
	void logState() {
		static bool loggedStart = false;
		static int lastState = -1, lastSubstate = -1, lastReason = -1, lastCharStep = -1, lastSetup = -1, lastForce = -1, lastSessionType = -1;
		static int nextHeartbeat = 0;
		if (!loggedStart) {
			loggedStart = true;
			int sessionHooks = hookSessionNatives();
			debugLog("[tempchar] --- maintransition hook running, ARE_ANY_CCS_PENDING hooked %i, session natives hooked %i/%i ---\n",
				hookedCcsPending ? 1 : 0, sessionHooks, SESSION_NATIVE_COUNT);
		}
		int state = Read_Global(G_TRANSITION_STATE);
		int substate = Read_Global(G_TRANSITION_SUBSTATE);
		int reason = Read_Global(G_TRANSITION_REASON);
		int charStep = Read_Global(G_CHAR_CHANGE_STEP);
		int setup = Read_Global(G_ON_ENTER_MP_CALLED);
		int force = forceCcsIdle ? 1 : 0;
		int sessionType = Read_Global(G_SESSION_TYPE);
		int now = GAMEPLAY::GET_GAME_TIMER();
		bool changed = state != lastState || substate != lastSubstate || reason != lastReason || charStep != lastCharStep || setup != lastSetup ||
			force != lastForce || sessionType != lastSessionType;
		if (!changed && (state == 0 || now < nextHeartbeat))
			return;
		lastState = state;
		lastSubstate = substate;
		lastReason = reason;
		lastCharStep = charStep;
		lastSetup = setup;
		lastForce = force;
		lastSessionType = sessionType;
		nextHeartbeat = now + 5000;
		//third test froze in sub-state 23 (session started, freemode loading). From there on log globals only, so the log
		//itself can't be what hangs
		if (Read_Global(G_TEMP_CHARACTER) == 1 && substate >= SUBSTATE_LOAD_FREEMODE) {
			debugLog("[tempchar] %s t %i state %i sub %i reason %i (globals only from sub-state 23)\n", changed ? "change" : "beat", now,
				state, substate, reason);
			return;
		}
		debugLog("[tempchar] %s t %i state %i sub %i reason %i charstep %i cloud %i temp %i\n", changed ? "change" : "beat", now,
			state, substate, reason, charStep, (int)NETWORK::NETWORK_IS_CLOUD_AVAILABLE(), Read_Global(G_TEMP_CHARACTER));
		debugLog("[tempchar]   setup %i done %i newchar %i %i streamed %i ccspending %i force %i\n", setup, Read_Global(G_ENTER_MP_DONE),
			Read_Global(G_NEW_CHARACTER + 1 + 0), Read_Global(G_NEW_CHARACTER + 1 + 1), (int)haveAllStreamingRequestsCompleted(PLAYER::PLAYER_PED_ID()),
			invoke<int>(NATIVE_ARE_ANY_CCS_PENDING), force);
		debugLog("[tempchar]   net signed %i canenter %i ingame %i session %i insession %i busy %i\n",
			(int)NETWORK::NETWORK_IS_SIGNED_ONLINE(), (int)NETWORK::NETWORK_CAN_ENTER_MULTIPLAYER(), (int)NETWORK::NETWORK_IS_GAME_IN_PROGRESS(),
			(int)NETWORK::NETWORK_IS_SESSION_ACTIVE(), (int)NETWORK::NETWORK_IS_IN_SESSION(), (int)NETWORK::NETWORK_IS_SESSION_BUSY());
		int accessCode = -1;
		int canAccess = NETWORK::_0xA520B982((int)&accessCode);//NETWORK_CAN_ACCESS_MULTIPLAYER, code 11/12 = no cloud tunables/bg script
		debugLog("[tempchar]   sessiontype %i gamemode %i started %i invite %i launcher %i 2404086 %i access %i code %i patched %i\n", sessionType,
			Read_Global(G_GAMEMODE), (int)NETWORK::NETWORK_IS_SESSION_STARTED(), Read_Global(1315333), Read_Global(1312316), Read_Global(2404086),
			canAccess, accessCode, (*(volatile unsigned int*)ACCESS_CHECK_TUNABLES == CMPWI_R3_5 ? 1 : 0) + (*(volatile unsigned int*)ACCESS_CHECK_BG_SCRIPT == CMPWI_R3_5 ? 1 : 0));
		debugLog("[tempchar]   ros %i %i %i %i %i %i\n", (int)NETWORK::_0x97287D68(), (int)NETWORK::_0xBDBB5948(),
			(int)NETWORK::_0xD3BBE42F(), (int)DLC2::_0xF79A97F5(), (int)DLC2::_0xF69B729C(), (int)NETWORK::_0x3FB40673());
	}
#endif

	//called from runGtaThread_hook after every script thread tick
	void onThreadTick(GtaThread* thread) {
		if (addrstruct().nativeTable == 0)
			return;//natives are resolved through the table the server sends, not available before auth
#if TEMPCHAR_DEBUG == 1
		logScriptStart(thread);
#endif
		if (thread->nameHash != MAINTRANSITION_HASH)
			return;
		if (!triedHookCcsPending)
			hookAreAnyCcsPending();
#if TEMPCHAR_DEBUG == 1
		logState();
#endif
		if (Read_Global(G_TRANSITION_STATE) == STATE_CONNECTION_PROBLEM && isCloudFailure()) {
#if TEMPCHAR_DEBUG == 1
			debugLog("[tempchar] creating temporary character\n");
#endif
			create();
#if TEMPCHAR_DEBUG == 1
			debugLog("[tempchar] access checks 11/12 patched %i/2\n", allowSessionsWithoutCloud());
#endif
		}
		updateCcsWorkaround();
		updateSessionFallback();
	}

}
