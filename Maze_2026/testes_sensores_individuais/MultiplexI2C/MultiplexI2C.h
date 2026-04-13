#ifndef MULTIPLEXI2C_H
#define MULTIPLEXI2C_H

#include <Wire.h>

class MultiplexI2C
{
  private:
    uint8_t endereco;

  public:
    MultiplexI2C(uint8_t addr);
    void begin();
    void selecionarCanal(uint8_t canal);
};

#endif
