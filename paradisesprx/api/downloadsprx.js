// GET /res/downloadsprx.php?key=<key>&filesize   ->  "<size> F"
// Used by the SPRX auto updater (AUTO_UPDATE in prx.cpp). The file itself is served statically
// from /files/ParadiseGTA.sprx.
import { statSync } from 'node:fs';
import { getQuery, sendText } from '../lib/http.js';
import { projectPath } from '../lib/paths.js';

export default function handler(req, res) {
  const q = getQuery(req);
  if (q.filesize === undefined) return sendText(res, 'PARADISE_ERROR');
  try {
    const size = statSync(projectPath('public', 'files', 'ParadiseGTA.sprx')).size;
    sendText(res, size + ' F');
  } catch {
    sendText(res, 'PARADISE_ERROR');
  }
}
