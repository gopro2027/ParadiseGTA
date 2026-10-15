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
- Host: `PARADISE_SERVER_HOST` in `prx.cpp` = `paradisesprx-proxy.gopro2027.workers.dev`. User-facing site name: `PARADISE_WEBSITE` = `paradisesprx.vercel.app`.
- **Vercel always 308-redirects http to https and the PS3 can't follow it**, so the PS3 talks to the Cloudflare Worker, which proxies to `https://paradisesprx.vercel.app`. The Worker buffers responses without a Content-Length (Cloudflare decompression drops it) because the SPRX downloads need it.
- Startup (`testSocket()` in Networking.h): `GET check.html` (must contain `READYFORCONNECTION`) → `GET connecq.php?sesh=<key>&data=<mac>&ver=5` → `BEGINDATA\n` + 60 values, each `%u` right-padded with spaces to 20 chars, read in the order of `struct Addresses` (prx.cpp) → `GET keyStatus.php?key=&id=` must return `VALIDVALIDVALID` (any other text is shown to the user). On failure the menu thread exits cleanly.
- The 60 values (game addresses, PPC hook opcodes, "privk" kick/script addresses) are in `paradisesprx/lib/offsets.js`. Field 19 `devmode` = 1 for keys with `dev=1`; fields 21-25 (FCW) are only sent to dev keys; field 38 is server time (unused).
- Other endpoints: `beat.php` (60s heartbeat, `NONE` or `PRINT:msg`), `gtartm.php` (web RTM relay), `chat/chat.php` (5-line chat, base64 messages), `res/getprop.php`, `res/downloadasset2.php` (`BEGINDATA\n` + DDS minus 0x80 header), `res/downloadsprx.php?filesize` (`<size> F`, auto-update only).
- Generic downloads (`downloadFileFromDownloadFolder`) fetch `files/<name>` statically and use the case-insensitive `Content-Length`. Files: Paradise.rpf (66447360 bytes, "Install Paradise Update.RPF"), BLJM.rpf (90209280, JP spoof), script_vary.rpf ("Install Paradise Script Menus", saved to `/dev_hdd0/tmp/gopro_2027/script.rpf`), rock_menu2.csc_*, textures, settings, strings.txt, native .dat tables.

## What was removed from the SPRX (don't reintroduce)

All protection layers from the paid era are gone: server-data XOR (`dataDecryptor`, keyhash, malloc-pointer XOR, per-field constant XORs), runtime code self-encryption (`encryptFunctionStart/End`, `findAndDecrypt`, `security.h`, `crypto.h`, the Java `encryptit.bat` post-build step), XOR-encoded strings and pointers, and anti-debug/tamper (FakeThread, checkTampering's debugger check, antiBreakpoint, MAC-function restore). `addrstruct()` is now just the plain global `socketConnectionStuff::addresses`. The worker thread (`WorkerThread`/`workerThreadTick`) remains for the quit combo, spooner loading and webMAN shutdown. Switches at the top of prx.cpp: `DEV_BUILD 0` (build watermark/script-host info), `AUTO_UPDATE 0` (self-update from `files/ParadiseGTA.sprx`).

## Temporary character mode

`ParadiseGTA_optimized_2020/TempCharacter.h`, always on (no menu option). It restores the 1.12 behaviour that 1.13+ removed: when the Rockstar cloud is down, GTA Online is played with a temporary character over PSN only. Tested on a PS3: it matchmakes into a public session and loads into freemode. The character isn't saved, so every join makes a new one (same as 1.12).

- **Temp character setup:** `runGtaThread_hook` calls `TempCharacter::onThreadTick` after every script tick. When `maintransition` (`0x5FF2841F`) enters transition state 21 (`Global_1315298`) because of the cloud, it replays the deleted 1.12 setup:
  - blocks saves and deletes the 3 stat slots;
  - sets the temp, cloud-down, skip-tutorial and slot flags (`Global_1315352`, `1315354`, `1312399`, `1312341[]`, `1315392[]`, `1315353`);
  - continues the join (state 3, substate 4) with no prompt.
- **Session access patch:** the 1.27 multiplayer access check in the EBOOT (`0x1389D98`) gates every session native. It added two failure codes that 1.12 lacks:
  - 11: `CTunables` +0x4D, tunables not downloaded
  - 12: `bgScriptData` +0x1019, background script not loaded

  `allowSessionsWithoutCloud()` patches both compares (`0x1389F20`, `0x1389F48`) to `cmpwi r3,5`, like the existing `0x387` bypass. It's applied when the temp character is created.
- **Debug logging:** `TEMPCHAR_DEBUG 1` in prx.cpp logs every transition state change to `/dev_hdd0/tmp/gopro_2027/tempchar_log.txt`. Keep it to globals: a test build that called network natives from the hook froze once while freemode was loading.
- **Gotchas:**
  - A game can't create files in the `/dev_hdd0` root (the old `printfFile` path).
  - `Local_152.imm_N` in the decompiled scripts is not local index 152+N.
- **Research:** `research/temp-character-mode.md` covers the script and EBOOT research: the hardware test logs, the access-check reason codes, and the Ghidra headless setup on the 1.27 ELF + `EBOOT.map` and the 1.12 ELF.

## Server rules (product decisions)

- Keys: 36 chars from `23456789abcdefghjkmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ`, never expire, **no bans and no console binding** (any console can use any key; the MAC the SPRX sends is ignored).
- Free key generation (`/key`, `api/generate.js`): Cloudflare Turnstile captcha verified server-side, one key per browser session (session cookie `paradise_key`), plus a 5/hour per-IP limit. Deployed environments without Turnstile keys refuse to generate.
- Redis (Upstash, `KV_REST_API_URL/TOKEN`) hashes `key:<KEY>` with `created`, `dev`, `customName` (chat name), `psn`, `beatTime`, `rtmKey`, `rtmData`, `rtmLastRetrieve`. `/api/health` checks the round trip.

## Website (`paradisesprx/public/`)

Styled after the original paradisesprx.net: blurred menu-screenshot background, 60% black tint, particles.js, Roboto, uppercase 7px letter-spaced headings, underlined links that invert on hover, `{ Section }` headings, big white rounded button. Pages: home, `gta.html` (features, gallery), `/key`, `/install` (install wizard), `/rtm/`, `news.html` (all original posts), `/user/` (key status + Key.txt download, chat name, downloads incl. EBOOTs, installation guide, forge creations). Rewrites/headers in `vercel.json` (no `cleanUrls`: it 308-redirects `check.html`).

Install wizard modes: **webMAN** (one click per step: `/write.ps3`, `/xmb.ps3/download.ps3?to=<dir>&url=<http url>`, `/rename.ps3`, `/copy_ps3`; needs webMAN admin mode, toggled on the PS3 with L2+R2+TRIANGLE, or `&pwd=<ftp password>`; downloads only work from the XMB) and **FTP** (generated .bat/.sh using curl, anonymous login, one-time `EBOOT.BIN.bak` backup).

EBOOTs in `public/files/eboot/`: `dex` (debug signed, DEX only), `hen-a` (retail signed, newer keys), `hen-b` (same code, older keys), `hen-c` (original HEN EBOOT, older keys, slightly different patch). Try A, then B, then C.

## Testing

From `paradisesprx/`:
- `npm test`: API unit tests (in-memory store, Turnstile stubbed).
- `npm run dev` (or `node scripts/dev-server.mjs <port>`): local server applying vercel.json, in-memory store, Turnstile test keys (token `XXXX.DUMMY.TOKEN.XXXX` passes).
- `node scripts/ps3-sim.mjs --host <host[:port]> [--key <key>]`: speaks raw HTTP/1.0 like the SPRX and checks every endpoint. Against production you must pass a real `--key` (the captcha blocks scripted generation).
- `node scripts/download-check.mjs --host paradisesprx-proxy.gopro2027.workers.dev`: downloads every menu file like the SPRX and compares bytes.

For SPRX source edits without a compiler, compare brace/paren and `#if`/`#endif` balance against HEAD after changes.

## Gotchas

- Source files are UTF-8 with BOM and CRLF; the repo stores LF (`core.autocrlf=true`). Edit with tools that keep CRLF. Git Bash `sed -i` converts files to LF, so avoid it.
- Shell heredocs and `python -c` in this environment can mangle backslashes; for edits containing `\\`, `\n` or `\r`, write a script file or use the Edit tool.
- Git Bash rewrites arguments that look like paths (`/dev_usb001/...`) unless `MSYS_NO_PATHCONV=1`.
- `paradisesprx/.gitattributes`: everything under `public/files/` is binary (`-text`); `*.rpf` and `eboot/**/*.BIN` go through Git LFS. Vercel has Git LFS enabled for the project.
- Vercel functions must resolve files relative to the code (`lib/paths.js`), not `process.cwd()`, because the project uses a root directory.
- The old paradisesprx.net backup (outside the repo) contains plaintext credentials. Never copy anything from it into the repo except reviewed assets.
