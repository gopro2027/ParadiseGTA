// GET /res/downloadsprx.php?key=<key>&filesize   ->  "<size> F"
// Used by the SPRX auto updater (AUTO_UPDATE in prx.cpp). The file itself is served statically
// from /files/ParadiseGTA.sprx.
import { statSync } from 'node:fs';
import { join } from 'node:path';
import { getQuery, sendText } from '../lib/http.js';

export default function handler(req, res) {
  const q = getQuery(req);
  if (q.filesize === undefined) return sendText(res, 'PARADISE_ERROR');
  try {
    const size = statSync(join(process.cwd(), 'public', 'files', 'ParadiseGTA.sprx')).size;
    sendText(res, size + ' F');
  } catch {
    sendText(res, 'PARADISE_ERROR');
  }
}
