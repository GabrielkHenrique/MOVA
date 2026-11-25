# Hardware e montagem do NEO MOVA

Na descoberta inicial desta sessão havia apenas `/dev/ttyS4` desconhecido. Em uma segunda descoberta surgiu `/dev/ttyUSB0`, conversor CP2102 (10c4:ea60). `esptool chip-id` identificou ESP32-D0WD-V3, revisão v3.1; o tamanho de flash detectado foi 4 MB. A equipe informa que validou fisicamente os sensores. O modelo comercial da placa, pinout/fiação em foto e a confirmação visual do LED precisam constar no relatório. Logs de identificação estão em `evidencias/2026-11-15/`.

A consulta de identificação executa código auxiliar em RAM e reinicia via RTS; não grava flash. A primeira consulta emitiu alerta de frequência de cristal inesperada. A segunda consulta, `--no-stub flash-id`, reportou cristal de 40 MHz, flash de 4 MB (fabricante c4, dispositivo 6016) e tensão de flash 3,3 V. O alerta inicial não se repetiu; os dois registros foram preservados. Confirmar estabilidade de boot na bancada.

## Pinagem configurada e evidência de montagem

| Função | Configuração inicial | Conferência necessária |
| --- | --- | --- |
| TRIG HC-SR04 | GPIO13 | Registrar no esquema/foto da equipe |
| ECHO HC-SR04 | GPIO26 | Registrar divisor/conversor e nível final de 3,3 V |
| LED | GPIO2, ativo alto | Confirmar LED visível, integrado ou externo com resistor/polaridade |
| GND | Comum entre placa e sensor | Mostrar no esquema e na montagem |
| VCC sensor | Conforme módulo real | Registrar tensão e capacidade da alimentação |

ECHO de módulo alimentado em 5 V não deve ir diretamente ao GPIO. Divisor/conversor e valores reais devem constar no esquema e na foto da equipe. GPIO2 pode ter função de boot; conferir a placa e circuito externo. Não presumir que qualquer ESP32 tem LED nesse GPIO.

## Estado e conferências restantes

1. Inserir foto com modelo completo da placa, sensor, LED, alimentação e GND.
2. Anexar a evidência da validação física do sensor com alvo no campo de visão; a consulta automatizada mais recente foi feita sem alvo e por isso retornou inválida.
3. Confirmar LED montado no GPIO2 e demonstrar visualmente os comandos HTTP `ligar`/`desligar`.
4. O firmware foi compilado com `esp32:esp32:esp32`; esse perfil foi funcional na placa, mas anotar o modelo comercial/partições no relatório.
5. Reproduzir o teste conectado ao AP com `python3 scripts/verificar-pipo-placa.py`; ver [manifesto de evidências atualizado](evidencias/2026-11-19-pipo/MANIFESTO.md).

Registro histórico: a sequência original de gravação/validação está em [evidências de 18/11](evidencias/2026-11-18/MANIFESTO.md). Em 19/11, Pipo foi gravado e página/API foram testadas pela rede real; veja [evidências de 19/11](evidencias/2026-11-19-pipo/MANIFESTO.md). A equipe informa que validou fisicamente os sensores, mas ainda é necessário anexar a foto/vídeo dessa validação e observar o LED instalado.
