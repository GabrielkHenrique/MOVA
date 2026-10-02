# A Maré (Em Breve)

## Resumo Técnico (Fase 2)
Este jogo explora o conceito hiperfocado do **Tapete como Espaço Físico (Risco × Recompensa)** e deslocamento inercial.

## Blueprint Arquitetural (Para a Equipe Desenvolvedora)
- **Mecânica Principal:** O jogador deve sair da Zona Central (casa), pisar em uma Zona Externa (concha) e *voltar obrigatoriamente* para a Zona Central antes que a maré suba.
- **Hardware constraints:** Exige que o "debounce" físico do ESP32 esteja perfeitamente calibrado para reconhecer dois passos rápidos em direções diferentes.
- **Integração:** 
  1. O motor do jogo deve implementar o conceito de `safeZone = 'center'`.
  2. Penalidade grave se o `footstep` mais recente não for `'center'` quando a maré subir.

*Status: Apenas Blueprint. Agendado para desenvolvimento na Fase 2.*
