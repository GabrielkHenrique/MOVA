/**
 * tests/engine.test.js
 * ====================
 * Unit tests for the MOVA engine's pure game logic.
 *
 * Uses Node's built-in test runner (node:test) — no external runner needed.
 * Run with:
 *   node --experimental-vm-modules tests/engine.test.js
 *   (or simply: node tests/engine.test.js  on Node 20+)
 */

import { test } from 'node:test';
import assert from 'node:assert/strict';
import { evaluateFootstep, STATES } from '../engine/game-logic.js';

// ── Helpers ───────────────────────────────────────────────────────────────────

/** Build a minimal gameState with no active targets and score 0. */
function makeGameState(overrides = {}) {
    return {
        score: 0,
        timeRemaining: 60,
        activeTargets: [],
        ...overrides
    };
}

/** Build a minimal sessionMetrics object. */
function makeMetrics(overrides = {}) {
    return {
        hits: 0,
        misses: 0,
        reactionTimes: [],
        totalRounds: 0,
        startTime: Date.now(),
        ...overrides
    };
}

/** Construct a fake active target in the given zone. */
function makeTarget(zone, id = 'balloon_test') {
    return { id, zone, spawnTime: Date.now() - 500 }; // 500ms old
}

// ── Tests ─────────────────────────────────────────────────────────────────────

test('footstep rejected in IDLE — score stays 0', () => {
    const gs = makeGameState();
    const metrics = makeMetrics();
    const msg = { type: 'footstep', zone: 'front', source: 'simulator' };

    const result = evaluateFootstep(STATES.IDLE, gs, metrics, msg);

    assert.equal(result.accepted, false, 'should not be accepted');
    assert.equal(result.feedback, null, 'no feedback should be emitted');
    assert.equal(result.updatedGameState.score, 0, 'score must remain 0');
    assert.equal(result.updatedMetrics.hits, 0, 'hits must remain 0');
});

test('footstep rejected in SHOWING_RESULTS — score stays 0', () => {
    const gs = makeGameState({ score: 30 }); // pretend a game just ended
    const metrics = makeMetrics({ hits: 3 });
    const msg = { type: 'footstep', zone: 'back', source: 'simulator' };

    const result = evaluateFootstep(STATES.SHOWING_RESULTS, gs, metrics, msg);

    assert.equal(result.accepted, false, 'should not be accepted');
    assert.equal(result.updatedGameState.score, 30, 'score must not change');
    assert.equal(result.updatedMetrics.hits, 3, 'hits must not change');
});

test('footstep accepted in ACTIVITY_RUNNING — matching zone gives HIT and score increases', () => {
    const target = makeTarget('left');
    const gs = makeGameState({ activeTargets: [target] });
    const metrics = makeMetrics();
    const msg = { type: 'footstep', zone: 'left', source: 'esp32' };

    const result = evaluateFootstep(STATES.ACTIVITY_RUNNING, gs, metrics, msg);

    assert.equal(result.accepted, true, 'should be accepted');
    assert.equal(result.feedback, 'POP', 'feedback should be POP');
    assert.equal(result.targetId, target.id, 'targetId should match');
    assert.equal(result.updatedGameState.score, 10, 'score should increase by 10');
    assert.equal(result.updatedGameState.activeTargets.length, 0, 'target should be removed');
    assert.equal(result.updatedMetrics.hits, 1, 'hits should increment');
    assert.equal(result.updatedMetrics.reactionTimes.length, 1, 'reaction time should be recorded');
});

test('footstep accepted in ACTIVITY_RUNNING — no matching zone gives STEP_EMPTY, score unchanged', () => {
    const target = makeTarget('right');
    const gs = makeGameState({ activeTargets: [target] });
    const metrics = makeMetrics();
    const msg = { type: 'footstep', zone: 'front', source: 'esp32' }; // wrong zone

    const result = evaluateFootstep(STATES.ACTIVITY_RUNNING, gs, metrics, msg);

    assert.equal(result.accepted, true, 'should be accepted (footstep is valid)');
    assert.equal(result.feedback, 'STEP_EMPTY', 'feedback should be STEP_EMPTY');
    assert.equal(result.targetId, null, 'no targetId on empty step');
    assert.equal(result.updatedGameState.score, 0, 'score must not change on empty step');
    assert.equal(result.updatedMetrics.hits, 0, 'hits must not change on empty step');
});

test('footstep rejected in ACTIVITY_PAUSED — score stays unchanged', () => {
    const target = makeTarget('center');
    const gs = makeGameState({ score: 20, activeTargets: [target] });
    const metrics = makeMetrics({ hits: 2 });
    const msg = { type: 'footstep', zone: 'center', source: 'esp32' };

    const result = evaluateFootstep(STATES.ACTIVITY_PAUSED, gs, metrics, msg);

    assert.equal(result.accepted, false, 'should not be accepted while paused');
    assert.equal(result.updatedGameState.score, 20, 'score must remain unchanged');
    assert.equal(result.updatedMetrics.hits, 2, 'hits must remain unchanged');
    assert.equal(result.updatedGameState.activeTargets.length, 1, 'active targets must not be removed');
});

test('source field is purely decorative — game result is identical regardless of source', () => {
    const target = makeTarget('back');
    const gsSim  = makeGameState({ activeTargets: [{ ...target }] });
    const gsEsp  = makeGameState({ activeTargets: [{ ...target }] });

    const resultSim = evaluateFootstep(
        STATES.ACTIVITY_RUNNING, gsSim, makeMetrics(),
        { type: 'footstep', zone: 'back', source: 'simulator' }
    );
    const resultEsp = evaluateFootstep(
        STATES.ACTIVITY_RUNNING, gsEsp, makeMetrics(),
        { type: 'footstep', zone: 'back', source: 'esp32' }
    );

    assert.equal(resultSim.feedback, resultEsp.feedback, 'feedback must match');
    assert.equal(resultSim.updatedGameState.score, resultEsp.updatedGameState.score, 'score must match');
    assert.equal(resultSim.updatedMetrics.hits, resultEsp.updatedMetrics.hits, 'hits must match');
});
