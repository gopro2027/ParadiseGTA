// Small helpers shared by the API functions. Handlers use the plain Node.js (req, res) API so they run
// the same on Vercel and in scripts/dev-server.mjs.

// Parses the query string without turning '+' into ' '. The SPRX sends base64 chat messages unescaped,
// so a '+' in the query really is a '+'.
export function getQuery(req) {
  const url = req.url || '';
  const q = url.indexOf('?');
  const params = {};
  if (q === -1) return params;
  for (const part of url.slice(q + 1).split('&')) {
    if (!part) continue;
    const eq = part.indexOf('=');
    const name = safeDecode(eq === -1 ? part : part.slice(0, eq));
    const value = eq === -1 ? '' : safeDecode(part.slice(eq + 1));
    if (!(name in params)) params[name] = value;
  }
  return params;
}

function safeDecode(s) {
  try {
    return decodeURIComponent(s);
  } catch {
    return s;
  }
}

export function sendText(res, body, status = 200, headers = {}) {
  res.statusCode = status;
  res.setHeader('Content-Type', 'text/plain; charset=utf-8');
  res.setHeader('Cache-Control', 'no-store');
  for (const [k, v] of Object.entries(headers)) res.setHeader(k, v);
  res.end(body);
}

export function sendBinary(res, buffer, headers = {}) {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'application/octet-stream');
  res.setHeader('Cache-Control', 'no-store, no-transform');
  res.setHeader('Content-Length', String(buffer.length));
  for (const [k, v] of Object.entries(headers)) res.setHeader(k, v);
  res.end(buffer);
}

export function sendJson(res, obj, status = 200) {
  res.statusCode = status;
  res.setHeader('Content-Type', 'application/json; charset=utf-8');
  res.setHeader('Cache-Control', 'no-store');
  res.end(JSON.stringify(obj));
}

export function clientIp(req) {
  const h = req.headers || {};
  const fwd = h['cf-connecting-ip'] || h['x-real-ip'] || (h['x-forwarded-for'] || '').split(',')[0];
  return (fwd || req.socket?.remoteAddress || 'unknown').trim();
}

export async function readJsonBody(req) {
  if (req.body !== undefined) {
    if (typeof req.body === 'string') return JSON.parse(req.body || '{}');
    if (Buffer.isBuffer(req.body)) return JSON.parse(req.body.toString('utf8') || '{}');
    return req.body || {};
  }
  const chunks = [];
  let size = 0;
  for await (const chunk of req) {
    size += chunk.length;
    if (size > 10000) throw new Error('body too large');
    chunks.push(chunk);
  }
  const text = Buffer.concat(chunks).toString('utf8');
  return text ? JSON.parse(text) : {};
}

// PHP's strip_tags(htmlspecialchars(text)), which the old server ran on user supplied text.
// After escaping there are no tags left to strip.
export function sanitize(text) {
  return String(text)
    .replace(/&/g, '&amp;')
    .replace(/"/g, '&quot;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;');
}
