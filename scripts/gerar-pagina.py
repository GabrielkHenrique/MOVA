#!/usr/bin/env python3
"""Embarca o jogo Pipo web original em uma string C++ servida pelo ESP32."""
from pathlib import Path
raiz = Path(__file__).resolve().parents[1]
pagina = (raiz/'pipo-entrega-gelada-final.html').read_text()
assert ')NEOPIPO"' not in pagina
(raiz/'firmware/neo_mova/pagina.h').write_text('// Gerado por scripts/gerar-pagina.py; editar pipo-entrega-gelada-final.html.\n#pragma once\nstatic const char PAGINA[] = R"NEOPIPO('+pagina+')NEOPIPO";\n')
