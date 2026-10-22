/**
 * MOVA – Five-Zone Firmware v2 (PassoCerto)
 * =========================================
 * Hardware : ESP32 DevKit V1 (DOIT ESP32 DEVKIT V1)
 * Network  : Wi-Fi Access Point  SSID=MOVA-ESP32  PW=mova1234  IP=192.168.4.1
 * WS port  : 81
 *
 * Pin Mapping (5 Zones - all Piezos on ADC1 so Wi-Fi never conflicts):
 *  - CENTER : Piezo = GPIO36 (VP) | LED = GPIO25
 *  - FRONT  : Piezo = GPIO34      | LED = GPIO26
 *  - RIGHT  : Piezo = GPIO35      | LED = GPIO27
 *  - BACK   : Piezo = GPIO32      | LED = GPIO14
 *  - LEFT   : Piezo = GPIO33      | LED = GPIO13
 *  - STATUS : Onboard Blue LED = GPIO2 (flashes on boot, ready, and any impact)
 *
 * Detection Pipeline:
 *  1. Boot noise-floor calibration per zone (200 samples / 2 s)
 *     dynamicThreshold[z] = constrain(noiseFloor[z] + 3*noiseStdDev[z], 300, 2000)
 *  2. Threshold crossing on any zone -> 30 ms multi-zone peak-capture window
 *  3. Greatest Peak Selection across all 5 zones (anti-crosstalk filter)
 *  4. Peak confirmation > dynamicThreshold[winner] * 1.2
 *  5. Instant WebSocket JSON broadcast + non-blocking 200 ms LED flash
 *  6. 220 ms refractory period to suppress foot bounce
 */

#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

// ── Zone definitions ─────────────────────────────────────────────────────────
static const int NUM_ZONES = 5;

const char* ZONE_NAMES[NUM_ZONES] = {
  "center",   // Zone 0
  "front",    // Zone 1
  "right",    // Zone 2
  "back",     // Zone 3
  "left"      // Zone 4
};

// ADC1 input pins (safe to use simultaneously with Wi-Fi)
const int PIEZO_PINS[NUM_ZONES] = {
  36,  // center (VP / ADC1_CH0)
  34,  // front  (ADC1_CH6)
  35,  // right  (ADC1_CH7)
  32,  // back   (ADC1_CH4)
  33   // left   (ADC1_CH5)
};

// Digital output pins for zone indicator LEDs
const int LED_PINS[NUM_ZONES] = {
  25,  // center LED
  26,  // front LED
  27,  // right LED
  14,  // back LED
  13   // left LED
};

#define PIN_ONBOARD_LED 2

// ── Wi-Fi AP credentials ─────────────────────────────────────────────────────
const char* AP_SSID     = "MOVA-ESP32";
const char* AP_PASSWORD = "mova1234";

// ── WebSocket server ─────────────────────────────────────────────────────────
WebSocketsServer webSocket(81);

// ── Per-zone calibration state ───────────────────────────────────────────────
float noiseFloor[NUM_ZONES]       = {0};
float noiseStdDev[NUM_ZONES]      = {0};
int   dynamicThreshold[NUM_ZONES] = {300, 300, 300, 300, 300};

// ── Timing & non-blocking LED state ──────────────────────────────────────────
static const unsigned long REFRACTORY_MS  = 220;
static const unsigned long PEAK_WINDOW_MS = 30;
static const unsigned long LED_FLASH_MS   = 200;

unsigned long lastTriggerMs = 0;
unsigned long ledOffTime[NUM_ZONES] = {0};
bool          ledActive[NUM_ZONES]  = {false};
unsigned long onboardLedOffTime     = 0;
bool          onboardLedActive      = false;

// ── Helpers ──────────────────────────────────────────────────────────────────

/** Trigger a non-blocking LED flash for a specific zone + onboard LED. */
void triggerZoneLED(int zone, unsigned long now) {
  digitalWrite(LED_PINS[zone], HIGH);
  ledActive[zone]  = true;
  ledOffTime[zone] = now + LED_FLASH_MS;

  digitalWrite(PIN_ONBOARD_LED, HIGH);
  onboardLedActive  = true;
  onboardLedOffTime = now + LED_FLASH_MS;
}

/** Extinguish any LEDs whose flash duration has elapsed. */
void updateLEDs(unsigned long now) {
  for (int z = 0; z < NUM_ZONES; z++) {
    if (ledActive[z] && (long)(now - ledOffTime[z]) >= 0) {
      digitalWrite(LED_PINS[z], LOW);
      ledActive[z] = false;
    }
  }
  if (onboardLedActive && (long)(now - onboardLedOffTime) >= 0) {
    digitalWrite(PIN_ONBOARD_LED, LOW);
    onboardLedActive = false;
  }
}

/** Blocking flash of all LEDs used only during setup() boot/ready signals. */
void flashAllLEDs(int count, unsigned int onMs = 120, unsigned int gapMs = 120) {
  for (int i = 0; i < count; i++) {
    for (int z = 0; z < NUM_ZONES; z++) digitalWrite(LED_PINS[z], HIGH);
    digitalWrite(PIN_ONBOARD_LED, HIGH);
    delay(onMs);
    for (int z = 0; z < NUM_ZONES; z++) digitalWrite(LED_PINS[z], LOW);
    digitalWrite(PIN_ONBOARD_LED, LOW);
    if (i < count - 1) delay(gapMs);
  }
}

// ── Step 1: Per-zone noise-floor calibration ─────────────────────────────────

void calibrateNoiseFloor() {
  const int   NUM_SAMPLES    = 200;
  const float TOTAL_DURATION = 2000.0f; // ms
  const float INTERVAL_MS    = TOTAL_DURATION / NUM_SAMPLES;

  Serial.println("[CAL] Starting 5-zone noise-floor calibration (200 samples / 2 s)...");

  float sum[NUM_ZONES]  = {0.0f};
  float sum2[NUM_ZONES] = {0.0f};

  for (int i = 0; i < NUM_SAMPLES; i++) {
    for (int z = 0; z < NUM_ZONES; z++) {
      int val = analogRead(PIEZO_PINS[z]);
      sum[z]  += val;
      sum2[z] += (float)val * val;
    }
    delay((unsigned long)INTERVAL_MS);
  }

  for (int z = 0; z < NUM_ZONES; z++) {
    noiseFloor[z]  = sum[z] / NUM_SAMPLES;
    float mean2    = sum2[z] / NUM_SAMPLES;
    float variance = mean2 - (noiseFloor[z] * noiseFloor[z]);
    if (variance < 0.0f) variance = 0.0f;
    noiseStdDev[z] = sqrtf(variance);

    int rawThreshold    = (int)(noiseFloor[z] + 3.0f * noiseStdDev[z]);
    dynamicThreshold[z] = constrain(rawThreshold, 300, 2000);

    Serial.printf("[CAL] Zone=%-6s (GPIO%d) | noiseFloor=%6.1f | stdDev=%5.1f | threshold=%d\n",
                  ZONE_NAMES[z], PIEZO_PINS[z], noiseFloor[z], noiseStdDev[z], dynamicThreshold[z]);
  }
}

// ── WebSocket event handler ──────────────────────────────────────────────────

void onWebSocketEvent(uint8_t clientNum, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED: {
      IPAddress clientIP = webSocket.remoteIP(clientNum);
      Serial.printf("[WS] Client #%u connected from %s\n", clientNum, clientIP.toString().c_str());

      StaticJsonDocument<192> doc;
      doc["type"]   = "connected";
      doc["device"] = "mova-esp32";
      doc["zones"]  = 5;
      doc["ip"]     = "192.168.4.1";
      char buf[192];
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

// ── Broadcast footstep JSON ──────────────────────────────────────────────────

void broadcastFootstep(int zone, int peakAdc, float intensity, unsigned long timestamp) {
  StaticJsonDocument<128> doc;
  doc["type"]      = "footstep";
  doc["zone"]      = ZONE_NAMES[zone];
  doc["intensity"] = roundf(intensity * 100.0f) / 100.0f;
  doc["timestamp"] = timestamp;
  doc["source"]    = "esp32";

  char buf[128];
  serializeJson(doc, buf, sizeof(buf));
  webSocket.broadcastTXT(buf);

  Serial.printf("[IMPACT] Zone=%-6s | ADC=%4d | Intensity=%.2f | JSON=%s\n",
                ZONE_NAMES[zone], peakAdc, intensity, buf);
}

// ── setup() ──────────────────────────────────────────────────────────────────

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n===== MOVA Five-Zone Firmware v2 =====");

  // Configure LED output pins
  pinMode(PIN_ONBOARD_LED, OUTPUT);
  digitalWrite(PIN_ONBOARD_LED, LOW);

  for (int z = 0; z < NUM_ZONES; z++) {
    pinMode(LED_PINS[z], OUTPUT);
    digitalWrite(LED_PINS[z], LOW);
  }

  // Single boot flash
  flashAllLEDs(1, 200, 200);
  delay(200);

  // Start Wi-Fi Access Point
  Serial.println("[AP] Starting access point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  delay(500);

  IPAddress apIP = WiFi.softAPIP();
  Serial.printf("[AP] MOVA-ESP32 started. IP: %s\n", apIP.toString().c_str());

  // Calibrate all 5 zones
  calibrateNoiseFloor();

  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
  Serial.println("[WS] WebSocket server listening on port 81");

  // Three flashes -> ready signal
  delay(200);
  flashAllLEDs(3, 120, 120);
  Serial.println("[SYS] Ready — listening for impacts on all 5 zones (center=36, front=34, right=35, back=32, left=33).");
}

// ── loop() ───────────────────────────────────────────────────────────────────

void loop() {
  webSocket.loop();

  unsigned long now = millis();
  updateLEDs(now);

  // Enforce refractory period after a confirmed footstep
  if ((now - lastTriggerMs) < REFRACTORY_MS) {
    return;
  }

  // Check if any zone crossed its dynamic threshold
  bool triggered = false;
  int peak[NUM_ZONES];

  for (int z = 0; z < NUM_ZONES; z++) {
    peak[z] = analogRead(PIEZO_PINS[z]);
    if (peak[z] > dynamicThreshold[z]) {
      triggered = true;
    }
  }

  if (triggered) {
    // ── 30 ms multi-zone peak-capture window ────────────────────────────────
    unsigned long windowStart = millis();
    while ((millis() - windowStart) < PEAK_WINDOW_MS) {
      for (int z = 0; z < NUM_ZONES; z++) {
        int sample = analogRead(PIEZO_PINS[z]);
        if (sample > peak[z]) {
          peak[z] = sample;
        }
      }
    }

    // ── Greatest Peak Selection (anti-crosstalk) ────────────────────────────
    // Pick the zone that exceeded its confirmation threshold (1.2x) with the
    // largest signal above its calibrated noise floor.
    int   bestZone  = -1;
    float bestDelta = 0.0f;

    for (int z = 0; z < NUM_ZONES; z++) {
      int confirmThreshold = (int)(dynamicThreshold[z] * 1.2f);
      if (peak[z] > confirmThreshold) {
        float delta = (float)peak[z] - noiseFloor[z];
        if (bestZone == -1 || delta > bestDelta) {
          bestZone  = z;
          bestDelta = delta;
        }
      }
    }

    if (bestZone != -1) {
      unsigned long hitTime = millis();
      float intensity = (float)peak[bestZone] / 4095.0f;
      if (intensity > 1.0f) intensity = 1.0f;
      if (intensity < 0.0f) intensity = 0.0f;

      // Non-blocking LED flash + immediate WebSocket broadcast (< 1 ms delay)
      triggerZoneLED(bestZone, hitTime);
      broadcastFootstep(bestZone, peak[bestZone], intensity, hitTime);

      lastTriggerMs = hitTime;
    }
  }
}
