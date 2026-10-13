// Local stand-in for Vercel: applies the rewrites/headers from vercel.json, runs the api/ handlers and
// serves public/. Uses the in-memory store unless Upstash env vars are set.
//   node scripts/dev-server.mjs [port]
import http from 'node:http';
import { readFileSync, statSync, createReadStream } from 'node:fs';
import { join, extname, dirname } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';

const root = join(dirname(fileURLToPath(import.meta.url)), '..');
process.chdir(root);
const config = JSON.parse(readFileSync(join(root, 'vercel.json'), 'utf8'));
const port = Number(process.argv[2] || process.env.PORT || 3000);

const TYPES = {
  '.html': 'text/html; charset=utf-8',
  '.css': 'text/css; charset=utf-8',
  '.js': 'text/javascript; charset=utf-8',
  '.svg': 'image/svg+xml',
  '.png': 'image/png',
  '.ico': 'image/x-icon',
  '.txt': 'text/plain; charset=utf-8',
};

function matchSource(source, path) {
  const escape = (s) => s.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
  return new RegExp('^' + source.split('(.*)').map(escape).join('(.*)') + '$').test(path);
}

function rewrite(path) {
  for (const r of config.rewrites || []) if (r.source === path) return r.destination;
  return path;
}

function extraHeaders(path) {
  const out = {};
  for (const h of config.headers || []) {
    if (matchSource(h.source, path)) for (const { key, value } of h.headers) out[key] = value;
  }
  return out;
}

const handlers = new Map();
async function apiHandler(name) {
  if (!handlers.has(name)) {
    const mod = await import(pathToFileURL(join(root, 'api', name + '.js')).href);
    handlers.set(name, mod.default);
  }
  return handlers.get(name);
}

function serveStatic(req, res, path) {
  let file = join(root, 'public', decodeURIComponent(path));
  if (!file.startsWith(join(root, 'public'))) return notFound(res);
  let st;
  try {
    st = statSync(file);
    if (st.isDirectory()) {
      file = join(file, 'index.html');
      st = statSync(file);
    }
  } catch {
    try {
      file = file + '.html'; // cleanUrls
      st = statSync(file);
    } catch {
      return notFound(res);
    }
  }
  const headers = {
    'Content-Type': TYPES[extname(file)] || 'application/octet-stream',
    'Content-Length': String(st.size),
    ...extraHeaders(path),
  };
  res.writeHead(200, headers);
  if (req.method === 'HEAD') return res.end();
  createReadStream(file).pipe(res);
}

function notFound(res) {
  res.writeHead(404, { 'Content-Type': 'text/plain' });
  res.end('Not found');
}

const server = http.createServer(async (req, res) => {
  const [rawPath] = req.url.split('?');
  const path = rewrite(rawPath);
  try {
    if (path.startsWith('/api/')) {
      const handler = await apiHandler(path.slice(5));
      await handler(req, res);
    } else {
      serveStatic(req, res, path);
    }
  } catch (err) {
    if (err.code === 'ERR_MODULE_NOT_FOUND') return notFound(res);
    console.error(err);
    if (!res.headersSent) res.writeHead(500, { 'Content-Type': 'text/plain' });
    res.end('Server error');
  }
  console.log(`${req.method} ${req.url} -> ${res.statusCode}`);
});

server.listen(port, () => console.log(`paradisesprx dev server on http://localhost:${port}`));
