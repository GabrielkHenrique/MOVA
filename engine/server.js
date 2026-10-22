import { WebSocketServer } from 'ws';
import { evaluateFootstep } from './game-logic.js';

const wss = new WebSocketServer({ port: 8080 });

// State Machine
const STATES = {
    IDLE: 'IDLE',
    WORLD_EXPLORATION: 'WORLD_EXPLORATION',
    ACTIVITY_INITIALIZING: 'ACTIVITY_INITIALIZING',
    ACTIVITY_RUNNING: 'ACTIVITY_RUNNING',
    ACTIVITY_PAUSED: 'ACTIVITY_PAUSED',
    ACTIVITY_ENDED: 'ACTIVITY_ENDED',
    SHOWING_RESULTS: 'SHOWING_RESULTS'
};

let currentState = STATES.IDLE;
let sessionConfig = null;

// Game State (Estoura-Baloes)
let gameState = {
    score: 0,
    timeRemaining: 0,
    activeTargets: [] // Each entry: { id, zone, spawnTime }
};
let gameTimer = null;
let spawnTimer = null;
const ZONES = ['front', 'back', 'left', 'right', 'center'];

// Session Metrics — reset at the start of every game
let sessionMetrics = {
    hits: 0,
    misses: 0,
    reactionTimes: [],  // ms between spawn and successful step
    totalRounds: 0,     // total targets spawned
    startTime: null     // Date.now() at game start, used to compute duration
};

// ── Hardware Status ───────────────────────────────────────────────────────────

/** @type {{ mode: 'SIMULATOR'|'ESP32_CONNECTING'|'ESP32_CONNECTED'|'ESP32_DISCONNECTED' }} */
let hardwareStatus = { mode: 'SIMULATOR' };

/** Tracks the socket of the currently registered esp32-bridge, if any. */
let esp32BridgeSocket = null;

/**
 * Update the hardware status and broadcast the change to all clients.
 * @param {'SIMULATOR'|'ESP32_CONNECTING'|'ESP32_CONNECTED'|'ESP32_DISCONNECTED'} mode
 */
function setHardwareStatus(mode) {
    hardwareStatus = { mode };
    console.log(`[ENGINE] hardwareStatus → ${mode}`);
    broadcast({ type: 'HARDWARE_STATUS', status: mode });
}

// ── Broadcast helpers ─────────────────────────────────────────────────────────

function broadcast(message) {
    const msgStr = JSON.stringify(message);
    wss.clients.forEach(client => {
        if (client.readyState === 1) { // WebSocket.OPEN
            client.send(msgStr);
        }
    });
}

function changeState(newState) {
    console.log(`State Transition: ${currentState} -> ${newState}`);
    currentState = newState;
    broadcast({ type: 'STATE_CHANGE', state: currentState });
}

// ── Game helpers ──────────────────────────────────────────────────────────────

function spawnTarget() {
    if (currentState !== STATES.ACTIVITY_RUNNING) return;
    
    // Spawn a new balloon in a random zone
    const zone = ZONES[Math.floor(Math.random() * ZONES.length)];
    const targetId = `balloon_${Date.now()}`;
    const spawnTime = Date.now();

    // 70% Normal, 15% Bomb, 15% Golden
    const rand = Math.random();
    let balloonType = 'NORMAL';
    let duration = 3000;

    if (rand > 0.85) {
        balloonType = 'BOMB';
        duration = 2000;
    } else if (rand > 0.70) {
        balloonType = 'GOLDEN';
        duration = 4000;
    }

    gameState.activeTargets.push({ id: targetId, zone, spawnTime, type: balloonType });
    if (balloonType !== 'BOMB') sessionMetrics.totalRounds++; // Bomb doesn't count as a normal round

    // Auto-remove after duration
    setTimeout(() => {
        const index = gameState.activeTargets.findIndex(t => t.id === targetId);
        if (index !== -1 && currentState === STATES.ACTIVITY_RUNNING) {
            const target = gameState.activeTargets[index];
            gameState.activeTargets.splice(index, 1);
            
            if (target.type !== 'BOMB') {
                sessionMetrics.misses++;
                broadcast({ type: 'EVT_PLAY_FEEDBACK', feedback: 'MISS', targetId });
            }
            broadcastGameState();
        }
    }, duration);
    
    broadcastGameState();
}

function broadcastGameState() {
    broadcast({
        type: 'STATE_UPDATE',
        gameState: {
            score: gameState.score,
            timeRemaining: gameState.timeRemaining,
            activeTargets: gameState.activeTargets
        }
    });
}

function startGame() {
    gameState = {
        score: 0,
        timeRemaining: 60, // 60 seconds game
        activeTargets: []
    };

    // Reset all per-session metrics
    sessionMetrics = {
        hits: 0,
        misses: 0,
        reactionTimes: [],
        totalRounds: 0,
        startTime: Date.now()
    };
    
    changeState(STATES.ACTIVITY_RUNNING);
    broadcastGameState();
    
    gameTimer = setInterval(() => {
        if (currentState !== STATES.ACTIVITY_RUNNING) return;
        
        gameState.timeRemaining--;
        if (gameState.timeRemaining <= 0) {
            endGame();
        } else {
            broadcastGameState();
        }
    }, 1000);
    
    spawnTimer = setInterval(() => {
        if (currentState === STATES.ACTIVITY_RUNNING) {
            spawnTarget();
        }
    }, 2000); // spawn every 2 seconds
}

function endGame() {
    clearInterval(gameTimer);
    clearInterval(spawnTimer);
    changeState(STATES.ACTIVITY_ENDED);

    // Compute derived metrics
    const duration = Math.round((Date.now() - sessionMetrics.startTime) / 1000);
    const avgReactionTime = sessionMetrics.reactionTimes.length > 0
        ? Math.round(
            sessionMetrics.reactionTimes.reduce((sum, t) => sum + t, 0) /
            sessionMetrics.reactionTimes.length
          )
        : 0;

    setTimeout(() => {
        changeState(STATES.SHOWING_RESULTS);
        broadcast({
            type: 'EVT_RESULTS_READY',
            metrics: {
                finalScore: gameState.score,
                hits: sessionMetrics.hits,
                misses: sessionMetrics.misses,
                totalRounds: sessionMetrics.totalRounds,
                avgReactionTime,
                reactionTimes: sessionMetrics.reactionTimes,
                duration
            }
        });
    }, 1000);
}

// ── WebSocket server ──────────────────────────────────────────────────────────

wss.on('connection', (ws) => {
    console.log('New client connected.');
    
    // Send current state and hardware status to the newly connected client
    ws.send(JSON.stringify({ type: 'STATE_CHANGE', state: currentState }));
    ws.send(JSON.stringify({ type: 'HARDWARE_STATUS', status: hardwareStatus.mode }));
    if (currentState === STATES.ACTIVITY_RUNNING || currentState === STATES.ACTIVITY_PAUSED) {
        ws.send(JSON.stringify({ type: 'STATE_UPDATE', gameState }));
    }

    ws.on('message', (message) => {
        let msg;
        try {
            msg = JSON.parse(message);
        } catch (e) {
            return;
        }

        console.log('Received:', msg);

        // Routing based on message type
        switch (msg.type) {
            // ── Hardware registration ─────────────────────────────────────────
            case 'client_register':
                if (msg.role === 'esp32-bridge') {
                    esp32BridgeSocket = ws;
                    setHardwareStatus(msg.status ?? 'ESP32_CONNECTED');
                    console.log(`[ENGINE] esp32-bridge registered (${msg.status ?? 'ESP32_CONNECTED'}).`);
                }
                break;

            // ── Therapist Commands ────────────────────────────────────────────
            case 'CMD_START_SESSION':
                // Accept from IDLE, SHOWING_RESULTS, or WORLD_EXPLORATION (restart)
                if (currentState !== STATES.ACTIVITY_RUNNING && currentState !== STATES.ACTIVITY_PAUSED) {
                    if (gameTimer) clearInterval(gameTimer);
                    if (spawnTimer) clearInterval(spawnTimer);
                    sessionConfig = msg.config;
                    changeState(STATES.WORLD_EXPLORATION);
                }
                break;
            case 'CMD_END_SESSION':
                if (currentState !== STATES.IDLE) {
                    if (gameTimer) clearInterval(gameTimer);
                    if (spawnTimer) clearInterval(spawnTimer);
                    changeState(STATES.IDLE);
                }
                break;
            case 'CMD_START_ACTIVITY':
                // Accept from WORLD_EXPLORATION or SHOWING_RESULTS (replay)
                if ((currentState === STATES.WORLD_EXPLORATION || currentState === STATES.SHOWING_RESULTS)
                    && msg.activity === 'Estoura-Baloes') {
                    if (gameTimer) clearInterval(gameTimer);
                    if (spawnTimer) clearInterval(spawnTimer);
                    changeState(STATES.ACTIVITY_INITIALIZING);
                    setTimeout(() => { startGame(); }, 800);
                }
                break;
            case 'CMD_PAUSE':
                if (currentState === STATES.ACTIVITY_RUNNING) {
                    changeState(STATES.ACTIVITY_PAUSED);
                }
                break;
            case 'CMD_RESUME':
                if (currentState === STATES.ACTIVITY_PAUSED) {
                    changeState(STATES.ACTIVITY_RUNNING);
                }
                break;
            case 'CMD_END_ACTIVITY':
                if (currentState === STATES.ACTIVITY_RUNNING || currentState === STATES.ACTIVITY_PAUSED) {
                    endGame();
                }
                break;
            case 'CMD_RETURN_TO_WORLD':
                if (currentState === STATES.SHOWING_RESULTS) {
                    changeState(STATES.WORLD_EXPLORATION);
                }
                break;

            // ── Footstep Events (simulator or ESP32 bridge) ───────────────────
            case 'footstep': {
                const source = msg.source ?? 'unknown';

                if (currentState !== STATES.ACTIVITY_RUNNING) {
                    console.log(`[ENGINE] footstep rejected — state is ${currentState} (source: ${source})`);
                    break;
                }

                console.log(`[ENGINE] footstep | zone=${msg.zone} | source=${source} | state=${currentState}`);

                const result = evaluateFootstep(currentState, gameState, sessionMetrics, msg);

                // Commit updated state back to module-level variables
                gameState = result.updatedGameState;
                sessionMetrics = result.updatedMetrics;

                if (result.feedback === 'POP' || result.feedback === 'POP_GOLDEN') {
                    broadcast({ type: 'EVT_PLAY_FEEDBACK', feedback: result.feedback, targetId: result.targetId, zone: result.zone });
                } else if (result.feedback === 'STEP_BOMB' || result.feedback === 'STEP_EMPTY') {
                    broadcast({ type: 'EVT_PLAY_FEEDBACK', feedback: result.feedback, zone: result.zone || msg.zone });
                }

                broadcastGameState();
                break;
            }
        }
    });

    ws.on('close', () => {
        // If the disconnecting socket is the registered esp32-bridge, update status
        if (ws === esp32BridgeSocket) {
            console.log('[ENGINE] esp32-bridge disconnected.');
            esp32BridgeSocket = null;
            setHardwareStatus('ESP32_DISCONNECTED');
        } else {
            console.log('Client disconnected.');
        }
    });
});

console.log('MOVA Engine WebSocket server running on ws://localhost:8080');
