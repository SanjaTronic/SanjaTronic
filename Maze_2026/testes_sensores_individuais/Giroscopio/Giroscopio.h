#ifndef GIROSCOPIO_H
#define GIROSCOPIO_H

#include "MultiplexI2C.h"
#include <Arduino.h>

class Giroscopio
{
  private:
    MultiplexI2C* mux;
    uint8_t canal;

  public:
    Giroscopio(MultiplexI2C* multiplex, uint8_t canal);

    void begin();
    void update();
    float getAngulo();
    void reset();
};

#endif
