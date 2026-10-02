# MOVA — ESP32 First Day Guide

**IMPORTANT: Do not assemble five zones before validating one zone.**

This is the step-by-step checklist for the exact moment the physical ESP32 arrives on your desk.

## Step 1: Arduino IDE Setup
1. Download and install the Arduino IDE.
2. Go to Preferences -> Additional Boards Manager URLs -> Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Go to Boards Manager -> Search "esp32" -> Install.
4. Select board: `DOIT ESP32 DEVKIT V1`.
5. Go to Library Manager -> Search `WebSockets` by Markus Sattler -> Install.
6. Go to Library Manager -> Search `ArduinoJson` by Benoit Blanchon -> Install.

## Step 2: One-Zone Breadboard (Hardware MVP)
1. Place ESP32 on breadboard.
2. Connect Piezo:
   - Positive to `GPIO36` (ADC1).
   - Negative to `GND`.
   - Add a `1 MΩ` resistor in parallel (between GPIO36 and GND).
   - Add a Zener diode (3.3V) or Schottky clamping diodes between GPIO36 and GND/3.3V to protect the ESP32.
3. Connect LED:
   - `GPIO25` -> `220Ω` resistor -> LED Anode (Long leg).
   - LED Cathode (Short leg) -> `GND`.

## Step 3: Flash Firmware
1. Open `firmware/mova_firmware_v2_one_zone.ino`.
2. Connect ESP32 via USB.
3. Click **Upload**.
4. Open **Serial Monitor** (Baud rate: `115200`).

## Step 4: Noise Measurement
1. Do not touch the breadboard.
2. Watch the Serial Monitor. The ESP32 will sample the ambient noise 200 times.
3. Note the printed `noiseFloor` and `dynamicThreshold`. If it's erratic, your wiring is loose.

## Step 5: Wi-Fi AP Connection
1. The Serial Monitor will say `[AP] MOVA-ESP32 started`.
2. On your Windows laptop, open Wi-Fi networks.
3. Connect to `MOVA-ESP32` (Password: `mova1234`).

## Step 6: Start Software Stack
Open 3 terminals in the MOVA folder:
1. `node engine/server.js`
2. `npx serve .`
3. `$env:ESP32_IP = "192.168.4.1"; node hardware/esp32-client.js`

## Step 7: First Physical Footstep
1. Open Browser: `http://localhost:3000/apps/therapist-panel/`
2. Ensure the hardware indicator says **● ESP32 conectado**.
3. Tap the physical piezo.
4. Watch the TV screen (`http://localhost:3000/apps/tv/`) react.
5. If it works, celebrate. Then proceed to `docs/VALIDATION_PLAN.md`.
