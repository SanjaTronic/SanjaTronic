#ifndef LASERS_H
#define LASERS_H

#include <Arduino.h>

class Lasers
{
  private:
    Adafruit_VL53L0X sensor0 = Adafruit_VL53L0X();
    Adafruit_VL53L0X sensor1 = Adafruit_VL53L0X();
    Adafruit_VL53L0X sensor2 = Adafruit_VL53L0X();
    Adafruit_VL53L0X sensor3 = Adafruit_VL53L0X();
    Adafruit_VL53L0X sensor4 = Adafruit_VL53L0X();
    Adafruit_VL53L0X sensor5 = Adafruit_VL53L0X();

    // Array das instancias dos sensores lasers
    Adafruit_VL53L0X* sensores[6] = {
      &sensor0, &sensor1, &sensor2,
      &sensor3, &sensor4, &sensor5
    };
}