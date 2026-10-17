// Plain HTTP front for the PS3. Vercel redirects every http:// request to https://, which the SPRX's raw
// socket code can't follow, so the SPRX connects to this Worker over plain HTTP instead and the Worker
// forwards the request to the Vercel deployment over HTTPS.
// Deployed as "paradisesprx-proxy" with two kinds of routes:
// - routes on paradisesprx.download for the paths the SPRX and webMAN use (check.html, the .php endpoints,
//   chat/*, res/*, files/*). The rest of that domain goes through Cloudflare's normal proxy and cache, but
//   on the Free plan the proxy talks to the origin in the visitor's scheme, so plain HTTP would hit
//   Vercel's redirect without this Worker.
// - the workers.dev subdomain, which SPRX builds released before the move to paradisesprx.download use.
//
// The Vercel firewall challenges every request that doesn't carry x-paradise-proxy (a JS challenge stops
// HTTP floods but the PS3 can't solve one), so the Worker adds it from the PROXY_SECRET secret binding.
const ORIGIN = 'https://paradisesprx.vercel.app';

// The big downloads live in a GitHub release instead of the Vercel deployment: every deployment stored
// another copy of them, and release downloads don't use Vercel bandwidth or the Git LFS quota. The
// Worker fetches them from GitHub (HTTPS + redirects, which the PS3 can't do) and streams them through.
const RELEASE = 'https://github.com/gopro2027/ParadiseGTA/releases/download/files-v1/';
// keys are lowercase; the lookup ignores case so a differently-cased URL can't bounce between Vercel's
// redirect and the Worker
const RELEASE_FILES = {
  '/files/paradise.rpf': 'Paradise.rpf',
  '/files/bljm.rpf': 'BLJM.rpf',
  '/files/eboot/dex/eboot.bin': 'EBOOT-dex.BIN',
  '/files/eboot/hen-a/eboot.bin': 'EBOOT-hen-a.BIN',
  '/files/eboot/hen-b/eboot.bin': 'EBOOT-hen-b.BIN',
  '/files/eboot/hen-c/eboot.bin': 'EBOOT-hen-c.BIN',
};

async function fromRelease(request, asset, ctx) {
  const headers = new Headers();
  const range = request.headers.get('range');
  if (range) headers.set('range', range);
  // cached at Cloudflare for a day so GitHub (which sometimes answers 429 to shared Cloudflare IPs) is rarely asked
  const upstream = await fetch(RELEASE + asset, {
    method: request.method,
    headers,
    redirect: 'follow',
    cf: { cacheEverything: true, cacheTtl: 86400 },
  });
  const out = new Headers();
  for (const name of ['content-length', 'content-range', 'accept-ranges', 'etag', 'last-modified']) {
    const value = upstream.headers.get(name);
    if (value) out.set(name, value);
  }
  out.set('content-type', 'application/octet-stream');
  out.set('cache-control', 'public, max-age=3600');
  const length = Number(upstream.headers.get('content-length'));
  let body = upstream.body;
  if (body && length > 0) {
    // FixedLengthStream makes the runtime send this exact Content-Length, which the SPRX needs
    const fixed = new FixedLengthStream(length);
    ctx.waitUntil(body.pipeTo(fixed.writable));
    body = fixed.readable;
  }
  return new Response(body, { status: upstream.status, headers: out });
}

export default {
  async fetch(request, env, ctx) {
    const url = new URL(request.url);
    const asset = RELEASE_FILES[url.pathname.toLowerCase()];
    if (asset && (request.method === 'GET' || request.method === 'HEAD')) return fromRelease(request, asset, ctx);
    const headers = new Headers(request.headers);
    headers.delete('host');
    const ip = request.headers.get('cf-connecting-ip');
    if (ip) headers.set('x-forwarded-for', ip);
    if (env.PROXY_SECRET) headers.set('x-paradise-proxy', env.PROXY_SECRET);
    const hasBody = request.method !== 'GET' && request.method !== 'HEAD';
    // menu downloads (/files/*) are cached at Cloudflare for 5 minutes, like the site's own Cache-Control
    const cacheable = request.method === 'GET' && url.pathname.startsWith('/files/');
    const upstream = await fetch(ORIGIN + url.pathname + url.search, {
      method: request.method,
      headers,
      body: hasBody ? request.body : undefined,
      redirect: 'manual',
      ...(cacheable ? { cf: { cacheEverything: true, cacheTtl: 300 } } : {}),
    });
    if (upstream.headers.has('content-length') || request.method === 'HEAD') return upstream;
    // The runtime decompresses compressed origin responses, which drops Content-Length. The SPRX's file
    // downloads need it, so buffer the (small) body and send it with an exact length.
    const body = await upstream.arrayBuffer();
    const out = new Headers(upstream.headers);
    out.delete('content-encoding');
    out.set('content-length', String(body.byteLength));
    return new Response(body, { status: upstream.status, statusText: upstream.statusText, headers: out });
  },
};
