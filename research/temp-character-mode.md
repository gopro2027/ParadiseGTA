# Temporary character mode (1.12) vs 1.27: script research

Goal: bring back the 1.12 "Rockstar cloud is down, create a temporary character and play over PSN" option in 1.27, from Paradise SPRX.

Sources compared:
- 1.12: `D:\win\Laptop C Drive Transer 5-14-2024\Documents\gta1.12\dev\libertyv\scripts_decompiled\*.csc.c`
- 1.27: `D:\win\Laptop C Drive Transer 5-14-2024\Documents\scriptsWglobals\*.c` (global numbers match the ones the SPRX already uses, e.g. 1312623, 1581767, 2390201)

Line numbers below are from those files.

## Summary

- The feature lives in `maintransition`, not in `freemode`. `freemode` only reads the flags it sets.
- Comparing string literals, the only labels that 1.12 has and 1.27 lacks in `maintransition` are `TEMP_CHARACTER`, `HUD_AUSVDIS`, `HUD_CONTSURE`, `TRAN_CLOUDDWN` and `CONT_CLOUDFAIL`. In `ingamehud` the only one is `BAIL_CLOUDDN`. Those labels are the temporary-character screens.
- **Rockstar removed only the entry point.** In 1.13+ the cloud-failure screen became a "return to story mode" dead end, and the function that set up the temporary character was deleted. All the downstream support is still in 1.27:
  - the global flags,
  - the stat-load bypass,
  - the "cloud came back" handler,
  - the tunables and background-script gates (they are skipped while the temp flag is set),
  - the freemode tutorial bypass.
- So re-enabling it in 1.27 comes down to doing what the deleted function did: a handful of global writes and stat natives, then sending the transition to the state it used to continue into. No bytecode patch is needed.
- The big unknown can't be answered from scripts: whether the 1.27 **executable** still lets a session start without ROS. The scripts are only the front door.

## How 1.12 did it

### Entry point 1: cloud unavailable when joining Online (transition state 21)

The `maintransition` state machine switches on `Global_1344033` (1.27: `Global_1315298`, set by `func_2246` / 1.27 `func_2706`). A second global, `Global_1344034` (1.27 `Global_1315299`, set by `func_2254` / 1.27 `func_2714`), is the sub-state or return code.

The pre-join check sends you to state 21 when any connectivity check fails (1.12 `maintransition.csc.c:137434`, `:134899`; 1.27 `maintransition.c:176116`, `:159309`):

```c
if (func_2130() == 0)          // Global_1344091: "already accepted the warning" (1.27 Global_1315353)
    if (cloud == 0 || friends/PSN == 0 || ...)
        { func_2254(5); func_2246(21); func_192(1); }
```

State 21 calls `func_182` → `func_183` (1.12 :4287). On its first frame it fills `f_1315[0..5]`:
- `[0]` cloud down (`func_2287()==0`, which is `!offline_content && NETWORK_IS_CLOUD_AVAILABLE`)
- `[1]` friends
- `[2]` ROS/NP
- `[3]` personal
- `[4]` disconnected
- `[5]` chat restriction

`func_184` (:4356) draws one of 3 sub-screens selected by `f_1314`. `func_185` (:4412) handles input:

| `f_1314` | Screen | Accept | Back |
|---|---|---|---|
| 0 | `HUD_CONNPROB` / `CONT_CLOUDFAIL` (cloud) or `CONT_FRIEN`/`CONT_ROCK`/... | cloud: go to 1. Otherwise `func_186` (continue) | quit (`func_2246(0)`, `func_2254(63)`) |
| 1 | `HUD_DELETEQUE` / `HUD_AUSVDIS` (autosave disabled) | go to 2 | back to 0 |
| 2 | `HUD_DELETEQUE` / `TEMP_CHARACTER` | `func_186` | back to 0 |

`func_186` (:4460) is the core:

```c
func_193();                // zero the Global_1373966.. block (1.27 func_202 / Global_1330639..)
func_192(1);               // Global_1344091 = 1      (1.27 Global_1315353)
if (f_1315[0]) {           // cloud down → temporary character
    func_189(1);
    func_188();            // Global_1332465 = 1      (1.27 Global_1312399)
    func_52(1);            // Global_1344092 = 1      (1.27 Global_1315354)
} else
    func_187(1);           // Global_1344093 = 1      (1.27 Global_1315355)
if (_0xD87F3A9E())         // always 0 on PS3
    { func_2246(31); func_2254(1); }
else
    { func_2246(3); func_2254(4); }   // continue into the normal join
```

`func_189(iParam0)` (:4498) wipes the stats so a new character starts:

```c
_0xCE7A2411(1);            // most likely STAT_SET_BLOCK_SAVES(true)  ("autosave disabled")
_0x395D18B1(-1);           // STAT_CLEAR_PENDING_SAVES
stat_delete_slot(0..5);    // 1.12 has 6 slots; 1.27 has 3 (0..2)
_0xE3247582(0..7);         // STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS (your annotation)
func_188();                // Global_1332465 = 1
func_191();                // Global_1332383[0..5] = 1   "slot loaded" flags (1.27 Global_1312341[0..2])
func_50(1);                // Global_1344090 = 1   THE temp-character flag (1.27 Global_1315352)
func_190(0, 1);            // Global_1344312[0] = 1  slot-exists flags (1.27 Global_1315392[0])
if (iParam0 == 0) { func_2254(4); func_2246(3); }
```

### Entry point 2: stats failed to load (transition state 24)

1.12 `func_252`/`func_253`/`func_254` (:6185–6330) is the `HUD_STATFAIL` / `HUD_STATCORR` screen. In 1.12 it had two extra sub-screens: `f_1314` 3 = `HUD_AUSVDIS` and 4 = `TEMP_CHARACTER`. Accept on 4 calls `func_189(0)` (wipe, then state 3/4). This path does **not** set `Global_1344092` (the cloud-down flag), only the temp flag.

1.27 `func_263`–`func_265` (:6699–6849) kept sub-states 0–2 (retry, quit, wipe-corrupt) and dropped 3 and 4.

### Entry point 3 (UI only): invites while the cloud is down

When an invite arrives with the cloud down, `main_persistent` and `maintransition` set `ingamehud` warning bit 6 (`func_752(6,1,-1)`, 1.12 `main_persistent.csc.c:44266`). In 1.12 `ingamehud` shows `BAIL_CLOUDDN`, the screen that says you need a temporary character. 1.27 still sets bit 6 but shows `HUD_STATFAIL`. The invite is cancelled in both versions; only the text changed.

## What 1.27 kept (why this is feasible)

| Thing | 1.12 | 1.27 | Status in 1.27 |
|---|---|---|---|
| Temp-character flag | `Global_1344090` (`func_50`/`func_180`) | `Global_1315352` (`func_54`/`func_194`) | Used in 80 scripts. Still skips stat load, tunables and background gates |
| Cloud-down session flag | `Global_1344092` (`func_52`/`func_46`) | `Global_1315354` (`func_56`/`func_50`) | Watcher `func_36` (:1940) won't kick you while set. Freemode/fmmc use it to pick offline UGC data |
| Skip-tutorial flag | `Global_1332465` | `Global_1312399` | freemode `func_401/410` (:14733, :14816) return "tutorial done" if set (same as 1.12 `func_389/396/397`) |
| Slot-loaded flags | `Global_1332383[0..5]` | `Global_1312341[0..2]` | Same use |
| Slot-exists flags | `Global_1344312[0..5]` | `Global_1315392[0..2]` | Same use |
| Warning-accepted flag | `Global_1344091` | `Global_1315353` | Still set when entering state 21 |
| Stat-load skip | `if (!NETWORK_IS_CLOUD_AVAILABLE() \|\| func_180())` (:135937) | same with `func_194()` (:161003) | Kept |
| `TRAN_CLOUDUP` "cloud is back, retry stats?" | `func_33`/`func_53` | `func_36`/`func_58` | Kept, but 1.27 forces a stat reload |
| `HUD_NOTUNE` / `HUD_NOBACKGRN` gates (state 36) | n/a | wrapped in `if (func_194() == 0)` (:175800, :177131) | Skipped for a temp char |
| Continue after a connection warning | `func_2246(3); func_2254(4)` | `func_2736(0); func_2706(3); func_2714(4)` (in `func_200`) | Still used for the non-cloud warnings |

### Exactly what 1.13+ removed (1.27 `maintransition.c:4910–5093`)

- `func_198` (draw): for `f_1419[0]` it now shows `HUD_CLOUDOFFLIN` with a single `HUD_SPRETURNTRY` button (flag 16384) instead of `CONT_CLOUDFAIL` with confirm.
- `func_199` (input): the `f_1418` 1/2 sub-states (`HUD_AUSVDIS`, `TEMP_CHARACTER`) are gone. Accept now always runs `func_200`, and back is ignored on a cloud failure.
- `func_200` still has the `if (f_1419[0]) { }` branch, but it's **empty**: the `func_189(1); func_188(); func_52(1);` calls were cut out. On a cloud failure it now quits to story mode (`func_51(-1)`, state 32, `"HUD_QUITTING"`, sub 58).
- The `func_189` equivalent no longer exists in 1.27. The closest relative is `func_2577` (:176584), the normal "reset stats and reload from cloud" routine, which only runs when the cloud **is** available.

## Things in 1.27 that could still block a temp character

These are in the `func_2605` watchdog (:177499) or the pre-join path. A temp character has to get past each of them on a real PS3 today:

1. **ROS privilege/ban checks → state 33 (`func_148`, `HUD_ROSBANNED`/`HUD_SCSBANNED`)** (:177540). They use `0x97287D68` (can play online), `0xBDBB5948` (SC banned), `0xD3BBE42F` (R* banned). They are **not** gated by the temp flag, only by `func_2607()` (`Global_1315326` reason code). The same checks exist in 1.12 (`_can_play_online`, `_is_socialclub_banned`, `_is_rockstar_banned`, 1.12 :138640), and temp characters worked there, so with no ROS ticket they presumably report "not banned". **Needs checking on hardware:** call the three natives and see what they return now.
2. **`0xF79A97F5() == 0` → state 8, reason 12**: present in both versions.
3. **New in 1.27:**
   - `0xF79A97F5 && 0xF69B729C → state 34` (:176124). State 34 shows `HUD_NOTUNE`, `HUD_NOBACKGRN`, `HUD_BADORDER` and `HUD_STATDIRTY3`.
   - `0x47978D7F()==0 && 0x20AB933A()==0` plus `0xA520B982` result 11/12 → state 28, reason 15.
4. **`DLC_CHECK_CLOUD_DATA_CORRECT` → state 10**: only checked when the cloud is available, so it doesn't matter here.
5. **The executable.** None of this proves the 1.27 exe still matchmakes or hosts with only NP. The 1.12 temp mode proves the engine could; 1.13 may have changed code paths too. This is the biggest risk and only a real test answers it.

## Implementation status

Implemented in `ParadiseGTA_optimized_2020/TempCharacter.h`, untested on hardware.
- **Mode:** fully automatic. There is no prompt: when the cloud is down, state 21 goes straight into the temporary character.
- **Where it runs:** from `runGtaThread_hook`.
- **Differences from the sketch below:**
  - `_0xE3247582` is called for 0..6, the range 1.27 uses itself.
  - The `Global_2428598` part of `func_202` is skipped.
  - The continue path ends with a native the decompilers call `get_broadcast_finished_los_sound(0)`. It isn't called, because its hash is unknown.

### First hardware test

- **Reaching state 21 worked.** The join goes 0 → 3/4 → **21/5** (cloud down; ROS checks `1 1 0 1 0 0`, so no ban screen) → create → 3/4 → 4/5 (character select: slots labelled `HUD_TEMP`) → 5 → 6 → 32/17 → **32/18**. It then hung there for over a minute with the "Loading GTA Online" spinner.
- **Network flags during the hang:** `NETWORK_CAN_ENTER_MULTIPLAYER` was 1, and no session existed yet.
- **The tutorial-skip prompt** (`HUD_NOTUT`, step 3 of `func_2440`) is the same in 1.12. That load sequence finished: `Global_1325170.imm_600` went to 99.
- **Sub-state 18 is `func_2428` (1.27 `maintransition.c:160394`).** It waits for `Global_1312437.imm_6[slot] || func_1(...)`. Then, new in 1.27, it waits for `func_893`: that calls `ON_ENTER_MP` (`0xC65586A9`) once (`Global_2403951 = 1`), then waits for `HAVE_ALL_STREAMING_REQUESTS_COMPLETED(PLAYER_PED_ID())` (`0xF9FB4B71`) and `ARE_ANY_CCS_PENDING` (`0x0AF83036`) to be false. 1.12 calls `func_2407`/`func_2066(-1)` straight away. Neither native appears in 1.12 or anywhere else in 1.27.
- **Next build:**
  - logs those values on every heartbeat;
  - OPD-hooks `ARE_ANY_CCS_PENDING` so scripts see 0, but only for a temp character in sub-state 18, after 10 s busy, and once the ped has streamed.
- **Script locals:** reading `Local_152.imm_1357` as local index 1509 always gave 0. So locals can't be addressed as `152 + imm` this way; use globals.

### Second hardware test

- **The CCS wait wasn't the blocker.** `ON_ENTER_MP` ran during state 5, `ARE_ANY_CCS_PENDING` was briefly 1, then the changesets finished on their own (`done 1`). The hook never had to force it.
- **Sub-state 18 still hung,** with every `func_893` input satisfied: `newchar` slot 0 = 1, streamed, nothing pending. No session was active, starting or busy.
- **Once its waits pass, sub-state 18 calls `func_2407` (1.27 `maintransition.c:159695`).** That function starts the session. It moves on to sub-state 21 only when the session native returns true; otherwise it retries every frame. Which native depends on the session type `Global_1315323`:
  - 0 (default): `NETWORK_SESSION_ENTER` (matchmake)
  - 1 / 11: `NETWORK_SESSION_HOST(gamemode, 18, 0/1)`
  - 10: `NETWORK_SESSION_HOST(gamemode, 1, 1)`
  - 6: `NETWORK_SESSION_HOST_FRIENDS_ONLY`
  - 2–5 and 8: `NETWORK_SESSION_HOST_CLOSED` (`0x8AC9EA19`)
  - 9: `NETWORK_SESSION_FRIEND_MATCHMAKING` (`0x4E53202A`)
  - 12: `NETWORK_SESSION_CREW_MATCHMAKING` (`0xD7624E6B`)
  - `Global_1312316` set: `NETWORK_SESSION_ACTIVITY_QUICKMATCH` (`0x3F75CC38`)
- **This code is unchanged since 1.12** (1.12 `func_2066`, `maintransition.csc.c:135012`). If the native keeps failing, the block is in the 1.27 executable, not the scripts.
- **Next build:**
  - Debug only: OPD-hooks all seven session natives and logs the results of maintransition's calls, plus session type, gamemode and invite flags.
  - Fallback for a temp character, always on: after 15 s in sub-state 18 with session type 0 and no session, set the type to 1 so the script hosts its own public session.

### Executable: why every session native fails (1.27 vs 1.12)

Sources: 1.27 `Documents\IDA\PS3\1.27\EBOOT.ELF` with `EBOOT.map` (IDA names), and 1.12 `gta1.12\dev\EBOOT.elf`. Decompiled with Ghidra 12 headless (`PowerPC:BE:64:64-32addr`, no auto-analysis, r2 set to the TOC: 1.27 `0x1C85330`, 1.12 `0x1BC3088`).

- **Both natives share a gate.** `NETWORK_SESSION_ENTER` (`0x3E3E08`) and `NETWORK_SESSION_HOST` (`0x3E3FBC`) both return 0 unless `0x3E3D04` passes. That gate is `0x1389D98(netSession, &code)` && `0x139C8F4` (the internals of `NETWORK_CAN_ENTER_MULTIPLAYER`). The session methods themselves call `0x1389D98` again: host `0x1389F84`, matchmake `importantFindLobbyFunc` `0x138ADD4` → `0x138A770`.
- **`0x1389D98` is the multiplayer access check.** It's the function behind `NETWORK_CAN_ACCESS_MULTIPLAYER` (script `0xA520B982`), and it writes a reason code:

  | Code | Check |
  |---|---|
  | 6 | `0x12F699C` |
  | 7 | `amISignedIn(1)` |
  | 8 | `NETWORK_HAVE_ONLINE_PRIVILEGES` |
  | 9 | `onlineRockstarPermissions` / `getPrivilege(…, 3)` / `getCertificateData(3)` |
  | 4 | profile not loaded |
  | 5 | stat `0x387` (prologue; Paradise already patches `0x1389EA4`) |
  | 10 | a tunable bool `0x0B5EE873` / `0x3C0AF527` is set (only checked if tunables are loaded) |
  | **11** | **`CTunables` (`0x1CFB0B8`) `+0x4D == 0`: tunables not downloaded** |
  | **12** | **`bgScriptData` (`0x1CFB100`) `+0x1019 == 0`: background script not loaded** |
  | 0 | OK |

- **1.12's version (`0x1304110`)** has 6/7/8/9/4/5 and a different 10, and no 11 or 12. So 1.12 could start sessions without the cloud and 1.27 can't. The scripts' own `HUD_NOTUNE` / `HUD_NOBACKGRN` screens are skipped for a temp character, but the executable added the same requirement inside the session gate.
- **Fix in `TempCharacter.h` (`allowSessionsWithoutCloud`, run from `create()`):** the same trick as Paradise's `0x387` bypass. Change the `cmpwi r3,0` at `0x1389F20` (code 11) and `0x1389F48` (code 12) to `cmpwi r3,5` (write byte `+3` = 5), so the `bne` past each failure is always taken. It only patches if the original instruction is there. This also fixes the script-side checks that treat codes 11/12 as a failure: the invite cancel in `main_persistent` and the state-28 watchdog in `func_2605`.
- **Debug log:** shows `NETWORK_CAN_ACCESS_MULTIPLAYER`'s result and code, and whether both checks are patched.

### Third hardware test (access patch)

- **The access patch worked.** `NETWORK_CAN_ACCESS_MULTIPLAYER` code went 11 → 0 after the patch (2/2 checks). `NETWORK_SESSION_ENTER(1, ...)` returned 1 on its first call, and sub-state 18 → 21.
- **Sub-state 21 (`func_2417`)** waits for `NETWORK_IS_GAME_IN_PROGRESS` + `func_2366`. During it, `session 1 busy 1` and `canenter 0`. About 12 s later it went to sub-state 23.
- **Sub-state 23 (`func_2385`)** requests the `freemode` script and launches it (→ 25). The game froze there (picture stuck, needed a hard restart). On PS3 a real crash looks like this too (it doesn't return to the XMB), and the owner thinks it was a crash, i.e. a bad instruction or bad memory access, not a hang. No debugger attached. The log stopped in the middle of a heartbeat, but `appendToFile` didn't fsync, so that doesn't pin the spot.
- **Background-script references in the 1.27 executable (23 total):** the network ones are
  - `0x139AEC4`: auto-matchmake guarded by tunables `+0x4C` / bg loaded;
  - `0x12F57F0` and `0x12E46C4`: write `bgScriptData +0x1028`.

  None is an obvious crash with an unloaded but allocated `bgScriptData`.
- **Next build:**
  - fsyncs every log line;
  - logs the first tick of every script thread once the session is starting;
  - from sub-state 23 on, the heartbeat only reads globals, so the logging can't be what hangs;
  - the session-native hook now checks that a current script thread exists.

## How to re-enable it from the SPRX (recommended: drive the state machine)

No script edits: replay the deleted `func_186`/`func_189` from the menu thread, using the global helpers the SPRX already has (`Read_Global`/`Write_Global` in `GlobalStuff.h`, against 1.27 numbering).

Trigger: `maintransition` is running, `Read_Global(1315298) == 21`, and `NETWORK_IS_CLOUD_AVAILABLE()` (0xC7FF5AFC) is false. Do it before the player presses accept, because accept on that screen quits to story mode.

Sequence (1.27 numbers):

```
0xCE7A2411(1)                  // block saves
0x395D18B1(-1)                 // STAT_CLEAR_PENDING_SAVES
STAT_DELETE_SLOT(0), (1), (2)
0xE3247582(0..7)               // local reset of online character stats (1.12 used 0..7; 1.27's own wipe uses 0..6)
Global_1330639.. block = 0     // what func_202 zeroes (optional: func_200 does it in 1.27 anyway)
Global_1312399 = 1             // skip tutorial
Global_1312341[0..2] = 1       // slots "loaded"
Global_1315352 = 1             // TEMP CHARACTER
Global_1315392[0] = 1
Global_1315354 = 1             // cloud-down session
Global_1315353 = 1
Global_1315326 = 0             // func_2736(0), like the non-cloud continue path
Global_1315299 = 4             // sub-state
Global_1315298 = 3             // continue the join
```

Prompt options:
- **Simplest:** a menu toggle ("Temporary character when R* cloud is down") that runs the sequence automatically, plus a notification.
- **Closer to 1.12:** park the transition in state 15, which is an empty `case 15: break;` in both versions. Draw your own `SET_WARNING_MESSAGE` with `HUD_AUSVDIS` / `TEMP_CHARACTER`, falling back to your own strings if `DOES_TEXT_LABEL_EXIST` says the 1.27 text tables dropped them. Then either run the sequence or quit with `Global_19940 = -1`, state 32, `"HUD_QUITTING"` into `Global_1315300`, sub 58. Untested: confirm nothing else advances the machine while it's in 15.

### Alternatives considered

- **Hook `NETWORK_IS_CLOUD_AVAILABLE` to return true:** the game would then try to load stats from the dead cloud and end up on the stat-fail screen (state 24), which in 1.27 only offers retry or quit. Not useful alone.
- **Patch `maintransition` bytecode in memory, or ship a patched `maintransition.ysc` in `script_vary.rpf`:** `func_200`'s empty branch has no room for the calls, so this needs a code cave or a recompiled script. That's much more work and fragile, for the same result as the global writes.
- **Restore the state-24 (stat fail) entry:** only matters if the cloud is up but stats fail. Since the PS3 cloud is gone for good, state 21 is the path that matters.

## Suggested next steps

1. **Probe on hardware first:** add a debug overlay that prints:
   - `Global_1315298`, `Global_1315299`, `Global_1315326`
   - `NETWORK_IS_CLOUD_AVAILABLE`
   - `0x97287D68`, `0xBDBB5948`, `0xD3BBE42F`, `0xF79A97F5`, `0xF69B729C`, `0x3FB40673`

   Then choose GTA Online from story mode and confirm the transition actually reaches state 21. It could get diverted to 8, 28, 33 or 34 first.
2. If it reaches 21, apply the sequence and watch for:
   - the character creator,
   - session host/join over PSN,
   - freemode starting,
   - no kick from watchdog states 8, 28 or 33.
3. Back up the PS3 savedata before testing. The sequence calls `STAT_DELETE_SLOT`, and while it should only touch the in-memory or unavailable cloud copy, that's unverified on 1.27.

## Native names used above

- From your annotations: `0x395D18B1` STAT_CLEAR_PENDING_SAVES, `0xE3247582` STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS, `0x84BDD475` = STAT_CLEAR_SLOT_FOR_RELOAD (named in the 1.12 decompile).
- From the 1.12 decompiler's names: `0x97287D68` _CAN_PLAY_ONLINE, `0xBDBB5948` _IS_SOCIALCLUB_BANNED, `0xD3BBE42F` _IS_ROCKSTAR_BANNED.
- Inferred from use, unconfirmed: `0xCE7A2411` (on for the temp char, off in the reload routine; most likely STAT_SET_BLOCK_SAVES).
- The 1.27 decompile mislabels some natives. For example, its `set_vehicle_cam_boost_blur_angle(...)` is `_SET_WARNING_MESSAGE_2`, and `set_player_vehicle_alone_impact` is `0x2D817A5E`.
