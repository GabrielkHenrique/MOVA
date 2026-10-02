# A Onça / Estátua (Em Breve)

## Resumo Técnico (Fase 3 - Experimento Avançado)
Este jogo é projetado para forçar a **Inibição Motora (Go-No-Go)**. É a mecânica que treina a capacidade de interromper o próprio corpo, vital para prevenir quedas no mundo real.

## Blueprint Arquitetural (Para a Equipe Desenvolvedora)
- **Mecânica Principal:** O jogador deve dar passos repetidos. Um sinal de alerta soa e 1 segundo depois o obstáculo aparece. O jogador deve interromper completamente o movimento (*Freeze*).
- **Hardware constraints:** O jogo é construído em torno do que o sensor *não deve* sentir. Se o Piezo detectar qualquer impacto > `noiseFloor + threshold` durante o período "congelado", o jogador falha.
- **Integração:** O motor vai precisar inverter a lógica. O `evaluateFootstep` penaliza a existência de um evento, em vez da ausência dele, durante os estados críticos.

*Status: Apenas Blueprint. Jogo puramente experimental.*
