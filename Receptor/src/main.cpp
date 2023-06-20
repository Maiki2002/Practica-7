#include <Arduino.h>

#define IRMP_INPUT_PIN PA6
#define IRMP_PROTOCOL_NAMES 1
#define IRMP_SUPPORT_NEC_PROTOCOL 1 


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <irmp.hpp>
#include <IRMPconfig.h>
#include <IRMP.h>

#define USE_ONE_TIMER_FOR_IRMP_AND_IRSND

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

IRMP_DATA irmp_data;


const int buttonPin1 = PA5;  // Pin del primer botón
const int buttonPin2 = PA6;  // Pin del segundo botón

bool buttonState1 = false;
bool buttonState2 = false;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);  // Configura el primer botón como entrada con resistencia pull-up interna
  pinMode(buttonPin2, INPUT_PULLUP);  // Configura el segundo botón como entrada con resistencia pull-up interna

  Serial.begin(9600);
  pinMode(IRMP_INPUT_PIN, INPUT);
  irmp_init();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED
  display.setTextColor(SSD1306_WHITE); // Configura el color del texto en blanco
  display.setTextSize(1); // Configura un tamaño de texto pequeño
  display.clearDisplay(); // Limpia la pantalla
}

void loop() {
  static uint8_t command;
   
  if (irmp_get_data(&irmp_data)) {
    
    //if(irmp_data.protocol == 1 && irmp_data.address == 0x01){
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print("Hola");
      display.display();
   // }
    
    
    /* if(irmp_data.command > 9){
      command = irmp_data.command;
    } else {
      command = 0;
      analogWrite(ANALOG_OUTPUT, command);
      irmp_result_print(&irmp_data);
    }*/
  
  }else{
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("No recibi info. :( ");
    display.display();
  }
  
  
  /*display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.println(command);
  display.display();*/

  delay(100); // Pequeña pausa para evitar lecturas rápidas y rebotes de botón
}

