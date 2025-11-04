#include <Arduino.h>
#include <WiFi.h>
#include <HomeSpan.h>
#include <DHT.h>
#include "config.h"

DHT dht(DHTPIN, DHTTYPE);

// -----------------------------
// Temperature Sensor Service
// -----------------------------
struct SpanTempSensor : Service::TemperatureSensor {
  Characteristic::CurrentTemperature *temp;
  unsigned long lastRead = 0;

  SpanTempSensor() : Service::TemperatureSensor() {
    temp = new Characteristic::CurrentTemperature(0.0);
    temp->setRange(-40, 125);
  }

  void loop() override {
    if (millis() - lastRead > UPDATE_INTERVAL) {
      lastRead = millis();

      float t = dht.readTemperature();
      if (!isnan(t)) {
        temp->setVal(t);
        LOG1("🌡 Temperature: "); LOG1(t); LOG1(" °C\n");
      }else{
        temp->setVal(0.0);
        LOG1("Failed to read from DHT sensor!\n");
      }
    }
  }
};

// -----------------------------
// Humidity Sensor Service
// -----------------------------
struct SpanHumSensor : Service::HumiditySensor {
  Characteristic::CurrentRelativeHumidity *hum;
  unsigned long lastRead = 0;

  SpanHumSensor() : Service::HumiditySensor() {
    hum = new Characteristic::CurrentRelativeHumidity(0.0);
  }

  void loop() override {
    if (millis() - lastRead > UPDATE_INTERVAL) {
      lastRead = millis();

      float h = dht.readHumidity();
      if (!isnan(h)) {
        hum->setVal(h);
        LOG1("💧 Humidity: "); LOG1(h); LOG1(" %\n");
      }else{
        hum->setVal(0.0);
        LOG1("Failed to read from DHT sensor!\n");
      }
    }
  }
};

void setup() {
  Serial.begin(115200);

  // ---- Wi-Fi init ----
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(WIFI_HOSTNAME);
  #ifdef WIFI_POWER
    WiFi.setTxPower(WIFI_POWER);
  #endif

  dht.begin();

  // ---- HomeSpan init ----
  homeSpan.setLogLevel(1);  // Log messages
  homeSpan.setStatusPin(LED_BUILTIN);       // Status LED pin
  homeSpan.setWifiCredentials(WIFI_SSID, WIFI_PASSWORD);
  homeSpan.setPairingCode(PAIRING_CODE);
  homeSpan.begin(Category::Sensors, SENSOR_NAME);

  // ---- Accessory ----
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Name(SENSOR_NAME);
      new Characteristic::Manufacturer(SENSOR_MANUFACTURER);
      new Characteristic::SerialNumber(SENSOR_SERIAL);
      new Characteristic::Model(SENSOR_MODEL);
      new Characteristic::FirmwareRevision(SENSOR_FIRMWARE);
      new Characteristic::Identify();
    new SpanTempSensor();
    new SpanHumSensor();
}

void loop() {
  homeSpan.poll();
}
