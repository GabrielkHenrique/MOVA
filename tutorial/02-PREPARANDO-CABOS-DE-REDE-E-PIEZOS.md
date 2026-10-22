# ✂️ Passo 2: Preparando os Cabos de Rede e os Piezos

Os fios originais que vêm soldados no disco piezo são curtos demais e muito moles. Usar **cabo de rede (Ethernet CAT5e/CAT6) descascado** resolve os dois problemas de uma vez: alonga os fios até o tapete e facilita o encaixe na protoboard!

---

## 1. O que tem dentro do Cabo de Rede?

Ao cortar e puxar a capa externa (azul, cinza ou preta) do cabo de rede, você vai encontrar **8 fios coloridos**, enrolados em **4 pares**:
- 🟠 **Par Laranja:** 1 fio Laranja inteiro + 1 fio Branco/Laranja
- 🟢 **Par Verde:** 1 fio Verde inteiro + 1 fio Branco/Verde
- 🔵 **Par Azul:** 1 fio Azul inteiro + 1 fio Branco/Azul
- 🟤 **Par Marrom:** 1 fio Marrom inteiro + 1 fio Branco/Marrom

### Como saber se o seu cabo de rede é Rígido ou Flexível?
Descasque `1 cm` da pontinha de um dos fios coloridos e olhe o cobre lá dentro:
1. **Cabo Rígido (1 único arame de cobre durinho):**
   - **Perfeito!** Quando você deixa a ponta reta (`~8 mm` descascados), ele **entra direto nos furinhos da protoboard** igualzinho a um fio jumper comprado pronto!
2. **Cabo Flexível (vários "cabelinhos" finos de cobre):**
   - Se você tentar empurrar direto na protoboard, os cabelinhos dobram.
   - **Solução super prática:** Na ponta que chega na protoboard, basta **enrolar os cabelinhos de cobre direto na perninha de metal do Resistor de 1 MΩ** (ou na ponta de um jumper macho) e espetar a perna do resistor no furo!

---

## 2. Duas Formas Práticas de Usar o Cabo de Rede

Escolha a opção que achar mais fácil para a sua montagem hoje:

### Opção A (Mais Limpa): Usar 1 ÚNICO Cabo de Rede para as 5 Zonas!
Como o cabo de rede já tem **8 fios lá dentro**, um único cabo consegue levar as **5 zonas inteiras** da protoboard até o centro do tapete!
Funciona assim:
- Usamos **5 fios** para os sinais positivos (**fio Vermelho `+`** de cada um dos 5 piezos).
- E como **todos os fios Pretos (`-`) dos 5 piezos vão ligados no mesmo lugar (`GND`)**, usamos os outros fios (ex: os brancos listrados) como **Terra Comum (`GND`)**!

| Zona do Tapete | Qual fio do Cabo de Rede emendar no **Vermelho (`+`) do Piezo**? | E o fio **Preto (`-`) do Piezo**? |
| :--- | :--- | :--- |
| 🎯 **1. CENTRO (`center`)** | 🟠 **Laranja** | Vai no fio **Terra Comum** *(ex: ⚪🔵 Branco/Azul ou ⚪🟤 Branco/Marrom)* |
| ⬆️ **2. FRENTE (`front`)** | 🟢 **Verde** | Vai no fio **Terra Comum** |
| ➡️ **3. DIREITA (`right`)** | 🔵 **Azul** | Vai no fio **Terra Comum** |
| ⬇️ **4. TRÁS (`back`)** | 🟤 **Marrom** | Vai no fio **Terra Comum** |
| ⬅️ **5. ESQUERDA (`left`)** | ⚪🟢 **Branco/Verde** | Vai no fio **Terra Comum** |

---

### Opção B (Pares Separados): Tirar 1 Par Trançado para cada Piezo
Se você preferir separar os pares trançados do cabo de rede para ter um cabo independente saindo de cada piezo até a protoboard:
- Em cada par trançado, emende sempre a **COR FORTE no fio Vermelho (`+`)** do piezo e o **BRANCO LISTRADO no fio Preto (`-`)** do piezo:
  - **Par 1 (Laranja):** Centro (`+` Laranja / `-` Branco-Laranja)
  - **Par 2 (Verde):** Frente (`+` Verde / `-` Branco-Verde)
  - **Par 3 (Azul):** Direita (`+` Azul / `-` Branco-Azul)
  - **Par 4 (Marrom):** Trás (`+` Marrom / `-` Branco-Marrom)
  - **Par 5 (de um 2º pedaço de cabo):** Esquerda (`+` Cor forte / `-` Branco listrado)

---

## 3. Como Fazer a Emenda no Disco Piezo sem Mau Contato

Para cada um dos 5 discos piezo:
1. **Cuidado com a solda original do disco:** A bolinha de solda no meio do disco piezo é delicada. Segure o fiozinho original com os dedos ao descascar a pontinha dele (`~1 cm`) para não dar puxão no disco.
2. **Descasque `~1,5 cm`** da ponta do fio do cabo de rede.
3. **Cruze as duas pontas de cobre em "X" e torça bem firme** (pelo menos 5 voltinhas bem apertadas).
   - *(Se tiver ferro de solda por perto, um pinguinho de solda deixa eterno; se não tiver, basta torcer bem firme e dobrar a pontinha).*
4. **Isole obrigatoriamente com Fita Isolante:**
   - Passe um pedacinho de fita isolante na emenda do fio vermelho (`+`) e outro na emenda do fio preto (`-`).
   - **Por quê?** Se o cobre do fio vermelho encostar no cobre do fio preto ou na borda dourada do disco piezo, o sinal entra em curto com o Terra e aquela zona fica muda!
5. **Etiquete a ponta que vai na protoboard:**
   - Coloque uma tirinha de fita crepe ou papelzinho na ponta de cada fio escrevendo **`C` (Centro)**, **`F` (Frente)**, **`D` (Direita)**, **`T` (Trás)** e **`E` (Esquerda)**.

---

👉 **Próximo passo:** Com os 5 piezos já alongados com os fios do cabo de rede, abra o arquivo **[`03-MONTAGEM-NA-PROTOBOARD-5-ZONAS.md`](./03-MONTAGEM-NA-PROTOBOARD-5-ZONAS.md)**!
