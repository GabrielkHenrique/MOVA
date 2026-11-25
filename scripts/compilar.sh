#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
python3 scripts/gerar-pagina.py
# Perfil de compilação; não confirma modelo, flash ou montagem da placa física.
arduino-cli compile --fqbn "${NEO_FQBN:-esp32:esp32:esp32}" --warnings all firmware/neo_mova "$@"
