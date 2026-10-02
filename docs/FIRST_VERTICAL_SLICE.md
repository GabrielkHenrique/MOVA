# First Vertical Slice: Estoura-Balões

## Objective
Establish the core technical loop: `Simulator -> Engine -> Game Logic -> TV` controlled by the `Therapist Panel`.

## Architecture Flow
```text
THERAPIST PANEL
        ↓ (CMD_START_SESSION)
ENGINE (Game State Machine)
        ↓ (STATE_UPDATE: "Estoura-Balões")
TV (MOVA Plaza -> zooms into Balloon Stand)
        ↓
GAME RUNNING
        ↓ (Wait for input)
SIMULATOR (Patient steps on "Left")
        ↓ (EVT_STEP_PRESSED, zone: "left")
ENGINE (Evaluates step, calculates reaction time, updates score)
        ↓ (EVT_PLAY_FEEDBACK: "POP")
TV (Renders balloon popping, score increases)
        ↓ (Game finishes)
ENGINE (Calculates final metrics)
        ↓ (STATE_UPDATE: Results)
TV (Shows Medals/Stars)
        ↓ (CMD_RETURN_TO_WORLD)
TV (Returns to MOVA Plaza)
```

## State Machine (Engine)
1. **IDLE**: Awaiting therapist connection.
2. **WORLD_EXPLORATION**: Rendering the MOVA Plaza.
3. **ACTIVITY_INITIALIZING**: Loading "Estoura-Balões".
4. **ACTIVITY_RUNNING**: Core game loop. Spawning targets, waiting for simulator events, scoring.
5. **SHOWING_RESULTS**: Displaying the final score and reaction time.

## Components Needed
1. **Simulator UI**: 5 simple buttons representing the mat zones, emitting JSON over WebSocket.
2. **Engine Router**: Node.js/Vite script maintaining the WebSocket server and the State Machine.
3. **Therapist Panel UI**: Minimal HTML/JS dashboard to start/stop the session and view live score.
4. **Patient TV UI**: HTML/CSS/DOM interface rendering the MOVA Plaza and the balloon game.

## Acceptance Criteria
- Therapist can start the session from their panel.
- TV transitions from Plaza to Game.
- Clicking the Simulator generates a step event.
- Engine correctly scores the step.
- TV shows visual feedback (balloon pops).
- TV returns to Plaza when finished.
- UI contains absolutely zero business logic.
