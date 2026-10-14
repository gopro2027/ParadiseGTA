// In-game chat (last 5 messages, shared by everyone)
//   chat/chat.php?function=get&key=<key>
//   chat/chat.php?function=rw&key=<key>[&psn=<name>]&message=<base64>   send then read
//   chat/chat.php?function=msg&key=<key>[&psn=<name>]&message=<base64>  send only
import { createHash } from 'node:crypto';
import { getStore } from '../lib/store.js';
import { getKey } from '../lib/keys.js';
import { getQuery, sendText, sanitize } from '../lib/http.js';

const NUM_LINES = 5;
const MAX_LINE = 99;
const ALLOWED = /^[A-Za-z0-9_.?', ]*$/;

function repeatLine(text) {
  return (text + '\n').repeat(NUM_LINES);
}

function username(key, psn, record) {
  if (record.customName) return record.customName;
  if (psn) return psn.slice(0, 16);
  return createHash('sha256').update(key.slice(8, 15)).digest('hex').slice(4, 8);
}

async function read(store) {
  const lines = await store.lrange('chat', -NUM_LINES, -1);
  let out = '';
  for (const line of lines) out += line + '\n';
  for (let i = lines.length; i < NUM_LINES; i++) out += ' \n';
  return out;
}

export default async function handler(req, res) {
  const q = getQuery(req);
  if (q.function === undefined || q.key === undefined) return sendText(res, '');
  const store = getStore();
  const record = await getKey(store, q.key);
  if (!record) return sendText(res, 'Invalid key');

  const name = username(q.key, q.psn, record);
  if (name.length < 3 || name.length > 16) return sendText(res, repeatLine('invalid name'));

  let out = '';
  if (q.function === 'msg' || q.function === 'rw') {
    const message = sanitize(Buffer.from(q.message || '', 'base64').toString('utf8'));
    if (!ALLOWED.test(message)) return sendText(res, repeatLine('invalid'));
    const line = message + ' :' + name;
    if (message.trim() && line.length <= MAX_LINE) {
      await store.rpush('chat', line);
      await store.ltrim('chat', -NUM_LINES, -1);
    }
  }
  if (q.function === 'get' || q.function === 'rw') out = await read(store);
  sendText(res, out);
}
