# 🎈 MOVA (por PassoCerto)

**Uma plataforma de reabilitação motora gamificada controlada por um tapete físico.**

`[Software: Pronto]` `[Hardware: MVP Projetado]` `[Testes: 6/6 Passando]`

---

## 🌟 2. O que é o MOVA?

Bem-vindo ao **MOVA**! Se você nunca mexeu com eletrônica, Arduino ou programação antes, não se preocupe: este guia foi feito para você. 

O MOVA transforma exercícios de fisioterapia chatos em **jogos interativos**. O paciente pisa em um tapete físico no chão, e os movimentos são enviados sem fio para um jogo na TV! Tudo é acompanhado por um terapeuta que vê os resultados em tempo real.

**Como a mágica acontece:**

```text
Você pisa no tapete físico
        ↓
Sensor Piezo detecta o impacto
        ↓
ESP32 processa e envia por Wi-Fi
        ↓
Motor de Jogo (Node.js) recebe o evento
        ↓
Jogo Estoura! reage na TV
        ↓
Terapeuta vê métricas em tempo real
        ↓
Relatório PDF salvo ao final
```

---

## 🎮 3. Os Jogos

Nós projetamos o MOVA para suportar vários minigames terapêuticos. Aqui estão os jogos:

- 🎈 **Estoura!** *(Disponível Agora)* — Pise no lugar certo para estourar os balões e desvie das bombas! Foco em tempo de reação e precisão.
- 🎺 **Banda do Coreto** *(Em breve)* — Acerte o ritmo com os seus passos. Foco em coordenação motora e ritmo.
- 🌊 **A Maré** *(Em breve)* — Risco e recompensa: pegue as conchas antes que a onda chegue. Foco em velocidade e recuo.
- 🐾 **A Onça** *(Em breve)* — Estátua! Não faça nenhum som ou movimento quando a onça aparecer. Foco em controle inibitório e equilíbrio.

---

## 🏗️ 4. Arquitetura do Sistema

Veja como as peças se encaixam:

```text
 [Tapete Físico] 
   └── 5x Sensores Piezo 
         ↓ (Fios)
 [Microcontrolador ESP32]  <-- Lê os sensores e cria uma rede Wi-Fi
         ↓ (Wi-Fi WebSocket)
 [Ponte de Hardware] <-- Script rodando no seu PC (esp32-client.js)
         ↓ (Eventos JSON)
 [Motor do Jogo Node.js] <-- O cérebro do sistema (server.js)
         ├─→ [Painel do Terapeuta] (Navegador - Controle da Sessão)
         └─→ [TV do Paciente] (Navegador - O Jogo Visual)
```

---

## 🛒 5. Pré-requisitos (O que você precisa)

### 🔌 Hardware (Componentes Físicos)

| Componente | Para que serve? | Onde encontrar? |
| :--- | :--- | :--- |
| **ESP32 DevKit V1** | O "cérebro" que lê os sensores e tem Wi-Fi. | Lojas de eletrônica/MercadoLivre |
| **5x Disco Piezoelétrico (27mm)** | Detecta o impacto da pisada. | Lojas de eletrônica |
| **5x Resistor 1 MΩ (1/4W)** | Descarrega a tensão do piezo com segurança. | Lojas de eletrônica |
| **5x Diodo Zener 3.3V (1N4728)** | Protege o ESP32 de picos de energia. | Lojas de eletrônica |
| **5x LED (qualquer cor, 5mm)** | Feedback visual para saber se pisou certo. | Lojas de eletrônica |
| **5x Resistor 220 Ω** | Limita a corrente elétrica para não queimar o LED. | Lojas de eletrônica |
| **Protoboard (grande)** | Placa com furos para montar sem precisar soldar. | Lojas de eletrônica |
| **Jumpers (Macho-Macho, ~30)** | Fios para conectar tudo. | Lojas de eletrônica |
| **Cabo Micro-USB** | Para ligar o ESP32 no PC e gravar o código. | Gaveta de casa / Lojas |
| **Notebook com Windows** | Para rodar o servidor e os jogos. | Você já deve ter! |

### 💻 Software (Totalmente Grátis)
- [Node.js](https://nodejs.org/) (versão 18 ou mais recente)
- [Arduino IDE](https://www.arduino.cc/en/software) (versão 2.x)
- Um navegador de internet moderno (Google Chrome ou Edge)

---

## 🚀 6. Instalação do Software (Do zero a rodando em 10 min)

Siga os passos abaixo para iniciar o programa no seu computador.

**Passo 1:** Instale o Node.js baixado do site oficial.
**Passo 2:** Baixe ou clone a pasta deste projeto (`MOVA`) no seu computador.
**Passo 3:** Abra um terminal (PowerShell) dentro da pasta `MOVA`.

> [!TIP]
> Se o PowerShell disser que o `npm` não tem permissão para rodar, copie e cole este comando para corrigir:
> ```powershell
> Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned -Force
> ```

**Passo 4:** Instale as dependências (baixa as bibliotecas necessárias):
```powershell
npm install
```

**Passo 5:** Inicie o Motor do Jogo:
```powershell
node engine/server.js
```

**Passo 6:** Abra um NOVO terminal na mesma pasta e inicie o Servidor Web:
```powershell
npx serve . --listen 3000
```

**Passo 7:** Abra o navegador e acesse as telas do sistema:
- 🩺 **Painel do Terapeuta:** [http://localhost:3000/apps/therapist-panel/](http://localhost:3000/apps/therapist-panel/)
- 📺 **TV do Paciente:** [http://localhost:3000/apps/tv/](http://localhost:3000/apps/tv/)
- 🕹️ **Simulador:** [http://localhost:3000/simulator/](http://localhost:3000/simulator/)

**Passo 8:** Teste usando o Simulador! Clique nos botões da tela do simulador para fingir pisadas. A TV e o Painel devem reagir na mesma hora. ✅

---

## 🔧 7. Guia de Montagem do Hardware (MVP de 1 Zona)

> [!CAUTION]
> **PARE. Antes de conectar qualquer fio, leia esta seção inteira.** Ligar componentes nos pinos errados pode queimar o seu ESP32.

### Entendendo o Sensor Piezo
Um disco piezoelétrico é como um microfone para vibrações. Quando você o aperta, ele gera eletricidade. O problema é que, quando você o solta rápido, ele pode gerar um **PICO de até 90 volts**! O ESP32 só aguenta 3.3 volts. É por isso que o circuito de proteção é OBRIGATÓRIO.

### O Circuito de Proteção — OBRIGATÓRIO
- O **Resistor de 1MΩ** é como um ralo para excesso de água (tensão).
- O **Diodo Zener** é como uma válvula de alívio: se a energia passar de 3.3V, ele abre e manda o excesso para o terra (GND), salvando o ESP32.

### Diagrama de Fiação para UMA ZONA (Centro)
```text
          ESP32 DevKit V1
         ┌─────────────────┐
         │                 │
         │     GPIO36 ─────┼──┬── [+] Disco Piezo [-] ──── GND
         │                 │  │
         │                 │  ├── [Resistor 1 MΩ] ──────── GND
         │                 │  │
         │                 │  └── [Cátodo Zener 3.3V] ──── GND
         │                 │      [Ânodo Zener 3.3V]  ──── GND
         │                 │        (Cátodo = lado com a listra)
         │     GPIO25 ─────┼── [Resistor 220Ω] ── [LED +] ── [LED -] ── GND
         │                 │
         │     GND ────────┼── Todas as conexões GND vão juntas!
         │     3.3V ───────┼── (NÃO use o pino 5V / VIN para isso)
         └─────────────────┘
```

**Passo a passo da montagem:**
1. Coloque o ESP32 na protoboard.
2. Escolha uma linha azul da protoboard para ser o GND (Terra comum). Conecte um pino GND do ESP32 a esta linha.
3. Conecte o fio negativo (geralmente preto) do piezo no GND.
4. Conecte o fio positivo (geralmente vermelho) na linha do GPIO36.
5. Coloque o Resistor de 1MΩ ligando a linha do piezo positivo até o GND.
6. Coloque o Diodo Zener ligando a linha do piezo positivo até o GND. **Atenção:** o lado com a listra preta (cátodo) deve ficar do lado positivo (GPIO36).
7. Conecte o Resistor de 220Ω do GPIO25 até uma linha vazia.
8. Conecte a perna longa do LED (Positivo) nessa linha do resistor, e a perna curta (Negativo) no GND.

---

## ⚡ 8. Configurando o Arduino IDE

Agora precisamos gravar o "cérebro" do hardware!

1. Abra a Arduino IDE.
2. Vá em `File > Preferences` e adicione a URL das placas ESP32 no campo "Additional Boards Manager URLs": `https://dl.espressif.com/dl/package_esp32_index.json`
3. Vá em `Tools > Board > Boards Manager`, busque por "esp32" e instale o pacote da Espressif.
4. Vá em `Sketch > Include Library > Manage Libraries` e instale:
   - **WebSockets** (por Markus Sattler)
   - **ArduinoJson** (por Benoit Blanchon)
5. Abra o arquivo `firmware/mova_firmware_v2_one_zone.ino` deste projeto na Arduino IDE.
6. Vá em `Tools > Board` e selecione **"DOIT ESP32 DEVKIT V1"**.
7. Vá em `Tools > Port` e selecione a porta COM que apareceu quando conectou o cabo USB.
8. Clique na seta para a direita (`->`) no topo para fazer o **Upload**.

---

## 📡 9. Primeira Inicialização — O que esperar

Após o upload, vá em `Tools > Serial Monitor` e mude a velocidade (canto inferior direito) para **115200 baud**. 

Você deverá ver exatamente isso:
```text
[MOVA] Booting...
[GPIO] LEDs configured.
[WiFi] Starting Access Point...
[AP] MOVA-ESP32 started. IP: 192.168.4.1
[CALIB] Sampling noise floor: .............................
[CALIB] noiseFloor=45, stdDev=12, threshold=81
[WS] WebSocket server starting on port 81
[MOVA] Ready. Listening for impacts...
```
> [!NOTE]
> Se o limite (`threshold`) não aparecer ou for muito baixo, tente dar um toquinho no piezo para ver se a palavra `[IMPACT]` aparece na tela!

---

## 🔗 10. Conectando o Hardware ao Software

1. No seu notebook Windows, clique no ícone de Wi-Fi.
2. Conecte-se à rede **MOVA-ESP32** (A senha é: `mova1234`).
3. Abra um **TERCEIRO** terminal na pasta MOVA.
4. Rode a ponte de conexão:
```powershell
$env:ESP32_IP = "192.168.4.1"
node hardware/esp32-client.js
```
5. Olhe para o seu navegador (Painel do Terapeuta): A bolinha no topo deve mudar de "Simulador ativo" para um círculo verde dizendo **"● ESP32 conectado"**!

---

## 🎉 11. Jogando o Primeiro Jogo Físico

Com tudo conectado:
1. No Painel do Terapeuta, clique em **"Iniciar Sessão"**.
2. Clique em **"Iniciar Atividade"** no jogo Estoura!
3. Dê um tapinha rápido com o dedo no disco Piezo!
4. Olhe para a tela da TV: você verá os pés do jogo pulando e os balões estourando!
5. Continue por 60 segundos. No final, a tela de resultados aparecerá.
6. Clique em **"🖨️ Imprimir / Salvar PDF"** para ver seu relatório.

---

## 🛠️ 12. Solução de Problemas

| Problema | Causa Provável | Solução |
| :--- | :--- | :--- |
| **ESP32 não aparece nas portas COM** | Cabo de energia apenas, sem dados. | Use um cabo Micro-USB de dados (o de carregar celular às vezes não passa dados). |
| **Piezo não dispara o evento** | Fio frouxo ou limite de calibração alto. | Verifique se GND e GPIO36 estão firmes na protoboard. |
| **Passos falsos (dispara sem tocar)** | Falta do resistor de 1MΩ (ruído). | Garanta que o Resistor de 1MΩ está ligando o positivo do piezo ao GND. |
| **Jogo não reage na TV** | Faltou rodar o Bridge (`esp32-client.js`). | Abra o 3º terminal e rode o `node hardware/esp32-client.js` enquanto conectado no Wi-Fi do ESP32. |
| **Painel mostra ESP32 desconectado** | PC não está na rede Wi-Fi correta. | Conecte-se ao Wi-Fi "MOVA-ESP32" no Windows. |
| **O PDF fica vazio** | O navegador bloqueou o pop-up. | Permita pop-ups para o `localhost` e clique no botão novamente. |
| **`node engine/server.js` falha** | Falta rodar o comando de instalar. | Execute `npm install` primeiro para baixar as bibliotecas necessárias. |
| **PowerShell diz que `npm` não é permitido** | Política de segurança do Windows. | Rode `Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned -Force`. |

---

## 📁 13. Estrutura de Arquivos do Projeto

Aqui é onde você encontra cada parte do código:

```text
MOVA/
├── engine/
│   ├── server.js          # O servidor principal (O coração do sistema)
│   └── game-logic.js      # Regras do jogo puro (testáveis sem servidor)
├── apps/
│   ├── tv/                # A tela que o paciente assiste
│   └── therapist-panel/   # A tela que o terapeuta controla
├── simulator/             # Site que finge ser o tapete físico para testes
├── hardware/
│   └── esp32-client.js    # A "Ponte": Lê do ESP32 e manda para o Node.js
├── firmware/
│   └── mova_firmware_v2_one_zone.ino  # O código em C++ para gravar no ESP32
├── games/
│   ├── estoura-baloes/    # Arquivos do jogo atual
│   ├── banda-do-coreto/   # Em breve...
│   ├── a-mare/            # Em breve...
│   └── a-onca/            # Em breve...
├── docs/                  # Documentação extra
├── tests/
│   └── engine.test.js     # Script de testes automatizados
└── README.md              # Este guia que você está lendo!
```

---

## 🧪 14. Rodando os Testes

Para garantir que a lógica do servidor está perfeita antes de uma sessão clínica, você pode rodar os testes automáticos:

```powershell
node tests/engine.test.js
```
**Resultado esperado:** Você deve ver mensagens verdes indicando `6/6 tests passing` (6 de 6 testes passando).

---

## 🤝 15. Contribuindo e Regras de Arquitetura

Se você for programar novas funcionalidades para o MOVA, por favor leia:
- [AGENTS.md](file:///c:/Users/ghsb0/Documents/MOVA/AGENTS.md) - Para entender como os subagentes devem operar.
- [ARCHITECTURE.md](file:///c:/Users/ghsb0/Documents/MOVA/ARCHITECTURE.md) - Regras de ouro do projeto.

---

## 🛡️ 16. Aviso de Segurança (Safety Notice)

> [!IMPORTANT]
> - Este é um **protótipo acadêmico** e **NÃO** possui certificação de uso clínico/médico. 
> - O uso deve ser feito estritamente sob a **supervisão de um fisioterapeuta responsável**.
> - O tapete físico **deve obrigatoriamente possuir superfície antiderrapante** (EVA texturizado ou material similar) para evitar quedas.
> - Os resultados gerados são dados de demonstração da performance no jogo e não substituem exames diagnósticos.

---

## 📄 17. Licença

`Projeto Acadêmico — PassoCerto. Não licenciado para distribuição comercial.`
