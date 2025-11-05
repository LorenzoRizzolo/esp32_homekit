# 🏠 esp32 HomeKit

A small project that turns an **ESP32 (classic or C3)** into an **Apple HomeKit** temperature & humidity sensor.  
Supports **DHT22**, **DHT11** and **DHT21** sensors and optionally an **SPI LCD** for local display.

---

## What it does

- Reads temperature and humidity from a DHT sensor.
- Exposes those values to Apple Home (HomeKit) so you can view them in the Home app and use them in automations.
- Optionally can also show readings on an SPI LCD connected to the ESP32.

---

## ⚙️ Requirements

### Hardware
- ESP32 (classic) **or** ESP32-C3  
- DHT22 sensor (recommended) — DHT11 or DHT21 also supported  
- Optional: SPI LCD display (i've tested with ST7789) 
- USB cable for flashing the board

### Software
- PlatformIO (recommended)  
  - Install options:
    - Via pip: `pip install platformio`
    - Or install the PlatformIO extension in VS Code
- macOS / iOS device with Apple Home (Home app) for pairing
- Git (optional, for repository management)

---

## Getting started

### 1. Copy the config template
Copy the example config into the include folder for your version:
```bash
cp config.example.h <version>/include/config.h
```
Replace <version> with the folder you use in your project (the same structure used by the repo, homekit or homekit_and_lcd).

### 2. Edit the config file
Open <version>/include/config.h and set:
- Wi-Fi SSID (WIFI_SSID) and password (WIFI_PASSWORD)
- HomeKit pairing code (the code shown by HomeKit)
- Any pin definitions (if different from defaults)
- WIFI_POWER (see next section)


#### Wi-Fi Power Settings
- If you're using an ESP32-C3 with an external antenna (for example a small copper wire antenna), use:
  ```c
  #define WIFI_POWER WIFI_POWER_5dBm
  ```
  like in image/esp32c3_antenna.png
- If you're using an ESP32-C3 with the built-in PCB antenna, use:
  ```c
  #define WIFI_POWER WIFI_POWER_8_5dBm
  ```
- If you're using an ESP32 (classic), comment the line:
  ```c
  // #define WIFI_POWER 
  ```

### 3. Connect the hardware
- Connect the DHT sensor to the ESP32 according to the pin definitions in your config.h
- If using an SPI LCD, connect it according to your pin definitions
- Connect the ESP32 to your computer via USB and run the following command to flash the firmware:
```bash
platformio run --target upload -e <environment> && sudo pio device monitor -e <environment>
```
Replace `<environment>` with the environment you are using (for example, `esp32ce` or `esp32`).

<<<<<<< HEAD
=======
---

## Associate with Homekit
After the upload, in serial monitor type the space key to print the Homekit options.
You have the wifi network and pairing code already setted in the `config.h` file, so you don't need to change anything.
Just connect your iPhone to the same wifi network and open the Homekit app.

---

## Features
- Temperature sensor
- Humidity sensor

# LCD Display (optional)
If you want to use an LCD display to show temperature and humidity values, connect it to your esp32 or esp32c3 as follows:
- VCC to 3.3V
- GND to GND
- SDA to GPIO21 (or any other I2C SDA pin)
- SCL to GPIO22 (or any other I2C SCL pin)
<img width="250" height="300" alt="IMG_9303" src="https://github.com/user-attachments/assets/9a713a55-9e1f-49ec-a2e5-21b2cfebf365" />
>>>>>>> 9f21eac4b4a5ca205f75b2bc1d4bba70944e36d2

### 4. Pair with HomeKit
- Open the Home app on your iOS device.
- Tap the "+" icon to add a new accessory.
- Select "I Don't Have a Code or Cannot Scan".
- Choose the ESP32 HomeKit accessory from the list.
- Enter the HomeKit pairing code you set in config.h when prompted.