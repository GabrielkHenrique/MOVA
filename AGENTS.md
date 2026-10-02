# MOVA Project Agents & Architecture Rules

This document defines the shared architecture rules and ownership models for the MOVA project, ensuring all agents and team members follow the same principles.

## Architecture Rules

1. **ESP32 is the physical-system authority.**
2. **Hardware and software communicate through an explicit event protocol.**
3. **Game logic must not directly access hardware.**
4. **TV must not contain business/game rules.**
5. **Therapist panel must not access GPIO directly.**
6. **Simulator must produce the same logical events as the real hardware.**
7. **The application should remain local-first.**
8. **Avoid cloud dependencies unless explicitly justified.**
9. **Keep modules understandable for a student team.**
10. **Prefer simple architecture over unnecessary enterprise patterns.**
11. **Never silently change the event protocol.**
12. **Never invent hardware capabilities.**
13. **Every major feature must have a testable acceptance criterion.**
14. **Avoid large rewrites.**
15. **Keep documentation synchronized with architectural decisions.**

---

## Ownership Map

The project is divided into four main areas, each owned by a specialized agent:

### PROJECT MANAGER (`mova-project-manager`)
- Architecture
- Roadmap
- Integration
- Documentation
- Reviews

### GAME/ENGINE (`mova-game-engineer`)
- Engine (`engine/`)
- Game Logic (`games/`)
- Simulator (`simulator/`)
- Game Contracts (`shared/`)

### UI/PANEL (`mova-ui-engineer`)
- TV Interface (`apps/tv/`)
- Therapist Panel (`apps/therapist-panel/`)
- Visual Assets (`assets/`)
- Presentation

### HARDWARE (`mova-hardware-engineer`)
- Firmware (`firmware/`)
- Sensors
- Electrical logic
- WebSocket hardware layer (`hardware/`)
- Calibration
- Hardware documentation (`docs/`)

**Rule of modification:** If an agent needs to modify another agent's area, it must clearly state why and ideally coordinate with the respective owner.
