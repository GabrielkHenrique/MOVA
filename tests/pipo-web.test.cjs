const test = require('node:test');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');

const root = path.resolve(__dirname, '..');
const game = fs.readFileSync(path.join(root, 'pipo-entrega-gelada-final.html'), 'utf8');
const ino = fs.readFileSync(path.join(root, 'firmware/neo_mova/neo_mova.ino'), 'utf8');
const generator = fs.readFileSync(path.join(root, 'scripts/gerar-pagina.py'), 'utf8');

test('a página embarcada é uma cópia exata do Pipo web original', () => {
  const header = fs.readFileSync(path.join(root, 'firmware/neo_mova/pagina.h'), 'utf8');
  const match = header.match(/R"NEOPIPO\(([\s\S]*)\)NEOPIPO";/);
  assert.ok(match, 'pagina.h precisa conter o HTML como string bruta');
  assert.equal(match[1], game);
  assert.match(generator, /pipo-entrega-gelada-final\.html/);
});

test('o cliente web mantém Pipo e integra sensor, status e atuador do ESP32', () => {
  assert.match(game, /window\.pipoSensor/);
  assert.match(game, /boardJson\('\/api\/sensor'/);
  assert.match(game, /boardJson\('\/api\/status'/);
  assert.match(game, /boardJson\('\/api\/led'/);
  assert.match(game, /data-mode="calm"/);
  assert.match(game, /function runStep\(/);
  assert.match(game, /exportMetrics/);
});

test('o firmware serve a página e mantém endpoints de requisito do TDE', () => {
  assert.match(ino, /httpd_start\(/);
  assert.match(ino, /httpd_register_uri_handler\(/);
  assert.match(ino, /"\/api\/sensor"/);
  assert.match(ino, /"\/api\/status"/);
  assert.match(ino, /"\/api\/led"/);
  assert.match(ino, /"\/"\)\)\s*\{/);
  assert.match(ino, /httpd_resp_send\(req, PAGINA/);
});
