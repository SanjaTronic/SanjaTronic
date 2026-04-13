#include "MultiplexI2C.h"

MultiplexI2C::MultiplexI2C(uint8_t addr)
{
  endereco = addr;
}

void MultiplexI2C::begin()
{
  Wire.begin();
}

void MultiplexI2C::selecionarCanal(uint8_t canal) 
{
  // Proteção: só aceita valores válidos do TCA9548A
  /*if (canal != 0x01 && canal != 0x02 && canal != 0x04 &&
      canal != 0x08 && canal != 0x10 && canal != 0x20 &&
      canal != 0x40 && canal != 0x80) 
  {
    return;
  }*/

  Wire.beginTransmission(endereco);
  Wire.write(canal);  
  Wire.endTransmission();
}
