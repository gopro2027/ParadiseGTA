// Talks to the server exactly like the SPRX does (raw HTTP/1.0 over a TCP socket, uppercase HOST header,
// same parsing) and runs through the startup flow and the other endpoints.
//   node scripts/ps3-sim.mjs --host localhost:3000 [--key <existing key>] [--mac 487409123]
// Point --host at the Cloudflare domain to check the real deployment over plain HTTP.
import net from 'node:net';
import { readFileSync, existsSync } from 'node:fs';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { OFFSETS, offsetValues } from '../lib/offsets.js';

const root = join(dirname(fileURLToPath(import.meta.url)), '..');
const args = Object.fromEntries(process.argv.slice(2).reduce((acc, a, i, all) => {
  if (a.startsWith('--')) acc.push([a.slice(2), all[i + 1] && !all[i + 1].startsWith('--') ? all[i + 1] : true]);
  return acc;
}, []));
const [hostname, portText] = String(args.host || 'localhost:3000').split(':');
const port = Number(portText || 80);
const hostHeader = port === 80 ? hostname : `${hostname}:${port}`;
const mac = String(args.mac || 487409123);

let failures = 0;
function check(name, ok, detail = '') {
  console.log(`${ok ? 'PASS' : 'FAIL'}  ${name}${detail ? '  ' + detail : ''}`);
  if (!ok) failures++;
}

// raw request, returns the whole response (headers + body) once the server closes the connection
function rawGet(path) {
  return new Promise((resolve, reject) => {
    const sock = net.connect(port, hostname);
    const chunks = [];
    sock.setTimeout(20000, () => sock.destroy(new Error('timeout')));
    sock.on('connect', () => {
      sock.write(`GET /${path} HTTP/1.0\r\nHOST: ${hostHeader}\r\nUser-Agent: paradise_semjases\r\nConnection: close\r\n\r\n`);
    });
    sock.on('data', (d) => chunks.push(d));
    sock.on('end', () => resolve(Buffer.concat(chunks)));
    sock.on('error', reject);
  });
}

function splitResponse(buf) {
  const sep = buf.indexOf('\r\n\r\n');
  return { head: buf.subarray(0, sep).toString('latin1'), body: buf.subarray(sep + 4) };
}

// requestURL(): everything after the header separator as a string
async function requestURL(path) {
  return splitResponse(await rawGet(path)).body.toString('latin1');
}

// StoUI(): digits up to the first non digit
const StoUI = (s) => {
  const m = /^\d+/.exec(s);
  return m ? Number(m[0]) >>> 0 : 0;
};

// SocketRequestWriteToFile() with useContentLength
async function downloadFile(path) {
  const { head, body } = splitResponse(await rawGet(path));
  const m = /content-length:\s*(\d+)/i.exec(head) || /content-size:\s*(\d+)/i.exec(head);
  if (!m) return { error: 'no Content-Length header', head };
  return { size: Number(m[1]), data: body.subarray(0, Number(m[1])), head };
}

// requestURLAtHeader(): bytes after "BEGINDATA\n"
async function afterBeginData(path, size) {
  const buf = await rawGet(path);
  const i = buf.indexOf('BEGINDATA\n');
  return i === -1 ? null : buf.subarray(i + 10, i + 10 + size);
}

async function getKey() {
  if (args.key) return String(args.key);
  const res = await fetch(`http://${hostHeader}/api/generate`, { method: 'POST' });
  const json = await res.json();
  check('generate free key', res.ok && typeof json.key === 'string' && json.key.length === 36, json.key || json.error);
  return json.key;
}

const localFile = (name) => join(root, 'public', 'files', name);

async function main() {
  console.log(`Simulating the SPRX against ${hostHeader}\n`);

  check('check.html', (await requestURL('check.html')).includes('READYFORCONNECTION'));

  const key = await getKey();
  if (!key) return;

  // connecq: BEGINDATA\n + 60 fields of 20 characters
  const fields = await afterBeginData(`connecq.php?sesh=${key}&data=${mac}&ver=5`, 60 * 20);
  check('connecq.php returned BEGINDATA + 60 fields', fields && fields.length === 1200, fields ? `${fields.length} bytes` : 'BEGINDATA not found');
  if (fields) {
    const values = [];
    for (let i = 0; i < 60; i++) values.push(StoUI(fields.subarray(i * 20, i * 20 + 20).toString('latin1')));
    const expected = offsetValues();
    const wrong = OFFSETS.map(([name], i) => [name, values[i], expected[i]])
      .filter(([name, got, want]) => name !== 'temporaryTimeVal' && name !== 'devmode' && got !== want);
    check('connecq.php values decode to the expected addresses', wrong.length === 0,
      wrong.map(([n, g, w]) => `${n}=0x${g.toString(16)} (want 0x${w.toString(16)})`).join(', '));
    check('connecq.php nativeTable', values[0] === 0x1E6FF38, '0x' + values[0].toString(16));
    check('connecq.php server time', Math.abs(values[37] - Date.now() / 1000) < 600);
  }

  check('keyStatus.php accepts this console', (await requestURL(`keyStatus.php?key=${key}&id=${mac}`)) === 'VALIDVALIDVALID');
  const other = await requestURL(`keyStatus.php?key=${key}&id=12345`);
  check('keyStatus.php rejects another console', other.includes('not registered'), JSON.stringify(other.slice(0, 60)));
  const otherFields = await afterBeginData(`connecq.php?sesh=${key}&data=12345&ver=5`, 60 * 20);
  check('connecq.php sends zeros to another console', otherFields && StoUI(otherFields.subarray(0, 20).toString()) === 0);
  const invalid = await requestURL('keyStatus.php?key=000000000000000000000000000000000000&id=1');
  check('keyStatus.php rejects an unknown key', invalid.startsWith('LOGIN FAILED\nInvalid key!'));

  // generic downloads come from /files/ with Content-Length
  const dl = await downloadFile('files/default_settings.xml');
  const expectedXml = existsSync(localFile('default_settings.xml')) ? readFileSync(localFile('default_settings.xml')) : null;
  check('files/default_settings.xml download', !dl.error && dl.data.length === dl.size && (!expectedXml || dl.data.equals(expectedXml)),
    dl.error || `${dl.size} bytes`);

  const dds = await afterBeginData(`res/downloadasset2.php?key=${key}&filename=portalCrosshair.dds`, 1152 - 0x80);
  const expectedDds = existsSync(localFile('portalCrosshair.dds')) ? readFileSync(localFile('portalCrosshair.dds')).subarray(0x80) : null;
  check('res/downloadasset2.php texture', dds && dds.length === 1152 - 0x80 && (!expectedDds || dds.equals(expectedDds)));

  check('beat.php', (await requestURL(`beat.php?k=${key}&psn=Tester_1`)) === 'NONE');

  const rtmKey = await requestURL(`gtartm.php?generateRTMKey=true&Key=${key}`);
  check('gtartm.php generateRTMKey', /^[a-z0-9]{4}$/.test(rtmKey), rtmKey);
  await requestURL(`gtartm.php?retreiveData=true&Key=${key}`); // the menu polls, which marks it online
  const sent = await fetch(`http://${hostHeader}/rtm/gtartm.php?setData=true&RTMKey=${rtmKey}&RTMData=1;hello,world;`).then((r) => r.text());
  check('gtartm.php setData (web page)', sent === 'Sent!', sent);
  const rtmData = await requestURL(`gtartm.php?retreiveData=true&Key=${key}`);
  check('gtartm.php retreiveData', rtmData === '1;hello world;\n', JSON.stringify(rtmData));

  const msg = Buffer.from('hi from the sim?').toString('base64'); // base64 with + / = sent unescaped like the SPRX
  const chat = await requestURL(`chat/chat.php?function=rw&key=${key}&psn=Tester_1&message=${msg}`);
  const lines = chat.split('\n').filter((l) => l.length);
  check('chat/chat.php rw', lines.length === 5 && lines.includes('hi from the sim? :Tester_1'), JSON.stringify(chat.slice(-80)));

  const prop = await requestURL('res/getprop.php?hash=162031196');
  check('res/getprop.php', prop === 'cj_cone', prop);

  const sprxSize = await requestURL(`res/downloadsprx.php?key=${key}&filesize`);
  check('res/downloadsprx.php filesize', /^\d+ F$/.test(sprxSize) || sprxSize === 'PARADISE_ERROR', sprxSize);

  console.log(failures ? `\n${failures} check(s) failed` : '\nAll checks passed');
  process.exitCode = failures ? 1 : 0;
}

main().catch((err) => {
  console.error(err);
  process.exitCode = 1;
});
