//Configuración de la pantalla
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define IR_OUTPUT_IS_ACTIVE_LOW
#define IRSND_IR_FREQUENCY          38000

#define IRSND_SUPPORT_NEC_PROTOCOL  1
#define IRSND_PROTOCOL_NAMES        1
#define IRSND_OUTPUT_PIN            PA7            

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
int sending();

namespace global{
  
  const int buttonPin1 = PA5;  // Pin del primer botón
  const int buttonPin2 = PA6;  // Pin del segundo botón
  const int Pin3 = PA1;        // Pin del led

  int valorPotenciometro;
  int voltajeEnviar;           // Voltaje en porcentaje
  int mode = 0;

  int sendValue;

  int porcentaje;
  float voltaje;

  bool buttonState1 = false;
  bool buttonState2 = false;

  bool newButtonState1;
  bool newButtonState2;

  Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

  IRMP_DATA irsnd_data;

}


void setup(){

  //IRSND
  global::irsnd_data.protocol = IRSND_SUPPORT_NEC_PROTOCOL;    // Protocolo utilizado
  global::irsnd_data.address = 0x02;                         // Dirección de la placa emisora
  global::irsnd_data.flags = 0;

  irsnd_init();

  pinMode(global::buttonPin1, INPUT_PULLUP);              // Configura el primer botón como entrada con resistencia pull-up interna
  pinMode(global::buttonPin2, INPUT_PULLUP);              // Configura el segundo botón como entrada con resistencia pull-up interna

  pinMode(global::Pin3, OUTPUT);                          // Configura el Pin3 como salida

  global::display.begin(SSD1306_SWITCHCAPVCC, 0x3C);      // Inicializa la pantalla OLED
  global::display.setTextColor(SSD1306_WHITE);            // Configura el color del texto en blanco
  global::display.setTextSize(1);                         // Configura un tamaño de texto pequeño
  global::display.clearDisplay();                         // Limpia la pantalla

  digitalWrite(global::Pin3, LOW);                        //El led inicia apagado
}

void loop(){

  //AQUI SE LEE EL VALOR DEL POTENCIOMETRO
  global::valorPotenciometro = analogRead(PA0);
  global::voltaje = global::valorPotenciometro * (3.3 / 1023);            //Se transforma el valor del potenciometro a voltaje
  global::porcentaje = map(global::valorPotenciometro, 0, 1028, 0, 100);  //Porcentaje del potenciometro
  
  global::display.clearDisplay();
  global::display.setCursor(10, 10);
  global::display.print("\n");
  global::display.print("Voltaje: ");
  global::display.print(global::voltaje);
  global::display.print(" v");
  global::display.print("\n");
  global::display.print("\n");
  global::display.print("Porcentaje: ");
  global::display.printf("%d", global::porcentaje);
  global::display.print("%");

  if(global::mode == 0){
    global::display.print("\n");
    global::display.print("\n");
    global::display.print("MODO APAGADO ");
  }else if(global::mode == 1){
    global::display.print("\n");
    global::display.print("\n");
    global::display.print("MODO ENCENDIDO ");
  }else if(global::mode == 2){
    global::display.print("\n");
    global::display.print("\n");
    global::display.print("MODO ENCENDIDO Y REGULADO");
  }

  global::display.display();

  // Lee el estado de los botones
  global::newButtonState1= digitalRead(global::buttonPin1);
  global::newButtonState2= digitalRead(global::buttonPin2);

  // Verifica si ha habido un cambio en el estado de los botones
  if (global::newButtonState1 != global::buttonState1){
    global::buttonState1 = global::newButtonState1;
    if(global::buttonState1){
      mandarValor();
    }
  }

  if(global::newButtonState2 != global::buttonState2){
    global::buttonState2 = global::newButtonState2;
    if(global::buttonState2){  
      conmutar();
    }
  }

  //Modo de trabajo
  if(global::mode == 0){
    analogWrite(global::Pin3, 0);
  }else if(global::mode == 1){
    analogWrite(global::Pin3, 1);
  }else if(global::mode == 2){
    analogWrite(global::Pin3, global::voltaje);
  }

}

//Funcion que envia por infrarojo
void mandarValor(){

  if(global::newButtonState1){
    
    global::sendValue = sending();

    global::irsnd_data.command = global::sendValue;

    irsnd_send_data(&global::irsnd_data, true);                         // Envio la data
  
    delay(100);                                       
    global::display.clearDisplay();                                     // Limpia la pantalla
    global::display.setCursor(0, 0);                                    // Establece la posición del cursor
    global::display.println("Se enviara la siguiente informacion:");    // Imprime el texto inicial en la pantalla
    global::display.print("Modo: ");
    global::display.print(global::mode);
    global::display.print("\n");
    global::display.print("Voltaje: ");
    global::display.print(global::voltaje);
    global::display.print("v");
    global::display.display();
    
    irmp_irsnd_LEDFeedback(true);                     // Si el envio se envia correctamente, se prende el led del transmisor infrarojo
  
    delay(2000); // Pequeña pausa para evitar lecturas rápidas y rebotes de botón
  
  }

}

//Funcion que cambia el modo de trabajo (apagado, encendido o controlado)
void conmutar(){
  
  if(global::mode == 0){
    global::mode++;
  }else if(global::mode == 1){
    global::mode++;
  }else if(global::mode == 2){
    global::mode = 0;
  }

  delay(1000);
}

//Funcion que retorna el modo de trabajo
int sending(){

  if(global::mode == 0){
    return 0;
  }else if(global::mode == 1){
    return 1;
  }else if (global::mode == 2){
    return global::porcentaje;
  }

}
