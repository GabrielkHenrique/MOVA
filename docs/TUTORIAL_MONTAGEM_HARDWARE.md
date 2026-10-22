# ⚡ Guia Prático de Montagem (Versão Cabo de Rede — 5 Zonas)

Usar **cabo de rede descascado** é a melhor ideia possível para o tapete! Se o cabo de rede for do tipo **rígido** (um único fiozinho de cobre duro dentro de cada plástico colorido), ele **entra direto nos furinhos da protoboard** igualzinho a um jumper, sem precisar de mais nada.

> [!TIP]
> **E se o seu cabo de rede for "molinho" (vários cabelinhos finos de cobre)?**
> Ele amassa se você tentar empurrar direto no furo da protoboard. Nesse caso, o truque prático é: **enrole o fiozinho descascado direto na perninha de metal do Resistor de 1 MΩ** antes de espetar o resistor na protoboard!

---

## 🎨 1. Código de Cores com o Cabo de Rede (Para não se perder!)

Quando você abre a capa externa de um cabo de rede, saem **4 pares trançados** (8 fios no total: 4 cores fortes e 4 brancos listrados).

Para ficar super organizado e nunca confundir qual fio vem de qual piezo:
- Use os **fios de COR FORTE** para o **Positivo (`+` / Fio Vermelho do Piezo)**
- Use os **fios BRANCOS LISTRADOS** para o **Negativo (`-` / Fio Preto do Piezo → vai no `GND`)**

| Zona do Tapete | Fio do Cabo de Rede p/ o **Vermelho (`+`) do Piezo** | Fio do Cabo de Rede p/ o **Preto (`-`) do Piezo** | Pino no ESP32 |
| :--- | :--- | :--- | :---: |
| 🎯 **1. CENTRO** | 🟠 **Laranja** | ⚪🟠 Branco/Laranja | **`VP` (`36`)** |
| ⬆️ **2. FRENTE** | 🟢 **Verde** | ⚪🟢 Branco/Verde | **`D34`** |
| ➡️ **3. DIREITA** | 🔵 **Azul** | ⚪🔵 Branco/Azul | **`D35`** |
| ⬇️ **4. TRÁS** | 🟤 **Marrom** | ⚪🟤 Branco/Marrom | **`D32`** |
| ⬅️ **5. ESQUERDA** | 🟠 **Laranja** *(de um 2º cabo)* **ou** ⚪🟠 **Branco/Laranja** *(se usar 1 cabo só)* | Qualquer fio ligado no **`GND`** | **`D33`** |

> **Atalho se quiser passar 1 CABO DE REDE SÓ do tapete até a protoboard:**
> Como todos os fios pretos (`-`) dos 5 piezos vão no mesmo lugar (`GND`), você pode juntar os 5 fios pretos dos piezos em **1 único fio do cabo de rede** (ex: ⚪🟤 Branco/Marrom ligado no `GND`), e usar outros **5 fios do mesmo cabo** para os 5 sinais (`+`):
> - 🎯 Centro = 🟠 **Laranja** → **`VP (36)`**
> - ⬆️ Frente = 🟢 **Verde** → **`D34`**
> - ➡️ Direita = 🔵 **Azul** → **`D35`**
> - ⬇️ Trás = 🟤 **Marrom** → **`D32`**
> - ⬅️ Esquerda = ⚪🟢 **Branco/Verde** → **`D33`**
> - ⚫ Terra comum dos 5 piezos = ⚪🔵 **Branco/Azul** → **Linha Azul (`GND`)**

---

## 🔧 2. Como Preparar os Fios Rapidinho

1. **Descasque ~1 cm** das pontas dos fios do cabo de rede (pode usar alicate, estilete de leve ou até tesoura sem cortar o cobre).
2. **Emende no Piezo:**
   - Descasque um pouquinho a ponta do fio vermelho e preto do piezo.
   - Enrole firme cobre com cobre (ou dê um pinguinho de solda se tiver ferro de solda) e passe um pedacinho de **fita isolante** para o fio vermelho nunca encostar no preto.
3. **Na outra ponta (que vai na protoboard):** Descasque **~8 mm** e deixe o arame de cobre bem retinho para espetar no furo.

---

## 🧱 3. A "Receita Prática" na Protoboard (Igual para as 5 Zonas)

Com o **ESP32 fora do USB**:

### Passo Único de Terra (`GND`):
- Ligue um fio do pino **`GND`** do ESP32 até a **Linha Azul (`-`)** da lateral da protoboard.
- Espete **todos os fios Negativos (`-`) dos piezos** direto nessa **Linha Azul (`-`)**.

---

### Receita de 4 Furos (Repita em 5 fileiras diferentes):

Escolha 5 fileiras da protoboard pulando espaço entre elas (ex: **Fileiras 10, 13, 16, 19 e 22**).
Em **cada uma** dessas 5 fileiras (nos 5 furinhos horizontais `A, B, C, D, E` da mesma fileira), espete estas **4 coisas**:

```text
  Na mesma fileira horizontal (A - B - C - D)              Na Linha Azul (-) da lateral
  ───────────────────────────────────────────              ────────────────────────────
  [Furo A] Perna COM LISTRA PRETA do Diodo Zener 3.3V ───► Outra perna (sem listra) na Linha Azul
  [Furo B] Uma perna do Resistor 1 MΩ (Marrom-Preto-Verde)► Outra perna na Linha Azul
  [Furo C] Fio POSITIVO (+) que veio do Piezo daquela zona
  [Furo D] Fio indo para o PINO DO ESP32 daquela zona
```

Confira na tabela rápida onde ligar o **[Furo D]** de cada fileira:

| Fileira da Protoboard | Qual fio do Piezo (`+`) entra no Furo C? | O Furo D vai em qual pino do ESP32? |
| :---: | :--- | :---: |
| **Fileira 10** | 🎯 **CENTRO** (🟠 Laranja) | **`VP` (`GPIO36`)** |
| **Fileira 13** | ⬆️ **FRENTE** (🟢 Verde) | **`D34`** |
| **Fileira 16** | ➡️ **DIREITA** (🔵 Azul) | **`D35`** |
| **Fileira 19** | ⬇️ **TRÁS** (🟤 Marrom) | **`D32`** |
| **Fileira 22** | ⬅️ **ESQUERDA** (⚪🟢 Branco/Verde) | **`D33`** |

> [!WARNING]
> **Os 2 únicos detalhes que têm lado certo:**
> 1. **Diodo Zener (peça de vidro laranja):** A **listra preta** fica SEMPRE na fileira junto com o fio do piezo (`Furo A`), e o lado sem listra vai na Linha Azul (`GND`).
> 2. **LED (se for montar os 5 LEDs nos pinos `D25, D26, D27, D14, D13`):** Passa pelo resistor de `220 Ω` (Vermelho-Vermelho-Marrom), entra na **perna MAIOR** do LED, e a **perna MENOR** vai na Linha Azul (`GND`). *(Mesmo sem espetar os 5 LEDs, o LED azul da própria placa ESP32 já vai piscar a cada pisada!)*

---

## 🚀 4. Teste Rápido em 30 Segundos

1. Plugue o USB no ESP32 e **espere 2 segundos sem tocar nos piezos** (o LED azul da placa pisca 1x ao ligar e **pisca 3x** quando termina de calibrar).
2. Dê um tapinha em cada piezo: o **LED azul da placa ESP32 tem que piscar** a cada batida!
3. Se alguma zona ficar disparando sozinha no Serial Monitor: aperte melhor a perninha do **Resistor de 1 MΩ** daquela fileira e aperte o botão **`EN`** do ESP32 para recalibrar.
