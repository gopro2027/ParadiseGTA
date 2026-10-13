// POST /api/generate  ->  { key }
// Free keys for anyone. Limited per IP so the database can't be flooded.
import { getStore } from '../lib/store.js';
import { createKey } from '../lib/keys.js';
import { clientIp, sendJson } from '../lib/http.js';

const LIMIT = Number(process.env.KEYS_PER_HOUR || 5);

export default async function handler(req, res) {
  if (req.method !== 'POST') {
    res.setHeader('Allow', 'POST');
    return sendJson(res, { error: 'Use POST' }, 405);
  }
  const store = getStore();
  const ip = clientIp(req);
  const rl = `rl:gen:${ip}`;
  const count = await store.incr(rl);
  if (count === 1) await store.expire(rl, 3600);
  if (count > LIMIT) {
    const wait = Math.max(1, Math.ceil((await store.ttl(rl)) / 60));
    return sendJson(res, { error: `Too many keys generated from your network. Try again in ${wait} minute${wait === 1 ? '' : 's'}.` }, 429);
  }
  const key = await createKey(store, { ip });
  sendJson(res, { key });
}
