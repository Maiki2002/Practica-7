//Librerias necesarias para el manejo de la pantalla OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Configuración de la pantalla
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

void actualizarPantalla();

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED
  display.setTextColor(SSD1306_WHITE); // Configura el color del texto en blanco
  display.setTextSize(1); // Configura un tamaño de texto pequeño
  display.clearDisplay(); // Limpia la pantalla
}

void loop(){
  actualizarPantalla();
}

void actualizarPantalla() {
  display.clearDisplay(); // Borra el contenido anterior en la pantalla

  display.print("Esto es un test");

  // Escribe el estado de los botones en la pantalla
  display.setCursor(10, 10);

  // Muestra el contenido en la pantalla OLED
  display.display();
} 