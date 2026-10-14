// User panel API
// GET  /api/key-info?key=<key>                                 -> key info
// POST /api/key-info {"key": "...", "action": "name", "name": ""} -> set (or clear) the in-game chat name
import { getStore } from '../lib/store.js';
import { getKey, updateKey } from '../lib/keys.js';
import { getQuery, sendJson, readJsonBody } from '../lib/http.js';

const NAME_COOLDOWN = 10 * 60;
// same characters the old changeName.php allowed, length limits from the chat
const NAME_RE = /^[A-Za-z0-9_.]{3,16}$/;

function describe(record) {
  return {
    created: Number(record.created || 0),
    lastSeen: Number(record.beatTime || 0) || null,
    chatName: record.customName || null,
  };
}

async function setName(store, key, name) {
  name = typeof name === 'string' ? name.trim() : '';
  if (name && !NAME_RE.test(name)) {
    return { status: 400, body: { error: 'Names are 3 to 16 characters: letters, numbers, _ and . only.' } };
  }
  const limit = `rl:name:${key}`;
  if ((await store.set(limit, '1', { nx: true, ex: NAME_COOLDOWN })) === null) {
    const minutes = Math.max(1, Math.ceil((await store.ttl(limit)) / 60));
    return { status: 429, body: { error: `You changed your name recently. Try again in ${minutes} minute${minutes === 1 ? '' : 's'}.` } };
  }
  await updateKey(store, key, { customName: name });
  return { body: { ok: true, chatName: name || null, message: name ? `Chat name set to ${name}.` : 'Chat name cleared.' } };
}

export default async function handler(req, res) {
  const store = getStore();
  if (req.method === 'GET') {
    const record = await getKey(store, getQuery(req).key || '');
    if (!record) return sendJson(res, { error: 'Key not found' }, 404);
    return sendJson(res, describe(record));
  }
  if (req.method === 'POST') {
    let body;
    try {
      body = await readJsonBody(req);
    } catch {
      return sendJson(res, { error: 'Invalid request' }, 400);
    }
    if (body.action !== 'name') return sendJson(res, { error: 'Unknown action' }, 400);
    const record = await getKey(store, body.key || '');
    if (!record) return sendJson(res, { error: 'Key not found' }, 404);
    const result = await setName(store, body.key, body.name);
    return sendJson(res, result.body, result.status || 200);
  }
  res.setHeader('Allow', 'GET, POST');
  sendJson(res, { error: 'Method not allowed' }, 405);
}
