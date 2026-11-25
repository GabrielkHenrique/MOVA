#!/usr/bin/env python3
"""Bancada HTTP. Sem --atuar faz apenas GET. Não comprova a atuação física."""
import argparse, json, urllib.request, urllib.error, pathlib, time
p = argparse.ArgumentParser(description=__doc__)
p.add_argument('url', help='http://IP_REAL_DA_PLACA')
p.add_argument('--atuar', action='store_true', help='Envia comandos de LED e restaura modo automático')
p.add_argument('--saida', required=True, help='Nova pasta para evidências desta execução')
a = p.parse_args()
out = pathlib.Path(a.saida); out.mkdir(parents=True, exist_ok=False)
registro = []
def consultar(rota, metodo='GET', corpo=None, tipo='application/json', esperado=200):
    req=urllib.request.Request(a.url.rstrip('/')+rota, data=corpo, method=metodo, headers={'Content-Type':tipo})
    t=time.monotonic()
    try: r=urllib.request.urlopen(req, timeout=5)
    except urllib.error.HTTPError as e: r=e
    with r: dados=r.read(); status=r.status; headers=dict(r.headers)
    i=len(registro)+1
    (out/f'{i:02d}.body').write_bytes(dados)
    registro.append({'rota':rota,'metodo':metodo,'corpo':corpo.decode(errors='replace') if corpo else None,'status':status,'esperado':esperado,'headers':headers,'duracao_ms':(time.monotonic()-t)*1000})
    (out/'http.json').write_text(json.dumps(registro,indent=2,ensure_ascii=False))
    assert status==esperado, (rota,status,esperado)
    return dados,headers
status=json.loads(consultar('/api/status')[0]); assert status['origem']=='ESP32'
consultar('/')
sensor=json.loads(consultar('/api/sensor')[0]); assert isinstance(sensor['valido'],bool)
assert sensor['distancia_cm'] is None or isinstance(sensor['distancia_cm'],(int,float))
if a.atuar:
    consultar('/api/led', esperado=405)
    consultar('/inexistente', esperado=404)
    consultar('/api/led','POST',b'{',esperado=400)
    consultar('/api/led','POST',b'{"modo":"invalido"}',esperado=400)
    consultar('/api/led','POST',b'{"modo":"ligar","modo":"desligar"}',esperado=400)
    consultar('/api/led','POST',b'x'*129,esperado=413)
    consultar('/api/led','POST',b'{"modo":"ligar"}',tipo='text/plain',esperado=415)
    for modo in ['ligar','desligar','automatico']:
        s=json.loads(consultar('/api/led','POST',json.dumps({'modo':modo}).encode())[0])
        assert s['led']['modo']==modo
        if modo!='automatico': assert s['led']['ligado']==(modo=='ligar')
print('Consultas HTTP aprovadas. Verificar sensor e LED fisicamente; respostas não comprovam circuito.')
