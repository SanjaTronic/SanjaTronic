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

  Wire.beginTransmission(endereco);
  Wire.write(canal);  
  Wire.endTransmission();
}
