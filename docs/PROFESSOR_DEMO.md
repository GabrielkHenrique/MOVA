# MOVA — Professor Demonstration Checklist

This document guides the final end-to-end presentation of the MOVA MVP.

## 1. Physical Setup
1. Mount the ESP32 breadboard (1 Center Zone).
2. Connect the ESP32 to power (USB).
3. Connect the presentation laptop to the `MOVA-ESP32` Wi-Fi network.
4. Open the TV view on a large external monitor/TV.
5. Open the Therapist Panel on the laptop screen.

## 2. Software Initialization
1. Terminal 1: `node engine/server.js`
2. Terminal 2: `npx serve .`
3. Terminal 3: `$env:ESP32_IP="192.168.4.1"; node hardware/esp32-client.js`

## 3. The Demonstration Flow

### Step A: The Connection
* **Action:** Show the Professor the Therapist Panel.
* **Expected:** The Hardware badge says `● ESP32 conectado`.
* **Talking point:** "The system is running entirely offline via an ESP32 Access Point and WebSockets."

### Step B: The Interface
* **Action:** Point to the TV screen showing the MOVA Plaza.
* **Talking point:** "This is the patient's view. It's designed to feel like a welcoming game world, not a medical dashboard."

### Step C: The Game Start
* **Action:** Click `Start Activity` on the Therapist Panel.
* **Expected:** The TV transitions smoothly into the `Estoura-Balões` game. The timer starts.

### Step D: The Physical Hit
* **Action:** Ask the Professor (or a team member) to tap the physical Piezo sensor firmly.
* **Expected:**
  1. The ESP32 LED flashes.
  2. The TV screen instantly shows the `💥 POP!` animation.
  3. The score increments on both the TV and the Therapist Panel.
* **Talking point:** "The ESP32 is reading the piezo ADC, filtering noise, finding the peak, and broadcasting the event in under 50ms."

### Step E: The End & Results
* **Action:** Wait for the game timer to reach zero.
* **Expected:** The TV automatically shows the Results Screen (Score, Hits, Misses, Reaction Time, and Stars).

### Step F: The PDF Report
* **Action:** On the Therapist Panel, click `🖨️ Imprimir / Salvar PDF`.
* **Expected:** The browser's native print dialog opens showing a beautifully formatted, clean clinical report.
* **Talking point:** "We generate clean, zero-dependency clinical reports that the therapist can save immediately to the patient's record."

---

## 🚨 Fallback Plan (If Hardware Fails)
Hardware demos fail. If the ESP32 refuses to connect or the piezo breaks during the presentation:
1. Disconnect the ESP32.
2. The Therapist Panel will show `✗ ESP32 desconectado`.
3. Open `http://localhost:3000/simulator/` on a tablet or a split window.
4. **Talking point:** "Unfortunately the physical sensor disconnected, but our architecture is completely decoupled. We can demonstrate the exact same cyber-physical logic using our software simulator."
5. Proceed with Steps C, D, E, F by clicking the Simulator buttons instead of hitting the physical piezo.
