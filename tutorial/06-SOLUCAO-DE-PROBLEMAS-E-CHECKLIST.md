# 🚑 Passo 6: Solução de Problemas e Checklist de Apresentação

Guarde este arquivo aberto no celular ou no computador durante a montagem e no dia da apresentação!

---

## 1. Tabela de Socorro Rápido (Hardware & Sensores)

| Sintoma / O que está acontecendo | Causa mais provável | Como resolver em 10 segundos |
| :--- | :--- | :--- |
| **Uma zona fica disparando `[IMPACT]` sozinha sem ninguém encostar** | O **Resistor de 1 MΩ** daquela fileira está frouxo no furo da protoboard, ou o fio `GND` soltou. | Empurre bem firme as duas pernas do Resistor de 1 MΩ daquela zona até o fundo do furo e aperte o botão **`EN`** no ESP32. |
| **Acabei de conectar um piezo com o ESP32 já ligado e ele ficou "duro" (precisa bater muito forte)** | O ESP32 calibrou o pino quando ele ainda estava vazio (flutuando com ruído alto, `threshold=900+`). | Aperte o botão **`EN` (Reset)** no ESP32 e aguarde 2 segundos sem tocar nos sensores. O `threshold` cairá para `300`. |
| **Bato no piezo de uma zona e NADA aparece no Serial Monitor** | 1) O fio vermelho (`+`) e o preto (`-`) estão encostando um no outro na emenda, ou<br>2) O **Diodo Zener está invertido**, ou<br>3) O fio está na fileira errada da protoboard. | 1) Veja se a emenda do piezo está isolada.<br>2) Confira se a **listra preta** do Diodo Zener está na fileira do piezo (`Furo A`) e **não** na Linha Azul (`GND`). |
| **Bato em uma zona (ex: Centro), mas no Serial Monitor sai outra zona (ex: Frente)** | Os fios do cabo de rede foram trocados na chegada da protoboard. | Confira a tabela: `VP(36)=Centro`, `D34=Frente`, `D35=Direita`, `D32=Trás`, `D33=Esquerda`. |
| **O sensor funciona no Serial Monitor, mas o LED daquela zona não acende** | O LED está invertido. | Tire o LED da protoboard e gire 180° (**perna MAIOR** no resistor de 220 Ω, **perna MENOR** na Linha Azul `GND`). |
| **O cabo de rede é flexível (cabelinhos finos) e não entra no furo da protoboard** | Fios multifilares dobram nas molinhas da protoboard. | Enrole a ponta descascada do cabo de rede direto na perninha metálica do **Resistor de 1 MΩ** e espete a perna do resistor no furo! |

---

## 2. Tabela de Socorro Rápido (Software & Wi-Fi)

| Sintoma / O que está acontecendo | Causa mais provável | Como resolver |
| :--- | :--- | :--- |
| **Painel do Terapeuta mostra `ESP32 conectando…` (laranja) ou `✗ ESP32 desconectado`** | O Wi-Fi do notebook ainda está conectado na internet da casa/faculdade em vez do ESP32. | Conecte o Wi-Fi do notebook na rede **`MOVA-ESP32`** (senha: **`mova1234`**). Em até 3 segundos o painel muda sozinho para **`● ESP32 conectado`** (verde)! |
| **O comando `node engine/server.js` dá erro `EADDRINUSE :::8080`** | Já existe outro `server.js` (ou outro programa) usando a porta `8080`. | No Linux rode `fuser -k 8080/tcp` (ou feche o outro terminal que já está rodando o `server.js`). |
| **Piso no tapete, o Serial Monitor mostra `[IMPACT]`, mas a TV não estoura o balão** | 1) A atividade ainda não foi iniciada no Painel do Terapeuta (`IDLE`), ou<br>2) O script `node hardware/esp32-client.js` não está rodando. | Clique em **`▶ Iniciar Atividade`** no Painel do Terapeuta e confira se o Terminal 3 (`node hardware/esp32-client.js`) está aberto. |

---

## 3. Checklist de 2 Minutos Antes de Apresentar para o Professor

Faça esta conferência rápida 5 minutos antes da banca/apresentação:

- [ ] **1. Fios firmes:** O fio `GND` do ESP32 está firme na Linha Azul (`-`) da protoboard e os 5 resistores de `1 MΩ` estão bem espetados.
- [ ] **2. Calibração limpa:** Ligue o ESP32 no USB (ou Powerbank), aperte o botão **`EN`** sem ninguém pisar no tapete por 2 segundos e veja o LED azul da placa dar as **3 piscadinhas de pronto**.
- [ ] **3. Wi-Fi conectado:** O notebook está conectado na rede Wi-Fi **`MOVA-ESP32`** (senha `mova1234`).
- [ ] **4. Três terminais abertos:**
  - Terminal 1: `node engine/server.js`
  - Terminal 2: `npx serve . --listen 3000`
  - Terminal 3: `node hardware/esp32-client.js`
- [ ] **5. Duas abas abertas no navegador:**
  - Aba 1 (na tela do notebook): `http://localhost:3000/apps/therapist-panel/` mostrando **`● ESP32 conectado`** em verde.
  - Aba 2 (na TV/Projetor em tela cheia `F11`): `http://localhost:3000/apps/tv/`
- [ ] **6. Som da TV:** Dê um clique em qualquer lugar da aba da TV antes de começar (os navegadores exigem 1 clique na página para liberar os efeitos sonoros do Web Audio API!).

---

## 🛡️ Plano B de Emergência (Se um fio soltar no meio da apresentação)

Se durante a apresentação alguém tropeçar no cabo e arrancar a protoboard:
1. Não precisa parar a apresentação nem reiniciar nenhum servidor!
2. Basta abrir uma aba em **`http://localhost:3000/simulator/`** (no próprio notebook ou celular).
3. Explique para a banca: *"Como a arquitetura do MOVA desacopla o hardware do motor de jogo via protocolo de eventos WebSocket, podemos continuar a sessão clínica exatamente do mesmo ponto usando o Simulador Virtual."*
