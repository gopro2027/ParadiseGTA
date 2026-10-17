# Paradise SPRX (ParadiseGTA)

Paradise SPRX is gopro_2027's GTA V mod menu for PS3 (2015-2021; GTA Online PS3 shut down Dec 16 2021). It was a paid, key-protected menu backed by paradisesprx.net (PHP + MySQL). It is now open source: keys are free, and the backend has been rebuilt as a Vercel site.

**Work happens on the `offline-version` branch. Never push to `main`.**

## Layout

| Path | What |
|---|---|
| `ParadiseGTA_optimized_2020/` | The SPRX (PS3 PRX plugin). VS2010 + PS3 SDK (SNC) solution `ParadiseGTA.sln`. Single compile unit: `prx.cpp` includes almost every `.h` (Mods.h, Networking.h, RTMTool.h, rce.h, ...). |
| `paradisesprx/` | The website + API, deployed to Vercel (root directory `paradisesprx`). Static `public/`, Node functions in `api/`, Redis via `lib/store.js`. Has its own README with full setup. |
| `paradisesprx/cloudflare-worker/worker.js` | Source of the Cloudflare Worker that gives the PS3 a plain-HTTP front (see below). |

The SDK isn't installed on the dev machine, so the SPRX can't be compiled here; the owner builds it elsewhere and drops the result in `paradisesprx/public/files/ParadiseGTA.sprx`.

## How the SPRX talks to the server

- Raw BSD sockets, plain **HTTP/1.0 on port 80**, uppercase `HOST:` header, UA `paradise_semjases`, `Connection: close`. No TLS.
- Host: `PARADISE_SERVER_HOST` and `PARADISE_WEBSITE` in `prx.cpp` = **`paradisesprx.download`** (Cloudflare zone, Free plan, proxied to the Vercel project). Everything goes through Cloudflare; old builds that used `paradisesprx-proxy.gopro2027.workers.dev` are intentionally unsupported (the Worker's workers.dev subdomain is off).
- **Vercel always 308-redirects http to https and the PS3 can't follow it.** On the Free plan Cloudflare's proxy talks to the origin in the visitor's scheme (forcing HTTPS is Enterprise-only). So the PS3 paths on paradisesprx.download (`/check.html`, `/connecq.php*`, `/keyStatus.php*`, `/beat.php*`, `/gtartm.php*`, `/chat/*`, `/res/*`, `/files/*`) are Worker routes. The Worker forwards to `https://paradisesprx.vercel.app` with the firewall secret and buffers responses without a Content-Length (the SPRX downloads need it). Everything else (pages, `/api`) uses Cloudflare's normal proxy and cache. Zone rules (transform, redirects, cache, config, rate limit) are listed in `paradisesprx/README.md`. Don't turn on Always Use HTTPS, Bot Fight Mode or Under Attack mode: they break the PS3.
- Startup (`testSocket()` in Networking.h): `GET check.html` (must contain `READYFORCONNECTION`) → `GET connecq.php?sesh=<key>&data=<mac>&ver=5` → `BEGINDATA\n` + 60 values, each `%u` right-padded with spaces to 20 chars, read in the order of `struct Addresses` (prx.cpp) → `GET keyStatus.php?key=&id=` must return `VALIDVALIDVALID` (any other text is shown to the user). On failure the menu thread exits cleanly.
- The 60 values (game addresses, PPC hook opcodes, "privk" kick/script addresses) are in `paradisesprx/lib/offsets.js`. Field 19 `devmode` = 1 for keys with `dev=1`; fields 21-25 (FCW) are only sent to dev keys; field 38 is server time (unused).
- Other endpoints: `beat.php` (60s heartbeat, `NONE` or `PRINT:msg`), `gtartm.php` (web RTM relay), `chat/chat.php` (5-line chat, base64 messages), `res/getprop.php`, `res/downloadasset2.php` (`BEGINDATA\n` + DDS minus 0x80 header), `res/downloadsprx.php?filesize` (`<size> F`, auto-update only).
- Generic downloads (`downloadFileFromDownloadFolder`) fetch `files/<name>` statically and use the case-insensitive `Content-Length`. Files: Paradise.rpf (66447360 bytes, "Install Paradise Update.RPF"), BLJM.rpf (90209280, JP spoof), script_vary.rpf ("Install Paradise Script Menus", saved to `/dev_hdd0/tmp/gopro_2027/script.rpf`), rock_menu2.csc_*, textures, settings, strings.txt, native .dat tables.

## What was removed from the SPRX (don't reintroduce)

All protection layers from the paid era are gone: server-data XOR (`dataDecryptor`, keyhash, malloc-pointer XOR, per-field constant XORs), runtime code self-encryption (`encryptFunctionStart/End`, `findAndDecrypt`, `security.h`, `crypto.h`, the Java `encryptit.bat` post-build step), XOR-encoded strings and pointers, and anti-debug/tamper (FakeThread, checkTampering's debugger check, antiBreakpoint, MAC-function restore). `addrstruct()` is now just the plain global `socketConnectionStuff::addresses`. The worker thread (`WorkerThread`/`workerThreadTick`) remains for the quit combo, spooner loading and webMAN shutdown. Switches at the top of prx.cpp: `DEV_BUILD 0` (build watermark/script-host info), `AUTO_UPDATE 0` (self-update from `files/ParadiseGTA.sprx`).

## Temporary character mode and local MP saves

`ParadiseGTA_optimized_2020/TempCharacter.h` + `LocalMpStats.h`, always on (no menu option). They restore the 1.12 behaviour that 1.13+ removed: when the Rockstar cloud is down, GTA Online is played over PSN only. Unlike 1.12, the character is saved on the console. Tested on a PS3 so far: temp character creation, matchmaking into a public session and loading freemode. The local saves aren't tested yet.

- **Join flow:** `runGtaThread_hook` calls `TempCharacter::onThreadTick` after every script tick. When `maintransition` (`0x5FF2841F`) enters transition state 21 (`Global_1315298`) because of the cloud:
  - **No saved character** (`create()`): replays the deleted 1.12 setup. It deletes the 3 stat slots, clears the "needs reload" bits (`0x1DDDAC8+0x58`) and sets the temp, cloud-down, skip-tutorial and slot flags (`Global_1315352`, `1315354`, `1312399`, `1312341[]`, `1315392[]`, `1315353`). Then it continues the join (state 3, substate 4). It doesn't block saves: `_0xCE7A2411(1)` blocks both loads and saves in the stats save manager.
  - **Saved character exists:** holds the transition in state 15 (an empty case) and loads each saved slot. Then it goes to character select. If nothing loads within 30 s, it falls back to `create()`.
    - Each slot load is `STAT_CLEAR_SLOT_FOR_RELOAD(slot)` right before `STAT_LOAD(slot)`. For slot 0 it first resets manager `+0x5C` to 0, because `STAT_LOAD` only records slots 1–2 there.
    - `STAT_LOAD` returns 1 without loading when the slot isn't marked, and loading slot 0 clears every slot's mark. So a slot only counts as loaded if `LocalMpStats::servedLoads` went up.
    - A loaded character slot only counts as a character if its packed bool stat 76 is set (`func_603`, hash at `Global_2427264[76 <3>][c]`). Unreadable counts as yes.
    - The periodic save only saves slot 0, the current character (`0x326880`) and characters that exist. An empty slot never gets a file.
  - **MP stat saves only run while a session is running.** The MP stats save manager is blocked (`_0xCE7A2411(1)`, after `STAT_CLEAR_PENDING_SAVES`) in story mode and around character select, and unblocked once `NETWORK_IS_GAME_IN_PROGRESS` with the temp flag set. `LocalMpStats::localCloudPost` also skips writing unless `savesAllowed` (temp flag 1). Two reasons:
    - Character select (`func_1077`, state 4) quits to story mode (state 22 / sub 58) if the cloud is down and any MP stats save is pending (`0xA3407CA3`), and the join itself queues one.
    - Back in story mode the MP stats are reset to defaults, and a save then overwrote the real character (char0001 dropped from 26773 to 26573 bytes; "character exists" stat 76 read 0 afterwards).

    The quit's own saves (sub-states 58–63) still run, because the temp flag is cleared after them.
  - **In a session:** `STAT_SAVE` on every loaded slot 2 minutes in, then every 5 minutes, on top of the game's own saves.
- **Local MP saves (`LocalMpStats.h`):** the MP stats save and load operations call cloud POST `0x129E5B4` and GET `0x129E478`, and nothing else does. Both are replaced (`PatchInJump2`) with file I/O on `/dev_hdd0/tmp/gopro_2027/mpstats_save_default0000.save` / `mpstats_save_char000N.save`.
  - The files hold exactly what the game would upload (already serialized and encrypted).
  - A load streams the file through a 256-byte stack chunk into the game's own response grow buffer (`0xA8AEB8` init, `0xA8B0E4` append, allocator `*0x1CF72D8`), just like a real download.
  - The 12 `isCloudAvailable` (`0x12DB918`) calls on the stats path are patched to `li r3,1`. `NETWORK_IS_CLOUD_AVAILABLE` itself is untouched, since the state-21 trigger depends on it.
  - So are 3 "MP profile stats read?" checks (`0x12E8A70(0x224A968, 2)`, at `0x32C138`, `0x32C68C`, `0x32EFF0`). The save manager won't save until Rockstar's server-side profile stats are read, which never happens now. The first local-save test failed on exactly this: every `STAT_SAVE` returned 0, and nothing was ever written.
- **Session access patch:** the 1.27 multiplayer access check in the EBOOT (`0x1389D98`) gates every session native. It added two failure codes that 1.12 lacks:
  - 11: `CTunables` +0x4D, tunables not downloaded
  - 12: `bgScriptData` +0x1019, background script not loaded

  `allowSessionsWithoutCloud()` patches both compares (`0x1389F20`, `0x1389F48`) to `cmpwi r3,5`, like the existing `0x387` bypass.
- **Memory:** the SPRX must not allocate. A 64 KB static buffer made the game crash at boot before the menu even ran. Keep new static data and stack buffers tiny (≤1 KB total), and prefer memory the game already owns.
- **Debug logging:** `TEMPCHAR_DEBUG 1` in prx.cpp logs transition state changes, every MP stats load/save and the stats save manager state to `/dev_hdd0/tmp/gopro_2027/tempchar_log.txt`. Keep the per-tick logging to globals: a test build that called network natives from the hook froze once while freemode was loading.
- **Gotchas:**
  - A game can't create files in the `/dev_hdd0` root (the old `printfFile` path).
  - `Local_152.imm_N` in the decompiled scripts is not local index 152+N.
- **Research:** `research/temp-character-mode.md` covers the script and EBOOT research: the hardware test logs, the access-check reason codes, the MP stats save path, and the Ghidra headless setup on the 1.27 ELF + `EBOOT.map` and the 1.12 ELF.

## Server rules (product decisions)

- Keys: 36 chars from `23456789abcdefghjkmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ`, never expire, **no bans and no console binding** (any console can use any key; the MAC the SPRX sends is ignored).
- Free key generation (`/key`, `api/generate.js`): Cloudflare Turnstile captcha verified server-side, one key per browser session (session cookie `paradise_key`), plus a 5/hour per-IP limit. Deployed environments without Turnstile keys refuse to generate.
- Redis (Upstash, `KV_REST_API_URL/TOKEN`) hashes `key:<KEY>` with `created`, `dev`, `customName` (chat name), `psn`, `beatTime`, `rtmKey`, `rtmData`, `rtmLastRetrieve`. `/api/health` checks the round trip.

## Website (`paradisesprx/public/`)

Styled after the original paradisesprx.net: blurred menu-screenshot background, 60% black tint, particles.js, Roboto, uppercase 7px letter-spaced headings, underlined links that invert on hover, `{ Section }` headings, big white rounded button. Pages: home, `gta.html` (features, gallery), `/key`, `/install` (install wizard), `/rtm/`, `news.html` (all original posts), `/user/` (key status + Key.txt download, chat name, downloads incl. EBOOTs, installation guide, forge creations). Rewrites/headers in `vercel.json` (no `cleanUrls`: it 308-redirects `check.html`).

Install wizard modes: **webMAN** (one click per step: `/write.ps3`, `/xmb.ps3/download.ps3?to=<dir>&url=<http url>`, `/rename.ps3`, `/copy_ps3`; needs webMAN admin mode, toggled on the PS3 with L2+R2+TRIANGLE, or `&pwd=<ftp password>`; downloads only work from the XMB) and **FTP** (generated .bat/.sh using curl, anonymous login, one-time `EBOOT.BIN.bak` backup).

EBOOTs at `/files/eboot/<variant>/EBOOT.BIN`: `dex` (debug signed, DEX only), `hen-a` (retail signed, newer keys), `hen-b` (same code, older keys), `hen-c` (original HEN EBOOT, older keys, slightly different patch). Try A, then B, then C.

## Testing

From `paradisesprx/`:
- `npm test`: API unit tests (in-memory store, Turnstile stubbed).
- `npm run dev` (or `node scripts/dev-server.mjs <port>`): local server applying vercel.json, in-memory store, Turnstile test keys (token `XXXX.DUMMY.TOKEN.XXXX` passes).
- `node scripts/ps3-sim.mjs --host <host[:port]> [--key <key>]`: speaks raw HTTP/1.0 like the SPRX and checks every endpoint. Against production you must pass a real `--key` (the captcha blocks scripted generation).
- `node scripts/download-check.mjs --host paradisesprx.download`: downloads every menu file like the SPRX and compares bytes.

For SPRX source edits without a compiler, compare brace/paren and `#if`/`#endif` balance against HEAD after changes.

## Gotchas

- Source files are UTF-8 with BOM and CRLF; the repo stores LF (`core.autocrlf=true`). Edit with tools that keep CRLF. Git Bash `sed -i` converts files to LF, so avoid it.
- Shell heredocs and `python -c` in this environment can mangle backslashes; for edits containing `\\`, `\n` or `\r`, write a script file or use the Edit tool.
- Git Bash rewrites arguments that look like paths (`/dev_usb001/...`) unless `MSYS_NO_PATHCONV=1`.
- `paradisesprx/.gitattributes`: everything under `public/files/` is binary (`-text`); `*.rpf` goes through Git LFS. Vercel has Git LFS enabled for the project.
- **Big files are not in the deployment.** `Paradise.rpf`, `BLJM.rpf` and the 4 EBOOTs are assets of the GitHub release `files-v1` (EBOOTs named `EBOOT-<variant>.BIN`). The Worker serves them at the old `/files/...` paths. Don't add large files to `public/`: every deployment stores a full copy (41 deployments × ~230 MB filled the 10 GB Hobby deployment storage), and each build pulls LFS files against GitHub's 10 GiB/month LFS bandwidth.
- `vercel.json` `ignoreCommand` skips deployments for pushes that don't touch `paradisesprx/`.
- **Vercel is only reachable through Cloudflare.** The Vercel firewall custom rule "Deny everything that didn't come through Cloudflare" denies every request without the secret `x-paradise-proxy` header, on any host: `paradisesprx.vercel.app`, deployment URLs, or the Vercel IP with a spoofed Host. The Cloudflare transform rule and the Worker are the only senders.
  - Denied requests don't count toward Vercel usage; challenged requests that pass would, which is why it's deny and not challenge.
  - The `*.vercel.app` address can't be deleted; it's only the origin address the Worker forwards to.
  - The Vercel MCP can't edit the firewall (scoped → 403, unscoped → 404), so it's managed in the dashboard. Rotating the secret means changing the Worker secret, the transform rule and the firewall rule together.
- Vercel functions must resolve files relative to the code (`lib/paths.js`), not `process.cwd()`, because the project uses a root directory.
- The old paradisesprx.net backup (outside the repo) contains plaintext credentials. Never copy anything from it into the repo except reviewed assets.
