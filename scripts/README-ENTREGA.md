# NEO MOVA — Pipo: Entrega Gelada

Sistema ciberfísico acadêmico: o ESP32 hospeda um servidor HTTP e um ponto de acesso Wi-Fi; adquire distância do HC-SR04 e comanda LED. O navegador recebe a página Pipo e executa o jogo, desenho, áudio e métricas. Esta entrega contém somente a versão Pipo Web e suas ferramentas, sem os motores/protótipos antigos.

```text
HC-SR04 → ESP32 (Wi-Fi AP + HTTP + sensor + LED) ↔ navegador Pipo
                     /api/sensor  /api/status  /api/led
```

O servidor fica em `http://192.168.4.1/` na rede `NEO-MOVA`. A senha local de demonstração está declarada em `firmware/neo_mova/config.h`; não é credencial de conta ou serviço externo.

## Arquivos

- `pipo-entrega-gelada-final.html`: cliente canônico com logo e painel de bancada.
- `firmware/neo_mova/neo_mova.ino`: aquisição do sensor e servidor HTTP.
- `firmware/neo_mova/pagina.h`: página embarcada, gerada a partir do HTML.
- `assets/mova-pipo.svg`: identidade MOVA adaptada ao Pipo.
- `data/audio.ogg`: trilha da aplicação, servida por SPIFFS.
- `docs/API.md` e `docs/HARDWARE.md`: contrato de rede e montagem.
- `docs/AUDITORIA-2026-11-24.md`: requisitos e pendências factuais.
- `docs/REVISAO-TECNICA-2026-11-24.md`: alterações e limites dos testes.
- `MANIFESTO-ARQUIVOS.tsv`: arquivos, tamanhos e SHA-256 da cópia preparada.

## Compilar e executar

Requer Python 3, Node.js, Arduino CLI com core `esp32:esp32` 3.3.12. O teste visual também usa Chromium e ChromeDriver. Instale o core, se ainda não disponível:

```sh
arduino-cli core update-index --additional-urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli core install esp32:esp32@3.3.12 --additional-urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
bash scripts/testar.sh
bash scripts/compilar.sh --output-dir /tmp/neo-mova-build
arduino-cli board list
```

Após conferir a placa e a porta reais:

```sh
arduino-cli upload --fqbn esp32:esp32:esp32 --port /dev/ttyUSB0 --upload-property upload.speed=115200 --input-dir /tmp/neo-mova-build firmware/neo_mova
```

A atualização da aplicação não instala a trilha SPIFFS. Em uma placa já preparada ela é preservada; em placa nova, será necessário preparar a partição SPIFFS com `data/audio.ogg` conforme a tabela de partições selecionada. O jogo funciona sem trilha se o arquivo estiver ausente. Não grave uma imagem de filesystem em offset presumido.

Conecte o computador/celular ao AP `NEO-MOVA` e abra `http://192.168.4.1/`. O cliente identifica esse endereço como placa. Abrir o arquivo local gera simulação e não permite comandos físicos.

```sh
python3 scripts/verificar-pipo-placa.py --saida /tmp/neo-evidencia-nova
python3 scripts/testar-http.py http://192.168.4.1 --atuar --saida /tmp/neo-http-novo
python3 tests/pipo-browser.py
```

Os dois primeiros comandos acessam a placa; com `--atuar` ou no verificador completo, enviam comandos ao LED. O último usa HTTP simulado, identificado nas capturas, sem comprovar hardware.

## Situação verificada

O baseline real de 24/11/2026 confirmou página, áudio, servidor e respostas aos comandos `ligar`, `desligar` e `automatico`. O sensor reportou 555 amostras inválidas e nenhuma válida naquele registro. Resposta de GPIO não comprova emissão luminosa: é necessário observar o LED físico. Consultar a auditoria para os resultados posteriores ao baseline e manter esta distinção ao apresentar o trabalho.

O build revisado usa 1.076.772 bytes de programa (82%) e 46.280 bytes de RAM estática (14%). Os testes de navegador com HTTP simulado cobrem layout, logo, comando, perda de rede, timeout e recuperação; não substituem a demonstração física.

## Entrega acadêmica e GitHub

Equipe, RAs, turma/professor, contribuições individuais e aprovação do tema ainda precisam ser informados. O PDF explicativo não substitui o modelo oficial do professor quando este for exigido.

Esta cópia foi inicializada localmente para revisão. Não há remoto publicado ou URL GitHub presumida. Depois de definir o repositório correto, publicar o histórico verdadeiro e permitir acesso ao professor quando necessário. Não inventar commits ou autores de integrantes.

A identificação visual e a mecânica de movimento descrevem um protótipo acadêmico; não há validação clínica de benefício terapêutico.
