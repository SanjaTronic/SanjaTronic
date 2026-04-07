#include <Wire.h>
#include "Adafruit_VL53L0X.h"

#define TCA_ADDR 0x70

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

void setup() {
  Serial.begin(9600);
  Wire.begin();

  iniciaLaser(2); // Inicia o sensor laser no canal 0 do multiplexador
  iniciaLaser(3);

  /*for(int i = 0; i < 6; i++)
  {
    iniciaLaser(i);
  }*/
}

void loop() {
  //VL53L0X_RangingMeasurementData_t measure;

  /*leituraLaser(0);
  leituraLaser(1);*/
  leituraLaser(2);
  leituraLaser(3);
  /*leituraLaser(4);
  leituraLaser(5);*/

  delay(1000);
}

// Funcoes auxiliares
void iniciaLaser(int numSensor)
{
  tcaSelect(numSensor);
  
  Serial.print("Lendo ");
  Serial.println(numSensor);

  if(!sensores[numSensor]->begin())
  {
    Serial.print("Erro no sensor ");
    Serial.println(numSensor);
    while (1);
  }
}
float leituraLaser(int numSensor)
{
  VL53L0X_RangingMeasurementData_t measure;

  tcaSelect(numSensor);
  sensores[numSensor]->rangingTest(&measure, false);
  Serial.print("Laser ");
  Serial.print(numSensor);
  Serial.print(": ");
  Serial.print(measure.RangeMilliMeter / 10);
  Serial.println(" cm ");

  return measure.RangeMilliMeter / 10;
}

void tcaSelect(uint8_t i) {
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}