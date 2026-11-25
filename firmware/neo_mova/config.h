#pragma once
// Pinagem usada no firmware; a equipe relata validação física do sensor.
// Anexar foto/esquema da montagem para documentar sinais e LED.
constexpr int PIN_TRIG=13, PIN_ECHO=26, PIN_LED=2;
constexpr bool LED_ATIVO_ALTO=true;
constexpr char AP_NOME[]="NEO-MOVA";
constexpr char AP_SENHA[]="neo-mova-2026"; // Rede local de demonstração; alterar para a bancada.
constexpr unsigned SENSOR_PERIODO_MS=70, SENSOR_VALIDADE_MS=250;
constexpr unsigned ECHO_TIMEOUT_US=25000;
