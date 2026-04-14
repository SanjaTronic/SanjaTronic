#include "MultiplexI2C.h"
#include "Giroscopio.h"

MultiplexI2C multiplex(0x70);
Giroscopio giro(&multiplex, 1);

void setup()
{
  Serial.begin(9600);

  multiplex.begin();
  delay(1000);

  giro.begin();
}

void loop()
{
  giro.update();

  float angulo = giro.getAngulo();

  Serial.println(angulo);

  if (angulo > 66 || angulo < -66)
  {
    Serial.println("Resetando...");
    delay(1000);
    giro.reset();
  }

  delay(100);
}
