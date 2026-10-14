// Cloudflare Turnstile (captcha) for the free key page.

// Cloudflare's documented test keys, which always pass. Only used for local development when no keys
// are configured; deployed environments must set TURNSTILE_SITE_KEY / TURNSTILE_SECRET_KEY.
const TEST_SITE_KEY = '1x00000000000000000000AA';
const TEST_SECRET_KEY = '1x0000000000000000000000000000000AA';

export function turnstileConfig() {
  const siteKey = process.env.TURNSTILE_SITE_KEY;
  const secret = process.env.TURNSTILE_SECRET_KEY;
  if (siteKey && secret) return { siteKey, secret };
  if (process.env.VERCEL_ENV) return null;
  return { siteKey: TEST_SITE_KEY, secret: TEST_SECRET_KEY };
}

export async function verifyTurnstile(token, secret, ip) {
  if (typeof token !== 'string' || !token || token.length > 2048) return false;
  const body = new URLSearchParams({ secret, response: token });
  if (ip && ip !== 'unknown') body.set('remoteip', ip);
  try {
    const res = await fetch('https://challenges.cloudflare.com/turnstile/v0/siteverify', { method: 'POST', body });
    const data = await res.json();
    return data.success === true;
  } catch {
    return false;
  }
}
