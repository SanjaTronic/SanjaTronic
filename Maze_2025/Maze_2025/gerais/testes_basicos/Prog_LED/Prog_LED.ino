#include <Adafruit_NeoPixel.h>

#define PIN 7
#define NUMLED 18

Adafruit_NeoPixel pixels(NUMLED, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYLOOP 100

void setup() {
  pixels.begin();
}

void loop() {
  pixels.clear();

  // Acende LEDs um por um com cores intercaladas
  /*for (int i = 0; i < NUMLED; i++) {
    if (i % 2 == 0) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));     // Verde
    } else if (i % 2 == 1) {
      pixels.setPixelColor(i, pixels.Color(150, 150, 150));     // Vermelho
    } 

    pixels.show();
    delay(DELAYLOOP);
  }*/
  pixels.setPixelColor(10, pixels.Color(150, 150, 150));     // Vermelho
  
  // Mantém todos os LEDs acesos por um tempo
  delay(500);

  // Apaga todos os LEDs juntos
  pixels.clear();
  pixels.show();
  delay(500); // Pausa antes de reiniciar
}

