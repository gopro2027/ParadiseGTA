// Downloads every file the menu fetches the same way the SPRX does (raw HTTP/1.0, Content-Length read
// case-insensitively, body written until Content-Length bytes) and compares it with public/files (or, for
// the files in the GitHub release, with their SHA-256).
//   node scripts/download-check.mjs --host paradisesprx.download
import net from 'node:net';
import { createHash } from 'node:crypto';
import { readFileSync } from 'node:fs';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const root = join(dirname(fileURLToPath(import.meta.url)), '..');
const hostArg = process.argv[process.argv.indexOf('--host') + 1] || 'localhost:3000';
const [hostname, portText] = hostArg.split(':');
const port = Number(portText || 80);
const hostHeader = port === 80 ? hostname : `${hostname}:${port}`;

// Served by the Worker from the GitHub release files-v1 (not in public/files), checked by SHA-256
const RELEASE_SHA256 = {
  'Paradise.rpf': '35d86b6c9f6f50a28867388b8e85a809340095be97c24c7bcaaa6098495a80df',
  'BLJM.rpf': 'e9eabdb1f1dc2decdecd2db1b9bf07e205a46a2bc138e4219f22f28f22e5ffc8',
  'eboot/dex/EBOOT.BIN': '877f861b04ca49f388f458c0eb6275c23cbf1a67c71b894aba987d77e98ae761',
  'eboot/hen-a/EBOOT.BIN': '6d3f278b747cdad7fc6ccb0b14df5a87cab3db1968f1387fc3117e1d9b83852c',
  'eboot/hen-b/EBOOT.BIN': 'bc5d049b3af0f6f740667814b178bc9cc8d81d51be6307f622a9b4121c216d6e',
  'eboot/hen-c/EBOOT.BIN': '1500c19fd123176947f8787312763d7f3d6882521997c0714f897511302e1a53',
};

// the files the menu downloads with downloadFileFromDownloadFolder() (plus the EBOOTs the install
// wizard has webMAN download), and what for
const FILES = [
  ['Paradise.rpf', 'Install Paradise Update.RPF (must be 66447360 bytes)'],
  ['BLJM.rpf', 'Spoof To JP Servers (must be 90209280 bytes)'],
  ['eboot/dex/EBOOT.BIN', 'install wizard, DEX'],
  ['eboot/hen-a/EBOOT.BIN', 'install wizard, HEN/CEX A'],
  ['eboot/hen-b/EBOOT.BIN', 'install wizard, HEN/CEX B'],
  ['eboot/hen-c/EBOOT.BIN', 'install wizard, HEN/CEX C'],
  ['script_vary.rpf', 'Install Paradise Script Menus'],
  ['tsunami_water.xml', 'Tsunami mod'],
  ['rock_menu2.csc_paradisemicro', 'script menu injected on startup'],
  ['rock_menu2.csc_vcahax', 'RCE menu option'],
  ['rock_menu2.csc_apiiintense', 'RCE menu option'],
  ['background.dds', 'menu background'],
  ['default_settings.xml', 'settings file'],
  ['gta_v_blus_addresses_narray.dat', 'native table'],
  ['gta_v_blus_addresses_oarray.dat', 'native table'],
  ['strings.txt', 'menu strings, checked every start'],
];

function download(path) {
  return new Promise((resolve, reject) => {
    const sock = net.connect(port, hostname);
    let header = Buffer.alloc(0);
    let length = -1;
    let body = null;
    let got = 0;
    const started = Date.now();
    sock.setTimeout(120000, () => sock.destroy(new Error('timeout')));
    sock.on('connect', () => sock.write(`GET /${path} HTTP/1.0\r\nHOST: ${hostHeader}\r\nUser-Agent: paradise_semjases\r\nConnection: close\r\n\r\n`));
    sock.on('data', (chunk) => {
      if (body === null) {
        header = Buffer.concat([header, chunk]);
        const end = header.indexOf('\r\n\r\n');
        if (end === -1) return;
        const head = header.subarray(0, end).toString('latin1');
        const m = /content-length:\s*(\d+)/i.exec(head) || /content-size:\s*(\d+)/i.exec(head);
        if (!m) return reject(new Error('no Content-Length: ' + head.split('\r\n')[0]));
        length = Number(m[1]);
        body = Buffer.alloc(length);
        chunk = header.subarray(end + 4);
      }
      const n = Math.min(chunk.length, length - got);
      chunk.copy(body, got, 0, n);
      got += n;
      if (got >= length) {
        sock.destroy();
        resolve({ body, seconds: (Date.now() - started) / 1000 });
      }
    });
    sock.on('end', () => (got < length ? reject(new Error(`connection closed at ${got}/${length} bytes`)) : null));
    sock.on('error', reject);
  });
}

const sha = (b) => createHash('sha256').update(b).digest('hex');
let failed = 0;
for (const [name, what] of FILES) {
  try {
    const { body, seconds } = await download(`files/${name}`);
    const expected = RELEASE_SHA256[name] || sha(readFileSync(join(root, 'public', 'files', name)));
    const ok = sha(body) === expected;
    if (!ok) failed++;
    console.log(`${ok ? 'PASS' : 'FAIL'}  ${name}  ${body.length} bytes in ${seconds.toFixed(1)}s  (${what})`);
  } catch (err) {
    failed++;
    console.log(`FAIL  ${name}  ${err.message}  (${what})`);
  }
}
console.log(failed ? `\n${failed} download(s) failed` : '\nAll downloads byte-identical');
process.exitCode = failed ? 1 : 0;
