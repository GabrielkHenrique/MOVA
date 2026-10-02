# MOVA — Roadmap & Gestão (Fases 1 a 3)

## Fase 1: Validação Física (MVP Estoura Balões) — EM ANDAMENTO
**Objetivo:** Conectar a peça física, o firmware V2 e o software, validando a latência e confiabilidade do piezo em 1 zona, depois expandindo para 5 zonas.
- [x] Motor de Jogo (Feature-frozen / Isolamento Lógico)
- [x] Firmware V2 (AP Mode + Algoritmo de Pico)
- [x] UI/UX do Terapeuta e PDF
- [x] Planta da Vila MOVA na UI do Paciente
- [ ] Construir o Protótipo Físico (ESP32 + 1 Piezo)
- [ ] Calibração de Threshold e Janela de Ruído (30ms peak)
- [ ] Concluir Validação Física e expandir para 5 zonas.

## Fase 2: O Nascimento dos Jogos Nativos
**Objetivo:** Começar a programar os jogos que dão identidade ao MOVA, substituindo os testes clínicos disfarçados por game design espacial.
- [ ] **Banda do Coreto:** Implementar motor síncrono para áudio. Emitir `EVT_BEAT`.
- [ ] **A Maré:** Implementar estado de "Zona Segura" (Centro) no motor e adicionar risco por não retorno.

## Fase 3: Experimentos de Sobrevivência Física
**Objetivo:** Forçar os limites motores do paciente.
- [ ] **A Onça:** Programar mecânica de inibição (falhar se o piezo detectar qualquer impacto no momento vermelho).
- [ ] Adicionar suporte a múltiplos perfis de dificuldade.
