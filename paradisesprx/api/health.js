// GET /api/health -> { store: "redis" | "memory", ok } (checks the database round trip)
import { getStore, storeKind } from '../lib/store.js';
import { sendJson } from '../lib/http.js';

export default async function handler(req, res) {
  const store = getStore();
  const value = String(Date.now());
  let ok = false;
  try {
    await store.set('health', value, { ex: 60 });
    ok = (await store.get('health')) === value;
  } catch {
    ok = false;
  }
  sendJson(res, { store: storeKind(), ok }, ok ? 200 : 503);
}
