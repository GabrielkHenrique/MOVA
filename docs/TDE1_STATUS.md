# MOVA — TDE1 Report Support

This document maps the current MOVA project state to the teacher's TDE1 requested sections.

## 1. Identification
* **Available:** Project Name (`PassoCerto`), Product Name (`MOVA`).
* **Missing:** Institutional headers, semester date.
* **Action:** Fill manually in the final Word/PDF document.

## 2. Team
* **Missing:** Full student names, IDs (RAs).
* **Action:** [STUDENT_NAMES_AND_IDs] placeholder.

## 3. Contextualization
* **Available:** Product Vision ("Videogame that happens to be controlled by movement", accessible, Wii-era inspiration, aimed at motor rehabilitation without infantilizing).
* **Missing:** Academic citations on gamified rehabilitation.
* **Action:** Copy vision from `ARCHITECTURE.md` and `MOVA_HOME_UX.md`. Add citations manually.

## 4. Architecture and Draft
* **Available:** Fully defined in `ARCHITECTURE.md`, `EVENT_PROTOCOL.md`, `SENSOR_REQUIREMENTS.md`. The cyber-physical split (ESP32 -> Node -> TV) is rigorously documented.
* **Action:** Include the ASCII diagrams from the docs and explain the separation of concerns (Engine owns logic, TV owns rendering).

## 5. State of the Art
* **Missing:** Literature review / similar products (e.g., Wii Fit, existing rehab mats).
* **Action:** Student team must research and write this section.

## 6. Schedule
* **Available:** Milestones (MVP 1-Zone, Integration, 5-Zone Expansion).
* **Missing:** Specific calendar dates.
* **Action:** Map our `VALIDATION_PLAN.md` phases to weeks on a calendar.

## 7. Bill of Materials (BOM)
* **Available:** Component list in `HARDWARE_SETUP.md` (ESP32 DevKit V1, 5x Piezo discs, 5x 1MΩ resistors, 5x Zener/Schottky diodes, 5x LEDs, 5x 220Ω resistors, wiring, wood/foam mat).
* **Missing:** Specific vendor links, exact prices.
* **Action:** [PRICES_AND_LINKS] placeholder. Add total estimated cost.

## 8. Risks
* **Available:** Fully detailed in `RISK_REGISTER.md` (RK-01 to RK-08).
* **Action:** Copy table directly to TDE1. Emphasize that software risks are mitigated, and hardware risks are pending physical validation.
