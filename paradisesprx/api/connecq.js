// GET /connecq.php?sesh=<key>&data=<mac>&ver=5
// Sends the 60 values the SPRX needs to run. The first request from a console binds the key to it.
import { getStore } from '../lib/store.js';
import { getKey, normalizeMac, bindMac } from '../lib/keys.js';
import { offsetValues, formatField, OFFSETS } from '../lib/offsets.js';
import { getQuery, sendText } from '../lib/http.js';

export const PROTOCOL_VERSION = '5';

export default async function handler(req, res) {
  const q = getQuery(req);
  if (q.sesh === undefined || q.data === undefined || q.ver !== PROTOCOL_VERSION) {
    return sendText(res, '000');
  }
  const store = getStore();
  const record = await getKey(store, q.sesh);
  let ok = false;
  if (record) {
    // a different console gets zeros; keyStatus.php tells the user why
    ok = await bindMac(store, q.sesh, record, normalizeMac(q.data));
  }
  const values = ok ? offsetValues({ dev: record.dev === '1' }) : OFFSETS.map(() => 0);
  sendText(res, 'BEGINDATA\n' + values.map(formatField).join(''));
}
