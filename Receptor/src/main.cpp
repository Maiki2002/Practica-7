#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define ANALOG_OUTPUT PA6

#define IRMP_INPUT_PIN PA6
#define IRMP_PROTOCOL_NAMES 1
#define IRMP_SUPPORT_NEC_PROTOCOL 1 

#include <Arduino.h>
#include <irmpSelectMain15Protocols.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <irmp.hpp>
#include <IRMPconfig.h>
#include <IRMP.h>

namespace global{
    Adafruit_SSD1306* oled;
    IRMP_DATA irmp_data;
    int command;
    float vcommand;
}

IRMP_DATA irmp_data;

void setup() {

    pinMode(IRMP_INPUT_PIN, INPUT);
    irmp_init();
    
    global::oled = new Adafruit_SSD1306 (OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
    global::oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);            // Inicializa la pantalla OLED
    global::oled->setTextColor(SSD1306_WHITE);                  // Configura el color del texto en blanco
    global::oled->setTextSize(1);                               // Configura un tamaño de texto pequeño
    global::oled->clearDisplay();                               // Limpia la pantalla

    analogWrite(PA1, LOW);
    }

void loop() {
   
  if (irmp_get_data(&(global::irmp_data))) {
    
    global::oled->clearDisplay();
    global::oled->setTextSize(2);
    global::oled->setCursor(0, 0);
    global::oled->print("INFO ");
    global::oled->print(global::irmp_data.command);
    global::oled->display();

    switch(irmp_data.command){
      case 0:
        global::oled->clearDisplay();
        global::oled->setTextSize(2);
        global::oled->setCursor(0, 0);
        global::oled->print("MODO APAGADO");
        global::oled->display();
      break;
      case 1:
        global::oled->clearDisplay();
        global::oled->setTextSize(2);
        global::oled->setCursor(0, 0);
        global::oled->print("MODO ENCENDIDO");
        global::oled->display();
      break;
      default: 
        global::oled->clearDisplay();
        global::oled->setTextSize(2);
        global::oled->setCursor(0, 0);
        global::oled->print("MODO ENCENDIDO Y REGULADO");
        global::oled->display();
      break;
    }
  
    delay(2000);
  }else{
    global::oled->clearDisplay();
    global::oled->setTextSize(2);
    global::oled->setCursor(0, 0);
    global::oled->print("Esperando info");
    global::oled->display();
  }

  if(global::irmp_data.command == 0){
    analogWrite(PA1, 0);
  } else if(global::irmp_data.command == 1){
    analogWrite(PA1, 100);
  }else{
    global::oled->clearDisplay();
    global::oled->setTextSize(1);
    global::oled->setCursor(0, 0);
    global::oled->print("\n");
    global::oled->print("Voltaje: ");
    global::command = global::irmp_data.command;
    global::vcommand = (global::irmp_data.command*3.3)/100;
    global::oled->print(global::vcommand,1);
    global::oled->display();
    analogWrite(PA1, global::vcommand);
  }

  global::oled->clearDisplay();

  delay(1000); // Pequeña pausa para evitar lecturas rápidas y rebotes de botón
}
