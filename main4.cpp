#include <Arduino.h>
#include <IRremote.h>

#define IR_LED_PIN PA1
#define POTENTIOMETER_PIN PA0
#define LED_PIN PA5

IRsend irsend(IR_LED_PIN);

void setup() {
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int potValue = analogRead(POTENTIOMETER_PIN);
  int percentage = map(potValue, 0, 4095, 0, 100);
  irsend.sendNEC(percentage, 32); // Envía el valor como comando NEC
  
  digitalWrite(LED_PIN, HIGH); // Enciende el LED
  delay(100); // Mantiene el LED encendido durante 100 ms
  
  digitalWrite(LED_PIN, LOW); // Apaga el LED
  delay(900); // Espera 900 ms antes de enviar el siguiente comando IR
}
