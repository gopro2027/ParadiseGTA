import { randomInt } from 'node:crypto';

// Same format as the original paradisesprx.net keys: 36 characters, no easily confused characters
export const KEY_ALPHABET = '23456789abcdefghjkmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ';
export const KEY_LENGTH = 36;
const KEY_RE = new RegExp(`^[${KEY_ALPHABET}]{${KEY_LENGTH}}$`);

export const RTM_ALPHABET = '23456789abcdefghijkmnopqrstuvwxyz';
export const RTM_KEY_LENGTH = 4;

export function isKeyFormat(key) {
  return typeof key === 'string' && KEY_RE.test(key);
}

export function randomString(length, alphabet) {
  let out = '';
  for (let i = 0; i < length; i++) out += alphabet[randomInt(alphabet.length)];
  return out;
}

const keyName = (key) => `key:${key}`;

export async function createKey(store, meta = {}) {
  for (let attempt = 0; attempt < 5; attempt++) {
    const key = randomString(KEY_LENGTH, KEY_ALPHABET);
    // claim the key name first so two requests can never get the same key
    if ((await store.set(`claim:${key}`, '1', { nx: true })) === null) continue;
    await store.hset(keyName(key), {
      created: Math.floor(Date.now() / 1000),
      dev: '0',
      createdIp: meta.ip || '',
    });
    return key;
  }
  throw new Error('could not generate a unique key');
}

export async function getKey(store, key) {
  if (!isKeyFormat(key)) return null;
  return store.hgetall(keyName(key));
}

export function updateKey(store, key, fields) {
  return store.hset(keyName(key), fields);
}

export async function setRtmKey(store, key, record) {
  if (record.rtmKey) await store.del(`rtm:${record.rtmKey}`);
  let rtmKey;
  for (let attempt = 0; attempt < 20; attempt++) {
    rtmKey = randomString(RTM_KEY_LENGTH, RTM_ALPHABET);
    if ((await store.set(`rtm:${rtmKey}`, key, { nx: true })) !== null) break;
    rtmKey = null;
  }
  if (!rtmKey) throw new Error('could not generate an rtm key');
  await updateKey(store, key, { rtmKey, rtmData: '' });
  return rtmKey;
}

export function keyForRtmKey(store, rtmKey) {
  if (typeof rtmKey !== 'string' || rtmKey.length !== RTM_KEY_LENGTH) return null;
  return store.get(`rtm:${rtmKey}`);
}
