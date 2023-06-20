//Configuración de la pantalla
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define IR_OUTPUT_IS_ACTIVE_LOW
#define IRSND_IR_FREQUENCY          38000

#define IRSND_SUPPORT_NEC_PROTOCOL  1
#define IRSND_PROTOCOL_NAMES        1
#define IRSND_OUTPUT_PIN            PA7            //Pin por donde mandare la señal de salida

//Librerias necesarias para el manejo de la pantalla OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Librerias necesarias para el envio por infrarojo
#include <irsndSelectMain15Protocols.h>
#include <irsnd.hpp>

//Declaracion de funciones auxiliares
void mandarValor();
void conmutar();

const int buttonPin1 = PA5;  // Pin del primer botón
const int buttonPin2 = PA6;  // Pin del segundo botón
const int Pin3 = PA1;        // Pin del led

int valorPotenciometro;
int voltajeEnviar;           // Voltaje en porcentaje
int mode = 0;

int porcentaje;
float voltaje;

bool buttonState1 = false;
bool buttonState2 = false;

bool newButtonState1;
bool newButtonState2;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

IRMP_DATA irsnd_data;

void setup(){

  //ENVIO DEL VALOR
  irsnd_data.protocol = IRSND_SUPPORT_NEC_PROTOCOL;    // Protocolo utilizado
  irsnd_data.address = 0x02;                         // Dirección de la placa emisora
  irsnd_data.flags = 0;

  irsnd_init();

  pinMode(buttonPin1, INPUT_PULLUP);    // Configura el primer botón como entrada con resistencia pull-up interna
  pinMode(buttonPin2, INPUT_PULLUP);    // Configura el segundo botón como entrada con resistencia pull-up interna

  pinMode(Pin3, OUTPUT);                // Configura el Pin3 como salida

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED
  display.setTextColor(SSD1306_WHITE); // Configura el color del texto en blanco
  display.setTextSize(1); // Configura un tamaño de texto pequeño
  display.clearDisplay(); // Limpia la pantalla

  digitalWrite(Pin3, LOW);    //El led inicia apagado
}

void loop(){

  //AQUI SE LEE EL VALOR DEL POTENCIOMETRO
  valorPotenciometro = analogRead(PA0);
  voltaje = valorPotenciometro * (3.3 / 1023); //Se transforma el valor del potenciometro a voltaje
  porcentaje = map(valorPotenciometro, 0, 1028, 0, 100); //Porcentaje del potenciometro
  

  display.clearDisplay();
  display.setCursor(10, 10);
  display.print("\n");
  display.print("Voltaje: ");
  display.print(voltaje);
  display.print(" v");
  display.print("\n");
  display.print("\n");
  display.print("Porcentaje: ");
  display.printf("%d", porcentaje);
  display.print("%");

  if(mode == 0){
    display.print("\n");
    display.print("\n");
    display.print("MODO APAGADO ");
    display.print(mode);
  }else if(mode == 1){
    display.print("\n");
    display.print("\n");
    display.print("MODO ENCENDIDO ");
    display.print(mode);
  }else if(mode == 2){
    display.print("\n");
    display.print("\n");
    display.print("MODO ENCENDIDO Y REGULADO");
    display.print(mode);
  }

  display.display();

  // Lee el estado de los botones
  newButtonState1= digitalRead(buttonPin1);
  newButtonState2= digitalRead(buttonPin2);

  // Verifica si ha habido un cambio en el estado de los botones
  if (newButtonState1 != buttonState1){
    buttonState1 = newButtonState1;
    if(buttonState1){
      mandarValor();
    }
    
  }

  if(newButtonState2 != buttonState2){
    
    buttonState2 = newButtonState2; 

    if(buttonState2){  
      conmutar();
    }
  
  }

  if(mode == 0){
    analogWrite(Pin3, 0);
  
  }else if(mode == 1){
    analogWrite(Pin3, 1);
  
  }else if(mode == 2){
    //int brillo = map(voltaje, 0, 3.3, 0, 255);
    analogWrite(Pin3, voltaje);
  }


}

void mandarValor(){

  if(newButtonState1){
    
    irsnd_data.command = mode;
    irsnd_send_data(&irsnd_data, true);                 // Envio la data
  
    delay(100);                                       
    display.clearDisplay();                           // Limpia la pantalla
    display.setCursor(0, 0);                          // Establece la posición del cursor
    display.println("Se enviara la siguiente informacion:");         // Imprime el texto inicial en la pantalla
    display.print("Modo: ");
    display.print(mode);
    display.print("\n");
    display.print("Voltaje: ");
    display.print(voltaje);
    display.print("v");
    display.display();
    
    irmp_irsnd_LEDFeedback(true);                     // Si el envio se envia correctamente, se prende el led de la blue pill
  
    delay(2000); // Pequeña pausa para evitar lecturas rápidas y rebotes de botón
  
  }

}

void conmutar(){
  
  if(mode == 0){
    /* display.clearDisplay();                           // Limpia la pantalla
    display.setCursor(0, 0);                          // Establece la posición del cursor
    display.println("LED APAGADO");                   // Imprime el texto inicial en la pantalla
    display.println(mode);                            // Imprime el texto inicial en la pantalla
    display.display(); */
    mode++;
  }else if(mode == 1){
    
    /* display.clearDisplay();                           // Limpia la pantalla
    display.setCursor(0, 0);                          // Establece la posición del cursor
    display.println("LED ENCENDIDO");                   // Imprime el texto inicial en la pantalla
    display.println(mode);                            // Imprime el texto inicial en la pantalla
    display.display(); */
    mode++;
  
  }else if(mode == 2){
    
    /* display.clearDisplay();                           // Limpia la pantalla
    display.setCursor(0, 0);                          // Establece la posición del cursor
    display.println("LED ENCENDIDO Y REGULADO");                   // Imprime el texto inicial en la pantalla
    display.println(mode);                            // Imprime el texto inicial en la pantalla
    display.display(); */

    mode = 0;
    
    //int brillo = map(voltaje, 0, 3.3, 0, 255); // Convierte el valor de voltaje a un entero entre 0 y 255
    //analogWrite(Pin3, brillo); //Este valor solo se actualiza si el led esta prendido y no en "tiempo real"
    //Hay que encontrar la forma de que lo haga en tiempo real.
  }

  delay(1000);
}
