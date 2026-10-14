import { test, beforeEach } from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

import { MemoryStore, setStore } from '../lib/store.js';
import { createKey, getKey, updateKey, KEY_ALPHABET } from '../lib/keys.js';
import { OFFSETS, offsetValues } from '../lib/offsets.js';
import connecq from '../api/connecq.js';
import keyStatus from '../api/keyStatus.js';
import beat from '../api/beat.js';
import gtartm from '../api/gtartm.js';
import chat from '../api/chat.js';
import getprop from '../api/getprop.js';
import downloadasset2 from '../api/downloadasset2.js';
import generate from '../api/generate.js';
import keyInfo from '../api/key-info.js';

const root = join(dirname(fileURLToPath(import.meta.url)), '..');
process.chdir(root);

let store;
beforeEach(() => {
  store = new MemoryStore();
  setStore(store);
});

// minimal Node req/res stand-ins
async function call(handler, url, { method = 'GET', body, ip = '1.2.3.4', cookie } = {}) {
  const req = { url, method, headers: { 'x-forwarded-for': ip, ...(cookie ? { cookie } : {}) }, body };
  const res = {
    statusCode: 200,
    headers: {},
    setHeader(k, v) { this.headers[k.toLowerCase()] = v; },
    end(data) { this.body = Buffer.isBuffer(data) ? data : Buffer.from(data ?? ''); },
  };
  await handler(req, res);
  res.text = res.body.toString('latin1');
  return res;
}

const MAC = '487409123';

function parseFields(text) {
  assert.ok(text.startsWith('BEGINDATA\n'));
  const data = text.slice(10);
  assert.equal(data.length, 60 * 20);
  return Array.from({ length: 60 }, (_, i) => Number(/^\d+/.exec(data.slice(i * 20, i * 20 + 20))[0]));
}

test('generated keys use the original format and are unique', async () => {
  const keys = new Set();
  for (let i = 0; i < 50; i++) keys.add(await createKey(store));
  assert.equal(keys.size, 50);
  for (const k of keys) {
    assert.equal(k.length, 36);
    for (const c of k) assert.ok(KEY_ALPHABET.includes(c));
  }
});

test('connecq sends the real addresses and binds the console', async () => {
  const key = await createKey(store);
  const res = await call(connecq, `/connecq.php?sesh=${key}&data=${MAC}&ver=5&r=123`);
  const values = parseFields(res.text);
  const expected = offsetValues();
  OFFSETS.forEach(([name], i) => {
    if (name !== 'temporaryTimeVal') assert.equal(values[i], expected[i], name);
  });
  assert.equal(values[0], 0x1E6FF38);
  assert.equal(values[14], 0x3E3A20); // hookAddress
  assert.equal(values[18], 0); // devmode off
  assert.equal(values[20], 0); // FCW only for dev keys
  assert.equal(values[58], 0x9FC1F4); // suggest
  assert.equal(values[59], 0x132AE30);
  assert.equal((await getKey(store, key)).mac, MAC);
});

test('connecq dev keys get devmode and FCW values', async () => {
  const key = await createKey(store);
  await updateKey(store, key, { dev: '1' });
  const values = parseFields((await call(connecq, `/connecq.php?sesh=${key}&data=${MAC}&ver=5`)).text);
  assert.equal(values[18], 1);
  assert.equal(values[20], 0x12C2ECC);
  assert.equal(values[24], 0xD04);
});

test('connecq rejects wrong versions and sends zeros for bad keys or other consoles', async () => {
  const key = await createKey(store);
  assert.equal((await call(connecq, `/connecq.php?sesh=${key}&data=${MAC}&ver=4`)).text, '000');
  assert.ok(parseFields((await call(connecq, `/connecq.php?sesh=nope&data=${MAC}&ver=5`)).text).every((v) => v === 0));
  await call(connecq, `/connecq.php?sesh=${key}&data=${MAC}&ver=5`);
  assert.ok(parseFields((await call(connecq, `/connecq.php?sesh=${key}&data=-5&ver=5`)).text).every((v) => v === 0));
});

test('keyStatus responses', async () => {
  const key = await createKey(store);
  await call(connecq, `/connecq.php?sesh=${key}&data=${MAC}&ver=5`);
  assert.equal((await call(keyStatus, `/keyStatus.php?key=${key}&id=${MAC}`)).text, 'VALIDVALIDVALID');
  assert.match((await call(keyStatus, `/keyStatus.php?key=${key}&id=1`)).text, /^LOGIN FAILED\nThis console is not registered on the server!/);
  assert.match((await call(keyStatus, `/keyStatus.php?key=abc&id=1`)).text, /^LOGIN FAILED\nInvalid key!/);
  assert.equal((await call(keyStatus, `/keyStatus.php?key=${key}`)).text, 'LOGIN FAILED\nNo info');
  await updateKey(store, key, { banned: 'true', banReason: 'Testing' });
  assert.equal((await call(keyStatus, `/keyStatus.php?key=${key}&id=${MAC}`)).text, 'LOGIN FAILED\nYou are banned.\nReason: Testing');
  assert.ok(parseFields((await call(connecq, `/connecq.php?sesh=${key}&data=${MAC}&ver=5`)).text).every((v) => v === 0));
});

test('beat stores the psn name and answers NONE', async () => {
  const key = await createKey(store);
  assert.equal((await call(beat, `/beat.php?k=${key}&psn=Some_Name`)).text, 'NONE');
  assert.equal((await getKey(store, key)).psn, 'Some_Name');
  await call(beat, `/beat.php?k=${key}&psn=bad<name>`);
  assert.equal((await getKey(store, key)).psn, 'NO_PSN');
});

test('gtartm round trip', async () => {
  const key = await createKey(store);
  const rtmKey = (await call(gtartm, `/gtartm.php?generateRTMKey=true&Key=${key}`)).text;
  assert.match(rtmKey, /^[a-z0-9]{4}$/);
  // the menu has not polled yet so it is not online
  assert.equal((await call(gtartm, `/gtartm.php?setData=true&RTMKey=${rtmKey}&RTMData=0;`)).text, 'Not valid Key!');
  assert.equal((await call(gtartm, `/gtartm.php?retreiveData=true&Key=${key}`)).text, '');
  assert.equal((await call(gtartm, `/gtartm.php?setData=true&RTMKey=${rtmKey}&RTMData=2;ALL;1.5;2;3;`)).text, 'Sent!');
  assert.equal((await call(gtartm, `/gtartm.php?setData=true&RTMKey=${rtmKey}&RTMData=1;hi,there;`)).text, 'Sent!');
  assert.equal((await call(gtartm, `/gtartm.php?setData=true&RTMKey=${rtmKey}&RTMData=${'x'.repeat(200)}`)).text, 'Too long!');
  assert.equal((await call(gtartm, `/gtartm.php?retreiveData=true&Key=${key}`)).text, '2;ALL;1.5;2;3;\n1;hi there;\n');
  assert.equal((await call(gtartm, `/gtartm.php?retreiveData=true&Key=${key}`)).text, '');
  assert.equal((await call(gtartm, `/gtartm.php?generateRTMKey=true&Key=bad`)).text, '!');
});

test('chat keeps the last 5 messages and handles unescaped base64', async () => {
  const key = await createKey(store);
  const empty = (await call(chat, `/chat/chat.php?function=get&key=${key}`)).text;
  assert.equal(empty, ' \n'.repeat(5));
  for (let i = 1; i <= 6; i++) {
    const b64 = Buffer.from(`message ${i}`).toString('base64');
    await call(chat, `/chat/chat.php?function=msg&key=${key}&psn=Tester&message=${b64}`);
  }
  // "hi?" base64 encodes to "aGk/" which the SPRX sends unescaped
  const b64 = Buffer.from('hi?').toString('base64');
  assert.equal(b64, 'aGk/');
  const out = (await call(chat, `/chat/chat.php?function=rw&key=${key}&psn=Tester&message=${b64}`)).text;
  assert.deepEqual(out.split('\n').filter(Boolean), ['message 3 :Tester', 'message 4 :Tester', 'message 5 :Tester', 'message 6 :Tester', 'hi? :Tester']);
  const bad = Buffer.from('<script>').toString('base64');
  assert.equal((await call(chat, `/chat/chat.php?function=rw&key=${key}&message=${bad}`)).text, 'invalid\n'.repeat(5));
  assert.equal((await call(chat, `/chat/chat.php?function=get&key=nope`)).text, 'Invalid key');
});

test('getprop looks up object names', async () => {
  assert.equal((await call(getprop, '/res/getprop.php?hash=162031196')).text, 'cj_cone');
  assert.equal((await call(getprop, '/res/getprop.php?hash=-1607885248')).text, 'cj_arrow_icon_2');
  assert.equal((await call(getprop, '/res/getprop.php?hash=12345678901')).text, 'Unknown Prop: 12345678901');
});

test('downloadasset2 sends BEGINDATA and the texture without its header', async () => {
  const res = await call(downloadasset2, '/res/downloadasset2.php?key=x&filename=portalCrosshair.dds');
  const file = readFileSync(join(root, 'public', 'files', 'portalCrosshair.dds'));
  assert.ok(res.body.subarray(0, 10).equals(Buffer.from('BEGINDATA\n')));
  assert.ok(res.body.subarray(10).equals(file.subarray(0x80)));
  assert.equal((await call(downloadasset2, '/res/downloadasset2.php?filename=../../package.json')).text, 'PARADISE_ERROR');
});

// Turnstile siteverify stub: only the token "good" passes
function stubTurnstile() {
  const realFetch = globalThis.fetch;
  const calls = [];
  globalThis.fetch = async (url, opts) => {
    assert.equal(url, 'https://challenges.cloudflare.com/turnstile/v0/siteverify');
    const params = new URLSearchParams(opts.body);
    calls.push(Object.fromEntries(params));
    return { json: async () => ({ success: params.get('response') === 'good' }) };
  };
  return { calls, restore: () => { globalThis.fetch = realFetch; } };
}

const cookieFrom = (res) => res.headers['set-cookie'].split(';')[0];

test('generate requires the captcha and gives one key per session', async () => {
  const stub = stubTurnstile();
  try {
    const info = JSON.parse((await call(generate, '/api/generate')).text);
    assert.equal(info.siteKey, '1x00000000000000000000AA'); // Cloudflare test key when not configured
    assert.equal(info.key, null);

    assert.equal((await call(generate, '/api/generate', { method: 'POST', body: {} })).statusCode, 403);
    assert.equal((await call(generate, '/api/generate', { method: 'POST', body: { token: 'bad' } })).statusCode, 403);

    const first = await call(generate, '/api/generate', { method: 'POST', body: { token: 'good' } });
    assert.equal(first.statusCode, 200);
    const { key } = JSON.parse(first.text);
    assert.ok(await getKey(store, key));
    assert.equal(stub.calls.at(-1).remoteip, '1.2.3.4');
    const cookie = cookieFrom(first);
    assert.match(first.headers['set-cookie'], /HttpOnly; Secure; SameSite=Strict$/);

    // same session: the same key comes back, no captcha needed, nothing new is created
    const again = JSON.parse((await call(generate, '/api/generate', { method: 'POST', body: {}, cookie })).text);
    assert.deepEqual(again, { key, existing: true });
    assert.equal(JSON.parse((await call(generate, '/api/generate', { cookie })).text).key, key);

    // a cookie with a key that doesn't exist is ignored
    const fake = await call(generate, '/api/generate', { method: 'POST', body: {}, cookie: 'paradise_key=' + 'a'.repeat(36) });
    assert.equal(fake.statusCode, 403);
  } finally {
    stub.restore();
  }
});

test('generate rate limit per IP', async () => {
  const stub = stubTurnstile();
  try {
    for (let i = 0; i < 5; i++) assert.equal((await call(generate, '/api/generate', { method: 'POST', body: { token: 'good' } })).statusCode, 200);
    assert.equal((await call(generate, '/api/generate', { method: 'POST', body: { token: 'good' } })).statusCode, 429);
    assert.equal((await call(generate, '/api/generate', { method: 'POST', body: { token: 'good' }, ip: '5.6.7.8' })).statusCode, 200);
    assert.equal((await call(generate, '/api/generate', { method: 'PUT' })).statusCode, 405);
  } finally {
    stub.restore();
  }
});

test('generate refuses to run deployed without Turnstile keys', async () => {
  process.env.VERCEL_ENV = 'production';
  try {
    assert.equal((await call(generate, '/api/generate', { method: 'POST', body: { token: 'good' } })).statusCode, 503);
    assert.equal(JSON.parse((await call(generate, '/api/generate')).text).siteKey, null);
  } finally {
    delete process.env.VERCEL_ENV;
  }
});

test('key-info status and console reset', async () => {
  const key = await createKey(store);
  await call(connecq, `/connecq.php?sesh=${key}&data=${MAC}&ver=5`);
  const info = JSON.parse((await call(keyInfo, `/api/key-info?key=${key}`)).text);
  assert.equal(info.status, 'active');
  assert.equal(info.consoleBound, true);
  assert.equal((await call(keyInfo, '/api/key-info?key=nope')).statusCode, 404);

  const reset = await call(keyInfo, '/api/key-info', { method: 'POST', body: { key, action: 'reset' } });
  assert.equal(reset.statusCode, 200);
  assert.equal((await getKey(store, key)).mac, '0');
  // a new console can now register
  await call(connecq, `/connecq.php?sesh=${key}&data=777&ver=5`);
  assert.equal((await call(keyStatus, `/keyStatus.php?key=${key}&id=777`)).text, 'VALIDVALIDVALID');
  // only once per day
  assert.equal((await call(keyInfo, '/api/key-info', { method: 'POST', body: { key, action: 'reset' } })).statusCode, 429);
});
