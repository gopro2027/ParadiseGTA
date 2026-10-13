// Web RTM relay between the RTM web page and the menu.
//   gtartm.php?generateRTMKey=true&Key=<key>        (menu)  new 4 character RTM key for this product key
//   gtartm.php?retreiveData=true&Key=<key>          (menu)  queued commands, then clears them
//   gtartm.php?setData=true&RTMKey=<rtm>&RTMData=.. (web)   queues a command for the menu
// Command format: functionid;data;data;...;\n  (max 200 characters queued)
import { getStore } from '../lib/store.js';
import { getKey, isUsable, updateKey, setRtmKey, keyForRtmKey } from '../lib/keys.js';
import { getQuery, sendText, sanitize } from '../lib/http.js';

const MAX_DATA = 200;
const MENU_ONLINE_SECONDS = 60;

export default async function handler(req, res) {
  const q = getQuery(req);
  const store = getStore();
  const now = Math.floor(Date.now() / 1000);

  if (q.retreiveData !== undefined && q.Key !== undefined) {
    const record = await getKey(store, q.Key);
    if (!isUsable(record)) return sendText(res, '');
    await updateKey(store, q.Key, { rtmLastRetrieve: now, rtmData: '' });
    return sendText(res, record.rtmData || '');
  }

  if (q.generateRTMKey !== undefined && q.Key !== undefined) {
    const record = await getKey(store, q.Key);
    if (!isUsable(record)) return sendText(res, '!');
    return sendText(res, await setRtmKey(store, q.Key, record));
  }

  if (q.setData !== undefined && q.RTMKey !== undefined && q.RTMData !== undefined) {
    const key = await keyForRtmKey(store, q.RTMKey);
    const record = key ? await getKey(store, key) : null;
    if (!isUsable(record) || record.rtmKey !== q.RTMKey) return sendText(res, 'Not valid Key!');
    if (now - Number(record.rtmLastRetrieve || 0) >= MENU_ONLINE_SECONDS) return sendText(res, 'Not valid Key!');
    const data = sanitize(q.RTMData).replace(/,/g, ' ');
    const queued = (record.rtmData || '') + data + '\n';
    if (queued.length > MAX_DATA) return sendText(res, 'Too long!');
    await updateKey(store, key, { rtmData: queued });
    return sendText(res, 'Sent!');
  }

  sendText(res, '');
}
