#ifndef CONFIG_H
#define CONFIG_H

#define DHTPIN 4
#define DHTTYPE DHT22

#define UPDATE_INTERVAL 5000  // update interval in milliseconds
// use 2 on esp32 and 8 on esp32c3
#define LED_BUILTIN 2 // Status LED pin

// set you wifi credentials
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
// manage the wifi power
// - for esp32 classic comment the #define line
// - for esp32c3 uncomment the #define line
// - for esp32c3 with external antenna as in README.md use WIFI_POWER_5dBm
#define WIFI_POWER WIFI_POWER_8_5dBm
#define WIFI_HOSTNAME "esp32c3"

// sensor characteristics
#define PAIRING_CODE "11223344"
#define SENSOR_NAME "DHT22 Sensor"
#define SENSOR_MANUFACTURER "RizzoloCloud Labs"
#define SENSOR_SERIAL "DHT22-000000"
#define SENSOR_MODEL "DHT22-ESP32C3"
#define SENSOR_FIRMWARE "1.0"

// remove that lines if you don't have the LCD display
// use your display detail of the device if you use one
// ---- TFT Display (ST7789 170x320) ----
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_DC   16
#define TFT_RST  17
#define TFT_CS   5
#define DISPLAY_UPDATE_INTERVAL 10000
#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 170

#endif // CONFIG_H
