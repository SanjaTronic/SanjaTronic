#include "Giroscopio.h"
#include "mpu6050.h"

Giroscopio::Giroscopio(MultiplexI2C* multiplex, uint8_t c)
{
  mux = multiplex;
  canal = c;
}

void Giroscopio::begin()
{
  mux->selecionarCanal(canal);

  mpu_begin();
  mpu_calibrate(200);
  mpu_reset();
}

void Giroscopio::update()
{
  mux->selecionarCanal(canal);
  mpu_loop();
}

float Giroscopio::getAngulo()
{
  return getAngleZ();
}

void Giroscopio::reset()
{
  mux->selecionarCanal(canal);
  mpu_reset();
}
