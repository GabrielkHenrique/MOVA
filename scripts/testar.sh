#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
python3 scripts/gerar-pagina.py
node --test tests/pipo-web.test.cjs
python3 - <<'CHECK'
from pathlib import Path
import re,subprocess,tempfile
source=Path('pipo-entrega-gelada-final.html').read_text()
with tempfile.NamedTemporaryFile(suffix='.js',mode='w') as f:
    f.write('\n'.join(re.findall(r'<script>(.*?)</script>',source,re.S)));f.flush()
    subprocess.run(['node','--check',f.name],check=True)
CHECK
