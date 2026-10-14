// Key/value storage. Uses Upstash Redis when its env vars are present (added automatically by the
// Vercel Marketplace integration), otherwise an in-memory store for local development and tests.
import { Redis } from '@upstash/redis';

class MemoryStore {
  constructor() {
    this.data = new Map();
    this.expiry = new Map();
  }

  _alive(key) {
    const exp = this.expiry.get(key);
    if (exp !== undefined && exp <= Date.now()) {
      this.data.delete(key);
      this.expiry.delete(key);
    }
    return this.data.has(key);
  }

  async hgetall(key) {
    if (!this._alive(key)) return null;
    return { ...this.data.get(key) };
  }

  async hset(key, fields) {
    const current = this._alive(key) ? this.data.get(key) : {};
    for (const [k, v] of Object.entries(fields)) current[k] = String(v);
    this.data.set(key, current);
  }

  async exists(key) {
    return this._alive(key) ? 1 : 0;
  }

  async get(key) {
    return this._alive(key) ? this.data.get(key) : null;
  }

  async set(key, value, opts = {}) {
    if (opts.nx && this._alive(key)) return null;
    this.data.set(key, String(value));
    if (opts.ex) this.expiry.set(key, Date.now() + opts.ex * 1000);
    else this.expiry.delete(key);
    return 'OK';
  }

  async del(key) {
    this.data.delete(key);
    this.expiry.delete(key);
  }

  async incr(key) {
    const next = Number(this._alive(key) ? this.data.get(key) : 0) + 1;
    this.data.set(key, String(next));
    return next;
  }

  async expire(key, seconds) {
    if (this._alive(key)) this.expiry.set(key, Date.now() + seconds * 1000);
  }

  async ttl(key) {
    if (!this._alive(key)) return -2;
    const exp = this.expiry.get(key);
    return exp === undefined ? -1 : Math.ceil((exp - Date.now()) / 1000);
  }

  async rpush(key, value) {
    const list = this._alive(key) ? this.data.get(key) : [];
    list.push(String(value));
    this.data.set(key, list);
  }

  async ltrim(key, start, stop) {
    if (!this._alive(key)) return;
    const list = this.data.get(key);
    const len = list.length;
    const s = start < 0 ? Math.max(len + start, 0) : start;
    const e = stop < 0 ? len + stop : stop;
    this.data.set(key, list.slice(s, e + 1));
  }

  async lrange(key, start, stop) {
    if (!this._alive(key)) return [];
    const list = this.data.get(key);
    const len = list.length;
    const s = start < 0 ? Math.max(len + start, 0) : start;
    const e = stop < 0 ? len + stop : stop;
    return list.slice(s, e + 1);
  }
}

class RedisStore {
  constructor(url, token) {
    // automaticDeserialization off so every value comes back as the string we stored
    this.redis = new Redis({ url, token, automaticDeserialization: false });
  }

  async hgetall(key) {
    const res = await this.redis.hgetall(key);
    return res && Object.keys(res).length ? res : null;
  }

  hset(key, fields) {
    return this.redis.hset(key, fields);
  }

  exists(key) {
    return this.redis.exists(key);
  }

  get(key) {
    return this.redis.get(key);
  }

  set(key, value, opts = {}) {
    return this.redis.set(key, value, opts);
  }

  del(key) {
    return this.redis.del(key);
  }

  incr(key) {
    return this.redis.incr(key);
  }

  expire(key, seconds) {
    return this.redis.expire(key, seconds);
  }

  ttl(key) {
    return this.redis.ttl(key);
  }

  rpush(key, value) {
    return this.redis.rpush(key, value);
  }

  ltrim(key, start, stop) {
    return this.redis.ltrim(key, start, stop);
  }

  lrange(key, start, stop) {
    return this.redis.lrange(key, start, stop);
  }
}

let store;

export function getStore() {
  if (!store) {
    const url = process.env.UPSTASH_REDIS_REST_URL || process.env.KV_REST_API_URL;
    const token = process.env.UPSTASH_REDIS_REST_TOKEN || process.env.KV_REST_API_TOKEN;
    if (url && token) {
      store = new RedisStore(url, token);
    } else {
      if (process.env.VERCEL_ENV === 'production') {
        console.warn('No Upstash Redis credentials found, using in-memory storage. Keys will not persist!');
      }
      store = new MemoryStore();
    }
  }
  return store;
}

export function storeKind() {
  return getStore() instanceof RedisStore ? 'redis' : 'memory';
}

// tests swap in a fresh store
export function setStore(s) {
  store = s;
}

export { MemoryStore };
