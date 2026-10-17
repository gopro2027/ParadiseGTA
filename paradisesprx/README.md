# paradisesprx

Open source replacement for the old paradisesprx.net backend, built to run on Vercel. It serves everything the Paradise SPRX (`../ParadiseGTA_optimized_2020`) needs at runtime and gives out keys for free. There are no payments.

## What's in here

| Path | Purpose |
|---|---|
| `public/index.html`, `public/key.html` | Website: install instructions and the free key generator |
| `public/install.html` | Install wizard: copies Key.txt, the SPRX and the EBOOT to a PS3 either with webMAN MOD web commands (the PS3 downloads the files over plain HTTP from the Worker) or with a generated FTP installer script (.bat / .sh using curl) |
| `public/rtm/` | Web RTM page that sends commands to a menu through `gtartm.php` |
| `public/check.html` | `READYFORCONNECTION`, the SPRX's connectivity check |
| `public/files/` | Files the menu downloads (settings, textures, small RPFs, scripts). Put your compiled `ParadiseGTA.sprx` here as well. `Paradise.rpf`, `BLJM.rpf` and the EBOOTs are in the GitHub release `files-v1` instead (see Vercel step 4) |
| `api/` | Serverless functions, mapped to the old PHP URLs in `vercel.json` |
| `data/objects.txt` | Model hash to object name table for `res/getprop.php` |
| `scripts/dev-server.mjs` | Local server that applies `vercel.json` like Vercel does |
| `scripts/ps3-sim.mjs` | Talks to a server exactly like the SPRX (raw HTTP/1.0) and checks every endpoint |

### Endpoints used by the SPRX

| Request | Response |
|---|---|
| `GET /check.html` | `READYFORCONNECTION` |
| `GET /connecq.php?sesh=<key>&data=<mac>&ver=5` | `BEGINDATA\n` then 60 plain decimal values, each padded with spaces to 20 characters (game addresses, see `lib/offsets.js`). Any console can use any valid key. Unknown keys get zeros |
| `GET /keyStatus.php?key=<key>&id=<mac>` | `VALIDVALIDVALID`, or a `LOGIN FAILED` message the menu shows |
| `GET /beat.php?k=<key>&psn=<name>` | `NONE`, or `PRINT:<message>` if `BEAT_MESSAGE` is set |
| `GET /gtartm.php?...` | Web RTM relay (`generateRTMKey`, `retreiveData`, `setData`) |
| `GET /chat/chat.php?function=get\|msg\|rw&key=..` | In-game chat, last 5 messages |
| `GET /res/getprop.php?hash=<hash>` | Object name |
| `GET /res/downloadasset2.php?filename=<x>.dds` | `BEGINDATA\n` + texture without its 0x80 byte header |
| `GET /res/downloadsprx.php?filesize` | `<size> F` for `files/ParadiseGTA.sprx` (only used when `AUTO_UPDATE` is enabled in `prx.cpp`) |
| `GET /files/<name>` | Static download; the SPRX reads `Content-Length` |

The website uses `GET/POST /api/generate` (captcha protected, one key per session) and `GET/POST /api/key-info`.

## Deploying

### 1. Vercel

1. Import the repository in Vercel and set **Root Directory** to `paradisesprx`. The framework preset is "Other", with no build command.
2. Name the project `paradisesprx`.
3. Add storage: **Storage → Marketplace → Upstash (Redis)** and connect it to the project. This sets `UPSTASH_REDIS_REST_URL`/`UPSTASH_REDIS_REST_TOKEN` (`KV_REST_API_URL`/`KV_REST_API_TOKEN` also work). Without these the API falls back to in-memory storage, and keys won't survive between requests.
4. The small `.rpf` files left in `public/files/` are stored with **Git LFS**. Turn on *Settings → Git → Git Large File Storage* so Vercel checks them out. The big downloads (`Paradise.rpf`, `BLJM.rpf`, the four EBOOTs) are not in the deployment: they are assets of the GitHub release [`files-v1`](https://github.com/gopro2027/ParadiseGTA/releases/tag/files-v1) (named `EBOOT-<variant>.BIN` there). The Worker serves them at the usual `/files/...` paths, and `vercel.json` redirects those paths on the site to the Worker. Release downloads have no bandwidth limit and don't use Vercel bandwidth, deployment storage or the Git LFS quota. To replace one, upload a new release (e.g. `files-v2`), then update `RELEASE` in the Worker and the hashes in `scripts/download-check.mjs`.
5. Under *Settings → Environments → Production*, set branch tracking to `offline-version` so pushes to that branch deploy to production.
6. Under *Settings → Deployment Protection*, limit Vercel Authentication to preview deployments. Otherwise `paradisesprx.vercel.app` asks visitors to log in to Vercel.
7. `vercel.json` has an `ignoreCommand`: pushes that don't touch `paradisesprx/` (SPRX-only commits) don't create a deployment.

Required environment variables for the free key page (Cloudflare Turnstile captcha). Create a Turnstile widget for your site's hostname in the Cloudflare dashboard (or API) and set:

| Variable | |
|---|---|
| `TURNSTILE_SITE_KEY` | Public site key of the widget |
| `TURNSTILE_SECRET_KEY` | Secret key (store as a sensitive variable) |

Without them, deployed key generation is disabled. Local development falls back to Cloudflare's always-pass test keys. Each browser session gets one key: the key is remembered in a session cookie, and asking again returns the same key.

Optional environment variables:

| Variable | Default | |
|---|---|---|
| `PARADISE_WEBSITE` | `paradisesprx.vercel.app` | Site name shown in login error messages |
| `KEYS_PER_HOUR` | `5` | Free keys per IP per hour, on top of the captcha and one key per session |
| `BEAT_MESSAGE` | none | Message shown in game to everyone online |

### 2. Plain HTTP in front of Vercel (required for the PS3)

The SPRX sends plain HTTP/1.0 on port 80 over raw sockets, with no TLS. Vercel redirects every HTTP request to HTTPS (308), and that can't be turned off. The PS3 can't follow that redirect. So the console talks to something on **Cloudflare** that accepts plain HTTP and forwards to Vercel over HTTPS.

**Option A, used now: Cloudflare Worker on workers.dev.** No domain needed.

1. Create a Worker named `paradisesprx-proxy` with the code in `cloudflare-worker/worker.js` and enable its `workers.dev` route. The current deployment is `paradisesprx-proxy.gopro2027.workers.dev`.
2. The Worker passes requests straight through to `https://paradisesprx.vercel.app`. It only buffers small compressed responses, so the PS3 always gets a `Content-Length`. The RPFs stream through unchanged.
3. `PARADISE_SERVER_HOST` in `ParadiseGTA_optimized_2020/prx.cpp` is set to the Worker hostname.
4. The Workers free plan allows 100,000 requests per day.
5. **Flood protection.** The Worker has a secret binding `PROXY_SECRET` and sends it as the `x-paradise-proxy` header. A Vercel firewall custom rule ("Challenge everything except the PS3 proxy": Request Header `x-paradise-proxy` is not any of `<secret>` → Challenge) gives every other request a JS challenge. Browsers pass it once; HTTP floods (400K requests on `/` on Oct 15 2026) don't, and the PS3 skips it through the Worker. Anything that downloads from the site without a browser (curl, the FTP installer scripts) must go through the Worker. To rotate the secret, change the Worker secret and the rule value together.

**Option B: your own domain proxied by Cloudflare.**

1. Add a domain (e.g. `paradisesprx.example.com`) to the Vercel project.
2. In Cloudflare DNS, point it at Vercel (`CNAME cname.vercel-dns.com`) with the proxy **on** (orange cloud).
3. SSL/TLS mode: **Full** ("Flexible" causes a redirect loop with Vercel).
4. SSL/TLS → Edge Certificates: **Always Use HTTPS off**, and **Automatic HTTPS Rewrites off**.
5. Security: turn off Bot Fight Mode and any JS challenge for this hostname. The PS3 can't solve challenges.
6. In `ParadiseGTA_optimized_2020/prx.cpp`, set `PARADISE_SERVER_HOST` to that domain and rebuild the SPRX.

Check it from a PC:

```bash
node scripts/ps3-sim.mjs --host paradisesprx-proxy.gopro2027.workers.dev
```

### 3. The SPRX file

Build `ParadiseGTA.sprx` from `../ParadiseGTA_optimized_2020` (Visual Studio 2010 + PS3 SDK). The build no longer needs the post-build encryption step. If you want the website to offer it for download, copy it to `public/files/ParadiseGTA.sprx`.

## Managing keys

Keys are Redis hashes named `key:<KEY>` with these fields: `dev`, `customName` (chat name), `psn`, `beatTime`, `rtmKey`, `rtmData`. Use the Upstash data browser to manage them:

- Dev mode (unlocks the dev-only menu features and FCW values): set `dev` to `1`.

## Local development

```bash
npm install
```

```bash
npm test
```

```bash
npm run dev
```

```bash
node scripts/ps3-sim.mjs --host localhost:3000
```

Check that every file the menu downloads comes through byte-identical (uses the same HTTP/1.0 parsing as the SPRX):

```bash
node scripts/download-check.mjs --host paradisesprx-proxy.gopro2027.workers.dev
```

`npm run dev` serves the site at http://localhost:3000 with in-memory storage. Set the Upstash variables in your shell to use the real database.

## Note about the old backup

The original PHP site backup has database, Stripe, PayPal and reCAPTCHA credentials in plain text in several files (`server/hidden/auth.php`, `includes/backend/odb.php`, `stripe-*.php`, ...). None of them were copied here. If any of them are still in use anywhere, rotate them.
