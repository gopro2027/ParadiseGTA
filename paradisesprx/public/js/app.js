// The site moved to paradisesprx.download. vercel.json redirects the old domain too, but Vercel serves
// static pages before that redirect runs, so pages opened on the old domain move over here.
if (location.hostname === 'paradisesprx.vercel.app') {
  location.replace('https://paradisesprx.download' + location.pathname + location.search + location.hash);
}

// Same particles.js settings the original paradisesprx.net used
if (window.particlesJS && !window.matchMedia('(prefers-reduced-motion: reduce)').matches) {
  particlesJS('particles-js', {
    particles: {
      number: { value: 80, density: { enable: true, value_area: 800 } },
      color: { value: '#ffffff' },
      shape: { type: 'circle', stroke: { width: 0, color: '#000000' } },
      opacity: { value: 0.5, random: false },
      size: { value: 5, random: true },
      line_linked: { enable: true, distance: 150, color: '#ffffff', opacity: 0.4, width: 1 },
      move: { enable: true, speed: 6, direction: 'none', random: false, straight: false, out_mode: 'out' },
    },
    interactivity: {
      detect_on: 'window',
      events: { onhover: { enable: true, mode: 'repulse' }, onclick: { enable: true, mode: 'push' }, resize: true },
      modes: { repulse: { distance: 200 }, push: { particles_nb: 4 } },
    },
    retina_detect: true,
  });
}
