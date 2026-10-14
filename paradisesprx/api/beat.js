// GET /beat.php?k=<key>&psn=<psn name>
// Heartbeat sent every 60 seconds while online. The response is a command for the menu:
//   NONE           nothing to do
//   PRINT:message  show a message on screen
import { getStore } from '../lib/store.js';
import { getKey, updateKey } from '../lib/keys.js';
import { getQuery, sendText } from '../lib/http.js';

export default async function handler(req, res) {
  const q = getQuery(req);
  if (q.k !== undefined && q.psn !== undefined) {
    const store = getStore();
    const record = await getKey(store, q.k);
    if (record) {
      let psn = q.psn.slice(0, 20);
      if (!/^[A-Za-z0-9_-]+$/.test(psn)) psn = 'NO_PSN';
      const now = Math.floor(Date.now() / 1000);
      await updateKey(store, q.k, { psn, psnTime: now, beatTime: now });
    }
  }
  const message = process.env.BEAT_MESSAGE;
  sendText(res, message ? 'PRINT:' + message : 'NONE');
}
