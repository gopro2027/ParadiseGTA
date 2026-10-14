// GET  /api/generate                    -> { siteKey, key? }  key is set if this browser session already has one
// POST /api/generate {"token": "..."}   -> { key }
// Free keys for anyone, but only one per browser session, behind a Cloudflare Turnstile captcha and an
// hourly per-IP limit so the database can't be flooded.
import { getStore } from '../lib/store.js';
import { createKey, getKey } from '../lib/keys.js';
import { clientIp, sendJson, readJsonBody } from '../lib/http.js';
import { turnstileConfig, verifyTurnstile } from '../lib/turnstile.js';

const LIMIT = Number(process.env.KEYS_PER_HOUR || 5);
const COOKIE = 'paradise_key';

function cookieKey(req) {
  const header = req.headers?.cookie || '';
  for (const part of header.split(';')) {
    const [name, ...rest] = part.trim().split('=');
    if (name === COOKIE) return decodeURIComponent(rest.join('='));
  }
  return null;
}

// returns the key already generated in this session, if it still exists
async function sessionKey(store, req) {
  const key = cookieKey(req);
  return key && (await getKey(store, key)) ? key : null;
}

export default async function handler(req, res) {
  const store = getStore();
  const config = turnstileConfig();

  if (req.method === 'GET') {
    return sendJson(res, { siteKey: config?.siteKey || null, key: await sessionKey(store, req) });
  }
  if (req.method !== 'POST') {
    res.setHeader('Allow', 'GET, POST');
    return sendJson(res, { error: 'Method not allowed' }, 405);
  }

  const existing = await sessionKey(store, req);
  if (existing) return sendJson(res, { key: existing, existing: true });

  if (!config) return sendJson(res, { error: 'Key generation is not configured yet.' }, 503);
  let body;
  try {
    body = await readJsonBody(req);
  } catch {
    return sendJson(res, { error: 'Invalid request' }, 400);
  }
  const ip = clientIp(req);
  if (!(await verifyTurnstile(body.token, config.secret, ip))) {
    return sendJson(res, { error: 'Captcha check failed. Please try again.' }, 403);
  }

  const rl = `rl:gen:${ip}`;
  const count = await store.incr(rl);
  if (count === 1) await store.expire(rl, 3600);
  if (count > LIMIT) {
    const wait = Math.max(1, Math.ceil((await store.ttl(rl)) / 60));
    return sendJson(res, { error: `Too many keys generated from your network. Try again in ${wait} minute${wait === 1 ? '' : 's'}.` }, 429);
  }

  const key = await createKey(store, { ip });
  // session cookie (no expiry), so one key per browser session
  res.setHeader('Set-Cookie', `${COOKIE}=${key}; Path=/; HttpOnly; Secure; SameSite=Strict`);
  sendJson(res, { key });
}
