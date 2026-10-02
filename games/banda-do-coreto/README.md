# Banda do Coreto (Em Breve)

## Resumo Técnico (Fase 2)
Este jogo será focado em **Precisão Temporal, Memória e Ritmo**. Ele valida a capacidade motora auditiva.

## Blueprint Arquitetural (Para a Equipe Desenvolvedora)
- **Mecânica Principal:** Sincronizar o passo com a batida musical ou repetir uma sequência tocada por um instrumento.
- **Hardware constraints:** A latência visual/auditiva deve estar estritamente alinhada com o servidor. O motor de jogo precisará calcular a diferença de tempo (em milissegundos) entre o "timestamp" do evento enviado pelo ESP32 e o tempo exato da batida na música.
- **Integração:** Adicionar suporte a áudio síncrono no frontend (`apps/tv`). O Motor (`engine/server.js`) emitirá `EVT_BEAT` para sincronizar.

*Status: Apenas Blueprint. Agendado para desenvolvimento pós-validação do MVP (Estoura Balões).*
