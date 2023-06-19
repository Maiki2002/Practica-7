//Librerias necesarias para el manejo de la pantalla OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Configuración de la pantalla
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

void actualizarPantalla();


const int buttonPin1 = PA5;  // Pin del primer botón
const int buttonPin2 = PA6;  // Pin del segundo botón

bool buttonState1 = false;
bool buttonState2 = false;

bool newButtonState1;
bool newButtonState2;


Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void setup(){

  pinMode(buttonPin1, INPUT_PULLUP);    // Configura el primer botón como entrada con resistencia pull-up interna
  pinMode(buttonPin2, INPUT_PULLUP);    // Configura el segundo botón como entrada con resistencia pull-up interna

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED
  display.setTextColor(SSD1306_WHITE); // Configura el color del texto en blanco
  display.setTextSize(1); // Configura un tamaño de texto pequeño
  display.clearDisplay(); // Limpia la pantalla
}

void loop(){

  display.clearDisplay();
  display.print("23I");

    // Escribe el estado de los botones en la pantalla
    display.setCursor(10, 10);

    // Muestra el contenido en la pantalla OLED
    display.display();

  // Lee el estado de los botones
  newButtonState1= digitalRead(buttonPin1);
  newButtonState2= digitalRead(buttonPin2);

  // Verifica si ha habido un cambio en el estado de los botones
  if (newButtonState1 != buttonState1){
    buttonState1 = newButtonState1;
    actualizarPantalla();
  }else if(newButtonState2 != buttonState2){
    buttonState2 = newButtonState2;
    actualizarPantalla();
  }

  actualizarPantalla();
}

void actualizarPantalla() {

  if(newButtonState1){
    display.clearDisplay(); // Borra el contenido anterior en la pantalla

    display.print("Boton 1 presionado");

    // Escribe el estado de los botones en la pantalla
    display.setCursor(10, 10);

    // Muestra el contenido en la pantalla OLED
    display.display();
    delay(100);
  }else if(newButtonState2){
    display.clearDisplay(); // Borra el contenido anterior en la pantalla

    display.print("Boton 2 presionado");

    // Escribe el estado de los botones en la pantalla
    display.setCursor(10, 10);

    // Muestra el contenido en la pantalla OLED
    display.display();

    delay(100);
  }

  
} 