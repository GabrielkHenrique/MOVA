# 💻 Passo 5: Gravando o ESP32 e Rodando o Jogo Completo

Aqui está o passo a passo para ligar o seu hardware pronto ao software do MOVA, ver os 5 sensores funcionando e jogar na TV + Painel do Terapeuta.

---

## 1. O Código do ESP32 já está gravado?

**SIM!** Neste computador o seu ESP32 já foi gravado com o **Firmware v2 de 5 Zonas** ([`firmware/mova_firmware.ino`](../firmware/mova_firmware.ino)).
A memória do ESP32 **não apaga quando você tira da tomada/USB**. Assim que você plugar o cabo USB nele, ele já liga rodando o programa das 5 zonas!

### Como regravar se você mudar alguma coisa no código (ou trocar de ESP32):

#### Pela Arduino IDE:
1. Abra o arquivo `firmware/mova_firmware_v2_one_zone/mova_firmware_v2_one_zone.ino` (ou `firmware/mova_firmware/mova_firmware.ino`).
2. No menu **Tools > Board**, selecione **`DOIT ESP32 DEVKIT V1`**.
3. No menu **Tools > Port**, selecione **`/dev/ttyUSB0`** (Linux) ou a porta **`COM`** (Windows).
4. Clique no botão da seta para a direita (**Upload `→`**) no canto superior esquerdo.

#### Ou pelo VS Code (1 clique):
1. No VS Code aberto na pasta `MOVA`, aperte `Ctrl+Shift+P` → digite **`Tasks: Run Task`**.
2. Clique em **`ESP32: Upload One-Zone Firmware (/dev/ttyUSB0)`**.

---

## 2. Calibrando e Testando as 5 Zonas no Serial Monitor

Toda vez que o ESP32 liga (ou quando você aperta o botão **`EN`** nele), ele mede o silêncio da sala durante **2 segundos** para calibrar as 5 zonas automaticamente.

1. Plugue o ESP32 no USB e **não encoste nos piezos por 2 segundos**.
2. Observe o **LED azul da placa ESP32**:
   - **1 piscada longa** = Ligou e criou o Wi-Fi `MOVA-ESP32`.
   - *(2 segundos calibrando...)*
   - **3 piscadas rápidas** = Calibração concluída! Pronto para receber pisadas.
3. Abra o **Serial Monitor** na Arduino IDE (ícone de lupa no canto superior direito, velocidade em **`115200 baud`**) e aperte o botão **`EN`** no ESP32. Você verá:
   ```text
   ===== MOVA Five-Zone Firmware v2 =====
   [AP] Starting access point...
   [AP] MOVA-ESP32 started. IP: 192.168.4.1
   [CAL] Starting 5-zone noise-floor calibration (200 samples / 2 s)...
   [CAL] Zone=center (GPIO36) | noiseFloor=   0.0 | stdDev=  0.0 | threshold=300
   [CAL] Zone=front  (GPIO34) | noiseFloor=   0.0 | stdDev=  0.0 | threshold=300
   [CAL] Zone=right  (GPIO35) | noiseFloor=   0.0 | stdDev=  0.0 | threshold=300
   [CAL] Zone=back   (GPIO32) | noiseFloor=   0.0 | stdDev=  0.0 | threshold=300
   [CAL] Zone=left   (GPIO33) | noiseFloor=   0.0 | stdDev=  0.0 | threshold=300
   [WS] WebSocket server listening on port 81
   [SYS] Ready — listening for impacts on all 5 zones (center=36, front=34, right=35, back=32, left=33).
   ```
4. Dê um tapinha em cada um dos 5 discos piezo e confira se cada um imprime a sua zona correta (`center`, `front`, `right`, `back`, `left`):
   ```text
   [IMPACT] Zone=center | ADC=1920 | Intensity=0.47 | JSON={"type":"footstep","zone":"center","intensity":0.47,"timestamp":12450,"source":"esp32"}
   ```

---

## 3. Conectando o Notebook ao Wi-Fi do Tapete (`MOVA-ESP32`)

O ESP32 cria uma rede Wi-Fi própria para funcionar em qualquer clínica ou sala de aula **sem precisar de roteador nem internet**:

1. Abra a lista de redes Wi-Fi do seu notebook.
2. Conecte-se na rede **`MOVA-ESP32`**.
3. Digite a senha: **`mova1234`**
   - *(O seu computador vai avisar "Conectado, sem internet" — isso é 100% normal, pois a rede é local entre o seu PC e o tapete!).*

---

## 4. Iniciando os 3 Serviços do Jogo

Dentro da pasta do projeto (`~/projects/MOVA`), abra **3 terminais** (ou use o menu `Terminal -> Run Task...` do VS Code):

### Terminal 1 — O Motor do Jogo (Porta 8080):
```bash
node engine/server.js
```

### Terminal 2 — O Servidor das Telas Web (Porta 3000):
```bash
npx serve . --listen 3000
```

### Terminal 3 — A Ponte do ESP32 (`192.168.4.1:81` → `localhost:8080`):
```bash
node hardware/esp32-client.js
```
*(No Windows PowerShell, se precisar definir o IP manualmente: `$env:ESP32_IP="192.168.4.1"; node hardware/esp32-client.js`)*

---

## 5. Abrindo as Telas e Jogando!

Com os 3 terminais rodando, abra o navegador (Chrome ou Edge) nestes endereços:

1. 🩺 **Painel do Terapeuta:** [http://localhost:3000/apps/therapist-panel/](http://localhost:3000/apps/therapist-panel/)
   - Olhe o selo em **Hardware**: com o Wi-Fi conectado no `MOVA-ESP32`, ele deve estar verde escrito **`● ESP32 conectado`**.
2. 📺 **TV do Paciente:** [http://localhost:3000/apps/tv/](http://localhost:3000/apps/tv/)
   - Coloque esta janela na TV/projetor (aperte `F11` para tela cheia).
3. 🕹️ **Simulador (Opcional / Testes sem tapete):** [http://localhost:3000/simulator/](http://localhost:3000/simulator/)

### Hora de Jogar:
1. No **Painel do Terapeuta**, digite o nome do paciente e clique em **`▶ Iniciar Atividade`**.
2. Na **TV do Paciente**, os balões começarão a aparecer nas 5 posições (`Frente`, `Esquerda`, `Centro`, `Direita`, `Trás`).
3. Pise (ou bata com o dedo) no piezo correspondente para estourar os balões normais e dourados — e **não pise nas bombas**!
4. Ao final dos 60 segundos (ou clicando em **`⏹ Encerrar Atividade`**), a tela mostra as estrelas e estatísticas, e você pode clicar em **`🖨️ Imprimir / Salvar PDF`** para gerar o relatório clínico!

---

👉 **Próximo passo:** Se qualquer coisa der errado na hora da montagem ou apresentação, consulte o **[`06-SOLUCAO-DE-PROBLEMAS-E-CHECKLIST.md`](./06-SOLUCAO-DE-PROBLEMAS-E-CHECKLIST.md)**!
