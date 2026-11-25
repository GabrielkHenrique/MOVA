#!/usr/bin/env python3
"""Prepara cópia Pipo por allowlist; não publica, não cria commits, não sobrescreve destino."""
import argparse,hashlib,pathlib,shutil,subprocess,json,re
ROOT=pathlib.Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser(description=__doc__);p.add_argument('destino');a=p.parse_args()
out=pathlib.Path(a.destino).resolve();out.mkdir(parents=True,exist_ok=False)
files=['pipo-entrega-gelada-final.html','assets/mova-pipo.svg','data/audio.ogg',
'firmware/neo_mova/neo_mova.ino','firmware/neo_mova/config.h','firmware/neo_mova/protocolo.h','firmware/neo_mova/pagina.h',
'scripts/gerar-pagina.py','scripts/compilar.sh','scripts/verificar-pipo-placa.py','scripts/testar-http.py','scripts/empacotar-entrega.py','scripts/README-ENTREGA.md',
 'tests/pipo-web.test.cjs','tests/pipo-browser.py',
'docs/API.md','docs/HARDWARE.md','docs/AUDITORIA-2026-11-24.md','docs/REVISAO-TECNICA-2026-11-24.md','docs/TDE01-regulamento-tde.pdf']
for optional in ['scripts/ensaio-rede.py']:
 if (ROOT/optional).is_file():files.append(optional)
for name in files:
 target=out/name;target.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(ROOT/name,target)
# Evidências atuais selecionadas; nunca flash de backup, vídeos ou fontes antigas.
for folder in ['docs/evidencias/2026-11-24-browser','docs/evidencias/2026-11-24/baseline']:
 for source in (ROOT/folder).glob('*'):
  if source.suffix in ('.png','.json'):
   target=out/source.relative_to(ROOT);target.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(source,target)
shutil.copy2(ROOT/'scripts/README-ENTREGA.md',out/'README.md')
(out/'.gitignore').write_text('**/build/\n__pycache__/\n*.pyc\n*.bin\n*.elf\n*.map\n.env\n.env.*\n!*.example\n')
(out/'scripts/testar.sh').write_text('''#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
python3 scripts/gerar-pagina.py
node --test tests/pipo-web.test.cjs
python3 - <<'CHECK'
from pathlib import Path
import re,subprocess,tempfile
source=Path('pipo-entrega-gelada-final.html').read_text()
with tempfile.NamedTemporaryFile(suffix='.js',mode='w') as f:
    f.write('\\n'.join(re.findall(r'<script>(.*?)</script>',source,re.S)));f.flush()
    subprocess.run(['node','--check',f.name],check=True)
CHECK
''')
patterns=[r'-----BEGIN (?:RSA |EC |OPENSSH )?PRIVATE KEY-----',r'gh[pousr]_[A-Za-z0-9]{20,}',r'github_pat_[A-Za-z0-9_]{20,}',r'AKIA[0-9A-Z]{16}',r'sk-[A-Za-z0-9]{32,}']
findings=[]
for source in out.rglob('*'):
 if source.is_file() and source.suffix not in ('.png','.pdf','.ogg'):
  content=source.read_text(errors='ignore')
  if any(re.search(pattern,content) for pattern in patterns):findings.append(str(source.relative_to(out)))
(out/'REVISAO-SEGREDOS.json').write_text(json.dumps({'tipo':'Varredura básica por padrões; não garantia absoluta','arquivos_com_alerta':findings,'senha_AP':'Credencial intencional de rede local de demonstração em config.h'},ensure_ascii=False,indent=2))
rows=['arquivo\tbytes\tsha256']
for source in sorted(out.rglob('*')):
 if source.is_file():rows.append(f'{source.relative_to(out)}\t{source.stat().st_size}\t{hashlib.sha256(source.read_bytes()).hexdigest()}')
(out/'MANIFESTO-ARQUIVOS.tsv').write_text('\n'.join(rows)+'\n')
subprocess.run(['git','init','-b','main',str(out)],check=True)
subprocess.run(['git','-C',str(out),'add','.'],check=True)
print(json.dumps({'destino':str(out),'arquivos':len(rows)-1,'alertas':findings,'commit':False,'remoto':False},ensure_ascii=False))
if findings:raise SystemExit(1)
