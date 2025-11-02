# esp32_homekit

## Hardware components
- ESP32 classic or ESP32-C3
- DHT22 sensor (or DHT11, DHT21)


## Get Started
Copy the file `/config.h.example` into `/include/config.h` and complete all data necessary for your ESP.

For the definintion of `WIFI_POWER` i've used `WIFI_POWER_5dBm` becouse i've added an external antenna of copper wire to my esp32c3 (like in the photo below), if you don't have it use `WIFI_POWER_8_5dBm` to maximase the performance of your wifi module.

![esp32c3_antenna][https://github.com/LorenzoRizzolo/esp32_homekit/blob/main/images/esp32c3_antenna.png?raw=true]


Connect your esp32c3 or esp32 to your computer and run
```bash
sudo pio run -e esp323/esp32
```
After compilation successfully, upload the firmware to your esp32 device.
Use the command
``` bash
# compile, upload and monitor
sudo pio run -e esp323/esp32 -t upload && sudo pio device monitor -e esp323/esp32
```

---

## Associate with Homekit
After the upload, in serial monitor type the space key to print the Homekit options.
You have the wifi network and pairing code already setted in the `config.h` file, so you don't need to change anything.
Just connect your iPhone to the same wifi network and open the Homekit app.

---

## Features
- Temperature sensor
- Humidity sensor