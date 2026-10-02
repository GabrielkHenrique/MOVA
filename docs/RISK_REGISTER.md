# MOVA — Risk Register

| Risk ID | Risk Description | Probability | Impact | Mitigation | Validation Method | Current Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **RK-01** | **Piezo Noise / False Positives:** Ambient vibrations or Wi-Fi radio interference cause false footsteps. | High | High | Dynamic noise floor calibration at boot; `1MΩ` bleed resistor; physical isolation of sensors. | Idle test (Phase 2). Observe for false triggers. | MITIGATION DESIGNED |
| **RK-02** | **Cross-talk:** Stepping on one zone sends vibrations through the mat that trigger adjacent zones. | High | High | "Greatest peak selection" logic inside a 30ms window across all ADC channels. | Phase 4 Validation (5-zones). | MITIGATION DESIGNED |
| **RK-03** | **Missed Impacts:** Patient step is too light to cross the ADC threshold. | Med | High | Dynamic threshold (Media + 3σ) instead of hardcoded 1500; Patient specific calibration phase. | Phase 7 Calibration testing. | MITIGATION DESIGNED |
| **RK-04** | **Mechanical Inconsistency:** Piezos break under direct pressure or yield different voltages depending on foot placement. | High | Critical | Mount piezos on foam/rubber shock absorbers; use a sturdy top plate to distribute weight. | Destructive physical testing / long session. | UNMITIGATED (Pending physical design) |
| **RK-05** | **Wi-Fi / WS Disconnects:** The ESP32 drops the connection during a session. | Low | High | ESP32 configured as AP (avoids router drops); Node bridge auto-reconnects every 3s; UI shows hardware status immediately. | Phase 8 Long Session test. | MITIGATION IMPLEMENTED |
| **RK-06** | **Repeated Events (Bouncing):** The foot bounces, triggering the threshold multiple times for a single step. | Med | Med | 220ms software refractory period (debounce). | Phase 5 Refractory validation. | MITIGATION IMPLEMENTED |
| **RK-07** | **Excessive Signal (Voltage Spikes):** Hard step generates > 5V, frying the ESP32 ADC pin. | High | Critical | Mandatory hardware clamping circuit (Zener diode 3.3V or Schottky diode array). | Oscilloscope measurement. | UNMITIGATED (Pending assembly) |
| **RK-08** | **System Latency:** Total trip from foot to TV screen takes > 150ms, ruining game feel. | Low | Med | Pure Vanilla JS UI; Local WebSocket network; No cloud routing. | Phase 6 High-speed camera test. | MITIGATION IMPLEMENTED |
