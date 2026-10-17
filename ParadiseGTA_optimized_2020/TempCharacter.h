//Temporary character mode (restored from 1.12)
//
//In 1.12, when the Rockstar cloud was unavailable, maintransition offered a temporary character that plays
//GTA Online over PSN only. 1.13+ turned that screen (transition state 21) into a "return to story mode" dead end
//and removed the setup function (1.12 maintransition func_186 / func_189), but 1.27 still honours every flag it
//set. Since the PS3 cloud is gone for good, this always does what 1.12 did: as soon as maintransition enters
//state 21 because of the cloud, set up the temporary character and continue the join (state 3, substate 4).
//1.27 also refuses every session without cloud tunables and the cloud background script, so the access check in
//the game code is patched too (allowSessionsWithoutCloud). Tested on a PS3: matchmakes into GTA Online. The
//character isn't saved, so every join makes a new one, same as 1.12.
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
	//debug log for testing on hardware. Written next to the other Paradise files, since a game can't create files in
	//the root of dev_hdd0. Fsynced so the last lines before a crash are on disk
	#define TEMPCHAR_LOG_FILE "/dev_hdd0/tmp/gopro_2027/tempchar_log.txt"

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

	//logs every change of the transition state. Only reads globals: a test build that also called network natives
	//here froze once while freemode was loading
	void logState() {
		static int lastState = -1, lastSubstate = -1, lastReason = -1;
		int state = Read_Global(G_TRANSITION_STATE);
		int substate = Read_Global(G_TRANSITION_SUBSTATE);
		int reason = Read_Global(G_TRANSITION_REASON);
		if (state == lastState && substate == lastSubstate && reason == lastReason)
			return;
		lastState = state;
		lastSubstate = substate;
		lastReason = reason;
		debugLog("[tempchar] state %i sub %i reason %i temp %i\n", state, substate, reason, Read_Global(G_TEMP_CHARACTER));
	}
#endif

	//called from runGtaThread_hook after every script thread tick
	void onThreadTick(GtaThread* thread) {
		if (thread->nameHash != MAINTRANSITION_HASH)
			return;
		if (addrstruct().nativeTable == 0)
			return;//natives are resolved through the table the server sends, not available before auth
#if TEMPCHAR_DEBUG == 1
		logState();
#endif
		if (Read_Global(G_TRANSITION_STATE) == STATE_CONNECTION_PROBLEM && isCloudFailure()) {
			create();
#if TEMPCHAR_DEBUG == 1
			debugLog("[tempchar] created temporary character, access checks patched %i/2\n", allowSessionsWithoutCloud());
#endif
		}
	}

}
