#include <Adafruit_NeoPixel.h>

#define PIN 3
#define NUMLED 8

Adafruit_NeoPixel pixels(NUMLED, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYBLINK 500  // tempo do LED aceso e apagado

void setup() 
{
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() 
{
  // Pisca os LEDs 5 vezes
  for (int j = 0; j < 5; j++) 
  {
    // Acende todos os LEDs em branco
    for (int i = 0; i < NUMLED; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // branco
    }
    pixels.show();
    delay(DELAYBLINK);

    // Apaga todos os LEDs
    pixels.clear();
    pixels.show();
    delay(DELAYBLINK);
  }

  // Garante que os LEDs fiquem desligados após os 5 piscos
  pixels.clear();
  pixels.show();

}
