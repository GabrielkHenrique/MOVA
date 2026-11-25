# Auditoria documental do TDE — NEO MOVA / Pipo

Data da inspeção: **24/11/2026**. Base normativa: [Manual e Regulamento do TDE — Conectividade em Sistemas Ciberfísicos, PUCPR](TDE01-regulamento-tde.pdf), lido integralmente por extração de texto. Esta matriz incorpora a inspeção inicial e o **ensaio real de baseline de 24/11**, anterior à gravação das correções desta rodada. A validação final do firmware revisado ainda está pendente nesta atualização.

## Conclusão parcial após o baseline real

A arquitetura do projeto é compatível com o requisito central: o ESP32 executa um servidor HTTP, recebe consultas e comandos de um navegador, lê um HC-SR04 e comanda um GPIO para LED. O jogo pode executar no navegador: o regulamento não exige que suas regras sejam processadas na placa. HTTP é suficiente; não é obrigatório implementar também TCP e UDP. O modo Access Point local sem internet é explicitamente aceito pela FAQ 14.

**Não há base documental para declarar toda a entrega concluída.** O ensaio real de 24/11 comprova servidor, página, áudio e respostas aos três comandos do LED, mas registra 555 amostras inválidas e nenhuma válida. Não comprova visualmente a atuação do LED. Os registros de 19/11 continuam identificados separadamente como históricos. Aprovação do tema, identificação da equipe, participação individual, demonstração presencial e modelo oficial do relatório dependem de documentos ou ações da equipe/professor.

## Matriz dos requisitos

| Referência | Exigência | Constatação nesta inspeção | Como encerrar a verificação |
|---|---|---|---|
| §2.1 | Equipe de 3–5 estudantes; exceções autorizadas | Não identificada nos documentos do NEO-MOVA; relatórios MOVA relacionados também mantêm campos em branco | Registrar nomes/RAs e, se aplicável, autorização real da exceção |
| §§2.3, 6.3 e 8.2 | Participação de todos, commits e defesa individual | Não demonstrada por arquivos locais isolados | Conferir histórico verdadeiro e preparar explicação de contribuições de cada integrante |
| §3.3 e Etapa 1 | Contexto justificável e tema aprovado | Pipo oferece interação lúdica por distância; aprovação do escopo não localizada | Anexar aprovação do tema; não afirmar benefício clínico validado |
| §3.4 | Montagem física e funcionamento real | Baseline real de 24/11 comprova comunicação com a placa; não encerra sensor/LED físicos | Demonstrar bancada e partida comandada por sensor físico |
| §4.1 | ESP32 com Wi-Fi | Placa disponível por USB/AP nesta rodada; HTTP real responde como ESP32; registros antigos identificam ESP32-D0WD-V3 | Guardar identificação atual e foto/modelo comercial da montagem |
| §4.2 — sensor | Pelo menos um sensor físico funcional | HC-SR04 implementado; baseline 24/11 tem 555 inválidas e `amostras_validas:0` | Obter e guardar leituras válidas variáveis com alvo em posições conhecidas |
| §4.2 — atuador | Pelo menos um atuador físico comandável | Saída LED GPIO2 implementada; baseline 24/11 confirma os três modos por HTTP 200 | Observar/filmar LED real acender e apagar por comando de rede |
| §4.3 | ESP32 como servidor ativo | HTTP real em 24/11: página, áudio, sensor/status e comandos responderam pela placa | Repetir após gravação das correções; baseline já registra boot e respostas |
| §4.4 | Ao menos um protocolo aceito | HTTP implementado e exercitado na placa em 24/11 | Revalidar firmware final |
| §4.5.1 | Leitura atualizada pela rede | `GET /api/sensor` respondeu HTTP 200 em 24/11, porém com distância nula/validade falsa | Demonstrar várias distâncias válidas e novas amostras recebidas pelo cliente |
| §4.5.2 | Comando remoto de atuador | `POST /api/led`: três modos com HTTP 200 e estados correspondentes guardados no baseline | Observar o atuador físico e repetir após gravação final |
| §4.5.3 | Exibição clara de conexão, sensor e atuador | Página atual do baseline capturada; revisão de logos, mobile e estado obsoleto em andamento | Inspecionar página atual em desktop/celular e durante falha/recuperação |
| Etapa 1 | Diagrama, materiais, prova local e GitHub inicial | Arquitetura textual e pinagem configurada documentadas; montagem não confirmada | Completar esquema e materiais reais e conferir repositório |
| Etapa 2 | Wi-Fi, servidor, API e validação das rotas | Wi-Fi/HTTP/API exercitados em placa em 24/11 | Encerrar leitura física, observação do LED e revalidar correções |
| Etapa 3 | Cliente integrado, estresse e falhas | Revisão de timeouts/estado obsoleto em andamento; testes com respostas simuladas relatados como aprovados, sem equivalência a bancada | Executar carga limitada, interrupção/retorno de rede, comandos inválidos e partida com sensor |
| §6.1 | Organização do repositório e `.gitignore` | Pastas firmware, scripts, tests e docs separadas; cópia inicial sem `.git` | Vincular versão correta ao GitHub e excluir artefatos de build/segredos do versionamento |
| §6.2 | README: título, problema, equipe, arquitetura, hardware, API, instalação e imagens | Título, arquitetura, API e comandos presentes; faltam equipe/RAs e montagem comprovada | Completar metadados reais, esquema, instrução de áudio/SPIFFS e evidências atuais |
| §6.3 e rubrica | Histórico de commits de todos | Não auditável na cópia inicial sem Git | Consultar repositório correto; preservar autoria real, sem commits retroativos inventados |
| §7 | Relatório técnico segundo guia separado | Guia genérico/PDF anterior existe; modelo específico do professor não localizado | Entregar PDF explicativo fiel e adequá-lo ao template quando fornecido |
| §8 | Apresentação presencial e defesa | Não é comprovável por testes automatizados | Apresentar sensor, consulta, atuador e explicações individuais ao professor |
| §9 | Responsabilidade e compreensão do código, mesmo com IA | Auxílio de IA pode ser documentado; compreensão não é verificável automaticamente | Equipe revisar firmware, protocolos, tratamento de ruído/falhas e contribuições |
| FAQ 12 | Se GitHub privado, acesso do professor | Destino e visibilidade ainda não confirmados nesta inspeção | Conferir acesso; convite exige identidade correta do professor |

## Baseline real de 24/11/2026

Fonte inspecionada: [`evidencias/2026-11-24/baseline/verificacao-http.json`](evidencias/2026-11-24/baseline/verificacao-http.json). URL: `http://192.168.4.1/`. O registro marca restauração Wi-Fi bem-sucedida e captura do navegador com código de saída zero.

| Verificação real | Resultado |
|---|---|
| Página | HTTP 200; 92.758 bytes; igualdade byte a byte com HTML canônico anterior às correções |
| Áudio | HTTP 200; 1.022.632 bytes; Ogg reconhecido, `audio/ogg` |
| Status | HTTP 200; `origem:ESP32`, versão `neo-mova-web-1`, boot `90d36f6cda5e49c3`, uptime 39.087 ms |
| Sensor | HTTP 200; `valido:false`, `distancia_cm:null`; contador 555 inválidas/0 válidas |
| LED ligar | HTTP 200; modo `ligar`, `ligado:true` |
| LED desligar | HTTP 200; modo `desligar`, `ligado:false` |
| LED automático | HTTP 200; modo `automatico`, `ligado:false` |

Esses resultados confirmam comunicação e comandos aplicados pelo firmware. A resposta JSON não é observação óptica do LED; o sensor ainda precisa de alvo/leitura válida. Foi solicitado ao usuário posicionar um alvo. A causa da ausência de eco não está estabelecida por esses dados.

Na atualização desta matriz, a cópia de segurança da flash está **em execução**, conforme acompanhamento da sessão principal; sua conclusão/integridade ainda não foi incorporada. A revisão técnica trata timeouts, indicação de estado obsoleto, logos e layout móvel. Testes com respostas simuladas foram relatados como aprovados, mas a gravação e a validação física finais ainda precisam de evidência própria.

## Detalhes técnicos observados

O arquivo `firmware/neo_mova/config.h` configura TRIG GPIO13, ECHO GPIO26 e LED GPIO2 ativo alto. O firmware dispara aquisição a cada 70 ms, aguarda eco por até 25 ms e aceita distância de 5–60 cm. A classificação usa limiares de 28/32 cm e duas amostras confirmadoras. Esses valores são configurações de software; não provam fiação ou distância física real. A montagem precisa registrar GND comum, alimentação, adaptação do nível de ECHO e LED/resistor quando externo.

O log histórico `evidencias/2026-11-19-tde-web/verificacao-http.json` registra HTML com 92.758 bytes, áudio com 1.022.632 bytes e HTTP 200 nas rotas testadas. O estado do sensor nessa coleta era inválido e as 1.609 amostras registradas eram inválidas. O texto histórico relata ausência de alvo; a resposta digital, sozinha, não identifica a causa de um eco ausente.

A inspeção inicial do HTML encontrou `fetch` de sensor/status/LED sem prazo explícito de cancelamento. Como a próxima consulta é agendada após a anterior terminar, uma requisição pendurada pode manter a interface sem atualização. Essa é uma melhoria verificável por software para a Etapa 3: limitar duração, marcar dado antigo/indisponível e testar recuperação. A ausência inicial desse tratamento não deve ser confundida com resultado de ensaio físico.

Logos visíveis são um pedido adicional do usuário. O regulamento fornecido não exige logos específicos, nem define tamanho/posição. Sua conferência deve incluir legibilidade, contraste e presença nos tamanhos de tela utilizados. Não se deve inventar marca institucional ou tratar inclusão de logo como prova de requisito de hardware.

## Ações que podem ser concluídas por software

1. Conferir e corrigir interface, legibilidade dos logos, conexão e idade/validade da telemetria.
2. Compilar firmware e executar testes pertinentes, distinguindo testes do Pipo atual de componentes legados.
3. Preparar captura de evidências com data, versão, requisições/respostas e limitações.
4. Organizar documentação, instruções de reprodução, esquema correspondente à configuração e PDF explicativo.
5. Conferir/publicar no repositório autorizado correto, preservando autoria e histórico existentes.

## Ações dependentes de bancada ou confirmação humana

- O ESP32 já está disponível por USB/AP; falta confirmar/documentar montagem e registrar o ensaio final após as correções.
- Mover alvo/perna no campo do HC-SR04 e observar o LED comandado; guardar evidência visual real.
- Confirmar nomes/RAs, turma, professor, aprovação do tema, composição e contribuições da equipe.
- Fornecer o template específico, caso já tenha sido divulgado, e realizar a apresentação/defesa.

Os pesos do §10 são hardware/firmware 25%, servidor/protocolos 25%, cliente/interface 15%, GitHub 15% e apresentação/defesa 20%. Esta auditoria não atribui nota nem aprovação acadêmica.
