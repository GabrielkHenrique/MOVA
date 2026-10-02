# MOVA — Sensor Requirements & Architecture

## Overview
The MOVA hardware interface depends on five zones (center, front, right, back, left). Each zone acts as a dynamic impact sensor using piezoelectric discs.

## Hardware Conditioning
* **ADC1 Mapping:** Piezos connect to ADC1 (e.g., GPIO36, 39, 34, 35, 32) to ensure continuous reading without conflicts from Wi-Fi (which uses ADC2).
* **Signal Conditioning:** Raw piezo signals can exceed ±90V. The circuit MUST include:
  * 1 MΩ bleed resistor in parallel to discharge the ceramic element.
  * Protection diodes (Schottky or Zener) to clamp voltage to 0V–3.3V before hitting the ESP32.
* **LED Outputs:** 5 discrete LEDs for visual feedback on impact and calibration.

## Signal Processing Pipeline
1. **Noise Floor Calibration:** On startup, the system samples the ambient baseline to establish a dynamic `noise_floor` and `std_dev`.
2. **Thresholding:** `Dynamic Threshold = noise_floor + (3 * std_dev)`.
3. **Capture Window:** Once the threshold is crossed, a **30 ms capture window** opens. The ADC samples as fast as possible to find the absolute peak.
4. **Greatest Peak Selection:** (For 5-zone mode) If multiple zones cross the threshold within the window, the zone with the highest peak "wins" (to prevent cross-talk).
5. **Normalized Intensity:** The peak value is normalized: `intensity = peak / 4095.0` (0.0 to 1.0).
6. **Refractory Period:** After a valid impact, a **220 ms refractory period** is enforced where subsequent threshold crossings are ignored to prevent double-triggering on a single step.
7. **Six-Step Calibration:** (Future Phase) A personal calibration mode where the patient steps 6 times to define their average "1.0" intensity profile.

---

## Status Matrix

| Component | Status |
| :--- | :--- |
| Five Zones Layout | DESIGNED |
| Piezo Behavior / Impact logic | DESIGNED |
| ADC1 Routing | DESIGNED |
| Signal Conditioning (1MΩ + Diodes) | DESIGNED |
| LED Outputs | DESIGNED |
| Noise Floor Calibration | IMPLEMENTED |
| Dynamic Threshold | IMPLEMENTED |
| 30 ms Capture Window | IMPLEMENTED (1-zone) |
| Greatest Peak Selection | DESIGNED (Pending 5-zone) |
| 220 ms Refractory Period | IMPLEMENTED |
| Normalized Intensity | IMPLEMENTED |
| Six-step Calibration | DESIGNED |
| Software Simulator | SIMULATED |
| **Complete System** | **PENDING PHYSICAL VALIDATION** |

**WARNING:** No hardware feature is considered "COMPLETE" until physically validated with the real ESP32, piezo discs, and an actual human footstep.
