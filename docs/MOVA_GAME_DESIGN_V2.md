# MOVA — Relatório de Game Design & Pesquisa (Rodada 2)
**Direção Criativa, Crítica e Expansão de Identidade**

---

## A. O que aprendemos desde a primeira rodada
1. **[FATO] O Tapete é um Espaço, não um Controle:** O jogador está fisicamente *dentro* da interface. O centro atua como "casa" (safe zone), criando um loop natural de *sair → agir → retornar*.
2. **[FATO] Limitações do Piezo:** Sensores piezoelétricos medem *impactos* (variação brusca de tensão), não pressão contínua. 
3. **[INFERÊNCIA] Precisão Temporal > Espacial:** Como temos apenas 5 zonas grandes (baixa resolução espacial), a riqueza do design deve vir de *quando* o jogador pisa (ritmo, espera, urgência).
4. **[INFERÊNCIA] A Inércia é a nossa "Física":** Em um controle tradicional, parar um movimento leva milissegundos (soltar um botão). No MOVA, parar um movimento exige recrutar músculos, equilibrar-se e vencer a inércia do próprio corpo.

## B. O que estava errado ou fraco na primeira rodada
* **A Armadilha do "Simon Says":** Criar jogos que dizem "apareceu alvo na esquerda → pise na esquerda" resultava em testes clínicos disfarçados, não em jogos. Faltava *decisão* e *risco*.
* **Mecânicas Incompatíveis:** Assumir que poderíamos usar "transferência lenta de peso" como mecânica, o que o hardware atual (piezo) não suporta de forma confiável.
* **Riscos de Segurança Não Mitigados:** Ideias como "fechar os olhos" (Farol da Neblina) criavam risco de queda (surpresa no corpo, não na regra).

## C. O que deve permanecer
* **A Regra de Ouro:** "A surpresa deve acontecer na REGRA do jogo, nunca no CORPO do jogador."
* **O Núcleo de "Banda do Coreto":** A combinação de ação simples + ritmo + surpresa é altamente escalável e segura.
* **A Estética Respeitosa:** Manter a identidade visual adulta, acolhedora e inspirada na cultura brasileira (sem caricaturas), evitando infantilização.

## D. Matriz Atualizada dos Eixos de Design

| Eixo | Potencial no MOVA | Risco / Desafio |
| :--- | :--- | :--- |
| **Precisão Temporal** | Altíssimo. Sincronizar pisadas com eventos na tela. | Latência do hardware (mitigado). |
| **Inibição (Go-No-Go)** | Altíssimo. Interromper o corpo gera engajamento motor real. | Jogador se desequilibrar ao frear bruscamente. |
| **Decisão / Troca de Regra** | Alto. Mapear regras mutáveis para o espaço físico. | Sobrecarga cognitiva muito rápida. |
| **Risco × Recompensa** | Alto. Sair do centro para ganhar pontos extras antes do tempo acabar. | Jogador tentar correr e tropeçar. |
| **Ritmo / Memória** | Alto. Sequências musicais. | Dependência excessiva de precisão de áudio. |
| **Exploração Lenta** | Baixo. Piezo não detecta presença contínua. | Falta de feedback do hardware. |

## E. Crítica dos Quatro Jogos Atuais

1. **Estoura! (O Show dos Balões)**
   * **O que funciona:** Excelente MVP técnico. Fácil de entender.
   * **O que é fraco:** Pode virar um teste médico chato.
   * **Veredito:** Manter, mas focar em *Risco/Recompensa* (balões que exigem esperar até o último segundo).
2. **Banda do Coreto**
   * **O que funciona:** Perfeito para o hardware (impacto = batida). Acessível via áudio.
   * **O que é fraco:** Exige sincronia perfeita de assets de áudio/animação.
   * **Veredito:** Manter como o "Jogo de Identidade" do MOVA. Eixo: *Precisão Temporal e Memória*.
3. **Rio Acima**
   * **O que funciona:** A fantasia de entrega.
   * **O que é fraco:** A estrutura WarioWare (dezenas de microjogos) é cara, complexa e fragmenta a experiência.
   * **Veredito:** Modificar drasticamente. Reduzir para uma única mecânica sólida (ver novo conceito "A Maré" abaixo).
4. **Farol da Neblina**
   * **O que funciona:** Foco auditivo.
   * **O que é fraco:** Exigir olhos fechados ou viradas rápidas é perigoso para reabilitação.
   * **Veredito:** Abandonar.

---

## F. Novos Conceitos

### Conceito 1: A Maré (Catador de Caranguejo)
* **Eixos:** Antecipação, Risco × Recompensa, Uso Espacial.
* **Fantasia:** O jogador está na areia (Centro). Ondas vêm e vão nas bordas (Frente, Esquerda, Direita). Caranguejos e conchas aparecem quando a onda recua.
* **Ação:** O jogador sai do centro, pisa na borda para coletar, e deve **voltar ao centro** antes que a próxima onda quebre.
* **A Surpresa (Regra):** Algumas ondas recuam rápido e voltam rápido; outras demoram. Ficar na borda dá mais pontos (coletando conchas extras), mas tomar uma onda zera o combo.
* **Segurança:** O ritmo das ondas é previsível visualmente e sonoramente. Não há sustos, apenas ganância do jogador.
* **[NÚCLEO MOVA]:** No controle, ir e voltar é apertar `↑` e `↓` em 1 milissegundo. No tapete físico, ir à frente e retornar exige deslocar o peso e vencer a inércia. O risco de "não dar tempo de voltar" é fisicamente sentido.

### Conceito 2: A Onça (ou Estátua na Floresta)
* **Eixos:** Sobrevivência, Inibição (Go-No-Go), Ritmo.
* **Fantasia:** O jogador caminha por uma trilha na floresta.
* **Ação:** Pisar repetidamente no Centro (ou alternar Frente/Trás) para fazer o personagem andar.
* **A Surpresa (Regra):** Um som de galho estalando avisa. Segundos depois, uma onça (ou bicho-preguiça dormindo que não pode acordar) aparece. O jogador deve **CONGELAR**. Qualquer impacto no tapete acorda o bicho e perde a rodada.
* **Segurança:** O estímulo avisa *antes* de acontecer.
* **[NÚCLEO MOVA]:** No controle, parar é simplesmente soltar o botão. No tapete, se você está no meio de um passo, precisa recrutar musculatura de core e perna para "frear" o corpo e não gerar impacto. É uma tarefa motora inibitória complexa disfarçada de brincadeira infantil.

### Conceito 3: Feira Livre (O Maestro das Caixas)
* **Eixos:** Decisão, Troca de Regra, Coordenação.
* **Fantasia:** Separar frutas que rolam em esteiras (Frente, Esquerda, Direita).
* **Ação:** Pisar na zona correspondente quando a fruta chega ao fim da esteira.
* **A Surpresa (Regra):** O jogo começa óbvio: Maçã = Frente, Banana = Lado. De repente, o "Chefe da Feira" grita uma promoção: "Hoje Banana é na Frente!". O jogador precisa desmapear e remapear as direções na cabeça sob leve pressão de tempo.
* **Segurança:** Frutas caem em ritmo constante. A dificuldade está na cognição, não na velocidade física.
* **Diferencial:** A carga cognitiva de mapear regras mutáveis para movimentos espaciais reais do corpo recruta vias neurais duplas (Dual-Tasking), muito usado em prevenção de quedas em idosos.

---

## G. Conceitos Genuinamente "MOVA"

A pergunta central era: *"Se trocar por um controle, continua igual?"*

* **Estoura! (MVP):** [FRACO PARA MOVA]. É divertido, mas no controle seria apenas um Whack-a-Mole comum. Serve bem como MVP técnico.
* **Feira Livre:** [MÉDIO]. Mapear botões mentalmente é comum em jogos (ex: Guitar Hero), embora fazê-lo com os pés adicione valor.
* **A Maré:** **[NÚCLEO MOVA]**. O risco de ir longe (bordas) e não conseguir voltar para a segurança (centro) a tempo usa a inércia e o tempo de deslocamento físico do jogador como principal mecânica de tensão.
* **A Onça:** **[NÚCLEO MOVA]**. Frear o próprio corpo exige propriocepção e controle motor inibitório que controles de videogame simplesmente ignoram.

## H. Jogos que recomendo manter
1. **Estoura!** (Apenas como MVP técnico para validar hardware e latência. Não sustenta o projeto sozinho a longo prazo).
2. **Banda do Coreto** (Excelente potencial audiovisual e rítmico. Muito polimento necessário, mas vale a pena).

## I. Jogos que recomendo modificar
1. **Rio Acima** -> Substituir pela mecânica de **A Maré**. Transformar a ideia difusa de "vários microjogos" na mecânica hiperfocada de *Risco Espacial* (ir para a borda e voltar para o centro).

## J. Jogos que recomendo abandonar
1. **Farol da Neblina** -> Problemas de segurança (olhos fechados, instabilidade). A mecânica de inibição que queríamos aqui é muito melhor resolvida no jogo **A Onça**.

---

## K. Coleção Final Proposta (Roadmap de Protótipos)

1. **MVP Técnico:** `ESTOURA!` (Valida reação simples, hardware e latência).
2. **Jogo de Identidade:** `BANDA DO CORETO` (Valida precisão temporal e ritmo).
3. **Jogo Complementar:** `A MARÉ` (Valida o conceito do centro como "casa" e risco de deslocamento físico).
4. **O Experimento:** `A ONÇA` (Valida inibição motora e freio corporal).

## L. Identidade Geral do MOVA
Abandonar a ideia genérica de "Dashboard de Minigames". 
Adotar a **"Vila MOVA"**.
* O "Centro" do tapete é a Praça. 
* Olhando para frente está a Tenda de Balões (Estoura!).
* Olhando para a esquerda está o Coreto da Banda (Ritmo).
* Olhando para a direita está a Praia (A Maré).
* Olhando para trás está a Trilha da Floresta (A Onça).
O jogador literalmente vira de frente para o jogo que quer jogar na interface. A identidade é calorosa, ensolarada, com forte influência da arquitetura de interior do Brasil (praças, feiras, coretos), sem cair em folclore estereotipado. É um mundo que convida a passear.

## M. Resumo para Fisioterapia
* **FATO:** Exercícios de dupla-tarefa (Dual-Task) e tempo de reação previnem quedas em idosos.
* **HIPÓTESE DO PROJETO:** Exigir que o jogador iniba um passo repentinamente (A Onça) ou decida alterar o destino do passo em tempo real (Feira Livre) treina os mesmos reflexos necessários para evitar um tropeço no dia a dia.
* **DECISÃO DE DESIGN:** Focaremos em mecânicas lúdicas que, por acidente, exijam essas valências (Inibição, Risco, Antecipação), sem jamais rotulá-las como "tratamento médico" na interface do paciente.
