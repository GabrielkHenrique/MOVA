const ws = new WebSocket('ws://localhost:8080');

// DOM Elements
const connectionStatus = document.getElementById('connection-status');
const btnStart  = document.getElementById('btn-start');
const btnPause  = document.getElementById('btn-pause');
const btnEnd    = document.getElementById('btn-end');
const valStatus = document.getElementById('val-status');
const valScore  = document.getElementById('val-score');
const valMedals = document.getElementById('val-medals');

// Hardware status badge
const hwBadge = document.getElementById('hw-badge');

// Patient nickname
const patientNickname = document.getElementById('patient-nickname');

// Results section
const resultsSection  = document.getElementById('results-section');
const panelScore      = document.getElementById('panel-score');
const panelHits       = document.getElementById('panel-hits');
const panelMisses     = document.getElementById('panel-misses');
const panelRounds     = document.getElementById('panel-rounds');
const panelRt         = document.getElementById('panel-rt');
const panelDuration   = document.getElementById('panel-duration');
const panelPerf       = document.getElementById('panel-perf');
const perfBarFill     = document.getElementById('perf-bar-fill');
const perfBarLabel    = document.getElementById('perf-bar-label');

// Print report elements
const prPatient  = document.getElementById('pr-patient');
const prDate     = document.getElementById('pr-date');
const prScore    = document.getElementById('pr-score');
const prHits     = document.getElementById('pr-hits');
const prMisses   = document.getElementById('pr-misses');
const prRounds   = document.getElementById('pr-rounds');
const prRt       = document.getElementById('pr-rt');
const prDuration = document.getElementById('pr-duration');

// ── Hardware status configuration ──
const HW_STATUS_CONFIG = {
  SIMULATOR:          { color: '#3f51b5', text: 'Simulador ativo' },
  ESP32_CONNECTING:   { color: '#ff8f00', text: 'ESP32 conectando…' },
  ESP32_CONNECTED:    { color: '#2e7d32', text: '● ESP32 conectado' },
  ESP32_DISCONNECTED: { color: '#c62828', text: '✗ ESP32 desconectado' },
};

function handleHardwareStatus(status) {
  const cfg = HW_STATUS_CONFIG[status] ?? HW_STATUS_CONFIG.SIMULATOR;
  hwBadge.textContent    = cfg.text;
  hwBadge.style.color    = cfg.color;
  hwBadge.style.borderColor = cfg.color;
  hwBadge.style.background = cfg.color + '18'; // 10% opacity tint
}

// WebSocket Events
ws.onopen = () => {
  console.log('[Panel] Conectado ao Motor');
  connectionStatus.innerText = 'Conectado ✓';
  connectionStatus.classList.add('connected');
};

ws.onclose = () => {
  console.log('[Panel] Desconectado do Motor');
  connectionStatus.innerText = 'Desconectado';
  connectionStatus.classList.remove('connected');
};

ws.onmessage = (event) => {
  try {
    const msg = JSON.parse(event.data);
    if (msg.type === 'STATE_CHANGE')      handleStateChange(msg.state);
    if (msg.type === 'STATE_UPDATE')      handleStateUpdate(msg.gameState);
    if (msg.type === 'EVT_RESULTS_READY') handleResults(msg.metrics);
    if (msg.type === 'HARDWARE_STATUS')   handleHardwareStatus(msg.status);
  } catch (err) {
    console.error('[Panel] Erro ao analisar mensagem:', err);
  }
};

function handleStateChange(state) {
  valStatus.innerText = state;
  const isRunning = state === 'ACTIVITY_RUNNING';
  const isPaused  = state === 'ACTIVITY_PAUSED';
  const isIdle    = state === 'IDLE';
  const isWorld   = state === 'WORLD_EXPLORATION';

  btnStart.disabled = !(isIdle || isWorld);
  btnPause.disabled = !(isRunning || isPaused);
  btnEnd.disabled   = !(isRunning || isPaused);
  btnPause.innerText = isPaused ? '▶ Retomar' : '⏸ Pausar';
}

function handleStateUpdate(gameState) {
  if (!gameState) return;
  if (gameState.score         !== undefined) valScore.innerText  = gameState.score;
  if (gameState.timeRemaining !== undefined) valMedals.innerText = gameState.timeRemaining + 's';
}

function handleResults(metrics) {
  valStatus.innerText = 'Sessão Encerrada';

  const hits     = metrics.hits   ?? metrics.pops   ?? 0;
  const misses   = metrics.misses ?? metrics.errors  ?? 0;
  const total    = hits + misses || 1;
  const rounds   = metrics.totalRounds ?? total;
  const hitRate  = hits / total;
  const pct      = Math.round(hitRate * 100);
  const avgRt    = metrics.avgReactionTime ?? metrics.averageReactionTime ?? null;
  const score    = metrics.finalScore ?? 0;
  const duration = metrics.durationSeconds ?? metrics.duration ?? null;

  const perfLabel = hitRate > 0.8
    ? '🏆 Excelente'
    : hitRate > 0.5
    ? '👍 Bom'
    : '💪 Em desenvolvimento';

  const rtStr       = avgRt    !== null ? Math.round(avgRt)    + ' ms' : '—';
  const durationStr = duration !== null ? Math.round(duration) + ' s'  : '—';
  const now         = new Date().toLocaleString('pt-BR', { dateStyle: 'long', timeStyle: 'short' });
  const nickname    = patientNickname.value.trim() || 'Paciente';

  // ── Panel summary ──
  panelScore.innerText    = score;
  panelHits.innerText     = hits;
  panelMisses.innerText   = misses;
  panelRounds.innerText   = rounds;
  panelRt.innerText       = rtStr;
  panelDuration.innerText = durationStr;
  panelPerf.innerText     = perfLabel;
  perfBarFill.style.width = pct + '%';
  perfBarLabel.innerText  = pct + '%';
  resultsSection.classList.remove('hidden');

  // ── Print report ──
  prPatient.innerText  = nickname;
  prDate.innerText     = now;
  prScore.innerText    = score;
  prHits.innerText     = hits;
  prMisses.innerText   = misses;
  prRounds.innerText   = rounds;
  prRt.innerText       = avgRt !== null ? Math.round(avgRt) + ' ms' : '—';
  prDuration.innerText = durationStr;

  valScore.innerText = score;
}

// Button Listeners
btnStart.addEventListener('click', () => {
  // Step 1: move engine from IDLE → WORLD_EXPLORATION
  sendMessage({ type: 'CMD_START_SESSION', config: {} });
  // Step 2: immediately queue the activity
  setTimeout(() => {
    sendMessage({ type: 'CMD_START_ACTIVITY', activity: 'Estoura-Baloes' });
  }, 150);
});

btnPause.addEventListener('click', () => {
  const isPaused = btnPause.innerText.includes('Retomar');
  sendMessage({ type: isPaused ? 'CMD_RESUME' : 'CMD_PAUSE' });
});

btnEnd.addEventListener('click', () => {
  sendMessage({ type: 'CMD_END_ACTIVITY' });
});

document.getElementById('btn-pdf').addEventListener('click', () => {
  window.print();
});

// ── Botão de Reset rápido ───────────────────────────────────────────────────
const btnReset = document.getElementById('btn-reset');
btnReset.addEventListener('click', () => {
  if (!confirm('Resetar para o início? A sessão atual será perdida.')) return;

  // 1. Mata qualquer sessão ativa
  sendMessage({ type: 'CMD_END_SESSION' });

  // 2. Esconde resultados, reseta valores na tela
  resultsSection.classList.add('hidden');
  valStatus.innerText  = 'Aguardando';
  valScore.innerText   = '0';
  valMedals.innerText  = '—';

  // 3. Feedback visual no botão
  btnReset.textContent = '✅ Resetado!';
  btnReset.disabled = true;
  setTimeout(() => {
    btnReset.textContent = '🔄 Resetar para o Início';
    btnReset.disabled = false;
  }, 2000);
});

function sendMessage(msg) {
  if (ws.readyState === WebSocket.OPEN) {
    ws.send(JSON.stringify(msg));
  } else {
    alert('Não conectado ao motor. Verifique se node engine/server.js está rodando.');
  }
}
