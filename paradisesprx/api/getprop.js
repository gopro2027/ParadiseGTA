// GET /res/getprop.php?hash=<signed int>   object name for a model hash (forge menu)
import { readFileSync } from 'node:fs';
import { getQuery, sendText } from '../lib/http.js';
import { projectPath } from '../lib/paths.js';

let byHash;
let lines;

function load() {
  if (byHash) return;
  const text = readFileSync(projectPath('data', 'objects.txt'), 'utf8');
  byHash = new Map();
  lines = text.split(/\r?\n/);
  for (const line of lines) {
    const eq = line.indexOf('=');
    if (eq > 0) {
      const hash = line.slice(eq + 1).trim();
      if (!byHash.has(hash)) byHash.set(hash, line.slice(0, eq));
    }
  }
}

export default function handler(req, res) {
  const hash = (getQuery(req).hash || '').trim();
  load();
  let name = hash ? byHash.get(hash) : undefined;
  if (name === undefined && hash) {
    // the old server matched any line containing the text
    const line = lines.find((l) => l.includes(hash));
    if (line) name = line.split('=')[0];
  }
  sendText(res, name ?? 'Unknown Prop: ' + hash.slice(0, 20));
}
