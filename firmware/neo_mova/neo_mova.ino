#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <esp_http_server.h>
#include <esp_system.h>
#include <esp_heap_caps.h>
#include <cJSON.h>
#include "config.h"
#include "protocolo.h"
#include "pagina.h"

// TDE: o ESP32 é o servidor, adquire o sensor e comanda o LED.
// O Pipo completo (regras, desenho e métricas de jogo) é o cliente web.
namespace {
portMUX_TYPE muxEco = portMUX_INITIALIZER_UNLOCKED;
SemaphoreHandle_t mutexEstado = nullptr;
volatile uint32_t ecoInicioUs = 0, ecoDuracaoUs = 0;
volatile bool ecoPronto = false, ecoArmado = false, ecoSubiu = false;
bool esperandoEco = false, temAmostra = false;
uint32_t disparoUs = 0, ultimoDisparoMs = 0, ultimaAmostraMs = 0, bootMs = 0;
uint32_t amostras = 0, amostrasValidas = 0, amostrasInvalidas = 0;
uint32_t transicoesPerna = 0, latenciaTransicaoMs = 0, latenciaMaxMs = 0;
float distanciaCm = 0;
bool sensorValido = false, pernaLevantada = false;
uint8_t candidatoPerna = 0, candidatoN = 0;
uint32_t candidatoDesdeMs = 0;
char bootId[24] = {};

enum class ModoLed : uint8_t { Automatico, Ligado, Desligado };
ModoLed modoLed = ModoLed::Automatico;
bool ledLigado = false;

void IRAM_ATTR bordaEco() {
  portENTER_CRITICAL_ISR(&muxEco);
  if (ecoArmado) {
    const uint32_t agora = micros();
    if (digitalRead(PIN_ECHO)) {
      ecoInicioUs = agora;
      ecoSubiu = true;
    } else if (ecoSubiu) {
      ecoDuracaoUs = agora - ecoInicioUs;
      ecoPronto = true;
      ecoArmado = false;
    }
  }
  portEXIT_CRITICAL_ISR(&muxEco);
}

const char* nomeModoLed() {
  switch (modoLed) {
    case ModoLed::Ligado: return "ligar";
    case ModoLed::Desligado: return "desligar";
    default: return "automatico";
  }
}

void aplicarLed() {
  ledLigado = modoLed == ModoLed::Ligado ||
      (modoLed == ModoLed::Automatico && sensorValido && pernaLevantada);
  digitalWrite(PIN_LED, ledLigado == LED_ATIVO_ALTO ? HIGH : LOW);
}

void registrarLeitura(float cm, bool valida, uint32_t agoraMs) {
  ++amostras;
  temAmostra = true;
  ultimaAmostraMs = agoraMs;
  sensorValido = valida && isfinite(cm) && cm >= 5.0f && cm <= 60.0f;
  if (!sensorValido) {
    ++amostrasInvalidas;
    distanciaCm = 0;
    candidatoN = 0;
    aplicarLed();
    return;
  }

  ++amostrasValidas;
  distanciaCm = cm;
  const uint8_t novoCandidato = cm <= 28.0f ? 1 : cm >= 32.0f ? 0 : candidatoPerna;
  if (novoCandidato == candidatoPerna) {
    if (candidatoN < 255) ++candidatoN;
  } else {
    candidatoPerna = novoCandidato;
    candidatoN = 1;
    candidatoDesdeMs = agoraMs;
  }
  if (candidatoN >= 2 && pernaLevantada != (candidatoPerna == 1)) {
    pernaLevantada = candidatoPerna == 1;
    ++transicoesPerna;
    latenciaTransicaoMs = agoraMs - candidatoDesdeMs;
    if (latenciaTransicaoMs > latenciaMaxMs) latenciaMaxMs = latenciaTransicaoMs;
  }
  aplicarLed();
}

void adquirirSensor(uint32_t agoraMs) {
  uint32_t duracao = 0;
  bool pronto = false;
  portENTER_CRITICAL(&muxEco);
  pronto = ecoPronto;
  if (pronto) {
    duracao = ecoDuracaoUs;
    ecoPronto = false;
  }
  portEXIT_CRITICAL(&muxEco);

  if (esperandoEco && (pronto || uint32_t(micros() - disparoUs) >= ECHO_TIMEOUT_US)) {
    portENTER_CRITICAL(&muxEco);
    ecoArmado = false;
    portEXIT_CRITICAL(&muxEco);
    esperandoEco = false;
    const bool ecoValido = pronto && duracao > 0 && duracao <= ECHO_TIMEOUT_US;
    registrarLeitura(ecoValido ? duracao * 0.0343f / 2.0f : 0.0f, ecoValido, agoraMs);
  }

  if (!esperandoEco && uint32_t(agoraMs - ultimoDisparoMs) >= SENSOR_PERIODO_MS) {
    ultimoDisparoMs = agoraMs;
    portENTER_CRITICAL(&muxEco);
    ecoPronto = false;
    ecoSubiu = false;
    ecoArmado = true;
    portEXIT_CRITICAL(&muxEco);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    disparoUs = micros();
    esperandoEco = true;
  }
}

void texto(cJSON* objeto, const char* chave, const char* valor) {
  if (objeto) cJSON_AddStringToObject(objeto, chave, valor);
}
void numero(cJSON* objeto, const char* chave, double valor) {
  if (objeto) cJSON_AddNumberToObject(objeto, chave, valor);
}

cJSON* criarStatus() {
  auto* raiz = cJSON_CreateObject();
  if (!raiz) return nullptr;
  texto(raiz, "versao", "neo-mova-web-1");
  texto(raiz, "origem", "ESP32");
  texto(raiz, "boot_id", bootId);
  numero(raiz, "uptime_ms", millis() - bootMs);

  auto* sensor = cJSON_AddObjectToObject(raiz, "sensor");
  if (!sensor) { cJSON_Delete(raiz); return nullptr; }
  cJSON_AddBoolToObject(sensor, "valido", sensorValido);
  cJSON_AddBoolToObject(sensor, "perna_levantada", sensorValido && pernaLevantada);
  if (sensorValido) numero(sensor, "distancia_cm", distanciaCm);
  else cJSON_AddNullToObject(sensor, "distancia_cm");
  if (temAmostra) numero(sensor, "idade_ms", uint32_t(millis() - ultimaAmostraMs));
  else cJSON_AddNullToObject(sensor, "idade_ms");

  auto* atuador = cJSON_AddObjectToObject(raiz, "led");
  if (!atuador) { cJSON_Delete(raiz); return nullptr; }
  texto(atuador, "modo", nomeModoLed());
  cJSON_AddBoolToObject(atuador, "ligado", ledLigado);

  auto* jogo = cJSON_AddObjectToObject(raiz, "jogo");
  if (!jogo) { cJSON_Delete(raiz); return nullptr; }
  texto(jogo, "execucao", "cliente_web");

  auto* metricas = cJSON_AddObjectToObject(raiz, "metricas");
  if (!metricas) { cJSON_Delete(raiz); return nullptr; }
  numero(metricas, "heap_livre", ESP.getFreeHeap());
  numero(metricas, "heap_minimo", ESP.getMinFreeHeap());
  numero(metricas, "maior_bloco_livre", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  numero(metricas, "amostras_sensor", amostras);
  numero(metricas, "amostras_validas", amostrasValidas);
  numero(metricas, "amostras_invalidas", amostrasInvalidas);
  numero(metricas, "transicoes_perna", transicoesPerna);
  numero(metricas, "latencia_transicao_ms", latenciaTransicaoMs);
  numero(metricas, "latencia_transicao_max_ms", latenciaMaxMs);
  return raiz;
}

esp_err_t enviarJson(httpd_req_t* req, cJSON* objeto) {
  if (!objeto) return httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Sem memoria");
  char* corpo = cJSON_PrintUnformatted(objeto);
  cJSON_Delete(objeto);
  if (!corpo) return httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Sem memoria");
  httpd_resp_set_type(req, "application/json; charset=utf-8");
  const auto resultado = httpd_resp_send(req, corpo, HTTPD_RESP_USE_STRLEN);
  cJSON_free(corpo);
  return resultado;
}

esp_err_t erroHttp(httpd_req_t* req, const char* status, const char* mensagem) {
  httpd_resp_set_status(req, status);
  httpd_resp_set_type(req, "text/plain; charset=utf-8");
  return httpd_resp_send(req, mensagem, HTTPD_RESP_USE_STRLEN);
}

esp_err_t enviarAudio(httpd_req_t* req) {
  File arquivo = SPIFFS.open("/audio.ogg", "r");
  if (!arquivo) return httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Audio indisponivel");
  httpd_resp_set_type(req, "audio/ogg");
  httpd_resp_set_hdr(req, "Cache-Control", "public, max-age=86400");
  uint8_t bloco[2048];
  esp_err_t resultado = ESP_OK;
  while (arquivo.available()) {
    const size_t tamanho = arquivo.read(bloco, sizeof(bloco));
    if (!tamanho) break;
    resultado = httpd_resp_send_chunk(req, reinterpret_cast<const char*>(bloco), tamanho);
    if (resultado != ESP_OK) break;
  }
  arquivo.close();
  if (resultado == ESP_OK) resultado = httpd_resp_send_chunk(req, nullptr, 0);
  return resultado;
}

esp_err_t atender(httpd_req_t* req) {
  httpd_resp_set_hdr(req, "Cache-Control", "no-store");
  const char* rota = req->uri;
  if (!strcmp(rota, "/audio.ogg") && req->method == HTTP_GET) return enviarAudio(req);
  const bool led = !strcmp(rota, "/api/led");
  const bool consulta = !strcmp(rota, "/") || !strcmp(rota, "/api/sensor") || !strcmp(rota, "/api/status");
  if (!led && !consulta) return httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Rota inexistente");
  if ((led && req->method != HTTP_POST) || (consulta && req->method != HTTP_GET)) {
    httpd_resp_set_hdr(req, "Allow", led ? "POST" : "GET");
    return httpd_resp_send_err(req, HTTPD_405_METHOD_NOT_ALLOWED, "Metodo incorreto");
  }
  if (!strcmp(rota, "/")) {
    httpd_resp_set_type(req, "text/html; charset=utf-8");
    return httpd_resp_send(req, PAGINA, sizeof(PAGINA) - 1);
  }
  if (led) {
    if (req->content_len > 128) return erroHttp(req, "413 Payload Too Large", "Limite 128 bytes");
    char tipo[64] = {};
    httpd_req_get_hdr_value_str(req, "Content-Type", tipo, sizeof(tipo));
    char* parametro = strchr(tipo, ';');
    if (parametro) *parametro = 0;
    if (strcasecmp(tipo, "application/json")) return erroHttp(req, "415 Unsupported Media Type", "Use application/json");
    char corpo[129] = {}, valor[16] = {};
    size_t recebido = 0;
    const uint32_t inicio = millis();
    while (recebido < req->content_len) {
      if (uint32_t(millis() - inicio) > 1500) return ESP_FAIL;
      const int n = httpd_req_recv(req, corpo + recebido, req->content_len - recebido);
      if (n <= 0) return ESP_FAIL;
      recebido += static_cast<size_t>(n);
    }
    if (!neo::lerComando(corpo, recebido, "modo", valor))
      return httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "JSON ou comando invalido");
    xSemaphoreTake(mutexEstado, portMAX_DELAY);
    if (!strcmp(valor, "ligar")) modoLed = ModoLed::Ligado;
    else if (!strcmp(valor, "desligar")) modoLed = ModoLed::Desligado;
    else modoLed = ModoLed::Automatico;
    aplicarLed();
    auto* resposta = criarStatus();
    xSemaphoreGive(mutexEstado);
    return enviarJson(req, resposta);
  }
  xSemaphoreTake(mutexEstado, portMAX_DELAY);
  cJSON* resposta = nullptr;
  if (!strcmp(rota, "/api/status")) resposta = criarStatus();
  else {
    resposta = cJSON_CreateObject();
    if (resposta) {
      cJSON_AddBoolToObject(resposta, "valido", sensorValido);
      cJSON_AddBoolToObject(resposta, "perna_levantada", sensorValido && pernaLevantada);
      if (sensorValido) numero(resposta, "distancia_cm", distanciaCm);
      else cJSON_AddNullToObject(resposta, "distancia_cm");
      if (temAmostra) numero(resposta, "idade_ms", uint32_t(millis() - ultimaAmostraMs));
      else cJSON_AddNullToObject(resposta, "idade_ms");
    }
  }
  xSemaphoreGive(mutexEstado);
  return enviarJson(req, resposta);
}

esp_err_t tratar(httpd_req_t* req) { return atender(req); }
} // namespace

void setup() {
  Serial.begin(115200);
  pinMode(PIN_TRIG, OUTPUT); digitalWrite(PIN_TRIG, LOW);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LED, OUTPUT); digitalWrite(PIN_LED, LOW);
  mutexEstado = xSemaphoreCreateMutex();
  if (!mutexEstado) { Serial.println("Falha ao criar mutex"); while (true) delay(1000); }
  bootMs = millis();
  snprintf(bootId, sizeof(bootId), "%08lx%08lx", (unsigned long)esp_random(), (unsigned long)esp_random());
  attachInterrupt(digitalPinToInterrupt(PIN_ECHO), bordaEco, CHANGE);
  if (!SPIFFS.begin(false)) Serial.println("SPIFFS sem audio; Pipo funciona sem trilha");

  WiFi.mode(WIFI_AP);
  if (!WiFi.softAP(AP_NOME, AP_SENHA)) { Serial.println("Falha ao iniciar Wi-Fi AP"); return; }
  Serial.printf("NEO MOVA boot=%s chip=%s rev=%d\n", bootId, ESP.getChipModel(), ESP.getChipRevision());
  Serial.printf("SERVIDOR AP=%s HTTP=http://%s/\n", AP_NOME, WiFi.softAPIP().toString().c_str());

  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.uri_match_fn = httpd_uri_match_wildcard;
  config.stack_size = 8192;
  config.max_open_sockets = 8;
  config.lru_purge_enable = true;
  config.recv_wait_timeout = 1;
  config.send_wait_timeout = 1;
  httpd_handle_t servidor = nullptr;
  if (httpd_start(&servidor, &config) != ESP_OK) { Serial.println("Falha ao iniciar HTTP"); return; }
  httpd_uri_t rota = {};
  rota.uri = "/*";
  rota.method = static_cast<httpd_method_t>(HTTP_ANY);
  rota.handler = tratar;
  if (httpd_register_uri_handler(servidor, &rota) != ESP_OK) Serial.println("Falha ao registrar rotas HTTP");
}

void loop() {
  const uint32_t agora = millis();
  xSemaphoreTake(mutexEstado, portMAX_DELAY);
  adquirirSensor(agora);
  xSemaphoreGive(mutexEstado);
  delay(1);
}
