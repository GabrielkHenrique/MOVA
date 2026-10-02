/**
 * engine/game-logic.js
 * ====================
 * Pure game-logic functions for the MOVA engine.
 *
 * These functions are completely decoupled from WebSocket / I/O so they can be
 * imported and unit-tested without spinning up any server.
 */

// Re-export STATES so tests can reference them without touching server.js
export const STATES = {
    IDLE: 'IDLE',
    WORLD_EXPLORATION: 'WORLD_EXPLORATION',
    ACTIVITY_INITIALIZING: 'ACTIVITY_INITIALIZING',
    ACTIVITY_RUNNING: 'ACTIVITY_RUNNING',
    ACTIVITY_PAUSED: 'ACTIVITY_PAUSED',
    ACTIVITY_ENDED: 'ACTIVITY_ENDED',
    SHOWING_RESULTS: 'SHOWING_RESULTS'
};

/**
 * Evaluate a footstep event against the current engine state.
 *
 * @param {string} currentState   - One of STATES.*
 * @param {{ score: number, activeTargets: Array }} gameState
 * @param {{ hits: number, misses: number, reactionTimes: number[] }} sessionMetrics
 * @param {{ zone: string, source?: string }} msg - The incoming footstep message
 *
 * @returns {{
 *   accepted: boolean,
 *   feedback: string|null,   // 'POP' | 'STEP_EMPTY' | null
 *   targetId: string|null,   // populated on HIT
 *   updatedGameState: object,
 *   updatedMetrics: object
 * }}
 */
export function evaluateFootstep(currentState, gameState, sessionMetrics, msg) {
    // Guard: only process footsteps while the activity is actively running
    if (currentState !== STATES.ACTIVITY_RUNNING) {
        return {
            accepted: false,
            feedback: null,
            targetId: null,
            updatedGameState: gameState,
            updatedMetrics: sessionMetrics
        };
    }

    const zone = msg.zone;

    // Shallow-clone mutable structures so callers can diff before/after
    const updatedGameState = {
        ...gameState,
        activeTargets: [...gameState.activeTargets]
    };
    const updatedMetrics = {
        ...sessionMetrics,
        reactionTimes: [...sessionMetrics.reactionTimes]
    };

    const targetIndex = updatedGameState.activeTargets.findIndex(t => t.zone === zone);

    if (targetIndex !== -1) {
        const target = updatedGameState.activeTargets[targetIndex];
        const reactionTime = Date.now() - target.spawnTime;
        
        if (target.type === 'BOMB') {
            // STEP_BOMB — stepped on a bomb! Penalty.
            updatedGameState.activeTargets.splice(targetIndex, 1);
            updatedGameState.score = Math.max(0, updatedGameState.score - 5);
            return {
                accepted: true,
                feedback: 'STEP_BOMB',
                targetId: target.id,
                zone: zone, // Need to pass zone for the TV to know where the bomb was
                updatedGameState,
                updatedMetrics
            };
        }

        // HIT — normal or golden
        updatedMetrics.reactionTimes.push(reactionTime);
        updatedMetrics.hits++;
        updatedGameState.activeTargets.splice(targetIndex, 1);
        
        let scoreGain = 10;
        if (target.type === 'GOLDEN') {
            // Mais tempo = mais pontos (risco/recompensa)
            scoreGain = reactionTime > 2000 ? 30 : 15;
        }
        updatedGameState.score += scoreGain;

        return {
            accepted: true,
            feedback: target.type === 'GOLDEN' ? 'POP_GOLDEN' : 'POP',
            targetId: target.id,
            zone: zone,
            updatedGameState,
            updatedMetrics
        };
    } else {
        // STEP_EMPTY — stepped on a zone with no active target
        return {
            accepted: true,
            feedback: 'STEP_EMPTY',
            targetId: null,
            updatedGameState,
            updatedMetrics
        };
    }
}
