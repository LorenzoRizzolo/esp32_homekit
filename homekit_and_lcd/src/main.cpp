#include <Arduino.h>
#include <WiFi.h>
#include <HomeSpan.h>
#include <DHT.h>
#include "config.h"
#include "display.h"

DHT dht(DHTPIN, DHTTYPE);
float temperature = 0.0;
float humidity = 0.0;

unsigned long lastDisplayUpdate = 0;

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

      temperature = dht.readTemperature();
      if (!isnan(temperature)) {
        LOG1("🌡 Temperature: "); LOG1(temperature); LOG1(" °C\n");
      }else{
        temperature = 0.0;
        LOG1("Failed to read from DHT sensor!\n");
      }
        temp->setVal(temperature);
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

      humidity = dht.readHumidity();
      if (!isnan(humidity)) {
        LOG1("💧 Humidity: "); LOG1(humidity); LOG1(" %\n");
      }else{
        humidity = 0.0;
        LOG1("Failed to read from DHT sensor!\n");
      }
        hum->setVal(humidity);
    }
  }
};

void setup() {
  Serial.begin(115200);

  // display init
  displayInit();

  // ---- Wi-Fi init ----
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(WIFI_HOSTNAME);
  #ifdef WIFI_POWER
    WiFi.setTxPower(WIFI_POWER);
  #endif

  dht.begin();

  // ---- HomeSpan init ----
  homeSpan.setLogLevel(1);  // Log messages
  homeSpan.setStatusPin(LED_BUILTIN);
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

  if (millis() - lastDisplayUpdate > DISPLAY_UPDATE_INTERVAL) {
    lastDisplayUpdate = millis();
    displayUpdate(temperature, humidity);
  }
}
