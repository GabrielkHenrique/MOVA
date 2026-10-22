# 🏃 Passo 4: Disposição no Chão e Montagem Física do Tapete

Este guia mostra como organizar os 5 sensores no formato do jogo **tanto para testes rápidos de bancada/mesa** quanto para **quando forem colar no EVA e na madeira**.

---

## 1. O Mapa Oficial das 5 Zonas (Visão de Quem Está Pisando)

Coloque-se na posição do **paciente olhando para a TV à sua frente**. A disposição em cruz (igual a um tapete de dança) deve seguir exatamente esta posição para bater com os balões da tela:

```text
                   📺 [ TV DO PACIENTE ] 📺

                        ┌────────────┐
                        │ ⬆️ FRENTE  │
                        │   (front)  │
                        │  Pino D34  │
                        └────────────┘
         ┌────────────┐ ┌────────────┐ ┌────────────┐
         │⬅️ ESQUERDA │ │ 🎯 CENTRO  │ │ ➡️ DIREITA │
         │   (left)   │ │  (center)  │ │  (right)   │
         │  Pino D33  │ │ Pino VP/36 │ │  Pino D35  │
         └────────────┘ └────────────┘ └────────────┘
                        ┌────────────┐
                        │  ⬇️ TRÁS   │
                        │   (back)   │
                        │  Pino D32  │
                        └────────────┘
```

---

## 2. Teste Sem Madeira e Sem EVA (Na Mesa ou no Chão)

Enquanto vocês ainda não colaram no EVA/madeira:
1. **Na mesa (teste com as mãos):** Posicione as 5 moedinhas piezo na mesa formando a cruz acima e prenda o cabo de cada uma na mesa com um pedacinho de **fita crepe** a uns `3 cm` do disco. Isso evita que o peso do cabo de rede fique puxando a solda do piezo.
2. **Qual lado do disco piezo fica para cima?**
   - Tanto faz eletricamente, mas se você colar um quadradinho de fita dupla-face espuma ou papelão em cima da parte branca para dar o toque, **nunca bata com objetos metálicos ou pontiagudos direto na cerâmica branca** para ela não trincar.

---

## 3. Quando Forem Montar com EVA e Madeira (Dicas de Ouro)

Quando chegar a hora de colocar na estrutura física do tapete:

### A) O Segredo para o Piezo Sentir Bem a Pisada (Sem Quebrar!)
O disco piezo gera energia quando ele sofre uma **micro-flexão** (enverga de leve no meio).
- Se você colar o disco piezo inteiro chapado em uma madeira dura, ele quase não flexiona.
- Se você deixar uma pedra ou calço pontudo embaixo dele e alguém pisar com todo o peso do corpo, a cerâmica trinca.
- **Como montar perfeito (Sanduíche de EVA):**
  ```text
       [ Camada Superior: EVA Grosso (onde o pé pisa) ]
                   [ Moedinha de EVA / Feltro no centro ]
                   [    Disco Piezoelétrico (27mm)     ]
       [ Anel de EVA fino ou fita dupla-face espuma nas bordas ]
       [ Base Inferior: Placa de MDF / Compensado / EVA firme  ]
  ```
  - Proteja sempre a **bolinha de solda** do piezo fazendo um pequeno rebaixo no EVA ao redor da solda, para que o pé não amasse a solda contra o disco ao pisar.

### B) Isolamento Mecânico entre as 5 Zonas (Anti-Crosstalk)
Quando alguém pisa forte no **Centro**, a pancada treme a madeira inteira.
- **No Software:** O firmware v2 que já está gravado no seu ESP32 possui o algoritmo **Greatest Peak Selection** (ele lê as 5 zonas ao mesmo tempo durante `30 ms` e escolhe apenas a zona que teve o maior pico de impacto).
- **Na Estrutura Física:** Para ajudar ainda mais o filtro do software:
  - Se possível, use **5 quadrados separados de MDF/EVA** (um para cada zona) unidos por baixo pela lona/borracha antiderrapante, deixando um espacinho de `1 a 2 cm` entre um quadrado e outro. Isso impede que a vibração da madeira passe de uma zona para a outra!

### C) Passagem dos Cabos de Rede e Segurança
- Faça um pequeno sulco (canaleta) no EVA inferior para o cabo de rede passar reto sem criar "lombada" onde o paciente pisa.
- Prenda o cabo de rede na borda da placa com fita forte (Silver Tape / Hellermann) antes de ele sair para a protoboard — assim, se alguém puxar o cabo sem querer, o puxão não chega nas soldas dos piezos nem arranca fios da protoboard.
- **Superfície Antiderrapante Obrigatória:** A base que encosta no chão deve ter EVA texturizado ou tapete emborrachado antiderrapante para o tapete nunca escorregar durante o passo do paciente.

---

👉 **Próximo passo:** Abra agora o **[`05-GRAVANDO-ESP32-E-RODANDO-O-JOGO.md`](./05-GRAVANDO-ESP32-E-RODANDO-O-JOGO.md)** para ligar tudo no computador e jogar!
