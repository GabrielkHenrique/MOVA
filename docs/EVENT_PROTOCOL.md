# MOVA Event Protocol

This document defines the initial contract for communication between the hardware (ESP32 / Simulator) and the software (Game Engine).

The protocol uses JSON over WebSocket.

---

### 1. `footstep`

Triggered by the hardware or simulator when a dynamic impact event is detected on one of the 5 zones.

```json
{
  "type": "footstep",
  "zone": "center", // ENUM: "center" | "front" | "right" | "back" | "left"
  "intensity": 0.72,
  "timestamp": 15342
}
```

### 2. `tapete_status`

Periodic or on-demand heartbeat to verify hardware connectivity.

```json
{
  "type": "tapete_status",
  "connected": true
}
```

### 3. `game_start`

Triggered by the software (Therapist Panel) to start a session.

```json
{
  "type": "game_start",
  "game": "estoura-baloes"
}
```

### 4. `game_stop`

Triggered by the software to forcefully stop a session or when the session naturally concludes.

```json
{
  "type": "game_stop"
}
```
