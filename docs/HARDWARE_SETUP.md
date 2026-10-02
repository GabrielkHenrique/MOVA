# MOVA Hardware Setup — One-Zone MVP

> [!IMPORTANT]
> This document covers the **one-zone (CENTER) MVP** only.
> Physical validation is **PENDING** — all statuses reflect the designed behaviour, not a tested board.

---

## 1. Component List

| Qty | Component | Notes |
|-----|-----------|-------|
| 1 | ESP32 DevKit V1 (38-pin or 30-pin) | Any standard Espressif DevKit |
| 1 | Piezoelectric disc (27 mm recommended) | Passive sensor — no power needed |
| 1 | Resistor 1 MΩ (brown-black-green) | Bias / bleed resistor across piezo |
| 1 | Protection diode or 5.1 V Zener | **Mandatory** — see safety note |
| 1 | LED (any colour, 3 mm or 5 mm) | Visual impact feedback |
| 1 | Resistor 220 Ω (red-red-brown) | LED current limiter |
| — | Breadboard + jumper wires | Prototyping |
| — | USB-A to Micro-USB cable | Power + programming |

---

## 2. Wiring Diagram — CENTER Zone

```
                ┌─────────────────────────────────┐
  PIEZO DISC    │            ESP32 DevKit V1       │
  ──────────    │                                  │
                │  3V3 ───── (do NOT connect) ─── │
  (+) Red  ─── ┤ GPIO36 (ADC1_CH0, input-only)   │
                │    │                             │
                │    ├──── 1 MΩ ─── GND           │  ← bias/bleed resistor
                │    │                             │
                │    └──── D_prot ─── GND         │  ← protection diode (cathode→GPIO, anode→GND)
                │                                  │
  (–) Black ── ┤ GND                              │
                │                                  │
                │  GPIO25 ─── 220 Ω ─── LED(+)   │
                │  GND    ─────────────── LED(–)  │
                │                                  │
                │  5V / 3V3  USB power             │
                └─────────────────────────────────┘
```

**GPIO36 notes:**
- GPIO36 (`ADC1_CH0`) is an **input-only** pin — it has no internal pull-up/pull-down.
- Do **not** drive it from an external voltage source; the piezo is passive.

---

## 3. Protection Circuit — Safety Notes

> [!CAUTION]
> A piezoelectric disc struck by a hard impact can generate **transient voltages of ±40 V to ±90 V**.
> Without protection, this will permanently destroy the ESP32's ADC input.

**Minimum protection (either option):**

| Option | Components | Description |
|--------|-----------|-------------|
| A — Zener clamp | 1× 3.3 V Zener + 1× 10 kΩ series resistor | Zener clamps the signal to ≤ 3.3 V; series R limits current |
| B — Schottky diodes | 2× BAT43 (or 1N5819) | One diode to VCC, one to GND; clamps to rail voltages |

**Recommended (Option A) wiring detail:**

```
PIEZO (+) ─── 10 kΩ ─── GPIO36
                    │
                  [3.3V Zener]  ← cathode to GPIO36 node, anode to GND
                    │
                   GND
```

> [!WARNING]
> Omitting the protection circuit risks not only the GPIO pin but the entire ESP32 module.
> A replacement module costs more than the protection components.

---

## 4. Installing Arduino IDE Libraries

1. Open **Arduino IDE** (≥ 2.0 recommended).
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for and install:

| Library | Author | Purpose |
|---------|--------|---------|
| `WebSockets` | Markus Sattler (links2004) | WebSocket server on ESP32 |
| `ArduinoJson` | Benoit Blanchon | JSON serialisation |

4. The `WiFi.h` library ships with the **ESP32 Arduino Core** — install via:
   - **File → Preferences → Additional boards manager URLs:**
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - **Tools → Board → Boards Manager** → search `esp32` → install **esp32 by Espressif Systems**.

---

## 5. Flashing the Firmware

### Board settings (Tools menu)

| Setting | Value |
|---------|-------|
| Board | ESP32 Dev Module |
| Upload Speed | 115200 or 921600 |
| CPU Frequency | 240 MHz |
| Flash Frequency | 80 MHz |
| Flash Mode | QIO |
| Partition Scheme | Default 4MB with spiffs |
| Port | whichever COM port appears when ESP32 is plugged in |

### Steps

1. Open `firmware/mova_firmware_v2_one_zone.ino` in Arduino IDE.
2. Select the correct **Port** and **Board** (see above).
3. Click **Upload** (→ arrow button).
4. Open **Serial Monitor** at **115200 baud**.
5. You should see:

```
===== MOVA One-Zone MVP Firmware v2 =====
[AP] Starting access point...
[AP] MOVA-ESP32 started. IP: 192.168.4.1
[CAL] Starting noise-floor calibration (200 samples / 2 s)...
[CAL] noiseFloor=412.3  noiseStdDev=18.7  rawThreshold=468  dynamicThreshold=468
[WS] WebSocket server listening on port 81
[SYS] Ready — waiting for impacts.
```

> [!NOTE]
> No SSID or password needs to be changed. The firmware runs in **AP (Access Point)** mode — the ESP32 creates its own Wi-Fi network. No router is required.

---

## 6. Connecting the Computer to MOVA-ESP32

### Step 1 — Connect to the Wi-Fi AP

1. On your laptop/PC, open **Wi-Fi settings**.
2. Connect to network **`MOVA-ESP32`**, password **`mova1234`**.
3. Your machine will receive an IP in the `192.168.4.x` subnet.

### Step 2 — Run the Node.js client

Open a PowerShell terminal in the project root and run:

```powershell
$env:ESP32_IP = '192.168.4.1'
node hardware/esp32-client.js
```

The client will connect to `ws://192.168.4.1:81` and print incoming events.

---

## 7. Hardware Validation Checklist

Work through each item after physical assembly.

### 7.1 Noise Floor

- [ ] Serial monitor shows `dynamicThreshold` between 300 and 2000 on a quiet surface.
- [ ] Threshold does **not** trigger spontaneously with no one touching the floor.
- [ ] Re-power the device and confirm threshold is reproducible (within ~10 %).

### 7.2 Weak vs. Strong Impacts

| Impact type | Expected intensity range |
|-------------|--------------------------|
| Light tap (finger) | 0.05 – 0.30 |
| Medium step | 0.30 – 0.60 |
| Heavy stomp | 0.60 – 1.00 |

- [ ] Weak taps produce low intensity values (or are filtered out below threshold × 1.2).
- [ ] Strong stomps produce high intensity values close to 1.0.

### 7.3 Refractory Period

- [ ] Rapidly tapping the piezo in succession fires events at most ~4–5 times per second.
- [ ] No "double trigger" from a single impact (i.e., one stomp → exactly one JSON event).

### 7.4 LED Feedback

- [ ] LED flashes **once** at boot (200 ms).
- [ ] LED flashes **three times** after calibration (ready signal).
- [ ] LED flashes for **200 ms** on every confirmed impact.

### 7.5 WebSocket Broadcast

- [ ] Node.js client receives `{"type":"connected",...}` immediately on connect.
- [ ] Each confirmed impact produces exactly one JSON event logged by the client.
- [ ] `intensity` field is a float between 0.0 and 1.0.

---

## 8. Validation Status

| Feature | Status |
|---------|--------|
| Noise floor calibration | DESIGNED |
| Impact detection (single zone) | DESIGNED |
| Refractory period (220 ms) | DESIGNED |
| LED feedback | DESIGNED |
| WebSocket broadcast | DESIGNED |
| Physical validation | PENDING |

---

*Last updated: September 2026 — One-Zone MVP*
