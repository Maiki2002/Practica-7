#include <Arduino.h>

// Definiciones de pines y configuraciones de la pantalla OLED
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define ANALOG_OUTPUT PA6

// Definiciones de pines y configuraciones para el receptor de infrarrojos (IR)
#define IRMP_INPUT_PIN PA6
#define IRMP_PROTOCOL_NAMES 1
#define IRMP_SUPPORT_NEC_PROTOCOL 1 

// Inclusión de las bibliotecas necesarias
#include <irmpSelectMain15Protocols.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <irmp.hpp>
#include <IRMPconfig.h>
#include <IRMP.h>

namespace global {
    Adafruit_SSD1306* oled;             // Objeto de la pantalla OLED
    int command;                        // Variable para almacenar el comando recibido
    IRMP_DATA irmp_data;                // Estructura para almacenar los datos del receptor IR
}

void setup() {
    Serial.begin(115200);               // Inicializa la comunicación serial

    pinMode(IRMP_INPUT_PIN, INPUT);     // Configura el pin de entrada del receptor IR
    irmp_init();                        // Inicializa el receptor de infrarrojos IR

    global::oled = new Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);  // Inicializa la pantalla OLED

    global::oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);   // Configura la pantalla OLED
    global::oled->setTextColor(SSD1306_WHITE);         // Configura el color del texto en blanco
    global::oled->setTextSize(1);                      // Configura un tamaño de texto pequeño
    global::oled->clearDisplay();                       // Limpia la pantalla OLED
}

void loop() {
    if (irmp_get_data(&(global::irmp_data))) {
        // Si se recibe un comando IR, se muestra la información en la pantalla OLED
        global::oled->clearDisplay();
        global::oled->setTextSize(2);
        global::oled->setCursor(0, 0);
        global::oled->print("INFO ");
        global::oled->print(global::irmp_data.command);
        global::oled->display();

        delay(2000);
    } else {
        // Si no se recibe un comando IR, se muestra un mensaje de espera en la pantalla OLED
        global::oled->clearDisplay();
        global::oled->setTextSize(2);
        global::oled->setCursor(0, 0);
        global::oled->print("Esperando info");
        global::oled->display();
    }

    delay(1000); // Pequeña pausa para evitar lecturas rápidas y rebotes de botón
}
