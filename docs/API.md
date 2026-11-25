# API do servidor NEO MOVA

O regulamento aceita a aplicação cliente em **Web, Mobile ou Terminal** (TDE01, seção 2.2/6.2; rubrica, p. 13). O cliente deste projeto é a página web original do Pipo. O ESP32 atua como servidor HTTP ativo, lê o HC-SR04, responde estado e comanda o LED. As regras, o Canvas, o áudio reproduzido e as métricas de jogo permanecem no navegador, sem mudança na lógica do Pipo.

Placa identificada nos registros: ESP32-D0WD-V3 rev. 3.1, flash 4 MB. Build Arduino-ESP32 3.3.12, FQBN de referência `esp32:esp32:esp32`. O servidor cria o AP `NEO-MOVA`; o IP usual da placa é `192.168.4.1`.

| Método e rota | Cliente/uso |
|---|---|
| GET `/` | Baixa a página HTML completa do Pipo, embarcada no firmware. |
| GET `/api/sensor` | Retorna leitura atual do HC-SR04, validade, perna classificada e idade da amostra. O jogo consulta a rota enquanto está servido pelo ESP32. |
| GET `/api/status` | Estado da placa, sensor, LED, boot/uptime e métricas do firmware. A interface de bancada usa a resposta para explicar a arquitetura. |
| POST `/api/led` | Comanda `ligar`, `desligar` ou `automatico` para a saída física. |
| GET `/audio.ogg` | Entrega trilha Ogg/Opus da partição SPIFFS. |

Exemplo:

```http
POST /api/led HTTP/1.1
Content-Type: application/json

{"modo":"ligar"}
```

Resposta JSON inclui `origem:"ESP32"`, `boot_id`, `uptime_ms`, `sensor`, `led`, `jogo.execucao:"cliente_web"` e `metricas`. `GET /api/sensor` retorna `{valido, distancia_cm, perna_levantada, idade_ms}`; distância sem eco é JSON `null`. Amostras aceitas pelo firmware: 5–60 cm; classificação com histerese 28/32 cm e duas amostras confirmadoras. O jogo mantém seu próprio filtro e estado na aplicação web.

LED automático acompanha o estado de perna alta; modos manuais forçam ligado/desligado até selecionar automático. A confirmação em JSON registra o nível GPIO comandado; não comprova visualmente a montagem do LED.

As métricas `/api/status` são da placa: heap livre/mínimo/maior bloco, uptime, contagens de amostras e transições, latência do filtro. As métricas de jogo (pontos, modos, desafios e interação) são calculadas pelo cliente Pipo e podem ser exportadas pelo próprio jogo. Não são medidas clínicas.

O servidor é local, sem TLS/autenticação. Não expor o AP à internet. Para testar a bancada e salvar respostas/screenshot:

```bash
python3 scripts/verificar-pipo-placa.py --conectar-wifi
```

Ver [manifesto da verificação web/ESP32](evidencias/2026-11-19-tde-web/MANIFESTO.md) e [texto integral do regulamento usado](TDE01-regulamento-tde.pdf).

Na revisão de 24/11, o cliente aplica timeout de 2 segundos, invalida estados ao perder conexão e tenta recuperar automaticamente. Testes com HTTP simulado comprovam esse comportamento do cliente; a evidência de hardware permanece registrada separadamente.
