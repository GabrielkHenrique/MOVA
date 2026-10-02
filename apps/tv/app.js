const ws = new WebSocket('ws://localhost:8080');

const plazaView       = document.getElementById('plaza-view');
const gameView        = document.getElementById('game-view');
const resultsView     = document.getElementById('results-view');
const scoreEl         = document.getElementById('score');
const timerEl         = document.getElementById('timer');
const feedbackOverlay = document.getElementById('feedback-overlay');

// Results screen elements
const resScore  = document.getElementById('res-score');
const resHits   = document.getElementById('res-hits');
const resMisses = document.getElementById('res-misses');
const resRt     = document.getElementById('res-rt');
const resStars  = document.getElementById('results-stars');
const resTagline = document.getElementById('results-tagline');

// Map zone name → DOM element
const zoneEls = {
  front:  document.querySelector('.zone-front'),
  back:   document.querySelector('.zone-back'),
  left:   document.querySelector('.zone-left'),
  right:  document.querySelector('.zone-right'),
  center: document.querySelector('.zone-center'),
};

ws.onopen  = () => console.log('[TV] Conectado ao motor');
ws.onclose = () => console.log('[TV] Desconectado do motor');

ws.onmessage = (event) => {
  try {
    const msg = JSON.parse(event.data);
    if (msg.type === 'STATE_CHANGE')     handleStateChange(msg.state);
    if (msg.type === 'STATE_UPDATE')     handleStateUpdate(msg.gameState);
    if (msg.type === 'EVT_PLAY_FEEDBACK') handleFeedback(msg);
    if (msg.type === 'EVT_RESULTS_READY') handleResults(msg.metrics);
  } catch (err) {
    console.error('[TV] Erro:', err);
  }
};

function handleStateChange(state) {
  if (state === 'ACTIVITY_RUNNING' || state === 'ACTIVITY_INITIALIZING') {
    plazaView.classList.remove('active');
    resultsView.classList.remove('active');
    gameView.classList.add('active');
  } else if (state === 'WORLD_EXPLORATION' || state === 'IDLE') {
    gameView.classList.remove('active');
    resultsView.classList.remove('active');
    plazaView.classList.add('active');
    clearAllZones();
  }
}

let lastTickTime = -1;
function handleStateUpdate(gameState) {
  if (!gameState) return;

  // Atualiza placar e timer
  if (scoreEl && gameState.score !== undefined) scoreEl.innerText = gameState.score;
  if (timerEl && gameState.timeRemaining !== undefined) {
    timerEl.innerText = gameState.timeRemaining + 's';
    if (gameState.timeRemaining <= 10 && gameState.timeRemaining > 0) {
      if (lastTickTime !== gameState.timeRemaining) {
        lastTickTime = gameState.timeRemaining;
        if (typeof playTick === 'function') playTick();
      }
    } else {
      lastTickTime = -1;
    }
  }

  // ── ILUMINA AS ZONAS ATIVAS ──────────────────────────────────
  clearAllZones();
  if (Array.isArray(gameState.activeTargets)) {
    gameState.activeTargets.forEach(target => {
      const el = zoneEls[target.zone];
      if (el) {
        el.classList.add('active');
        if (target.type === 'BOMB') el.classList.add('target-bomb');
        if (target.type === 'GOLDEN') el.classList.add('target-golden');
      }
    });
  }
}

function clearAllZones() {
  Object.values(zoneEls).forEach(el => { 
    if (el) {
      el.classList.remove('active', 'target-bomb', 'target-golden');
    }
  });
}

function handleFeedback(msg) {
  const el = msg.zone ? zoneEls[msg.zone] : null;

  if (msg.feedback === 'POP') {
    if (typeof playPop === 'function') playPop();
    if (el) { el.classList.add('popped'); setTimeout(() => el.classList.remove('popped'), 400); }
    showBurst('💥 POP!', '#ff4e1a');
  } else if (msg.feedback === 'POP_GOLDEN') {
    if (typeof playGoldenPop === 'function') playGoldenPop();
    if (el) { el.classList.add('popped-golden'); setTimeout(() => el.classList.remove('popped-golden'), 400); }
    showBurst('⭐ INCRÍVEL!', '#ffca28');
  } else if (msg.feedback === 'STEP_BOMB') {
    if (typeof playBomb === 'function') playBomb();
    if (el) { el.classList.add('popped-bomb'); setTimeout(() => el.classList.remove('popped-bomb'), 400); }
    showBurst('💣 NÃO!', '#d32f2f');
  } else if (msg.feedback === 'MISS') {
    if (typeof playMiss === 'function') playMiss();
    showBurst('✗ Errou!', '#888');
  } else if (msg.feedback === 'STEP_EMPTY') {
    showBurst('Zona vazia!', '#ffa500');
  }
}

function handleResults(metrics) {
  clearAllZones();

  // Populate stats
  const hits      = metrics.hits   ?? metrics.pops   ?? 0;
  const misses    = metrics.misses ?? metrics.errors  ?? 0;
  const total     = hits + misses || 1;
  const hitRate   = hits / total;
  const avgRt     = metrics.avgReactionTime ?? metrics.averageReactionTime ?? null;

  resScore.innerText  = metrics.finalScore ?? 0;
  resHits.innerText   = hits;
  resMisses.innerText = misses;
  resRt.innerText     = avgRt !== null ? Math.round(avgRt) + ' ms' : '— ms';

  // Stars rating
  const starCount = hitRate > 0.8 ? 3 : hitRate > 0.5 ? 2 : 1;
  const taglines  = ['Continue treinando! 💪', 'Bom trabalho! 👏', 'Incrível! Campeão! 🏆'];
  resTagline.innerText = taglines[starCount - 1];

  resStars.innerHTML = '';
  for (let i = 0; i < 3; i++) {
    const star = document.createElement('span');
    star.className = 'results-star' + (i < starCount ? ' earned' : ' empty');
    star.style.animationDelay = (i * 0.25) + 's';
    star.innerText = '⭐';
    resStars.appendChild(star);
  }

  // Switch to results view
  gameView.classList.remove('active');
  plazaView.classList.remove('active');
  resultsView.classList.add('active');
}

function showBurst(text, color) {
  const el = document.createElement('div');
  el.className = 'feedback-burst';
  el.innerText = text;
  el.style.color = color;
  feedbackOverlay.appendChild(el);
  setTimeout(() => el.remove(), 1200);
}

// ── SOUND SYSTEM (Web Audio API — zero file dependencies) ────────────────────
const AudioCtx = window.AudioContext || window.webkitAudioContext;
let audioCtx = null;

function getAudioCtx() {
  if (!audioCtx) audioCtx = new AudioCtx();
  return audioCtx;
}

function playPop() {
  const ctx = getAudioCtx();
  const o = ctx.createOscillator();
  const g = ctx.createGain();
  o.connect(g); g.connect(ctx.destination);
  o.frequency.setValueAtTime(600, ctx.currentTime);
  o.frequency.exponentialRampToValueAtTime(200, ctx.currentTime + 0.15);
  g.gain.setValueAtTime(0.4, ctx.currentTime);
  g.gain.exponentialRampToValueAtTime(0.001, ctx.currentTime + 0.18);
  o.start(); o.stop(ctx.currentTime + 0.18);
}

function playGoldenPop() {
  const ctx = getAudioCtx();
  [0, 0.06, 0.12].forEach((delay, i) => {
    const o = ctx.createOscillator();
    const g = ctx.createGain();
    o.connect(g); g.connect(ctx.destination);
    o.frequency.value = [880, 1100, 1320][i];
    g.gain.setValueAtTime(0.3, ctx.currentTime + delay);
    g.gain.exponentialRampToValueAtTime(0.001, ctx.currentTime + delay + 0.2);
    o.start(ctx.currentTime + delay);
    o.stop(ctx.currentTime + delay + 0.2);
  });
}

function playBomb() {
  const ctx = getAudioCtx();
  const o = ctx.createOscillator();
  const g = ctx.createGain();
  o.type = 'sawtooth';
  o.connect(g); g.connect(ctx.destination);
  o.frequency.setValueAtTime(180, ctx.currentTime);
  o.frequency.exponentialRampToValueAtTime(60, ctx.currentTime + 0.3);
  g.gain.setValueAtTime(0.5, ctx.currentTime);
  g.gain.exponentialRampToValueAtTime(0.001, ctx.currentTime + 0.35);
  o.start(); o.stop(ctx.currentTime + 0.35);
}

function playMiss() {
  const ctx = getAudioCtx();
  const o = ctx.createOscillator();
  const g = ctx.createGain();
  o.type = 'triangle';
  o.connect(g); g.connect(ctx.destination);
  o.frequency.setValueAtTime(300, ctx.currentTime);
  o.frequency.exponentialRampToValueAtTime(150, ctx.currentTime + 0.2);
  g.gain.setValueAtTime(0.25, ctx.currentTime);
  g.gain.exponentialRampToValueAtTime(0.001, ctx.currentTime + 0.25);
  o.start(); o.stop(ctx.currentTime + 0.25);
}

function playTick() {
  const ctx = getAudioCtx();
  const o = ctx.createOscillator();
  const g = ctx.createGain();
  o.type = 'sine';
  o.connect(g); g.connect(ctx.destination);
  o.frequency.setValueAtTime(1000, ctx.currentTime);
  g.gain.setValueAtTime(0.1, ctx.currentTime);
  g.gain.exponentialRampToValueAtTime(0.001, ctx.currentTime + 0.05);
  o.start(); o.stop(ctx.currentTime + 0.05);
}
