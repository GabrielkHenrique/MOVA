# MOVA — Project Requirements

## Functional Requirements (RF)
* **RF-01:** The system shall allow the therapist to start and end a session.
* **RF-02:** The system shall display a gamified interface (TV) for the patient.
* **RF-03:** The engine shall collect session metrics (hits, misses, total rounds, reaction times, session duration).
* **RF-04:** The system shall generate a PDF report at the end of the session.
* **RF-05:** The engine shall validate footstep events against the current game state (ignore footsteps in IDLE, PAUSED, SHOWING_RESULTS).
* **RF-06:** The system shall provide a software Simulator for testing without hardware.

## Performance Requirements (RP)
* **RP-01:** The ESP32 shall process and transmit a valid impact event in < 50ms.
* **RP-02:** The Node.js engine shall process incoming events and broadcast state updates in < 20ms.
* **RP-03:** The TV interface shall render feedback animations at 60 FPS without blocking the main thread.

## Hardware Requirements (RH)
* **RH-01:** The physical interface shall consist of 5 zones (center, front, right, back, left).
* **RH-02:** Each zone shall use a piezoelectric disc as an impact sensor.
* **RH-03:** The system shall use an ESP32 DevKit V1 microcontroller.
* **RH-04:** Each zone shall have a dedicated indicator LED for visual feedback.

## Safety Requirements (RS)
* **RS-01:** The piezo signal conditioning circuit must include a 1 MΩ bleed resistor to discharge voltage spikes.
* **RS-02:** The piezo circuit must include clamping diodes (or Zener) to prevent voltages above 3.3V or below 0V from reaching the ESP32 ADC.
* **RS-03:** The physical mat must have a non-slip surface to prevent patient falls.

## Communication Requirements (RC)
* **RC-01:** Hardware and software shall communicate via WebSockets using a defined JSON protocol.
* **RC-02:** The ESP32 shall operate in Access Point (AP) mode, creating an isolated local network (e.g., `MOVA-ESP32`).
* **RC-03:** The connection shall not depend on external internet or cloud infrastructure.

## Accessibility Requirements (RA)
* **RA-01:** All patient-facing text and feedback must be in Portuguese (PT-BR).
* **RA-02:** The TV interface must use high contrast and large typography.
* **RA-03:** The feedback must be multimodal (visual animation + text).

## Software Requirements (RSw)
* **RSw-01:** The backend engine shall be written in Node.js.
* **RSw-02:** The frontend interfaces shall use Vanilla JS/HTML/CSS without heavy build steps (e.g., no Webpack/React requirement) to facilitate student handovers.
* **RSw-03:** The PDF generation must be handled natively by the browser (`window.print()`).
