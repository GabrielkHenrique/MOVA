/**
 * MOVA – One-Zone MVP Firmware v2
 * ================================
 * Zone    : CENTER
 * Piezo   : GPIO36 (ADC1_CH0, input-only)
 * LED     : GPIO25
 * Network : Wi-Fi Access Point  SSID=MOVA-ESP32  PW=mova1234
 * WS port : 81
 *
 * Detection pipeline:
 *  1. Boot noise-floor calibration (200 samples / 2 s)
 *     dynamicThreshold = noiseFloor + 3*noiseStdDev  (clamped 300-2000)
 *  2. Threshold crossing → 30 ms peak-capture window
 *  3. Peak confirmation  > dynamicThreshold * 1.2
 *  4. Broadcast JSON footstep event over WebSocket
 *  5. 220 ms refractory period
 */

#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

// ── Pin definitions ──────────────────────────────────────────────────────────
#define PIN_PIEZO_CENTER  36   // ADC1_CH0, input-only
#define PIN_LED           25

// ── Wi-Fi AP credentials ─────────────────────────────────────────────────────
const char* AP_SSID     = "MOVA-ESP32";
const char* AP_PASSWORD = "mova1234";

// ── WebSocket server ─────────────────────────────────────────────────────────
WebSocketsServer webSocket(81);

// ── Calibration results ──────────────────────────────────────────────────────
float noiseFloor    = 0.0f;
float noiseStdDev   = 0.0f;
int   dynamicThreshold = 300;   // computed at boot

// ── Refractory period state ──────────────────────────────────────────────────
static const unsigned long REFRACTORY_MS  = 220;
static const unsigned long PEAK_WINDOW_MS = 30;
unsigned long lastTriggerMs = 0;

// ── Helpers ──────────────────────────────────────────────────────────────────

/** Flash the LED for `durationMs` milliseconds. */
void flashLED(unsigned int durationMs) {
  digitalWrite(PIN_LED, HIGH);
  delay(durationMs);
  digitalWrite(PIN_LED, LOW);
}

/** Flash the LED `count` times with a short gap between flashes. */
void flashLEDMultiple(int count, unsigned int onMs = 120, unsigned int gapMs = 120) {
  for (int i = 0; i < count; i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(onMs);
    digitalWrite(PIN_LED, LOW);
    if (i < count - 1) delay(gapMs);
  }
}

// ── Step 1: Noise-floor calibration ─────────────────────────────────────────

/**
 * Sample the center piezo 200 times over ~2 seconds.
 * Computes mean and standard deviation, then sets dynamicThreshold.
 * Clamped to [300, 2000].
 */
void calibrateNoiseFloor() {
  const int   NUM_SAMPLES    = 200;
  const float TOTAL_DURATION = 2000.0f; // ms
  const float INTERVAL_MS    = TOTAL_DURATION / NUM_SAMPLES;

  Serial.println("[CAL] Starting noise-floor calibration (200 samples / 2 s)...");

  float sum  = 0.0f;
  float sum2 = 0.0f;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    int val = analogRead(PIN_PIEZO_CENTER);
    sum  += val;
    sum2 += (float)val * val;
    delay((unsigned long)INTERVAL_MS);
  }

  noiseFloor  = sum / NUM_SAMPLES;
  float mean2 = sum2 / NUM_SAMPLES;
  float variance = mean2 - (noiseFloor * noiseFloor);
  if (variance < 0.0f) variance = 0.0f;   // floating-point guard
  noiseStdDev = sqrtf(variance);

  int rawThreshold = (int)(noiseFloor + 3.0f * noiseStdDev);
  dynamicThreshold = constrain(rawThreshold, 300, 2000);

  Serial.printf("[CAL] noiseFloor=%.1f  noiseStdDev=%.1f  rawThreshold=%d  dynamicThreshold=%d\n",
                noiseFloor, noiseStdDev, rawThreshold, dynamicThreshold);
}

// ── Step 5: WebSocket event handler ─────────────────────────────────────────

void onWebSocketEvent(uint8_t clientNum, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED: {
      IPAddress clientIP = webSocket.remoteIP(clientNum);
      Serial.printf("[WS] Client #%u connected from %s\n", clientNum, clientIP.toString().c_str());

      // Send welcome / handshake message
      StaticJsonDocument<128> doc;
      doc["type"]   = "connected";
      doc["device"] = "mova-esp32";
      doc["zone"]   = "center";
      doc["ip"]     = "192.168.4.1";
      char buf[128];
      serializeJson(doc, buf);
      webSocket.sendTXT(clientNum, buf);
      break;
    }

    case WStype_DISCONNECTED:
      Serial.printf("[WS] Client #%u disconnected\n", clientNum);
      break;

    case WStype_TEXT:
      Serial.printf("[WS] Message from #%u: %s\n", clientNum, (char*)payload);
      break;

    case WStype_ERROR:
      Serial.printf("[WS] Error on client #%u\n", clientNum);
      break;

    default:
      break;
  }
}

// ── Step 3: Build and broadcast footstep JSON ────────────────────────────────

void broadcastFootstep(float intensity) {
  StaticJsonDocument<128> doc;
  doc["type"]      = "footstep";
  doc["zone"]      = "center";
  doc["intensity"] = intensity;
  doc["timestamp"] = millis();
  doc["source"]    = "esp32";

  char buf[128];
  serializeJson(doc, buf);
  webSocket.broadcastTXT(buf);
  Serial.printf("[EVT] %s\n", buf);
}

// ── setup() ─────────────────────────────────────────────────────────────────

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n===== MOVA One-Zone MVP Firmware v2 =====");

  // Configure pins
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  // GPIO36 is input-only; no pinMode needed (ADC read works by default)

  // Step 4-1: Single boot flash
  flashLED(200);
  delay(200);

  // Step 4-2: Start Wi-Fi AP
  Serial.println("[AP] Starting access point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  delay(500); // let the AP stabilise

  IPAddress apIP = WiFi.softAPIP();
  // Step 4-3: Print IP
  Serial.printf("[AP] MOVA-ESP32 started. IP: %s\n", apIP.toString().c_str());

  // Step 4-4: Noise-floor calibration
  calibrateNoiseFloor();

  // Step 4-5: Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
  Serial.println("[WS] WebSocket server listening on port 81");

  // Step 4-6: Three flashes → ready signal
  delay(200);
  flashLEDMultiple(3);
  Serial.println("[SYS] Ready — waiting for impacts.");
}

// ── loop() ──────────────────────────────────────────────────────────────────

void loop() {
  webSocket.loop();

  // ── Step 2: Impact detection ────────────────────────────────────────────
  int raw = analogRead(PIN_PIEZO_CENTER);

  if (raw > dynamicThreshold) {
    unsigned long now = millis();

    // Check refractory period
    if ((now - lastTriggerMs) >= REFRACTORY_MS) {

      // ── 30 ms peak-capture window ────────────────────────────────────────
      int peak = raw;
      unsigned long windowStart = millis();
      while ((millis() - windowStart) < PEAK_WINDOW_MS) {
        int sample = analogRead(PIN_PIEZO_CENTER);
        if (sample > peak) peak = sample;
      }

      // ── Confirmation: peak must exceed 120 % of threshold ────────────────
      int confirmThreshold = (int)(dynamicThreshold * 1.2f);
      if (peak > confirmThreshold) {
        // Compute intensity, clamped to [0.0, 1.0]
        float intensity = (float)peak / 4095.0f;
        if (intensity > 1.0f) intensity = 1.0f;
        if (intensity < 0.0f) intensity = 0.0f;

        // Flash LED (non-blocking-ish: 200 ms — WebSocket loop resumes after)
        flashLED(200);

        // Broadcast JSON event
        broadcastFootstep(intensity);

        // Start refractory period
        lastTriggerMs = millis();
      }
      // else: noise spike — ignore, no refractory period consumed
    }
  }
}
