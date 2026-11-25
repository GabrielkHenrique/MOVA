#!/usr/bin/env python3
"""Ensaio HTTP de duração limitada; registra leituras reais sem simulação."""
import argparse
import concurrent.futures
import datetime
import json
import pathlib
import statistics
import time
import urllib.request

p = argparse.ArgumentParser(description=__doc__)
p.add_argument('--url', default='http://192.168.4.1')
p.add_argument('--segundos', type=int, default=180)
p.add_argument('--saida', required=True)
a = p.parse_args()
out = pathlib.Path(a.saida)
out.mkdir(parents=True, exist_ok=False)

def consulta(rota):
    inicio = time.monotonic()
    row = {'rota': rota, 'instante': datetime.datetime.now(datetime.timezone.utc).isoformat()}
    try:
        opener = urllib.request.build_opener(urllib.request.ProxyHandler({}))
        with opener.open(a.url.rstrip('/') + rota, timeout=4) as r:
            row.update(status=r.status, resposta=json.loads(r.read()))
    except Exception as e:
        row['erro'] = str(e)
    row['ms'] = round((time.monotonic() - inicio) * 1000, 2)
    return row

rows = []
fim = time.monotonic() + a.segundos
with (out / 'amostras.jsonl').open('w') as log, concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:
    while time.monotonic() < fim:
        lote = list(pool.map(consulta, ['/api/sensor', '/api/sensor', '/api/status']))
        rows.extend(lote)
        for row in lote:
            log.write(json.dumps(row, ensure_ascii=False) + '\n')
        log.flush()
        time.sleep(.2)
ok = [r for r in rows if r.get('status') == 200]
sensor = [r['resposta'] for r in ok if r['rota'] == '/api/sensor']
status = [r['resposta'] for r in ok if r['rota'] == '/api/status']
latencias = sorted(r['ms'] for r in ok)
validas = [s for s in sensor if s.get('valido')]
resumo = {'url': a.url, 'duracao_solicitada_s': a.segundos, 'requisicoes': len(rows),
          'sucessos': len(ok), 'falhas': len(rows) - len(ok),
          'leituras_sensor': len(sensor), 'leituras_validas': len(validas),
          'distancias_validas_cm': sorted(set(s['distancia_cm'] for s in validas)),
          'boot_ids': sorted(set(s.get('boot_id', '') for s in status)),
          'latencia_mediana_ms': statistics.median(latencias) if latencias else None,
          'latencia_p95_ms': latencias[int((len(latencias)-1)*.95)] if latencias else None,
          'primeiro_status': status[0] if status else None, 'ultimo_status': status[-1] if status else None,
          'limite': 'HTTP comprova resposta; observar o LED e a montagem requer confirmação física.'}
(out / 'resumo.json').write_text(json.dumps(resumo, indent=2, ensure_ascii=False))
print(json.dumps(resumo, indent=2, ensure_ascii=False))
raise SystemExit(0 if ok and len(ok) == len(rows) else 1)
