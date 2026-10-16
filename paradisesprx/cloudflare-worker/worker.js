// Plain HTTP front for the PS3. Vercel redirects every http:// request to https://, which the SPRX's raw
// socket code can't follow, so the SPRX connects to this Worker over plain HTTP instead and the Worker
// forwards the request to the Vercel deployment over HTTPS.
// Deployed as "paradisesprx-proxy" on the account's workers.dev subdomain.
//
// The Vercel firewall challenges every request that doesn't carry x-paradise-proxy (a JS challenge stops
// HTTP floods but the PS3 can't solve one), so the Worker adds it from the PROXY_SECRET secret binding.
const ORIGIN = 'https://paradisesprx.vercel.app';

export default {
  async fetch(request, env) {
    const url = new URL(request.url);
    const headers = new Headers(request.headers);
    headers.delete('host');
    const ip = request.headers.get('cf-connecting-ip');
    if (ip) headers.set('x-forwarded-for', ip);
    if (env.PROXY_SECRET) headers.set('x-paradise-proxy', env.PROXY_SECRET);
    const hasBody = request.method !== 'GET' && request.method !== 'HEAD';
    const upstream = await fetch(ORIGIN + url.pathname + url.search, {
      method: request.method,
      headers,
      body: hasBody ? request.body : undefined,
      redirect: 'manual',
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
