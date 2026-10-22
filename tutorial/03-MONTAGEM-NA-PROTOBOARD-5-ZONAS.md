# 🧱 Passo 3: Montagem na Protoboard (Furo por Furo — 5 Zonas)

Agora vamos espetar tudo na protoboard!
Lembre-se: **Cabo USB fora do ESP32** enquanto estiver montando.

---

## Etapa 1: Ligar o Terra Comum (`GND`)

1. Espete o ESP32 no topo da protoboard (deixando furinhos livres do lado dos pinos `VP`, `D34`, `D35`, `D32`, `D33`, `D25`, `D26`, `D27`, `D14`, `D13` e `GND`).
2. Pegue um pedaço de fio e ligue o pino **`GND`** do ESP32 em **qualquer furinho da Linha Azul (`-`)** na lateral da protoboard.
3. Espete **todos os fios Negativos (`-` / fios pretos dos piezos ou fios brancos listrados do cabo de rede)** direto ao longo dessa **Linha Azul (`-`)**.

---

## Etapa 2: A "Receita de 4 Furos" (Como funciona cada Zona)

Cada uma das 5 zonas usa **1 fileira horizontal de 5 furinhos (`A, B, C, D, E`)** da protoboard.
Dentro da fileira daquela zona, você **SEMPRE** espeta exatamente as mesmas **4 coisas**:

```text
  NA FILEIRA DA ZONA (Furos Horizontais A - B - C - D)         NA LINHA AZUL (-) DA LATERAL
  ────────────────────────────────────────────────────         ────────────────────────────
  [Furo A] Perna COM LISTRA PRETA do Diodo Zener 3.3V   ─────► Outra perna (sem listra) na Linha Azul
  [Furo B] Uma perna do Resistor 1 MΩ (Marrom-Preto-Verde)───► Outra perna na Linha Azul
  [Furo C] Fio POSITIVO (+) que veio do Piezo daquela zona
  [Furo D] Fio ligando esta fileira até o PINO DO ESP32
```

> [!TIP]
> **Por que funciona?** Porque na horizontal (`A, B, C, D`) todos esses 4 furos estão conectados entre si por baixo da protoboard! Assim o sinal do piezo (`C`) é protegido pelo Zener (`A`), descarregado pelo resistor de 1 MΩ (`B`) e lido pelo pino do ESP32 (`D`).

---

## Etapa 3: Monte e Teste a ZONA 1 (Centro) Primeiro!

Antes de espetar as 5 zonas, monte **só a primeira (Centro)** na **Fileira 10** para pegar o jeito em 1 minuto:

1. **`10A`:** Perna **COM listra preta** do 1º Diodo Zener *(outra perna na Linha Azul `GND`)*.
2. **`10B`:** Uma perna do 1º **Resistor de 1 MΩ** *(outra perna na Linha Azul `GND`)*.
3. **`10C`:** Fio Positivo (`+` / 🟠 Laranja) do **Piezo CENTRO** *(e confira se o negativo `-` dele já está na Linha Azul `GND`)*.
4. **`10D`:** Fio ligando o furo `10D` até o pino **`VP` (`GPIO36`)** do ESP32.

### ⚡ Teste Rápido da Zona 1 (30 segundos):
1. Plugue o cabo USB no ESP32 e **não toque no piezo por 2 segundos**.
2. Veja o **LED azul da própria placa ESP32**: ele dá **1 piscada** ao ligar e, após 2 segundos, dá **3 piscadas rápidas** (sinal de pronto!).
3. Dê um tapinha no Piezo do Centro: **o LED azul da placa ESP32 piscou na hora?**
   - **SIM!** Você acertou em cheio! Desplugue o USB e faça igualzinho para as outras 4 zonas na tabela abaixo.
   - **NÃO?** Confira se a **listra preta** do Diodo Zener está no `10A` (e não na Linha Azul) e se o pino `GND` do ESP32 está ligado na Linha Azul.

---

## Etapa 4: Multiplicando para as 5 Zonas Completas

Com o USB desconectado, repita a mesma **Receita de 4 Furos** nas fileiras abaixo (pulando fileiras vazias no meio para um resistor não encostar no outro):

| Zona | Fileira na Protoboard | Furo `A` | Furo `B` | Furo `C` (Fio `+` do Piezo) | Furo `D` (Vai para qual pino do ESP32?) |
| :--- | :---: | :--- | :--- | :--- | :---: |
| 🎯 **1. CENTRO (`center`)** | **Fileira 10** | Zener *(listra preta)* → `GND` | Resistor `1 MΩ` → `GND` | Piezo Centro (`+` 🟠 Laranja) | Pino **`VP`** *(`GPIO36`)* |
| ⬆️ **2. FRENTE (`front`)** | **Fileira 13** | Zener *(listra preta)* → `GND` | Resistor `1 MΩ` → `GND` | Piezo Frente (`+` 🟢 Verde) | Pino **`D34`** *(`GPIO34`)* |
| ➡️ **3. DIREITA (`right`)** | **Fileira 16** | Zener *(listra preta)* → `GND` | Resistor `1 MΩ` → `GND` | Piezo Direita (`+` 🔵 Azul) | Pino **`D35`** *(`GPIO35`)* |
| ⬇️ **4. TRÁS (`back`)** | **Fileira 19** | Zener *(listra preta)* → `GND` | Resistor `1 MΩ` → `GND` | Piezo Trás (`+` 🟤 Marrom) | Pino **`D32`** *(`GPIO32`)* |
| ⬅️ **5. ESQUERDA (`left`)** | **Fileira 22** | Zener *(listra preta)* → `GND` | Resistor `1 MΩ` → `GND` | Piezo Esquerda (`+` ⚪🟢 Branco/Verde) | Pino **`D33`** *(`GPIO33`)* |

---

## Etapa 5: Montando os 5 LEDs Indicadores (Opcional na Bancada)

> **Nota:** Mesmo sem estes 5 LEDs externos, o **LED azul soldado na própria placa ESP32** já pisca automaticamente quando qualquer uma das 5 zonas detecta impacto!

Se quiser montar os 5 LEDs individuais na protoboard (para ver uma luz diferente acender para cada zona):
Para cada zona, saia do pino do ESP32 com um **Resistor de 220 Ω** (Vermelho-Vermelho-Marrom) até uma fileira livre, espete a **perna MAIOR (`+`) do LED** nessa fileira, e espete a **perna MENOR (`-`) do LED** direto na **Linha Azul (`GND`)**:

| LED de qual Zona? | Sai de qual pino do ESP32? | Passa pelo... | Entra em qual perna do LED? | Onde vai a perna MENOR (`-`) do LED? |
| :--- | :---: | :---: | :---: | :---: |
| 🎯 **LED Centro** | Pino **`D25`** | Resistor `220 Ω` | Perna **MAIOR (`+`)** | **Linha Azul (`GND`)** |
| ⬆️ **LED Frente** | Pino **`D26`** | Resistor `220 Ω` | Perna **MAIOR (`+`)** | **Linha Azul (`GND`)** |
| ➡️ **LED Direita** | Pino **`D27`** | Resistor `220 Ω` | Perna **MAIOR (`+`)** | **Linha Azul (`GND`)** |
| ⬇️ **LED Trás** | Pino **`D14`** | Resistor `220 Ω` | Perna **MAIOR (`+`)** | **Linha Azul (`GND`)** |
| ⬅️ **LED Esquerda** | Pino **`D13`** | Resistor `220 Ω` | Perna **MAIOR (`+`)** | **Linha Azul (`GND`)** |

---

👉 **Próximo passo:**
- Se você está apenas testando na bancada hoje (sem o tapete físico de EVA/madeira), pode pular direto para o **[`05-GRAVANDO-ESP32-E-RODANDO-O-JOGO.md`](./05-GRAVANDO-ESP32-E-RODANDO-O-JOGO.md)**!
- Se quiser ver como posicionar os sensores no chão ou quando forem montar a estrutura do tapete, veja o **[`04-MONTAGEM-FISICA-DO-TAPETE.md`](./04-MONTAGEM-FISICA-DO-TAPETE.md)**.
