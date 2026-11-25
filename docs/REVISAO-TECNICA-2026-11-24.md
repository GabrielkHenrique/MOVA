# Revisão técnica — NEO MOVA / Pipo

Data: 24/11/2026. Escopo desta revisão: código, compilação e navegador com servidor HTTP simulado. **Esta revisão isolada não comprova funcionamento físico do sensor ou LED.** As evidências reais da placa coletadas separadamente devem ser consultadas em conjunto.

## Correções realizadas

- Logo MOVA existente adaptado para Pipo, preservando o símbolo e substituindo identificações antigas por “PIPO · ENTREGA GELADA” e “NEO MOVA”. Arquivo `assets/mova-pipo.svg`, embarcado no HTML como data URI; não depende da internet ou de rota adicional no ESP32.
- Cabeçalho com contraste, título Pipo e link direto para painel de servidor/sensor/atuador.
- Menu em telas pequenas permite rolagem interna para alcançar todos os modos e opções.
- Consultas HTTP com prazo de 2 segundos, incluindo consumo do corpo JSON; reagendamento após falha permite recuperação sem recarregar a página.
- Ausência de rede invalida leitura e estado atual do atuador na interface; controles indisponíveis enquanto não há conexão confirmada.
- Confirmação de POST permanece no painel, sem ser substituída pela consulta periódica de status.
- Antes da primeira resposta do ESP32, a entrada permanece sem sinal: não utiliza movimento simulado na página servida pela placa.
- Cliente rejeita leituras de sensor com idade superior a 250 ms ou distância não numérica; falha de consulta invalida o sinal.
- Removida indicação de fase de jogo inexistente na API de status. O LED aparece como saída **comandada**, exigindo inspeção física para provar emissão de luz.
- Script `testar-http.py` atualizado para `/api/sensor`, retirando dependência das rotas legadas `/api/quadro` e `/api/logs`.
- Script `verificar-pipo-placa.py` usa pasta nova por execução, retorna erro ao falhar, verifica resposta dos comandos e permite URL/destino explícitos. A conexão Wi-Fi é opcional; por padrão preserva a rede atual.

## Validação local

`bash scripts/testar.sh`: 23 testes Node aprovados; 11 grupos C++ aprovados com AddressSanitizer/UndefinedBehaviorSanitizer; referência de quadro idêntica entre C++ e JavaScript. Parte substancial dessa suíte pertence ao protótipo legado de quebra-blocos, portanto não deve ser apresentada como cobertura integral do Pipo.

`python3 tests/pipo-browser.py`: teste específico do Pipo em Chromium real, usando servidor HTTP simulado em loopback. A captura traz indicação explícita de simulação. Verificações:

1. Prévia local identificada como simulada e comandos físicos desabilitados.
2. Logo carregado e ausência de overflow horizontal em 390 px.
3. Menu móvel com rolagem interna.
4. Leitura simulada de 40 para 20 cm produz mudança no controle da perna.
5. Comando LED apresenta confirmação e preserva o log após consultas periódicas.
6. HTTP 503 invalida estados e entrada, desabilitando controles.
7. Resposta lenta excede o prazo e a conexão se recupera automaticamente.
8. Ausência de exceções JavaScript no navegador.

Evidências: `docs/evidencias/2026-11-24-browser/resultado.json`, `desktop-local.png`, `mobile-local.png`, `desktop-fixture.png`, `painel-fixture.png`.

Compilação: `bash scripts/compilar.sh --output-dir /tmp/neo-mova-build-2026-11-24`, perfil `esp32:esp32:esp32`, core instalado. O build inclui a página gerada novamente a partir do HTML canônico. Valores finais do build devem ser consultados no registro do processo de gravação.

## Limites e reprodução

O HTTP simulado usa `boot_id=FIXTURE-NAO-HARDWARE` e não acessa a rede da placa. Logo visível, layout e comportamento de falha são comprovados no navegador; sensor físico, LED luminoso, fiação e IP real dependem de ensaio na placa.

A identificação do modo placa usa o endereço `http://192.168.4.1`, coerente com o AP atual. Servir a página por outro endereço requer adaptar essa identificação. A trilha continua em SPIFFS e não integra o binário de aplicação; atualizar somente o firmware preserva, mas não instala, o arquivo de áudio.
