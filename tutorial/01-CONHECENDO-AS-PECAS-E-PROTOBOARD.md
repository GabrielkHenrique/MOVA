# 🔍 Passo 1: Conhecendo as Peças e a Protoboard

Se você nunca montou um circuito eletrônico antes, fique tranquilo: você só precisa entender **como os furinhos da placa funcionam** e **quais peças têm lado certo**.

> [!CAUTION]
> **REGRA DE OURO:** Sempre mantenha o **cabo USB desconectado do ESP32** enquanto estiver colocando ou tirando fios da protoboard. Só ligue o USB na hora de testar!

---

## 1. Como funciona a Protoboard (Matriz de Contatos)?

A protoboard é uma placa plástica cheia de furinhos. Por baixo do plástico existem chapinhas metálicas que ligam certos furos entre si para você não precisar soldar nada.

Ela tem **duas regiões com regras diferentes**:

```text
   LATERAL ESQUERDA                MEIO DA PLACA                 LATERAL DIREITA
  (Linhas Compridas)            (Fileiras Numeradas)            (Linhas Compridas)
   [+]  [-]                    A  B  C  D  E     F  G  H  I  J   [+]  [-]
    │    │                  1 [●][●][●][●][●] │ [●][●][●][●][●]   │    │
    │    │                  2 [●][●][●][●][●] │ [●][●][●][●][●]   │    │
    │    │                  3 [●][●][●][●][●] │ [●][●][●][●][●]   │    │
    │    │                  4 [●][●][●][●][●] │ [●][●][●][●][●]   │    │
    ▼    ▼                                    ▲                   ▼    ▼
  Ligados na VERTICAL                  Canaleta Central          Ligados na VERTICAL
  (de cima até embaixo!)             (divide A-E de F-J)        (de cima até embaixo!)
```

### A) As Linhas Laterais (`-` Azul e `+` Vermelha)
- Correm nas laterais da placa **na VERTICAL (de ponta a ponta)**.
- Todos os furinhos da **Linha Azul (`-`)** estão conectados entre si de cima até embaixo.
- Nós vamos usar a **Linha Azul (`-`)** como o nosso **Terra Comum (`GND`)** — todo fio negativo do projeto vai espetado nela!
- *(Atenção: Se a linha azul pintada na sua protoboard tiver uma falha no meio da placa, coloque um fiozinho ligando a metade de cima na metade de baixo da linha azul).*

### B) As Fileiras do Meio (Números `1, 2, 3...` e Letras `A B C D E` | `F G H I J`)
- No meio da placa, os furinhos são ligados **na HORIZONTAL, de 5 em 5**.
- **Exemplo:** Na **Fileira 10**, os furos **`10A`, `10B`, `10C`, `10D` e `10E`** são o mesmo ponto elétrico (estão todos dando as mãos por baixo do plástico).
- Mas a **Fileira 10 NÃO se comunica com a Fileira 11**!
- E o rasgo (canaleta) no meio da placa separa os furos `A-E` dos furos `F-J`.

---

## 2. Identificando cada Componente com os Olhos

### 🧠 A Placa ESP32 DevKit V1
É o "cérebro" do tapete. Ela lê os sensores e cria o Wi-Fi `MOVA-ESP32`.
- Ao lado do conector USB existem dois botõezinhos: **`EN`** (serve para reiniciar/recalibrar a placa) e **`BOOT`**.
- **Boa notícia:** Todos os 10 pinos que vamos usar no projeto ficam **do mesmo lado da placa ESP32**! Veja a ordem deles olhando as letras escritas na placa:

```text
          LADO ESQUERDO DO ESP32 DEVKIT V1
         ┌──────────────────────┐
         │  EN                  │
         │  VP  (GPIO36) ◄──────┼── 1. Piezo CENTRO (+)
         │  VN  (GPIO39)        │   (pule este pino - deixe vazio)
         │  D34 (GPIO34) ◄──────┼── 2. Piezo FRENTE (+)
         │  D35 (GPIO35) ◄──────┼── 3. Piezo DIREITA (+)
         │  D32 (GPIO32) ◄──────┼── 4. Piezo TRÁS (+)
         │  D33 (GPIO33) ◄──────┼── 5. Piezo ESQUERDA (+)
         │  D25 (GPIO25) ◄──────┼── LED 1: CENTRO
         │  D26 (GPIO26) ◄──────┼── LED 2: FRENTE
         │  D27 (GPIO27) ◄──────┼── LED 3: DIREITA
         │  D14 (GPIO14) ◄──────┼── LED 4: TRÁS
         │  D12 (GPIO12)        │   (pule este pino - deixe vazio)
         │  D13 (GPIO13) ◄──────┼── LED 5: ESQUERDA
         │  GND          ◄──────┼── Terra Comum (vai na Linha Azul)
         └──────────────────────┘
```
> **Dica de encaixe:** O ESP32 é largo. Se quando você espetar ele na protoboard sobrar furinhos só de um lado, **deixe os furinhos livres do lado onde ficam os pinos `VP`, `D34`, `D35`, `D32`, `D33`**, pois é só desse lado que vamos ligar os sensores e LEDs!

---

### 🪙 O Disco Piezoelétrico (5 unidades)
É a moedinha dourada com um círculo branco no centro. Quando sofre impacto ou dobra de leve, a cerâmica branca gera eletricidade.
- 🔴 **Fio Vermelho (`+` / Sinal):** Soldado na parte branca central. Vai para a fileira do sensor na protoboard.
- ⚫ **Fio Preto (`-` / Terra):** Soldado na borda dourada. Vai sempre na **Linha Azul (`GND`)**.

---

### 📏 Os Dois Tipos de Resistor (NÃO têm lado certo!)
Resistores **não têm positivo nem negativo** — você pode espetar em qualquer direção. Só não confunda os dois valores:

| Componente | Para que serve? | Cores das Faixas no Corpo | Onde vai? |
| :--- | :--- | :--- | :--- |
| **Resistor de 1 MΩ** *(5 unidades)* | Descarrega a energia do piezo após o passo e evita disparos falsos. | **Marrom – Preto – Verde – Dourado** *(ou Marrom-Preto-Preto-Amarelo)* | Liga a fileira do Piezo (`+`) até a **Linha Azul (`GND`)** |
| **Resistor de 220 Ω** *(5 unidades)* | Reduz a corrente para o LED não queimar. | **Vermelho – Vermelho – Marrom – Dourado** | Fica entre o pino do LED no ESP32 e a perna maior do LED |

---

### 🚨 As 2 Únicas Peças que TÊM LADO CERTO (Polaridade)

Preste muita atenção nestas duas peças na hora de espetar:

#### 1. Diodo Zener de 3.3V (1N4728 — 5 unidades)
- **Aparência:** Um cilindrinho minúsculo de vidro laranja/vermelho com **uma listra preta pintada em uma ponta**.
- **Função:** O piezo pode gerar picos de até **90 Volts** num pisão forte! O Diodo Zener trava qualquer pico acima de **3.3V** e joga o excesso para o Terra (`GND`), salvando o ESP32.
- **LADO CERTO:**
  ```text
                       LISTRA PRETA
                            │
                            ▼
  (Fileira do Piezo +) ────┤█████├──── (Linha Azul / GND)
  ```
  - **Perna COM a listra preta:** Vai espetada na **fileira do fio vermelho (`+`) do Piezo**.
  - **Perna SEM listra:** Vai espetada na **Linha Azul (`GND`)**.

#### 2. LED (Luzinha — 5 unidades)
- **Olhe as duas pernas de arame do LED:** uma é **mais comprida** que a outra!
  - **Perna MAIOR (`+`):** Recebe o sinal que vem do Resistor de 220 Ω.
  - **Perna MENOR (`-`):** Vai espetada direto na **Linha Azul (`GND`)**.

---

👉 **Próximo passo:** Agora que você já conhece as peças, abra o arquivo **[`02-PREPARANDO-CABOS-DE-REDE-E-PIEZOS.md`](./02-PREPARANDO-CABOS-DE-REDE-E-PIEZOS.md)** para preparar os cabos de rede e sensores!
