//Librerias necesarias para el manejo de la pantalla OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Librerias necesarias para el envio por infrarojo
#define USE_ONE_TIMER_FOR_IRMP_AND_IRSND
#include <IRMP.h>
#include <IRMPconfig.h>
#include <irsnd.hpp>

//Configuración de la pantalla
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define IR_OUTPUT_IS_ACTIVE_LOW
#define IRSND_IR_FREQUENCY          38000

#define IRSND_SUPPORT_NEC_PROTOCOL  1
#define IRSND_PROTOCOL_NAMES        1
#define IRSND_OUTPUT_PIN            PA7            //Pin por donde mandare la señal de salida

void actualizarPantalla();
void mandarValor();


const int buttonPin1 = PA5;  // Pin del primer botón
const int buttonPin2 = PA6;  // Pin del segundo botón
const int Pin3 = PA1;        // Pin del led

int valorPotenciometro;
int voltajeEnviar; //porcentaje

bool buttonState1 = false;
bool buttonState2 = false;

bool newButtonState1;
bool newButtonState2;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

IRMP_DATA irsnd_data;

void setup(){

  irsnd_init();

  pinMode(buttonPin1, INPUT_PULLUP);    // Configura el primer botón como entrada con resistencia pull-up interna
  pinMode(buttonPin2, INPUT_PULLUP);    // Configura el segundo botón como entrada con resistencia pull-up interna

  pinMode(Pin3, OUTPUT);                // Configura el Pin3 como salida

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED
  display.setTextColor(SSD1306_WHITE); // Configura el color del texto en blanco
  display.setTextSize(1); // Configura un tamaño de texto pequeño
  display.clearDisplay(); // Limpia la pantalla
}

void loop(){

  //AQUI SE LEE EL VALOR DEL POTENCIOMETRO
  valorPotenciometro = analogRead(PA0);
  voltajeEnviar = map(valorPotenciometro, 0, 1028, 0, 100);
  analogWrite(Pin3, voltajeEnviar);

  display.clearDisplay();
  display.setCursor(10, 10);
  display.print("Voltaje: ");
  display.print(valorPotenciometro);
  display.display();

  // Lee el estado de los botones
  newButtonState1= digitalRead(buttonPin1);
  newButtonState2= digitalRead(buttonPin2);

  // Verifica si ha habido un cambio en el estado de los botones
  if (newButtonState1 != buttonState1){
    buttonState1 = newButtonState1;
    mandarValor();
  }else if(newButtonState2 != buttonState2){
    buttonState2 = newButtonState2;
  
  }

}

void mandarValor(){

  if(newButtonState1){
    
    //ENVIO DEL VALOR
    irsnd_data.protocol = IRSND_SUPPORT_NEC_PROTOCOL; // Protocolo utilizado
    irsnd_data.address = 0x01;                        // Dirección de la placa emisora
    irsnd_data.command = voltajeEnviar;                  // Valor que se enviara
    irsnd_data.flags = 0;

    irsnd_send_data(&irsnd_data, true);               // Envio la data
  
    delay(100);                                       
    display.clearDisplay();                           // Limpia la pantalla
    display.setCursor(0, 0);                          // Establece la posición del cursor
    display.println("Se enviara el valor: ");         // Imprime el texto inicial en la pantalla
    display.print(voltajeEnviar);                        // Imprime el valor del potenciómetro
    display.print("%");
    display.display();
    
    irmp_irsnd_LEDFeedback(true);                     // Si el envio se envia correctamente, se prende el led de la blue pill
  
    delay(2000); // Pequeña pausa para evitar lecturas rápidas y rebotes de botón
  }else if(newButtonState2){

  }

}

/* void actualizarPantalla() {

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

  
}  */