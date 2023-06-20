#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

void actualizarPantalla();

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

const int buttonPin1 = PA5;  // Pin del primer botón
const int buttonPin2 = PA6;  // Pin del segundo botón

bool buttonState1 = false;
bool buttonState2 = false;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);  // Configura el primer botón como entrada con resistencia pull-up interna
  pinMode(buttonPin2, INPUT_PULLUP);  // Configura el segundo botón como entrada con resistencia pull-up interna

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED
  display.setTextColor(SSD1306_WHITE); // Configura el color del texto en blanco
  display.setTextSize(1); // Configura un tamaño de texto pequeño
  display.clearDisplay(); // Limpia la pantalla
}

void loop() {
  // Lee el estado de los botones
  bool newButtonState1 = digitalRead(buttonPin1);
  bool newButtonState2 = digitalRead(buttonPin2);

  // Verifica si ha habido un cambio en el estado de los botones
  if (newButtonState1 != buttonState1 || newButtonState2 != buttonState2) {
    buttonState1 = newButtonState1;
    buttonState2 = newButtonState2;

    // Llama a la función para actualizar la pantalla
    actualizarPantalla();
  }

  delay(100); // Pequeña pausa para evitar lecturas rápidas y rebotes de botón
}

void actualizarPantalla() {
  display.clearDisplay(); // Borra el contenido anterior en la pantalla

  // Escribe el estado de los botones en la pantalla
  display.setCursor(10, 10);
  display.print("Boton 1: ");
  display.println(buttonState1 ? "Presionado" : "No presionado");
  display.setCursor(10, 30);
  display.print("Boton 2: ");
  display.println(buttonState2 ? "Presionado" : "No presionado");

  // Muestra el contenido en la pantalla OLED
  display.display();
}
