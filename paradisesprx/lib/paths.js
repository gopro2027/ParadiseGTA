// Paths relative to the project folder. On Vercel the working directory is not the project root
// (the project uses a root directory inside the repo), so resolve from this file instead of process.cwd().
import { fileURLToPath } from 'node:url';
import { join } from 'node:path';

export const PROJECT_ROOT = fileURLToPath(new URL('..', import.meta.url));

export const projectPath = (...parts) => join(PROJECT_ROOT, ...parts);
