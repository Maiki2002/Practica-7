//Definicion de pines y configuraciones de la pantalla oled
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define ANALOG_OUTPUT PA6

#define IRMP_INPUT_PIN PA6
#define IRMP_PROTOCOL_NAMES 1
#define IRMP_SUPPORT_NEC_PROTOCOL 1 

//Inclusión de las bibliotecas necesarias
#include <Arduino.h>
#include <irmpSelectMain15Protocols.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <irmp.hpp>
#include <IRMPconfig.h>
#include <IRMP.h>

namespace global {
  Adafruit_SSD1306* oled;   // Objeto de la clase Adafruit_SSD1306 para la pantalla OLED
  IRMP_DATA irmp_data;      // Estructura para almacenar los datos recibidos por IRMP
  int command;              // Variable para almacenar el comando recibido
  float vcommand;           // Variable para almacenar el valor de voltaje calculado
}

void setup() {
  pinMode(IRMP_INPUT_PIN, INPUT);
  irmp_init();

  global::oled = new Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
  global::oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Inicializa la pantalla OLED
  global::oled->setTextColor(SSD1306_WHITE);        // Configura el color del texto en blanco
  global::oled->setTextSize(1);                     // Configura un tamaño de texto pequeño
  global::oled->clearDisplay();                     // Limpia la pantalla

  analogWrite(PA1, LOW);  // Configura el pin PA1 para salida analógica y lo establece en LOW
}

void loop() {
  if (irmp_get_data(&(global::irmp_data))) {
    global::oled->clearDisplay();
    global::oled->setTextSize(2);
    global::oled->setCursor(0, 0);
    global::oled->print("INFO ");
    global::oled->print(global::irmp_data.command);
    global::oled->display();

    // Realizar acciones según el comando recibido
    switch (global::irmp_data.command) {
      case 0:                                   //Si el receptor recibe un 0, se muestra en modo apagado
        global::oled->clearDisplay();
        global::oled->setTextSize(2);
        global::oled->setCursor(0, 0);
        global::oled->print("MODO APAGADO");
        global::oled->display();
        break;
      case 1:                                   //Si el receptor recibe un 1, se muestra en modo encendido
        global::oled->clearDisplay();
        global::oled->setTextSize(2);
        global::oled->setCursor(0, 0);
        global::oled->print("MODO ENCENDIDO");
        global::oled->display();
        break;
      default:                                  //Si el receptor recibe un numero diferente a 1 y 0,se muestra en modo regulado
        global::oled->clearDisplay();
        global::oled->setTextSize(2);
        global::oled->setCursor(0, 0);
        global::oled->print("MODO ENCENDIDO Y REGULADO");
        global::oled->display();
        break;
    }

    delay(2000);
  } else {                                      //Se muestra si el receptor no recibe una señal infraroja
    global::oled->clearDisplay();
    global::oled->setTextSize(2);
    global::oled->setCursor(0, 0);
    global::oled->print("Esperando info");
    global::oled->display();
  }

  // Realizar acciones adicionales según el comando recibido
  if (global::irmp_data.command == 0) {
    analogWrite(PA1, 0);                        // Establece el pin PA1 en 0 (LOW)
  } else if (global::irmp_data.command == 1) {
    analogWrite(PA1, 100);                      // Establece el pin PA1 en 100 (HIGH)
  } else {
    global::oled->clearDisplay();               // Establece el pin PA1 la conversion del valor recibido y se muestra el resultado en la pantalla oled
    global::oled->setTextSize(1);
    global::oled->setCursor(0, 0);
    global::oled->print("\n");
    global::oled->print("Voltaje: ");
    global::command = global::irmp_data.command;
    global::vcommand = (global::irmp_data.command * 3.3) / 100;
    global::oled->print(global::vcommand, 1);
    global::oled->display();
    analogWrite(PA1, global::vcommand);
  }

  global::oled->clearDisplay();

  delay(1000);  // Pequeña pausa para evitar lecturas rápidas y rebotes de botón
}
