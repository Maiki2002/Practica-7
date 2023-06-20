#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SSD1306_Defs.h"
#include "utilities.h"

#define ANALOG_INPUT PA0
#define ANALOG_OUTPUT PA1
// Objects that links the loop and setup function
namespace global {
  unsigned int analogReading;
  Adafruit_SSD1306* oled;
}

void setup() {
  // i2c configuration
  Wire.begin(SDA, SCL);
  // Instances an Adafruit_SSD1306 object
  global::oled = new Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT);
  // Initializes the oled object. Stops if the initialization fails
  if(!global::oled->begin(SSD1306_SWITCHCAPVCC, 60))
    utilities::blinkBreakpoint(100);
  // Set the color of the oled screen
  global::oled->setTextColor(SSD1306_WHITE);
  // Set A1 as an output
  pinMode(ANALOG_OUTPUT, OUTPUT);
}

void loop() {
  global::oled->clearDisplay();
  global::oled->setCursor(0, 0);
  global::oled->setTextSize(3);
  global::oled->print("uC 23i\n");
  global::oled->setTextSize(2);
  global::oled->print("Reading\n");
  global::analogReading = analogRead(ANALOG_INPUT);
  analogWrite(ANALOG_OUTPUT, global::analogReading/4);
  global::oled->printf("%d", global::analogReading);
  global::oled->display();
  delay(500);
}
