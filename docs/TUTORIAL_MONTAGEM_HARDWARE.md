# 🛠️ Guia Completo de Montagem do Hardware MOVA (5 Zonas na Bancada)
*Para quem nunca mexeu com eletrônica na vida — passo a passo, furo por furo, sem madeira e sem EVA.*

> [!CAUTION]
> **REGRA DE OURO Nº 1:** Sempre **desconecte o cabo USB do ESP32** enquanto estiver espetando ou mudando fios de lugar. Só ligue o USB na hora de testar!

---

## 🧠 Parte 1: Entendendo a Protoboard em 2 Minutos

A **protoboard** (matriz de contatos) é uma placa plástica cheia de furinhos. Por dentro dela existem trilhas de metal que conectam certos furos entre si para você não precisar soldar nada.

Ela é dividida em **duas regiões totalmente diferentes**:

```text
   LATERAL ESQUERDA                MEIO DA PLACA                 LATERAL DIREITA
  (Barramentos Longos)          (Fileiras Numeradas)           (Barramentos Longos)
   [+]  [-]                    A  B  C  D  E     F  G  H  I  J   [+]  [-]
    │    │                  1 [●][●][●][●][●] │ [●][●][●][●][●]   │    │
    │    │                  2 [●][●][●][●][●] │ [●][●][●][●][●]   │    │
    │    │                  3 [●][●][●][●][●] │ [●][●][●][●][●]   │    │
    │    │                  4 [●][●][●][●][●] │ [●][●][●][●][●]   │    │
    ▼    ▼                                    ▲                   ▼    ▼
  Conectados na VERTICAL             Canaleta Central           Conectados na VERTICAL
  (de cima até embaixo!)         (separa A-E de F-J)            (de cima até embaixo!)
```

1. **As Linhas Laterais (`-` Azul e `+` Vermelha):**
   - Correm nas bordas da placa **de cima até embaixo**.
   - Todos os furinhos da coluna **Azul (`-`)** estão ligados entre si na vertical. Nós vamos usar essa linha azul como a nossa **"Lixeira de Energia" (Terra / `GND`)**.
   - *(Atenção: Em algumas protoboards grandes, a linha azul tem uma falha/espaço exatamente na metade da placa. Se a sua tiver a linha pintada cortada no meio, basta colocar um fiozinho ligando a metade de cima com a metade de baixo da linha azul).*
2. **As Fileiras do Meio (Numeradas `1, 2, 3...` com letras `A B C D E` e `F G H I J`):**
   - Aqui a conexão é **na HORIZONTAL** (de 5 em 5 furinhos).
   - Exemplo: Na **fileira 10**, os furos **`10A`, `10B`, `10C`, `10D` e `10E`** estão todos dando as mãos por baixo do plástico! Se você espetar dois fios em `10A` e `10D`, eles estão conectados.
   - Mas a **fileira 10 NÃO encosta na fileira 11**!
   - E a **canaleta (vala) no meio** separa o lado `A-E` do lado `F-J` (`10E` **não** está ligado em `10F`).

---

## 🔍 Parte 2: Conhecendo cada Peça com os Olhos

Antes de começar, separe as peças na mesa e veja como identificar cada uma:

### 1. A Placa ESP32 DevKit V1
- Tem uma entrada Micro-USB (ou USB-C) em uma ponta e dois botões pequenininhos ao lado dela: **`EN`** (Reset/Reiniciar) e **`BOOT`**.
- **Como ler os nomes dos pinos:** Olhe na placa (em cima ou na parte de baixo). Você verá códigos escritos ao lado de cada perninha:
  - **`GND`** = Terra (Negativo). A placa tem 2 ou 3 pinos `GND` — qualquer um serve.
  - **`VP` (ou `36`)**, **`D34`**, **`D35`**, **`D32`**, **`D33`** = São os 5 pinos que vão sentir as pisadas (**todos ficam do mesmo lado da placa!**).
  - **`D25`**, **`D26`**, **`D27`**, **`D14`**, **`D13`** = São os 5 pinos que vão acender os LEDs (**também ficam todos desse mesmo lado da placa, logo abaixo do `D33`!**).

> [!TIP]
> **O ESP32 é "gordinho" na protoboard!**
> Quando você espeta o ESP32 no meio da protoboard, às vezes sobra apenas **1 coluna de furinhos livres** de um lado e nenhuma do outro.
> **Truque fácil:** Você pode espetar apenas o lado esquerdo do ESP32 na protoboard (ou usar duas protoboards lado a lado), porque **todos os 10 pinos que usamos nos sensores e LEDs (`VP/36, 34, 35, 32, 33, 25, 26, 27, 14, 13`) e também um pino `GND` ficam do MESMO lado da placa** (ou você pega o `GND` com um fio jumper Fêmea-Macho se preferir)!

```text
          LADO ESQUERDO DO ESP32 DEVKIT V1
         (Com o conector USB apontando para BAIXO ou para CIMA —
          sempre confira o nome escrito na placa!)
         ┌──────────────────────┐
         │  EN                  │
         │  VP  (GPIO36) ◄──────┼── Piezo CENTRO (+)
         │  VN  (GPIO39)        │   (pule este pino!)
         │  D34 (GPIO34) ◄──────┼── Piezo FRENTE (+)
         │  D35 (GPIO35) ◄──────┼── Piezo DIREITA (+)
         │  D32 (GPIO32) ◄──────┼── Piezo TRÁS (+)
         │  D33 (GPIO33) ◄──────┼── Piezo ESQUERDA (+)
         │  D25 (GPIO25) ◄──────┼── LED CENTRO
         │  D26 (GPIO26) ◄──────┼── LED FRENTE
         │  D27 (GPIO27) ◄──────┼── LED DIREITA
         │  D14 (GPIO14) ◄──────┼── LED TRÁS
         │  D12 (GPIO12)        │   (pule este pino!)
         │  D13 (GPIO13) ◄──────┼── LED ESQUERDA
         │  GND          ◄──────┼── Terra Comum (Linha Azul)
         └──────────────────────┘
```
*(Nota: Em algumas versões de 30 pinos do ESP32, o `GND` e o `D13` ficam logo abaixo do `D12` ou na quina. Basta ler a palavrinha escrita na placa ao lado do pino!)*

---

### 2. O Disco Piezoelétrico (Sensor de Impacto — 5 unidades)
É aquela moedinha dourada com um círculo branco no meio e dois fios soldados:
- 🔴 **Fio Vermelho (`+` / Positivo):** Soldado na parte branca central. É por onde sai o sinal do impacto.
- ⚫ **Fio Preto (`-` / Negativo):** Soldado na borda dourada. Vai sempre ligado no **Terra (`GND` / Linha Azul)**.
- *(Dica: Os fios originais do piezo costumam ser muito fininhos e moles para entrar na protoboard. Enrole ou solde a pontinha deles em um **fio jumper macho** ou estane com um pinguinho de solda para ficar firme no furinho).*

---

### 3. O Resistor de 1 MΩ (1 Megaohm — 5 unidades)
- **Para que serve:** Quando você pisa no piezo, a eletricidade gerada precisa ter por onde escoar de volta ao zero. Sem esse resistor, o pino fica "flutuando" e dispara sozinho no ar.
- **Como identificar:** Tem listras coloridas: **Marrom – Preto – Verde – Dourado** (se for de 4 faixas) ou **Marrom – Preto – Preto – Amarelo** (5 faixas).
- **Tem lado certo (`+` ou `-`)?** **NÃO!** Resistor não tem polaridade. Pode espetar de qualquer lado.

---

### 4. O Diodo Zener de 3.3V (1N4728 — 5 unidades) — ⚠️ ATENÇÃO TOTAL AQUI!
- **Como ele é:** Parece uma miçanga de vidro laranja/avermelhada bem pequenininha com duas pernas de arame e **uma listra preta pintada em uma das pontas**.
- **Para que serve:** O piezo pode gerar até **90 Volts** num pisão forte, e o ESP32 queima se receber mais de **3.3 Volts**. O Diodo Zener funciona como um "ladrão de caixa d'água": passou de 3.3V, ele joga o excesso para o Terra (`GND`).
- **TEM LADO CERTO? SIM! MUITO IMPORTANTE:**
  ```text
                      LISTRA PRETA
                           │
                           ▼
     (Fileira do Piezo +) ──┤█████├── (Linha Azul / GND)
                          Cátodo    Ânodo
  ```
  - **Perna DO LADO DA LISTRA PRETA (Cátodo):** Vai na **mesma fileira do fio Vermelho (`+`) do Piezo** (que vai para o ESP32).
  - **Perna SEM LISTRA (Ânodo):** Vai na **Linha Azul (`GND`)**.
  - *(O que acontece se você colocar ao contrário? Não queima nada, mas o diodo vai cortar o sinal em 0.7V em vez de 3.3V, deixando o sensor "surdo" para toques leves!)*

---

### 5. O LED (5 unidades) e o Resistor de 220 Ω (5 unidades)
- **Resistor de 220 Ω:** Listras **Vermelho – Vermelho – Marrom – Dourado** (ou Vermelho-Vermelho-Preto-Preto). Não tem lado certo. Impede o LED de queimar.
- **LED (Luzinha):** **TEM LADO CERTO!** Olhe as duas perninhas dele:
  - **Perna MAIOR (`+` / Ânodo):** É o Positivo (recebe energia vinda do resistor de 220 Ω).
  - **Perna MENOR (`-` / Cátodo, lado "achatado" do plástico):** É o Negativo. Vai direto na **Linha Azul (`GND`)**.

---

## 🧱 Parte 3: Montando a ZONA 1 (Centro) — Passo a Passo Furo por Furo

> [!IMPORTANT]
> **Não monte as 5 zonas de uma vez!** Monte **apenas a Zona Centro (`GPIO36`)** primeiro e teste no computador. Depois que a primeira funcionar, as outras 4 são literalmente "copiar e colar" a mesma receita!

### Passo 1: Criar o Terra Comum (`GND`)
1. Com o ESP32 **desconectado do USB**, espete o ESP32 no topo da protoboard (ou deixe-o ao lado se for usar jumpers Fêmea-Macho).
2. Pegue **1 fio jumper (de preferência preto ou azul)**.
3. Ligue uma ponta no pino escrito **`GND`** do ESP32.
4. Ligue a outra ponta em **qualquer furinho da Linha Azul (`-`)** na lateral da protoboard.
   - *Pronto! Agora a Linha Azul inteira da sua protoboard é Terra (`GND`).*

---

### Passo 2: Montar a "Receita do Piezo" para o CENTRO (`GPIO36` / `VP`)
Escolha uma fileira vazia da protoboard (vamos usar a **fileira 15** como exemplo — os 5 furos `15A, 15B, 15C, 15D, 15E`):

```text
  LINHA AZUL (-)           FILEIRA 15 DA PROTOBOARD
     (GND)               15A    15B    15C    15D    15E
      [●]                 [●]    [●]    [●]    [●]    [●]
       ▲                   ▲      ▲      ▲      ▲
       │                   │      │      │      └──── 1. Fio Jumper para o pino VP (GPIO36) do ESP32
       │                   │      │      └─────────── 2. Fio VERMELHO (+) do Piezo Centro
       ├───────────────────┼──────┴────────────────── 3. Resistor 1 MΩ (uma perna no 15B, outra na Linha Azul)
       ├───────────────────┴───────────────────────── 4. Diodo Zener 3.3V:
       │                                                 • Lado COM LISTRA PRETA no 15A
       │                                                 • Lado SEM LISTRA na Linha Azul (GND)
       └───────────────────────────────────────────── 5. Fio PRETO (-) do Piezo Centro direto na Linha Azul
```

Faça exatamente nesta ordem:
1. **Fio para o ESP32:** Espete uma ponta de um jumper no furo **`15D`** e a outra ponta na fileira do pino **`VP` (`GPIO36`)** do ESP32.
2. **Resistor de 1 MΩ:** Dobre as perninhas dele. Espete uma perna no furo **`15B`** e a outra perna na **Linha Azul (`GND`)**.
3. **Diodo Zener 3.3V:** Olhe onde está a **listra preta**!
   - Espete a perna **COM a listra preta** no furo **`15A`**.
   - Espete a perna **SEM listra** na **Linha Azul (`GND`)**.
4. **Disco Piezo do Centro:**
   - Espete o **fio VERMELHO (`+`)** do piezo no furo **`15C`**.
   - Espete o **fio PRETO (`-`)** do piezo direto na **Linha Azul (`GND`)**.

*(Veja como é simples: no furo `15A, 15B, 15C, 15D` estão dando as mãos o fio para o ESP32, o resistor de 1MΩ, a listra preta do Zener e o fio vermelho do piezo! E todo o resto vai para a Linha Azul `GND`!)*

---

### Passo 3: Montar o LED do CENTRO (`GPIO25` / `D25`) — *Opcional no primeiro teste*
*(Lembre-se: eu programei o **LED azul que já vem soldado na própria placa ESP32** para piscar quando você bater em qualquer piezo! Mas para montar o LED externo da Zona Centro, escolha a **fileira 25** como exemplo):*

1. Ligue um fio jumper do pino **`D25` (`GPIO25`)** do ESP32 até o furo **`25A`**.
2. Pegue um **Resistor de 220 Ω**: espete uma perna no furo **`25B`** e a outra perna na fileira de baixo, no furo **`26B`**.
3. Pegue o **LED**:
   - Espete a **perna MAIOR (`+`)** no furo **`26C`** (conectando com o resistor na fileira 26).
   - Espete a **perna MENOR (`-`)** direto na **Linha Azul (`GND`)**.

---

## 🧪 Parte 4: O Grande Teste da Zona 1 (Antes de montar o resto!)

1. Confira se o `GND` do ESP32 está ligado na Linha Azul e se nenhum fio desencapado está encostando no outro.
2. **Plugue o cabo USB no ESP32.**
3. **Olhe para o ESP32:**
   - O LED azul da placa vai dar **1 piscada** ao ligar.
   - Ele vai calibrar o silêncio por **2 segundos** (não toque no piezo durante esses 2 segundos!).
   - Depois de 2 segundos, o LED azul da placa vai dar **3 piscadas rápidas**! Isso significa: **"Calibrado e pronto!"**
4. **Dê um peteleco / tapinha rápido com o dedo no disco Piezo:**
   - O LED azul do ESP32 (e o LED do pino `D25`) deve **piscar na mesma hora**!
5. **Conferindo na tela do PC (Arduino IDE):**
   - Na **Arduino IDE** (que já deixei aberta no seu computador), clique no ícone de lupa no canto superior direito (**Serial Monitor**) e garanta que a velocidade está em **`115200 baud`**.
   - Aperte o botão físico **`EN`** no ESP32 e veja aparecer:
     ```text
     ===== MOVA Five-Zone Firmware v2 =====
     [AP] Starting access point...
     [AP] MOVA-ESP32 started. IP: 192.168.4.1
     [CAL] Starting 5-zone noise-floor calibration (200 samples / 2 s)...
     [CAL] Zone=center (GPIO36) | noiseFloor=   0.0 | stdDev=  0.0 | threshold=300
     ...
     [SYS] Ready — listening for impacts on all 5 zones
     ```
   - Dê um tapinha no piezo e veja aparecer na hora:
     ```text
     [IMPACT] Zone=center | ADC=1850 | Intensity=0.45 | JSON={"type":"footstep","zone":"center","intensity":0.45,"timestamp":8420,"source":"esp32"}
     ```

---

## 🖐️ Parte 5: Multiplicando para as 5 Zonas!

Funcionou a Zona Centro? Parabéns, você já sabe montar o projeto inteiro!
Para as outras **4 zonas (`front`, `right`, `back`, `left`)**, você vai repetir **exatamente a mesma receita de 4 conexões na fileira**, mudando apenas a fileira da protoboard e o pino do ESP32.

**Desplugue o USB** e siga este mapa de fileiras na protoboard:

### Mapa Completo dos 5 Sensores Piezo

Em cada fileira abaixo, você SEMPRE coloca:
- **Furo `A`:** Perna **COM listra preta** do Diodo Zener 3.3V *(a outra perna sem listra vai na **Linha Azul `GND`**)*
- **Furo `B`:** Uma perna do **Resistor de 1 MΩ** *(a outra perna vai na **Linha Azul `GND`**)*
- **Furo `C`:** **Fio VERMELHO (`+`)** do Piezo daquela zona *(o **fio PRETO (`-`)** do Piezo vai direto na **Linha Azul `GND`**)*
- **Furo `D`:** Fio Jumper indo para o **Pino do ESP32** indicado na tabela:

| Ordem | Zona do Tapete | Fileira Sugerida na Protoboard | Ligar o Furo `D` em qual pino do ESP32? |
| :---: | :--- | :---: | :--- |
| **1** | 🎯 **CENTRO (`center`)** | **Fileira 15** (`15A` a `15D`) | Pino **`VP`** *(que é o `GPIO36`)* |
| **2** | ⬆️ **FRENTE (`front`)** | **Fileira 17** (`17A` a `17D`) | Pino **`D34`** *(que é o `GPIO34`)* |
| **3** | ➡️ **DIREITA (`right`)** | **Fileira 19** (`19A` a `19D`) | Pino **`D35`** *(que é o `GPIO35`)* |
| **4** | ⬇️ **TRÁS (`back`)** | **Fileira 21** (`21A` a `21D`) | Pino **`D32`** *(que é o `GPIO32`)* |
| **5** | ⬅️ **ESQUERDA (`left`)** | **Fileira 23** (`23A` a `23D`) | Pino **`D33`** *(que é o `GPIO33`)* |

*(Pular uma fileira vazia entre cada zona — 15, 17, 19, 21, 23 — evita que as perninhas de metal de um resistor encostem no resistor do vizinho!)*

---

### Mapa Completo dos 5 LEDs (Indicadores Visuais)

Para cada LED, o pino do ESP32 passa por um **Resistor de 220 Ω**, entra na **perna MAIOR (`+`)** do LED, e a **perna MENOR (`-`)** do LED vai na **Linha Azul (`GND`)**:

| Zona do Tapete | Pino do ESP32 | Vai para... | Perna MAIOR (`+`) do LED | Perna MENOR (`-`) do LED |
| :--- | :--- | :---: | :---: | :---: |
| 🎯 **CENTRO (`center`)** | Pino **`D25`** | Resistor 220 Ω | Na outra ponta do resistor | Na **Linha Azul (`GND`)** |
| ⬆️ **FRENTE (`front`)** | Pino **`D26`** | Resistor 220 Ω | Na outra ponta do resistor | Na **Linha Azul (`GND`)** |
| ➡️ **DIREITA (`right`)** | Pino **`D27`** | Resistor 220 Ω | Na outra ponta do resistor | Na **Linha Azul (`GND`)** |
| ⬇️ **TRÁS (`back`)** | Pino **`D14`** | Resistor 220 Ω | Na outra ponta do resistor | Na **Linha Azul (`GND`)** |
| ⬅️ **ESQUERDA (`left`)** | Pino **`D13`** | Resistor 220 Ω | Na outra ponta do resistor | Na **Linha Azul (`GND`)** |

---

## 🎮 Parte 6: Testando as 5 Zonas no Jogo (TV + Painel do Terapeuta)

Depois que os 5 piezos estiverem espetados:

1. **Plugue o cabo USB no ESP32** (ou aperte o botão **`EN`** se já estiver plugado) e **não toque nos piezos por 2 segundos** enquanto ele calibra as 5 zonas.
2. No Serial Monitor da Arduino IDE, dê um tapinha em cada um dos 5 discos piezo um por um e confira se aparece:
   - `Zone=center`
   - `Zone=front`
   - `Zone=right`
   - `Zone=back`
   - `Zone=left`
3. **Conecte o Wi-Fi do seu notebook na rede do ESP32:**
   - Nome da Rede (SSID): **`MOVA-ESP32`**
   - Senha: **`mova1234`**
4. Abra o navegador (os servidores já estão rodando no seu PC!):
   - **Painel do Terapeuta:** `http://localhost:3000/apps/therapist-panel/`
     - Confira se o selo no topo ficou verde: **`● ESP32 conectado`**.
   - **TV do Paciente:** `http://localhost:3000/apps/tv/`
5. No Painel do Terapeuta, clique em **`▶ Iniciar Atividade`** e bata no piezo correspondente à posição do balão que acender na TV!

---

## 🚑 Solução Rápida de Problemas na Bancada

| O que aconteceu? | Causa certeira | Como resolver em 10 segundos |
| :--- | :--- | :--- |
| **Uma zona dispara sozinha sem ninguém tocar** | O **Resistor de 1 MΩ** daquela zona está mal encaixado no furinho ou o `GND` soltou. | Aperte firme as duas pernas do Resistor de 1 MΩ na protoboard e aperte o botão **`EN`** do ESP32 para recalibrar. |
| **Bato forte no piezo e nada acontece naquela zona** | 1) Fio vermelho/preto frouxo no furo, ou<br>2) **Diodo Zener invertido** (listra preta virada para o GND). | Confira se a **listra preta** do Diodo Zener está na fileira do fio vermelho (`+`) e não na linha azul (`GND`). |
| **O piezo funciona no Serial Monitor, mas o LED dele não acende** | O LED está invertido. | Tire o LED e gire 180° (perna **maior** no resistor, perna **menor** na linha azul `GND`). |
| **Acabei de espetar um piezo novo e o limiar (`threshold`) dele ficou alto** | O ESP32 calibrou quando o pino ainda estava vazio (sem o resistor de 1 MΩ). | Basta apertar o botão **`EN` (Reset)** na placa do ESP32 e esperar 2 segundos sem tocar nos sensores. |
