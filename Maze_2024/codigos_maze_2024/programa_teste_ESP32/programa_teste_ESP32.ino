// Incluindo a biblioteca necessária
#include <Arduino.h>

// Definindo o pino do LED
#define LED_PIN 13

void setup() {
  // Inicializando o pino do LED como saída
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Acendendo o LED
  digitalWrite(LED_PIN, HIGH);
  // Esperando 1 segundo
  delay(1000);
  // Apagando o LED
  digitalWrite(LED_PIN, LOW);
  // Esperando 1 segundo novamente
  delay(1000);
}

