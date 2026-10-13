// GET  /api/key-info?key=<key>                       -> key status for the website
// POST /api/key-info {"key": "...", "action": "reset"} -> unbind the key from its console (once per day)
import { getStore } from '../lib/store.js';
import { getKey, updateKey } from '../lib/keys.js';
import { getQuery, sendJson, readJsonBody } from '../lib/http.js';

const RESET_COOLDOWN = 24 * 60 * 60;

function describe(record) {
  return {
    status: record.banned === 'false' ? 'active' : 'banned',
    banReason: record.banned === 'false' ? undefined : record.banReason || '',
    consoleBound: !!record.mac && record.mac !== '0',
    created: Number(record.created || 0),
    lastSeen: Number(record.beatTime || 0) || null,
  };
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
    if (body.action !== 'reset') return sendJson(res, { error: 'Unknown action' }, 400);
    const record = await getKey(store, body.key || '');
    if (!record) return sendJson(res, { error: 'Key not found' }, 404);
    if (record.banned !== 'false') return sendJson(res, { error: 'This key is banned' }, 403);
    if (!record.mac || record.mac === '0') return sendJson(res, { ok: true, message: 'This key is not bound to a console yet.' });
    if ((await store.set(`rl:reset:${body.key}`, '1', { nx: true, ex: RESET_COOLDOWN })) === null) {
      const hours = Math.max(1, Math.ceil((await store.ttl(`rl:reset:${body.key}`)) / 3600));
      return sendJson(res, { error: `This key's console was reset recently. Try again in ${hours} hour${hours === 1 ? '' : 's'}.` }, 429);
    }
    await updateKey(store, body.key, { mac: '0' });
    return sendJson(res, { ok: true, message: 'Console reset. The next console that uses this key will be registered to it.' });
  }
  res.setHeader('Allow', 'GET, POST');
  sendJson(res, { error: 'Method not allowed' }, 405);
}
