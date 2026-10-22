/**
 * hardware/esp32-client.js
 * ========================
 * WebSocket bridge: ESP32  →  this process  →  MOVA Engine
 *
 * HOW TO USE
 * ----------
 * 1. Make sure the MOVA engine (engine/server.js) is already running on port 8080.
 * 2. Set the ESP32's IP address via an environment variable:
 *      $env:ESP32_IP = "192.168.1.50"   # PowerShell
 *      export ESP32_IP=192.168.1.50      # bash
 *    If not set, defaults to 192.168.1.100.
 * 3. Run this bridge:
 *      node hardware/esp32-client.js
 *
 * EXPECTED MESSAGE FORMAT (from the ESP32)
 * -----------------------------------------
 * The ESP32 should send JSON strings over its WebSocket server, e.g.:
 *      {"type":"footstep","zone":"front"}
 * Valid zones: front | back | left | right | center
 *
 * WHAT THIS BRIDGE DOES
 * ----------------------
 * - On engine connection: sends { type:'client_register', role:'esp32-bridge' }
 *   so the engine can update its hardware-status indicator.
 * - On each ESP32 footstep message: stamps source:'esp32' before forwarding.
 *   The engine uses source ONLY for logging; it never affects game logic.
 * - All other ESP32 messages are forwarded as-is.
 */

import WebSocket from 'ws';

// ── Configuration ─────────────────────────────────────────────────────────────

const ESP32_IP      = process.env.ESP32_IP ?? '192.168.4.1';
const ESP32_PORT    = process.env.ESP32_PORT ?? 81;        // typical ESP32 WS port
const ENGINE_URL    = process.env.ENGINE_URL  ?? 'ws://localhost:8080';

const ESP32_URL = `ws://${ESP32_IP}:${ESP32_PORT}`;

// ── Reconnect helpers ─────────────────────────────────────────────────────────

const RECONNECT_DELAY_MS = 3000; // wait before attempting to reconnect

/**
 * Opens a persistent WebSocket connection to the given URL.
 * Automatically reconnects on close or error.
 *
 * @param {string} url         - WebSocket URL to connect to
 * @param {string} label       - Human-readable name used in log messages
 * @param {(ws: WebSocket) => void} onOpen  - Called with the socket once open
 * @param {(data: string) => void}  onMessage - Called with each raw message string
 * @param {() => void} [onClose] - Called when the socket closes
 * @returns {{ getSocket: () => WebSocket | null }}
 */
function createPersistentSocket(url, label, onOpen, onMessage, onClose) {
    let socket = null;

    function connect() {
        console.log(`[${label}] Connecting to ${url} …`);
        socket = new WebSocket(url);

        socket.on('open', () => {
            console.log(`[${label}] ✅ Connected to ${url}`);
            onOpen(socket);
        });

        socket.on('message', (raw) => {
            onMessage(raw.toString());
        });

        socket.on('close', (code, reason) => {
            console.warn(`[${label}] ⚠️  Connection closed (${code}${reason ? ': ' + reason : ''}). Retrying in ${RECONNECT_DELAY_MS / 1000}s …`);
            socket = null;
            if (onClose) onClose();
            setTimeout(connect, RECONNECT_DELAY_MS);
        });

        socket.on('error', (err) => {
            console.error(`[${label}] ❌ Error: ${err.message}`);
            // 'close' event will fire next and trigger reconnect
        });
    }

    connect();
    return { getSocket: () => socket };
}

// ── Engine connection ─────────────────────────────────────────────────────────

let engineSocket = null;
let esp32Connected = false;

function sendHardwareStatusToEngine() {
    if (engineSocket && engineSocket.readyState === WebSocket.OPEN) {
        const status = esp32Connected ? 'ESP32_CONNECTED' : 'ESP32_CONNECTING';
        engineSocket.send(JSON.stringify({ type: 'client_register', role: 'esp32-bridge', status }));
    }
}

const engineConn = createPersistentSocket(
    ENGINE_URL,
    'Engine',
    (ws) => {
        engineSocket = ws;
        // Identify this process to the engine with actual ESP32 connection state
        sendHardwareStatusToEngine();
        console.log('[Engine] Sent client_register as esp32-bridge.');
    },
    (data) => {
        // We don't need to act on engine→bridge messages, but log them for debugging
        console.log(`[Engine → Bridge] ${data}`);
    }
);

// ── ESP32 connection ──────────────────────────────────────────────────────────

createPersistentSocket(
    ESP32_URL,
    'ESP32',
    (_ws) => {
        esp32Connected = true;
        sendHardwareStatusToEngine();
        console.log('[ESP32] Ready to receive footstep events.');
    },
    (data) => {
        console.log(`[ESP32 → Bridge] ${data}`);

        // Forward every message from the ESP32 to the engine.
        // Stamp footstep messages with source:'esp32' for engine-side logging
        // (the engine is 100% source-agnostic for game logic).
        if (engineSocket && engineSocket.readyState === WebSocket.OPEN) {
            try {
                const parsed = JSON.parse(data);
                if (parsed.type === 'footstep') parsed.source = 'esp32';
                engineSocket.send(JSON.stringify(parsed));
            } catch {
                // If the message isn't valid JSON, forward it as-is
                engineSocket.send(data);
            }
            console.log(`[Bridge → Engine] Forwarded: ${data}`);
        } else {
            console.warn('[Bridge] Engine not connected — message dropped.');
        }
    },
    () => {
        if (esp32Connected) {
            esp32Connected = false;
            if (engineSocket && engineSocket.readyState === WebSocket.OPEN) {
                engineSocket.send(JSON.stringify({ type: 'client_register', role: 'esp32-bridge', status: 'ESP32_DISCONNECTED' }));
            }
        }
    }
);

console.log('─────────────────────────────────────────────');
console.log(' MOVA ESP32 Bridge starting up');
console.log(`  ESP32  : ${ESP32_URL}`);
console.log(`  Engine : ${ENGINE_URL}`);
console.log('─────────────────────────────────────────────');
