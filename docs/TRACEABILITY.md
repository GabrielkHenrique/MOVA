# MOVA — Traceability Matrix

| Requirement | Implementation | Test | Evidence | Status |
| :--- | :--- | :--- | :--- | :--- |
| **RF-01** (Start/End) | `therapist-panel/app.js`, `engine/server.js` | UI click to Engine state transition | Engine log: `State Transition: IDLE -> WORLD_EXPLORATION` | IMPLEMENTED |
| **RF-02** (Patient TV) | `apps/tv/index.html` | Visual verification of DOM state | Browser renders `#game-view` | IMPLEMENTED |
| **RF-03** (Metrics) | `engine/game-logic.js`, `sessionMetrics` | `engine.test.js` | Test output: Reaction times, hits, misses tracked | IMPLEMENTED |
| **RF-04** (PDF Report) | `therapist-panel/index.html`, `@media print` | Browser Print Dialog trigger | Visual PDF layout verification | IMPLEMENTED |
| **RF-05** (State Guard) | `engine/game-logic.js` (evaluateFootstep) | `engine.test.js` | 6/6 passing unit tests for footstep rejection | IMPLEMENTED |
| **RF-06** (Simulator) | `simulator/index.html` | Manual UI tap | Engine logs `footstep` from simulator | IMPLEMENTED |
| **RP-01** (HW < 50ms) | `firmware_v2_one_zone.ino` | Serial timestamp vs Wi-Fi payload | N/A | PENDING PHYSICAL VALIDATION |
| **RP-02** (Node < 20ms) | `engine/server.js` | Log timestamps | N/A | PENDING PHYSICAL VALIDATION |
| **RH-01** (5 Zones) | Firmware Arrays, Engine `ZONES` | N/A | N/A | PENDING PHYSICAL VALIDATION |
| **RH-02** (Piezo) | Physical assembly | Oscilloscope reading / ADC print | N/A | PENDING PHYSICAL VALIDATION |
| **RS-01** (1MΩ Bleed) | Physical circuit | Multimeter continuity / resistance | N/A | PENDING PHYSICAL VALIDATION |
| **RS-02** (Diodes) | Physical circuit | Oscilloscope peak voltage limit | N/A | PENDING PHYSICAL VALIDATION |
| **RC-01** (WebSocket) | `ws` package, `WebSocketsServer.h` | Connection success | `[WS] Client #1 connected` | IMPLEMENTED |
| **RC-02** (Wi-Fi AP) | `WiFi.softAP()` | Network scan | SSID `MOVA-ESP32` visible | PENDING PHYSICAL VALIDATION |
