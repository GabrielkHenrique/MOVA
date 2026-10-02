# MOVA — Hardware Validation Plan

This plan defines the exact sequence for physical hardware validation. **Do not skip phases.**

## Phase 1: ONE ZONE
* **Setup:** ESP32 + 1 Piezo (Center) + 1 LED on breadboard.
* **Procedure:** Power on. Tap piezo gently, then hard.
* **Expected Result:** LED flashes once per tap. Serial monitor shows impact intensity varying from 0.01 to 1.00.
* **Pass/Fail:** Fails if touches are not detected or if noise triggers randomly.
* **Evidence:** Serial Monitor logs.

## Phase 2: NOISE WITH WIFI
* **Setup:** Same as Phase 1, but with Wi-Fi AP active.
* **Procedure:** Observe Serial monitor without touching the piezo.
* **Expected Result:** Wi-Fi radio pulses (which consume high current) should not cause false positive ADC readings on the piezo pin.
* **Pass/Fail:** Fails if `footstep` events fire automatically when a client connects to the WebSocket.
* **Evidence:** Serial Monitor logs over 5 minutes idle time.

## Phase 3: FIVE ZONES
* **Setup:** Add 4 more piezos and 4 more LEDs.
* **Procedure:** Tap each zone individually.
* **Expected Result:** Only the corresponding LED flashes. Proper JSON zone identifier (`front`, `back`, etc.) is sent.
* **Pass/Fail:** Fails if one tap triggers two different zones randomly.
* **Evidence:** Serial logs showing distinct zones.

## Phase 4: CROSS-TALK
* **Setup:** 5 zones mounted on the physical prototype mat (wood/foam).
* **Procedure:** Step heavily on the `center` zone.
* **Expected Result:** The vibration travels through the wood, but the firmware's "Greatest Peak Selection" logic correctly attributes the hit ONLY to `center`.
* **Pass/Fail:** Fails if stepping on Center triggers Right and Left simultaneously.
* **Evidence:** Video recording of step + Serial log showing only one event.

## Phase 5: REPEATED IMPACT / REFRACTORY
* **Setup:** 1 zone.
* **Procedure:** Step once, but let the foot bounce naturally.
* **Expected Result:** Only ONE event is fired. The 220ms refractory period suppresses the bounce.
* **Pass/Fail:** Fails if one physical step generates 2 or 3 `footstep` JSON messages.
* **Evidence:** Serial logs vs physical observation.

## Phase 6: LATENCY
* **Setup:** Complete system (ESP32 -> Node -> TV).
* **Procedure:** Record a high-speed video (e.g., 240fps on a phone) showing the foot hitting the mat and the TV displaying the `💥 POP!` animation.
* **Expected Result:** Visual latency between physical impact and screen reaction should be < 100ms.
* **Pass/Fail:** Fails if the delay feels sluggish or exceeds 150ms.
* **Evidence:** High-speed video frame counting.

## Phase 7: CALIBRATION
* **Setup:** Patient testing.
* **Procedure:** Run the 6-step calibration script.
* **Expected Result:** System generates a patient-specific multiplier.
* **Pass/Fail:** Fails if lightweight patients cannot trigger the threshold or heavy patients constantly max out at 1.0.
* **Evidence:** CSV log of 6 steps per patient.

## Phase 8: LONG SESSION
* **Setup:** Complete system.
* **Procedure:** Play Estoura-Balões continuously for 15 minutes.
* **Expected Result:** No WebSocket disconnects. No memory leaks in ESP32 (heap stays stable).
* **Pass/Fail:** Fails if the game freezes, ESP32 reboots, or Wi-Fi drops.
* **Evidence:** Uninterrupted game completion screen.
