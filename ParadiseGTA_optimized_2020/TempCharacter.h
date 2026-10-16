//Temporary character mode (restored from 1.12), with local saves
//
//In 1.12, when the Rockstar cloud was unavailable, maintransition offered a temporary character that plays
//GTA Online over PSN only. 1.13+ turned that screen (transition state 21) into a "return to story mode" dead end
//and removed the setup function (1.12 maintransition func_186 / func_189), but 1.27 still honours every flag it
//set. Since the PS3 cloud is gone for good, this always does what 1.12 did: as soon as maintransition enters
//state 21 because of the cloud, set up the character and continue the join (state 3, substate 4).
//1.27 also refuses every session without cloud tunables and the cloud background script, so the access check in
//the game code is patched too (allowSessionsWithoutCloud). Tested on a PS3: matchmakes into GTA Online.
//
//MP stats are saved to files on the console instead of the cloud (LocalMpStats.h). The first join creates a new
//character as in 1.12, but without blocking saves, so the game saves it like a normal character. Every later join
//(also after a reboot) loads the saved slots instead and goes to character select with the saved character.
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
	const int G_SLOT_EXISTS = 1315392;//array of 3 by stat slot, func_244 / func_245 (1.12 Global_1344312)

	const int STATE_CONNECTION_PROBLEM = 21;
	const int STATE_IDLE = 15;//an empty case in maintransition's state switch, used to hold the transition while slots load
	const int STAT_SLOT_COUNT = 3;//slot 0 is shared (MPPLY), 1 and 2 are the characters. 1.12 had 6

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

	//flags both paths share: the transition treats this as a cloud-down session, which skips the cloud stat load and
	//the tunables / background script screens
	void setCloudDownSessionFlags() {
		allowSessionsWithoutCloud();
		resetConnectionWarnings();
		Write_Global(G_WARNING_ACCEPTED, 1);
		STATS::_0xCE7A2411(0);//don't block the stats save manager (it blocks loads and saves alike)
		Write_Global(G_SKIP_TUTORIAL, 1);
		Write_Global(G_TEMP_CHARACTER, 1);
		Write_Global(G_CLOUD_DOWN_SESSION, 1);
		Write_Global(G_TRANSITION_REASON, 0);
	}

	void continueJoin() {
		Write_Global(G_TRANSITION_SUBSTATE, 4);
		Write_Global(G_TRANSITION_STATE, 3);
	}

	//MP stat saves only run while a session is running (0xCE7A2411 blocks the stats save manager otherwise):
	//- Character select (maintransition func_1077, state 4) quits to story mode when the cloud is down and an MP stats
	//  save is pending (0xA3407CA3, any slot queued), and the join itself queues one (second local-save test: state 22 /
	//  sub-state 58 right after the setup). So saves are blocked from the setup until the session runs.
	//- Back in story mode the transition resets the MP stats to defaults, and the game then saved those over the real
	//  character (fourth test: char0001 26773 bytes at the quit, 26573 bytes of defaults after it, "character exists"
	//  stat 0 on the next load). So saves are blocked again as soon as the temp flag is gone.
	//The quit's own saves (sub-states 58-63) still run: the temp flag is only cleared after them.
	bool savesBlocked = false;

	void blockSaves() {
		STATS::_0x395D18B1(-1);//STAT_CLEAR_PENDING_SAVES
		STATS::_0xCE7A2411(1);
		savesBlocked = true;
	}

	void blockSavesForJoin() {
		blockSaves();
	}

	void updateSaveBlock() {
		bool inTempSession = Read_Global(G_TEMP_CHARACTER) == 1;
		LocalMpStats::savesAllowed = inTempSession;
		if (!inTempSession) {
			if (!savesBlocked) {
				blockSaves();
#if TEMPCHAR_DEBUG == 1
				tempcharLog("[tempchar] MP stats saves blocked (not in a session)\n");
#endif
			}
			return;
		}
		if (!savesBlocked || !NETWORK::NETWORK_IS_GAME_IN_PROGRESS())
			return;
		STATS::_0xCE7A2411(0);
		savesBlocked = false;
#if TEMPCHAR_DEBUG == 1
		tempcharLog("[tempchar] MP stats saves unblocked (session running)\n");
#endif
	}

	//no saved character: 1.12 maintransition func_186 (cloud branch) + func_189(1), a new character in empty slots.
	//The game then saves it through the local MP stats files
	void create() {
		setCloudDownSessionFlags();
		STATS::_0x395D18B1(-1);//STAT_CLEAR_PENDING_SAVES
		for (int slot = 0; slot < STAT_SLOT_COUNT; slot++)
			STATS::STAT_DELETE_SLOT(slot);
		for (int i = 0; i <= 6; i++)
			STATS::_0xE3247582(i);//local reset of the online character stats, same range 1.27 func_2577 uses
		//stats save manager (0x1DDDAC8) +0x58: slots waiting for a (re)load, +0x64: slots whose load failed. Saving
		//refuses a slot with either bit set, and a wiped slot is loaded (empty), so clear them or the new character
		//never gets saved
		*(volatile unsigned int*)(0x1DDDAC8 + 0x58) &= ~7u;
		*(volatile unsigned int*)(0x1DDDAC8 + 0x64) &= ~7u;
		for (int slot = 0; slot < STAT_SLOT_COUNT; slot++)
			Write_Global(G_SLOT_LOADED + 1 + slot, 1);
		Write_Global(G_SLOT_EXISTS + 1 + 0, 1);
		blockSavesForJoin();
		continueJoin();
		print2("~b~Rockstar cloud unavailable: creating a new character, saved on this console", 8000);
	}

	//saved character: load every slot that has a file (STAT_CLEAR_SLOT_FOR_RELOAD + STAT_LOAD, served by
	//LocalMpStats::localCloudGet) while the transition waits in STATE_IDLE, then continue to character select
	const int LOAD_TIMEOUT_MS = 30000;
	enum LoadStep { LOAD_NONE, LOAD_START_SLOT, LOAD_WAIT_SLOT, LOAD_DONE };
	LoadStep loadStep = LOAD_NONE;
	int loadSlot = 0;
	int loadStarted = 0;
	int servedLoadsBefore = 0;
	int loadWaitTicks = 0;
	const int LOAD_WAIT_TICKS = 120;//maintransition ticks to wait for a load that hasn't started yet
	bool slotLoaded[STAT_SLOT_COUNT];

	//Character c (0 or 1, stat slot c + 1) exists when its packed bool stat 76 is set: maintransition func_603(c) =
	//func_347(76, c), which reads the hash from Global_2427264[76 <3>][c]
	const int G_PACKED_BOOL_STAT_HASHES = 2427264;
	const int CHARACTER_EXISTS_STAT = 76;

	//1 exists, 0 doesn't, -1 unknown (hash table not filled in or stat unreadable: then a loaded slot counts as a
	//character, so a real save is never thrown away)
	int characterExists(int character) {
		int hash = Read_Global(G_PACKED_BOOL_STAT_HASHES + 1 + CHARACTER_EXISTS_STAT * 3 + 1 + character);
		if (hash == 0)
			return -1;
		int value = 0;
		if (!STATS::STAT_GET_BOOL(hash, &value, -1))
			return -1;
		return value != 0 ? 1 : 0;
	}

	//the character the game plays (MPPLY_LAST_MP_CHAR, EBOOT 0x326880, the one STAT_SAVE itself checks)
	int currentCharacter() {
		return call<int>(0x326880)();
	}

	//STAT_LOAD(slot) records the slot to load in the stats save manager's +0x5C, but only for slots 1 and 2: slot 0 loads
	//whatever +0x5C still holds. It also returns 1 without loading when the slot isn't marked for reload, and loading
	//slot 0 clears the marks of all slots (third local-save test: the characters "loaded" with no file read). So each
	//slot is marked right before its own load
	const unsigned int STATS_SAVE_MANAGER = 0x1DDDAC8;

	bool hasSavedCharacter() {
		return LocalMpStats::hasSlotSave(1) || LocalMpStats::hasSlotSave(2);
	}

	void startLoadingSaved() {
		setCloudDownSessionFlags();
		Write_Global(G_TRANSITION_STATE, STATE_IDLE);
		for (int slot = 0; slot < STAT_SLOT_COUNT; slot++)
			slotLoaded[slot] = false;
		loadSlot = 0;
		loadStarted = GAMEPLAY::GET_GAME_TIMER();
		loadStep = LOAD_START_SLOT;
		print2("~b~Rockstar cloud unavailable: loading your character from this console", 8000);
	}

	void finishLoadingSaved() {
		loadStep = LOAD_NONE;
		//a loaded slot only holds a character when that character's "exists" stat is set (an empty slot can get saved too)
		bool exists[STAT_SLOT_COUNT];
		exists[0] = slotLoaded[0];
		int existsStat[STAT_SLOT_COUNT] = {1, -1, -1};
		for (int slot = 1; slot < STAT_SLOT_COUNT; slot++) {
			existsStat[slot] = characterExists(slot - 1);
			exists[slot] = slotLoaded[slot] && existsStat[slot] != 0;
		}
		bool anyCharacter = slotLoaded[0] && (exists[1] || exists[2]);
#if TEMPCHAR_DEBUG == 1
		tempcharLog("[tempchar] slots loaded %i %i %i, character exists stat %i %i\n", slotLoaded[0] ? 1 : 0, slotLoaded[1] ? 1 : 0,
			slotLoaded[2] ? 1 : 0, existsStat[1], existsStat[2]);
#endif
		if (!anyCharacter) {
			//the saves didn't load, start over with a new character rather than getting stuck
			print2("~r~Couldn't load your saved character, creating a new one", 8000);
			create();
			return;
		}
		for (int slot = 0; slot < STAT_SLOT_COUNT; slot++) {
			Write_Global(G_SLOT_LOADED + 1 + slot, 1);//empty slots count as loaded too, like create()
			Write_Global(G_SLOT_EXISTS + 1 + slot, exists[slot] ? 1 : 0);
		}
		blockSavesForJoin();
		continueJoin();
	}

	void updateLoadingSaved() {
		if (loadStep == LOAD_NONE)
			return;
		Write_Global(G_TRANSITION_STATE, STATE_IDLE);//keep the transition waiting
		if (GAMEPLAY::GET_GAME_TIMER() - loadStarted > LOAD_TIMEOUT_MS) {
#if TEMPCHAR_DEBUG == 1
			tempcharLog("[tempchar] slot load timed out at slot %i\n", loadSlot);
#endif
			finishLoadingSaved();
			return;
		}
		if (loadStep == LOAD_START_SLOT) {
			while (loadSlot < STAT_SLOT_COUNT && !LocalMpStats::hasSlotSave(loadSlot))
				loadSlot++;
			if (loadSlot >= STAT_SLOT_COUNT) {
				finishLoadingSaved();
				return;
			}
			if (STATS::STAT_LOAD_PENDING(-1))
				return;
			STATS::_0x84BDD475(loadSlot);//STAT_CLEAR_SLOT_FOR_RELOAD
			if (loadSlot == 0)
				*(volatile int*)(STATS_SAVE_MANAGER + 0x5C) = 0;
			servedLoadsBefore = LocalMpStats::servedLoads;
			if (STATS::STAT_LOAD(loadSlot)) {
#if TEMPCHAR_DEBUG == 1
				tempcharLog("[tempchar] STAT_LOAD(%i) started\n", loadSlot);
#endif
				loadWaitTicks = 0;
				loadStep = LOAD_WAIT_SLOT;
			}
			return;
		}
		if (loadStep == LOAD_WAIT_SLOT) {
			if (STATS::STAT_LOAD_PENDING(-1))
				return;
			bool served = LocalMpStats::servedLoads > servedLoadsBefore;
			//the load op runs from the savegame queue, so the load may not be pending yet right after STAT_LOAD
			if (!served && ++loadWaitTicks < LOAD_WAIT_TICKS)
				return;
			slotLoaded[loadSlot] = served && STATS::_0x7A299C13(loadSlot) && !STATS::_0x0BF0F4B2(loadSlot);//STAT_SLOT_IS_LOADED, !STAT_CLOUD_SLOT_LOAD_FAILED
#if TEMPCHAR_DEBUG == 1
			tempcharLog("[tempchar] slot %i served %i loaded %i failed %i code %i\n", loadSlot, served ? 1 : 0,
				(int)STATS::_0x7A299C13(loadSlot), (int)STATS::_0x0BF0F4B2(loadSlot), (int)STATS::_0xCE6B62B5(loadSlot));
#endif
			loadSlot++;
			loadStep = LOAD_START_SLOT;
		}
	}

	//The game queues MP stat saves itself (scripts, timers in the stats save manager). On top of that, save every
	//loaded slot every SAVE_INTERVAL_MS while in a session, so progress is on disk even if the game never asks.
	const int FIRST_SAVE_AFTER_MS = 120000;
	const int SAVE_INTERVAL_MS = 300000;
	const int SAVE_REASON = 3;//same reason ingamehud/maintransition pass most often
	int nextSave = 0;

	void updatePeriodicSave() {
		if (Read_Global(G_TEMP_CHARACTER) != 1 || !NETWORK::NETWORK_IS_GAME_IN_PROGRESS()) {
			nextSave = 0;
			return;
		}
		int now = GAMEPLAY::GET_GAME_TIMER();
		if (nextSave == 0) {
			nextSave = now + FIRST_SAVE_AFTER_MS;
			return;
		}
		if (now < nextSave)
			return;
		nextSave = now + SAVE_INTERVAL_MS;
		if (STATS::STAT_SAVE_PENDING())
			return;
#if TEMPCHAR_DEBUG == 1
		LocalMpStats::logSaveGates();
#endif
		int current = currentCharacter();
		for (int slot = 0; slot < STAT_SLOT_COUNT; slot++) {
			if (!STATS::_0x7A299C13(slot))
				continue;
			//slot 0 always; a character slot only if it's played or exists, so an empty slot never gets a save file
			//(it would show up as a second character)
			if (slot != 0 && slot != current + 1 && characterExists(slot - 1) != 1)
				continue;
			int queued = STATS::STAT_SAVE(slot, 0, SAVE_REASON);
			(void)queued;
#if TEMPCHAR_DEBUG == 1
			tempcharLog("[tempchar] STAT_SAVE(%i) queued %i\n", slot, queued);
#endif
		}
	}

#if TEMPCHAR_DEBUG == 1
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
		tempcharLog("[tempchar] state %i sub %i reason %i temp %i\n", state, substate, reason, Read_Global(G_TEMP_CHARACTER));
	}
#endif

	//called from runGtaThread_hook after every script thread tick
	void onThreadTick(GtaThread* thread) {
		if (thread->nameHash != MAINTRANSITION_HASH)
			return;
		if (addrstruct().nativeTable == 0)
			return;//natives are resolved through the table the server sends, not available before auth
		if (!LocalMpStats::installed) {
			int patched = LocalMpStats::install();
#if TEMPCHAR_DEBUG == 1
			tempcharLog("[mpstats] local saves installed, checks patched %i/%i, character saves %i %i\n", patched,
				LocalMpStats::PATCH_SITE_COUNT, LocalMpStats::hasSlotSave(1) ? 1 : 0, LocalMpStats::hasSlotSave(2) ? 1 : 0);
#endif
		}
#if TEMPCHAR_DEBUG == 1
		logState();
		LocalMpStats::logManagerState();
#endif
		if (loadStep != LOAD_NONE) {
			updateLoadingSaved();
		} else if (Read_Global(G_TRANSITION_STATE) == STATE_CONNECTION_PROBLEM && isCloudFailure()) {
			if (hasSavedCharacter()) {
#if TEMPCHAR_DEBUG == 1
				tempcharLog("[tempchar] loading saved character\n");
#endif
				startLoadingSaved();
			} else {
				create();
#if TEMPCHAR_DEBUG == 1
				tempcharLog("[tempchar] created new character, access checks patched %i/2\n", allowSessionsWithoutCloud());
#endif
			}
		}
		updateSaveBlock();
		updatePeriodicSave();
	}

}
