#include <Arduino.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define ANALOG_OUTPUT PA6

#define IRMP_INPUT_PIN PA6
#define IRMP_PROTOCOL_NAMES 1
#define IRMP_SUPPORT_NEC_PROTOCOL 1 

#include <irmpSelectMain15Protocols.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <irmp.hpp>
#include <IRMPconfig.h>
#include <IRMP.h>


Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

IRMP_DATA irmp_data;

void setup() {
  Serial.begin(115200);
  pinMode(IRMP_INPUT_PIN, INPUT);
  irmp_init();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED
  display.setTextColor(SSD1306_WHITE); // Configura el color del texto en blanco
  display.setTextSize(1); // Configura un tamaño de texto pequeño
  display.clearDisplay(); // Limpia la pantalla
}

void loop() {
  
  int command;
   
  if (irmp_get_data(&irmp_data)) {
    
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("INFO ");
    display.print(irmp_data.command);
    display.display();

    delay(2000);
    
  
  }else{
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("Esperando info");
    display.display();
  }
  
  
  /*display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.println(command);
  display.display();*/

  delay(1000); // Pequeña pausa para evitar lecturas rápidas y rebotes de botón
}


