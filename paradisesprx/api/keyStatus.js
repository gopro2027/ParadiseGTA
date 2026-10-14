// GET /keyStatus.php?key=<key>&id=<mac>
// Final login check the SPRX shows to the user. Anything other than VALIDVALIDVALID is displayed as-is.
import { getStore } from '../lib/store.js';
import { getKey, normalizeMac } from '../lib/keys.js';
import { getQuery, sendText } from '../lib/http.js';

const WEBSITE = process.env.PARADISE_WEBSITE || 'paradisesprx.vercel.app';

export default async function handler(req, res) {
  const q = getQuery(req);
  if (q.id === undefined || q.key === undefined) {
    // id2 (PSN name hash) reports from older builds are accepted and ignored
    return sendText(res, 'LOGIN FAILED\nNo info');
  }
  const record = await getKey(getStore(), q.key);
  if (!record) {
    return sendText(res,
      'LOGIN FAILED\nInvalid key!\nKey:' + q.key.slice(0, 64) +
      '\nIf this is not your key, check these files for the wrong key and delete it:\n' +
      'dev_hdd0/tmp/gopro_2027/Key.txt\ndev_hdd0/tmp/gopro_2027/key.txt\ndev_hdd0/tmp/Key.txt\ndev_hdd0/tmp/key.txt\n' +
      'Get a free key at ' + WEBSITE);
  }
  if (normalizeMac(q.id) !== record.mac) {
    return sendText(res,
      'LOGIN FAILED\nThis console is not registered on the server!\n' +
      'Reset the console for your key or get a new free key at ' + WEBSITE);
  }
  sendText(res, 'VALIDVALIDVALID');
}
