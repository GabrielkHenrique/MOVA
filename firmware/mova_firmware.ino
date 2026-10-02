/**
 * MOVA ESP32 Firmware
 * ===================
 * Reads 5 piezoelectric sensors (one per foot zone), detects impact events,
 * and streams JSON footstep events to all connected WebSocket clients.
 * Also controls 5 indicator LEDs (one per zone).
 *
 * Hardware: ESP32 DevKit V1
 * Library:  WebSocketsServer by Markus Sattler (links2004/arduinowebsockets)
 *           Install via Arduino Library Manager: "WebSockets"
 *
 * Zones (in order): center, front, right, back, left
 */

#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>   // Install via Library Manager: "ArduinoJson" by Benoit Blanchon

// ---------------------------------------------------------------------------
// CONFIGURATION — Edit these before flashing
// ---------------------------------------------------------------------------
const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const uint16_t WS_PORT    = 81;    // WebSocket port (must match engine bridge)

// Impact threshold: ADC values range 0–4095 on ESP32 (12-bit).
// 1500 ≈ ~1.8 V; adjust lower for light taps, higher to reduce noise.
const int THRESHOLD       = 1500;

// Debounce window in milliseconds — ignore re-triggers within this period.
const unsigned long DEBOUNCE_MS = 300;

// LED flash duration in milliseconds.
const unsigned long LED_FLASH_MS = 200;

// ---------------------------------------------------------------------------
// ZONE DEFINITIONS
// ---------------------------------------------------------------------------
const int NUM_ZONES = 5;

// Human-readable zone names (must match engine expectations exactly)
const char* ZONE_NAMES[NUM_ZONES] = {
  "center",   // Zone 0
  "front",    // Zone 1
  "right",    // Zone 2
  "back",     // Zone 3
  "left"      // Zone 4
};

// ADC input pins — GPIO 34, 35, 32, 33, 36 are input-only on ESP32 DevKit V1
// and do NOT have internal pull-ups (correct for piezo/ADC use).
const int PIEZO_PINS[NUM_ZONES] = { 34, 35, 32, 33, 36 };

// Digital output pins for indicator LEDs
const int LED_PINS[NUM_ZONES] = { 2, 4, 5, 18, 19 };

// ---------------------------------------------------------------------------
// RUNTIME STATE
// ---------------------------------------------------------------------------
unsigned long lastTriggerTime[NUM_ZONES]; // Timestamp of last trigger per zone
unsigned long ledOffTime[NUM_ZONES];      // Timestamp when LED should turn off
bool          ledActive[NUM_ZONES];       // Whether LED is currently flashing

// ---------------------------------------------------------------------------
// WEBSOCKET SERVER
// ---------------------------------------------------------------------------
WebSocketsServer webSocket = WebSocketsServer(WS_PORT);

/**
 * WebSocket event handler.
 * Handles client connect / disconnect / incoming messages.
 */
void onWebSocketEvent(uint8_t clientNum, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED: {
      IPAddress clientIP = webSocket.remoteIP(clientNum);
      Serial.printf("[WS] Client #%u connected from %s\n", clientNum, clientIP.toString().c_str());
      // Send a hello/handshake so the engine bridge knows the server is ready
      webSocket.sendTXT(clientNum, "{\"type\":\"connected\",\"device\":\"mova-esp32\"}");
      break;
    }
    case WStype_DISCONNECTED:
      Serial.printf("[WS] Client #%u disconnected\n", clientNum);
      break;
    case WStype_TEXT:
      // The ESP32 currently only sends data; it does not act on incoming text.
      // Log it for debugging.
      Serial.printf("[WS] Message from client #%u: %s\n", clientNum, (char*)payload);
      break;
    default:
      break;
  }
}

// ---------------------------------------------------------------------------
// IMPACT DETECTION & EVENT EMISSION
// ---------------------------------------------------------------------------

/**
 * Evaluate a single zone for an impact event.
 * @param zone  Zone index (0–4)
 * @param now   Current millis() value (passed in to avoid repeated calls)
 */
void checkZone(int zone, unsigned long now) {
  int adcValue = analogRead(PIEZO_PINS[zone]);

  // Gate 1: Must exceed threshold
  if (adcValue < THRESHOLD) return;

  // Gate 2: Debounce — must not have triggered recently
  if ((now - lastTriggerTime[zone]) < DEBOUNCE_MS) return;

  // --- Impact confirmed ---
  lastTriggerTime[zone] = now;

  // Normalize intensity to 0.0–1.0
  float intensity = (float)adcValue / 4095.0f;
  // Clamp to [0, 1] in case of ADC overshoot
  if (intensity > 1.0f) intensity = 1.0f;

  // Flash the corresponding LED
  digitalWrite(LED_PINS[zone], HIGH);
  ledActive[zone]  = true;
  ledOffTime[zone] = now + LED_FLASH_MS;

  // Build and broadcast JSON event
  // e.g. {"type":"footstep","zone":"left","intensity":0.72,"timestamp":12345}
  StaticJsonDocument<128> doc;
  doc["type"]      = "footstep";
  doc["zone"]      = ZONE_NAMES[zone];
  doc["intensity"] = round(intensity * 100.0f) / 100.0f;  // 2 decimal places
  doc["timestamp"] = (unsigned long)now;

  char jsonBuffer[128];
  serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));

  Serial.printf("[IMPACT] Zone=%s | ADC=%d | Intensity=%.2f | JSON=%s\n",
                ZONE_NAMES[zone], adcValue, intensity, jsonBuffer);

  webSocket.broadcastTXT(jsonBuffer);
}

/**
 * Turn off any LEDs whose flash duration has elapsed.
 */
void updateLEDs(unsigned long now) {
  for (int i = 0; i < NUM_ZONES; i++) {
    if (ledActive[i] && now >= ledOffTime[i]) {
      digitalWrite(LED_PINS[i], LOW);
      ledActive[i] = false;
    }
  }
}

// ---------------------------------------------------------------------------
// SETUP
// ---------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("\n[MOVA] Booting...");

  // --- Configure GPIO pins ---
  for (int i = 0; i < NUM_ZONES; i++) {
    // ADC pins 34, 35, 36 are input-only; analogRead works without pinMode call,
    // but we set the others explicitly for clarity.
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);

    lastTriggerTime[i] = 0;
    ledOffTime[i]      = 0;
    ledActive[i]       = false;
  }

  // --- Wi-Fi connection ---
  Serial.printf("[WiFi] Connecting to SSID: %s\n", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Blink LED 0 (center) while connecting
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_PINS[0], !digitalRead(LED_PINS[0]));  // toggle
    if (++attempts > 40) {
      Serial.println("\n[WiFi] FAILED — check SSID/password. Restarting in 5s...");
      delay(5000);
      ESP.restart();
    }
  }

  digitalWrite(LED_PINS[0], LOW);
  Serial.println();
  Serial.printf("[WiFi] Connected! IP address: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("[WS]   WebSocket server starting on port %d\n", WS_PORT);

  // --- Start WebSocket server ---
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  Serial.println("[MOVA] Ready. Listening for impacts...\n");

  // --- Startup flash: blink all LEDs once to confirm boot ---
  for (int i = 0; i < NUM_ZONES; i++) digitalWrite(LED_PINS[i], HIGH);
  delay(300);
  for (int i = 0; i < NUM_ZONES; i++) digitalWrite(LED_PINS[i], LOW);
}

// ---------------------------------------------------------------------------
// MAIN LOOP
// ---------------------------------------------------------------------------
void loop() {
  // Process incoming WebSocket frames
  webSocket.loop();

  unsigned long now = millis();

  // Check all zones for impact events
  for (int i = 0; i < NUM_ZONES; i++) {
    checkZone(i, now);
  }

  // Extinguish expired LED flashes
  updateLEDs(now);

  // Small yield to keep Wi-Fi stack healthy; does NOT delay impact detection
  // significantly since the loop runs in microseconds.
  delay(1);
}
