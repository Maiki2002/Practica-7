#include <IRremote.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
IRrecv irReceiver(PA3);  // Pin de entrada del módulo receptor infrarrojo

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED
  display.setTextColor(SSD1306_WHITE); // Configura el color del texto en blanco
  display.setTextSize(1); // Configura un tamaño de texto pequeño
  display.clearDisplay(); // Limpia la pantalla

  irReceiver.enableIRIn(); // Habilita la recepción de señales infrarrojas
}

void loop() {
  decode_results results;
  
  if (irReceiver.decode(&results)) {
    display.clearDisplay(); // Borra el contenido anterior en la pantalla
    
    // Muestra el valor recibido del transmisor infrarrojo
    display.setCursor(10, 10);
    display.print("Valor IR: ");
    display.println(results.value, DEC);
    
    // Muestra otros detalles del paquete IR
    display.setCursor(10, 30);
    display.print("Bits: ");
    display.println(results.bits);
    display.setCursor(10, 50);
    display.print("Protocolo: ");
    display.println(results.decode_type);
    
    display.display(); // Muestra el contenido en la pantalla OLED
    
    irReceiver.resume(); // Continúa esperando por la siguiente señal infrarroja
  }
}
