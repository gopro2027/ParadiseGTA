// GET /res/downloadasset2.php?key=<key>&filename=<name>.dds
// Textures injected straight into game memory: "BEGINDATA\n" followed by the file without its 0x80 byte DDS header.
import { readFile } from 'node:fs/promises';
import { join, basename } from 'node:path';
import { getQuery, sendText, sendBinary } from '../lib/http.js';

const DDS_HEADER_SIZE = 0x80;

export default async function handler(req, res) {
  const name = basename(getQuery(req).filename || '');
  if (!/^[A-Za-z0-9_.-]+\.dds$/.test(name)) return sendText(res, 'PARADISE_ERROR');
  let file;
  try {
    file = await readFile(join(process.cwd(), 'public', 'files', name));
  } catch {
    return sendText(res, 'PARADISE_ERROR');
  }
  sendBinary(res, Buffer.concat([Buffer.from('BEGINDATA\n'), file.subarray(DDS_HEADER_SIZE)]));
}
