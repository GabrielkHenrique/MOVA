#!/usr/bin/env python3
"""Teste navegador com HTTP simulado explícito; nunca comprova hardware."""
import base64,json,pathlib,subprocess,threading,time,urllib.request,urllib.error
from http.server import ThreadingHTTPServer,BaseHTTPRequestHandler
ROOT=pathlib.Path(__file__).resolve().parents[1]
OUT=ROOT/'docs/evidencias/2026-11-24-browser';OUT.mkdir(parents=True,exist_ok=True)
state={'offline':False,'slow':False,'led':'automatico','cm':40}
class Handler(BaseHTTPRequestHandler):
 def log_message(self,*args):pass
 def do_GET(self):
  if self.path.startswith('/api/'):
   if state['slow']:time.sleep(3)
   status=503 if state['offline'] else 200
   sensor={'valido':True,'distancia_cm':state['cm'],'idade_ms':20}
   body=json.dumps(sensor if self.path=='/api/sensor' else {'origem':'ESP32','boot_id':'FIXTURE-NAO-HARDWARE','uptime_ms':100,'sensor':sensor,'led':{'modo':state['led'],'ligado':state['led']=='ligar'}}).encode()
  elif self.path=='/audio.ogg':status=200;body=(ROOT/'data/audio.ogg').read_bytes()
  elif self.path in ('/','/local'):
   status=200;body=(ROOT/'pipo-entrega-gelada-final.html').read_text()
   if self.path=='/':body=body.replace("location.hostname==='192.168.4.1'","location.hostname==='127.0.0.1'")
   body=body.replace('<main>','<main><p style="background:#ffe16a;color:#111;padding:12px;font-weight:bold">TESTE LOCAL · HTTP SIMULADO · NÃO É HARDWARE</p>').encode()
  else:status=404;body=b''
  self.send_response(status);self.send_header('Content-Type','text/html' if self.path in ('/','/local') else 'application/json');self.end_headers()
  try:self.wfile.write(body)
  except (BrokenPipeError,ConnectionResetError):pass
 def do_POST(self):
  state['led']=json.loads(self.rfile.read(int(self.headers['Content-Length'])))['modo'];self.path='/api/status';self.do_GET()
server=ThreadingHTTPServer(('127.0.0.1',0),Handler);threading.Thread(target=server.serve_forever,daemon=True).start()
driver=subprocess.Popen(['chromedriver','--port=9517','--allowed-ips=127.0.0.1'],stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
sid=None
opener=urllib.request.build_opener(urllib.request.ProxyHandler({}))
def req(method,path,data=None):
 r=urllib.request.Request('http://127.0.0.1:9517'+path,data=None if data is None else json.dumps(data).encode(),method=method,headers={'Content-Type':'application/json'})
 with opener.open(r,timeout=15) as f:return json.load(f)['value']
def js(s):return req('POST',f'/session/{sid}/execute/sync',{'script':s,'args':[]})
def wait(s,timeout=10):
 end=time.monotonic()+timeout
 while time.monotonic()<end:
  if js('return '+s):return
  time.sleep(.1)
 raise AssertionError(s)
def shot(name): (OUT/name).write_bytes(base64.b64decode(req('GET',f'/session/{sid}/screenshot')))
checks=[]
try:
 for i in range(50):
  try:req('GET','/status');break
  except urllib.error.URLError:time.sleep(.1)
 sid=req('POST','/session',{'capabilities':{'alwaysMatch':{'browserName':'chrome','goog:chromeOptions':{'args':['--headless=new','--no-sandbox','--disable-dev-shm-usage','--window-size=1280,1400']},'goog:loggingPrefs':{'browser':'ALL'}}}})['sessionId']
 url=f'http://127.0.0.1:{server.server_port}'
 req('POST',f'/session/{sid}/url',{'url':url+'/local'})
 wait("document.querySelector('#benchSensor').textContent.includes('Simulado')")
 assert js("return document.querySelector('[data-led]').disabled")
 shot('desktop-local.png');checks.append('Prévia identificada como simulada, LED desabilitado')
 req('POST',f'/session/{sid}/window/rect',{'width':390,'height':844})
 assert js('return document.documentElement.scrollWidth<=innerWidth')
 assert js("return document.querySelector('.project-brand img').naturalWidth>0")
 assert js("return getComputedStyle(document.querySelector('#menuOv')).overflowY==='auto'")
 shot('mobile-local.png');checks.append('390px sem overflow, logo carregado e menu com rolagem interna')
 req('POST',f'/session/{sid}/url',{'url':url+'/'})
 wait("document.querySelector('#benchSensor').textContent.includes('40 cm')")
 js("document.querySelector('[data-mode=calm]').click();return true")
 state['cm']=20;wait("document.querySelector('#ledTxt').textContent.includes('PERNA NO ALTO')")
 js("document.querySelector('[data-led=ligar]').click();return true")
 wait("document.querySelector('#benchLog').textContent.includes('confirmado')")
 time.sleep(1.2);assert js("return document.querySelector('#benchLog').textContent.includes('POST')")
 checks.append('Distância simulada controla jogo; comando LED e confirmação persistente')
 state['offline']=True
 wait("document.querySelector('#benchLed').textContent.includes('não confirmado')")
 assert js("return document.querySelector('[data-led]').disabled")
 wait("document.querySelector('#ledTxt').textContent==='SEM SINAL'")
 checks.append('HTTP 503 invalida estado e entrada, desabilita comandos')
 state['offline']=False;wait("!document.querySelector('[data-led]').disabled")
 state['slow']=True
 wait("document.querySelector('#benchLed').textContent.includes('não confirmado')")
 state['slow']=False;wait("!document.querySelector('[data-led]').disabled")
 checks.append('Timeout 2s e recuperação automática sem recarregar')
 req('POST',f'/session/{sid}/window/rect',{'width':1280,'height':1400})
 shot('desktop-fixture.png')
 js("document.querySelector('#benchPanel').scrollIntoView();return true");shot('painel-fixture.png')
 errors=req('POST',f'/session/{sid}/log',{'type':'browser'})
 severe=[e for e in errors if e['level']=='SEVERE' and 'javascript' in e.get('source','')]
 assert not severe,severe
 checks.append('Sem exceções JavaScript no navegador')
 (OUT/'resultado.json').write_text(json.dumps({'tipo':'HTTP SIMULADO, NÃO HARDWARE','aprovado':True,'verificacoes':checks},ensure_ascii=False,indent=2))
 print('\n'.join(checks))
finally:
 if sid:req('DELETE',f'/session/{sid}')
 driver.terminate();driver.wait(timeout=5);server.shutdown()
