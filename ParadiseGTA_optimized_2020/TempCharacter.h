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

	//1.12 maintransition func_186 (cloud branch) + func_189(1)
	void create() {
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

	void debugLog(const char *fmt, ...) {
		char buf[200];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, sizeof(buf), fmt, args);
		va_end(args);
		appendToFile(TEMPCHAR_LOG_FILE, buf, strlen(buf));
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

	opd_s originalAreAnyCcsPending;
	bool triedHookCcsPending = false;
	bool hookedCcsPending = false;
	bool forceCcsIdle = false;
	int ccsPendingSince = 0;

	void ARE_ANY_CCS_PENDING_hook(NativeArg_s* args) {
		((void(*)(NativeArg_s*))&originalAreAnyCcsPending)(args);
		if (forceCcsIdle && args != NativeArg)//only for script calls; Paradise's own invoke (NativeArg) still gets the real value
			*args->ReturnValue = 0;
	}

	//swaps the native's OPD contents, so scripts that already resolved the native go through the hook too
	void hookAreAnyCcsPending() {
		triedHookCcsPending = true;
		int opd = getOPDOfNative(NATIVE_ARE_ANY_CCS_PENDING);
		if (opd == -1)
			return;
		*(uint64_t*)&originalAreAnyCcsPending = *(uint64_t*)opd;
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

#if TEMPCHAR_DEBUG == 1
	const int G_CHAR_CHANGE_STEP = 1325170 + 600;//func_2445 step, the last step of the load-into-freemode sequence (func_2440)

	//logs every change of the transition state, plus a heartbeat every 5 seconds outside state 0, so a hang shows what
	//the transition is waiting on
	void logState() {
		static bool loggedStart = false;
		static int lastState = -1, lastSubstate = -1, lastReason = -1, lastCharStep = -1, lastSetup = -1, lastForce = -1;
		static int nextHeartbeat = 0;
		if (!loggedStart) {
			loggedStart = true;
			debugLog("[tempchar] --- maintransition hook running, ARE_ANY_CCS_PENDING hooked %i ---\n", hookedCcsPending ? 1 : 0);
		}
		int state = Read_Global(G_TRANSITION_STATE);
		int substate = Read_Global(G_TRANSITION_SUBSTATE);
		int reason = Read_Global(G_TRANSITION_REASON);
		int charStep = Read_Global(G_CHAR_CHANGE_STEP);
		int setup = Read_Global(G_ON_ENTER_MP_CALLED);
		int force = forceCcsIdle ? 1 : 0;
		int now = GAMEPLAY::GET_GAME_TIMER();
		bool changed = state != lastState || substate != lastSubstate || reason != lastReason || charStep != lastCharStep || setup != lastSetup || force != lastForce;
		if (!changed && (state == 0 || now < nextHeartbeat))
			return;
		lastState = state;
		lastSubstate = substate;
		lastReason = reason;
		lastCharStep = charStep;
		lastSetup = setup;
		lastForce = force;
		nextHeartbeat = now + 5000;
		debugLog("[tempchar] %s t %i state %i sub %i reason %i charstep %i cloud %i temp %i\n", changed ? "change" : "beat", now,
			state, substate, reason, charStep, (int)NETWORK::NETWORK_IS_CLOUD_AVAILABLE(), Read_Global(G_TEMP_CHARACTER));
		debugLog("[tempchar]   setup %i done %i newchar %i %i streamed %i ccspending %i force %i\n", setup, Read_Global(G_ENTER_MP_DONE),
			Read_Global(G_NEW_CHARACTER + 1 + 0), Read_Global(G_NEW_CHARACTER + 1 + 1), (int)haveAllStreamingRequestsCompleted(PLAYER::PLAYER_PED_ID()),
			invoke<int>(NATIVE_ARE_ANY_CCS_PENDING), force);
		debugLog("[tempchar]   net signed %i canenter %i ingame %i session %i insession %i busy %i\n",
			(int)NETWORK::NETWORK_IS_SIGNED_ONLINE(), (int)NETWORK::NETWORK_CAN_ENTER_MULTIPLAYER(), (int)NETWORK::NETWORK_IS_GAME_IN_PROGRESS(),
			(int)NETWORK::NETWORK_IS_SESSION_ACTIVE(), (int)NETWORK::NETWORK_IS_IN_SESSION(), (int)NETWORK::NETWORK_IS_SESSION_BUSY());
		debugLog("[tempchar]   ros %i %i %i %i %i %i\n", (int)NETWORK::_0x97287D68(), (int)NETWORK::_0xBDBB5948(),
			(int)NETWORK::_0xD3BBE42F(), (int)DLC2::_0xF79A97F5(), (int)DLC2::_0xF69B729C(), (int)NETWORK::_0x3FB40673());
	}
#endif

	//called from runGtaThread_hook after every script thread tick
	void onThreadTick(GtaThread* thread) {
		if (thread->nameHash != MAINTRANSITION_HASH)
			return;
		if (addrstruct().nativeTable == 0)
			return;//natives are resolved through the table the server sends, not available before auth
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
		}
		updateCcsWorkaround();
	}

}
