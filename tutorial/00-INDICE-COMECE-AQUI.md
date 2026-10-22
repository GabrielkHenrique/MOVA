# 🎈 Manual Completo de Montagem do Projeto MOVA (PassoCerto)

Bem-vindo ao guia oficial de montagem do **MOVA**! Este diretório foi criado para ensinar **qualquer pessoa da equipe — mesmo quem nunca mexeu com eletrônica, fios ou programação antes —** a montar o projeto inteiro do zero até funcionar no jogo.

---

## 📂 Ordem de Leitura e Montagem

Siga os arquivos exatamente na ordem numérica abaixo:

1. **[`01-CONHECENDO-AS-PECAS-E-PROTOBOARD.md`](./01-CONHECENDO-AS-PECAS-E-PROTOBOARD.md)**
   - Aprenda em 3 minutos como os furinhos da protoboard funcionam e como identificar cada peça (ESP32, Piezo, Resistores, Diodo Zener e LEDs) só de olhar para elas.
2. **[`02-PREPARANDO-CABOS-DE-REDE-E-PIEZOS.md`](./02-PREPARANDO-CABOS-DE-REDE-E-PIEZOS.md)**
   - Como descascar o cabo de rede, qual cor de fio usar para cada uma das 5 zonas do tapete e como emendar os fios nos sensores piezoelétricos sem dar mau contato.
3. **[`03-MONTAGEM-NA-PROTOBOARD-5-ZONAS.md`](./03-MONTAGEM-NA-PROTOBOARD-5-ZONAS.md)**
   - O passo a passo **furo por furo** para espetar os componentes na protoboard (começando por 1 zona para testar e depois multiplicando para as 5 zonas + 5 LEDs).
4. **[`04-MONTAGEM-FISICA-DO-TAPETE.md`](./04-MONTAGEM-FISICA-DO-TAPETE.md)**
   - Como organizar os 5 sensores no formato de cruz no chão, passar os cabos de rede com segurança e montar a estrutura física (com ou sem madeira/EVA).
5. **[`05-GRAVANDO-ESP32-E-RODANDO-O-JOGO.md`](./05-GRAVANDO-ESP32-E-RODANDO-O-JOGO.md)**
   - Como gravar o código no ESP32, testar os 5 sensores no computador, conectar no Wi-Fi `MOVA-ESP32` e abrir o Painel do Terapeuta e a TV do Paciente.
6. **[`06-SOLUCAO-DE-PROBLEMAS-E-CHECKLIST.md`](./06-SOLUCAO-DE-PROBLEMAS-E-CHECKLIST.md)**
   - Guia de socorro rápido ("E se uma zona disparar sozinha?", "E se não acender?", "Checklist para o dia da apresentação").

---

## 🛒 Lista Geral de Materiais na Mesa

Antes de abrir o arquivo `01`, confira se você tem tudo separado na bancada:

### Eletrônica
- [ ] **1x Placa ESP32 DevKit V1** (30 ou 38 pinos) + **1x Cabo USB de dados** (Micro-USB ou USB-C)
- [ ] **1x Protoboard** (matriz de contatos grande, de preferência 830 pontos — ou 2 protoboards médias)
- [ ] **5x Discos Piezoelétricos (27 mm ou 35 mm)** com fios vermelho e preto
- [ ] **5x Resistores de 1 MΩ (1 Megaohm)** *(Cores: Marrom – Preto – Verde – Dourado)*
- [ ] **5x Diodos Zener de 3.3V (ex: 1N4728)** *(Pequena peça de vidro laranja com uma listra preta)*
- [ ] **5x LEDs comuns (5 mm ou 3 mm)** de qualquer cor
- [ ] **5x Resistores de 220 Ω (ou 330 Ω)** *(Cores: Vermelho – Vermelho – Marrom – Dourado)*
- [ ] **Jumpers Macho-Macho** (ou pedacinhos do próprio fio rígido do cabo de rede)

### Cabos e Ferramentas Práticas
- [ ] **Cabo de rede (Ethernet CAT5e ou CAT6)** para descascar
- [ ] **Tesoura, alicate de corte ou estilete** (para descascar os fios)
- [ ] **Fita isolante** (ou fita crepe/esparadrapo em último caso) para isolar as emendas dos piezos

---

👉 **Próximo passo:** Abra agora o arquivo **[`01-CONHECENDO-AS-PECAS-E-PROTOBOARD.md`](./01-CONHECENDO-AS-PECAS-E-PROTOBOARD.md)**!
