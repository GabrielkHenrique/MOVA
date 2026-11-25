#!/usr/bin/env python3
"""Verifica o Pipo Web e a API do ESP32 no AP local; restaura o Wi-Fi anterior."""
import argparse
import datetime
import sys
import json
import pathlib
import shutil
import subprocess
import time
import urllib.request

ROOT = pathlib.Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--url', default='http://192.168.4.1/')
parser.add_argument('--saida', default=str(ROOT / 'docs/evidencias' / datetime.datetime.now().strftime('%Y-%m-%d-%H%M%S-placa')))
parser.add_argument('--conectar-wifi', action='store_true', help='Conecta ao AP e restaura a rede anterior')
parser.add_argument('--interface', default='wlp1s0')
args = parser.parse_args()
EVIDENCE = pathlib.Path(args.saida)
EVIDENCE.mkdir(parents=True, exist_ok=False)
URL = args.url.rstrip('/') + '/'
WIFI = args.interface
uuid = None
if args.conectar_wifi:
    uuid = subprocess.check_output(['nmcli', '-g', 'GENERAL.CON-UUID', 'device', 'show', WIFI], text=True).strip()
    if not uuid or uuid == '--':
        raise SystemExit('Não encontrei a conexão Wi-Fi anterior para restaurar.')

log = {"url": URL, "data": datetime.datetime.now().astimezone().isoformat(), "restauracao_wifi": None}
try:
    if args.conectar_wifi:
        scan = subprocess.run(["nmcli", "device", "wifi", "list", "--rescan", "yes"], capture_output=True, text=True, timeout=20)
        if "NEO-MOVA" not in scan.stdout:
            raise RuntimeError("A rede NEO-MOVA não apareceu na busca.")
        up = subprocess.run(["nmcli", "device", "wifi", "connect", "NEO-MOVA", "password", "neo-mova-2026", "ifname", WIFI], capture_output=True, text=True, timeout=30)
        if up.returncode:
            raise RuntimeError(up.stderr.strip() or "Não foi possível conectar ao AP.")
    opener = urllib.request.build_opener(urllib.request.ProxyHandler({}))

    def get(path):
        inicio = time.monotonic()
        with opener.open(URL + path, timeout=30) as response:
            data, headers, status = response.read(), dict(response.headers), response.status
        return data, headers, status, round((time.monotonic() - inicio) * 1000, 2)

    page, _, page_status, page_ms = get("")
    (EVIDENCE / "pipo-servido.html").write_bytes(page)
    source = (ROOT / "pipo-entrega-gelada-final.html").read_bytes()
    page_lower = page.lower()
    log["pagina"] = {
        "status": page_status,
        "bytes": len(page),
        "igual_ao_original": page == source,
        "pipo": b"PIPO: ENTREGA GELADA" in page,
        "interface_web": b"<canvas" in page_lower and b"tela cheia" in page_lower,
        "latencia_ms": page_ms,
    }

    audio, audio_headers, audio_status, audio_ms = get("audio.ogg")
    (EVIDENCE / "audio-servido.ogg").write_bytes(audio)
    log["audio"] = {
        "status": audio_status,
        "bytes": len(audio),
        "ogg": audio.startswith(b"OggS"),
        "content_type": audio_headers.get("Content-Type"),
        "latencia_ms": audio_ms,
    }
    sensor, _, sensor_status, sensor_ms = get("api/sensor")
    log["sensor"] = {"status": sensor_status, "resposta": json.loads(sensor), "latencia_ms": sensor_ms}
    status, _, status_code, status_ms = get("api/status")
    log["status"] = {"status": status_code, "resposta": json.loads(status), "latencia_ms": status_ms}

    log["comandos_led"] = []
    for mode in ("ligar", "desligar", "automatico"):
        payload = json.dumps({"modo": mode}).encode()
        request = urllib.request.Request(URL + "api/led", data=payload, headers={"Content-Type": "application/json"}, method="POST")
        inicio = time.monotonic()
        with opener.open(request, timeout=10) as response:
            result = json.loads(response.read())
            log["comandos_led"].append({
                "modo_solicitado": mode,
                "status": response.status,
                "modo_retornado": result.get("led", {}).get("modo"),
                "led_ligado": result.get("led", {}).get("ligado"),
                "latencia_ms": round((time.monotonic() - inicio) * 1000, 2),
            })

    for command in log["comandos_led"]:
        if command["modo_solicitado"] != command["modo_retornado"]:
            raise RuntimeError("Estado retornado não corresponde ao comando LED")
        if command["modo_solicitado"] != "automatico" and command["led_ligado"] != (command["modo_solicitado"] == "ligar"):
            raise RuntimeError("Saída comandada do LED inconsistente")

    browser = shutil.which("chromium")
    if browser:
        screenshot = EVIDENCE / "pipo-web-esp32.png"
        result = subprocess.run([
            browser, "--headless", "--no-sandbox", "--disable-gpu", "--disable-dev-shm-usage",
            "--hide-scrollbars", "--window-size=1280,1500", "--virtual-time-budget=2500",
            "--user-data-dir=/tmp/pipo-web-esp32-chromium", "--screenshot=" + str(screenshot), URL,
        ], capture_output=True, text=True, timeout=40)
        log["navegador"] = {"screenshot": str(screenshot), "exit_code": result.returncode, "saida": result.stderr[-2000:]}

    if not (log["pagina"]["igual_ao_original"] and log["pagina"]["interface_web"] and log["audio"]["ogg"]):
        raise RuntimeError("A página embarcada não corresponde ao Pipo Web original ou o áudio falhou.")
    if log["status"]["resposta"].get("origem") != "ESP32":
        raise RuntimeError("GET /api/status não confirmou origem ESP32.")
except Exception as exc:
    log["erro"] = str(exc)
finally:
    if uuid:
        down = subprocess.run(["nmcli", "connection", "up", "uuid", uuid, "ifname", WIFI], capture_output=True, text=True, timeout=30)
        log["restauracao_wifi"] = down.returncode == 0
    (EVIDENCE / "verificacao-http.json").write_text(json.dumps(log, indent=2, ensure_ascii=False))
print(json.dumps(log, indent=2, ensure_ascii=False))

sys.exit(1 if "erro" in log or log["restauracao_wifi"] is False else 0)
