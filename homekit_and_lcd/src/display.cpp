#include "display.h"
#include "config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void displayInit() {
  tft.init(DISPLAY_HEIGHT, DISPLAY_WIDTH);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Initializing...");
}

void displayUpdate(float temperature, float humidity) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(7);
  tft.printf("%.1f", temperature);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.print(" C");

  tft.setTextColor(ST77XX_YELLOW);
  tft.print("\n\n\n"+String(humidity, 1));
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" % \nof humidity");
}
void displayClear() {
  tft.fillScreen(ST77XX_BLACK);
}