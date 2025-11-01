#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include "config.h" // 🔐 Secure credentials header

// ------------------- Pin Configuration -------------------
#define DHTPIN 2
#define DHTTYPE DHT11
#define SOIL_PIN 34
#define VIBRATION_PIN 27
#define BUZZER_PIN 25

// ------------------- DHT Sensor -------------------
DHT dht(DHTPIN, DHTTYPE);

// ------------------- Timer Variables -------------------
unsigned long previousMillis = 0;
const unsigned long interval = 15000; // 15 seconds

// ------------------- Helper: Timestamped Logging -------------------
void logWithTime(const String &message) {
  unsigned long seconds = millis() / 1000;
  unsigned long mins = seconds / 60;
  unsigned long secs = seconds % 60;
  Serial.print("[");
  if (mins < 10) Serial.print("0");
  Serial.print(mins);
  Serial.print(":");
  if (secs < 10) Serial.print("0");
  Serial.print(secs);
  Serial.print("] ");
  Serial.println(message);
}

// ------------------- Helper: WiFi Reconnect -------------------
void ensureWiFiConnected() {
  if (WiFi.status() != WL_CONNECTED) {
    logWithTime("⚠️ WiFi disconnected, reconnecting...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    unsigned long startAttemptTime = millis();
    
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
      delay(1000);
      Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      logWithTime("✅ Reconnected to WiFi!");
    } else {
      logWithTime("❌ WiFi reconnection failed!");
    }
  }
}

// ------------------- Setup -------------------
void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(SOIL_PIN, INPUT);
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  logWithTime("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  logWithTime("✅ WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ------------------- Loop -------------------
void loop() {
  ensureWiFiConnected();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    float soilMoisture = analogRead(SOIL_PIN);
    int vibration = digitalRead(VIBRATION_PIN);

    if (isnan(humidity) || isnan(temperature)) {
      logWithTime("⚠️ DHT read failed!");
      return;
    }

    logWithTime("------ Sensor Readings ------");
    Serial.print("🌡️ Temperature: "); Serial.println(temperature);
    Serial.print("💧 Humidity: "); Serial.println(humidity);
    Serial.print("🌱 Soil Moisture (raw): "); Serial.println(soilMoisture);
    Serial.print("📳 Vibration: "); Serial.println(vibration);
    Serial.println("-----------------------------");

    // ------------------- Send to ML API (with Retry) -------------------
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["temperature_C"] = temperature;
    jsonDoc["soil_moisture"] = soilMoisture;
    jsonDoc["vibration_peak_g"] = vibration;

    String jsonData;
    serializeJson(jsonDoc, jsonData);

    logWithTime("📡 Sending to ML API...");
    Serial.println(jsonData);

    HTTPClient http;
    int httpResponseCode = -1;
    int retryCount = 0;
    const int maxRetries = 3;

    while (retryCount < maxRetries) {
      http.begin(mlServer);
      http.addHeader("Content-Type", "application/json");
      httpResponseCode = http.POST(jsonData);

      if (httpResponseCode > 0) break;
      logWithTime("⚠️ Retry ML API...");
      retryCount++;
      delay(1000);
    }

    if (httpResponseCode > 0) {
      String response = http.getString();
      logWithTime("🔍 ML API Response:");
      Serial.println(response);

      StaticJsonDocument<512> respDoc;
      DeserializationError error = deserializeJson(respDoc, response);
      if (!error) {
        const char *prediction = respDoc["prediction"];
        float landslideProb = respDoc["probabilities"]["Landslide Event"] | 0.0;

        if (prediction) {
          Serial.print("📊 ML Prediction: ");
          Serial.println(prediction);
          Serial.print("🎯 Landslide Probability: ");
          Serial.println(landslideProb, 3);

          // 🚨 Trigger only if probability > 0.8
          if (String(prediction) == "Landslide Event" && landslideProb > 0.8) {
            logWithTime("🚨 ML Model Predicts Landslide Event with high confidence!");
            for (int i = 0; i < 4; i++) {
              digitalWrite(BUZZER_PIN, HIGH);
              delay(200);
              digitalWrite(BUZZER_PIN, LOW);
              delay(200);
            }
          }
        }
      } else {
        logWithTime("⚠️ Could not parse ML response!");
      }
    } else {
      Serial.print("❌ Error calling ML API: ");
      Serial.println(httpResponseCode);
    }
    http.end();

    // ------------------- Send to ThingSpeak (with Retry) -------------------
    String url = String(thingSpeakServer) +
                 "?api_key=" + apiKey +
                 "&field1=" + String(humidity) +
                 "&field2=" + String(temperature) +
                 "&field3=" + String(soilMoisture) +
                 "&field4=" + String(vibration);

    HTTPClient httpTS;
    int tsResponse = -1;
    retryCount = 0;
    while (retryCount < maxRetries) {
      httpTS.begin(url);
      tsResponse = httpTS.GET();
      if (tsResponse > 0) break;
      logWithTime("⚠️ Retry ThingSpeak...");
      retryCount++;
      delay(1000);
    }

    if (tsResponse > 0) {
      logWithTime("📤 Data sent to ThingSpeak successfully!");
    } else {
      Serial.println("❌ ThingSpeak Error: " + String(tsResponse));
    }
    httpTS.end();
  }
}
