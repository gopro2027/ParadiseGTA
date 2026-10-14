// GET /connecq.php?sesh=<key>&data=<mac>&ver=5
// Sends the 60 values the SPRX needs to run. Any console can use any valid key; the MAC the SPRX
// sends in `data` is ignored.
import { getStore } from '../lib/store.js';
import { getKey } from '../lib/keys.js';
import { offsetValues, formatField, OFFSETS } from '../lib/offsets.js';
import { getQuery, sendText } from '../lib/http.js';

export const PROTOCOL_VERSION = '5';

export default async function handler(req, res) {
  const q = getQuery(req);
  if (q.sesh === undefined || q.ver !== PROTOCOL_VERSION) return sendText(res, '000');
  const record = await getKey(getStore(), q.sesh);
  // unknown keys get zeros; keyStatus.php tells the user why
  const values = record ? offsetValues({ dev: record.dev === '1' }) : OFFSETS.map(() => 0);
  sendText(res, 'BEGINDATA\n' + values.map(formatField).join(''));
}
