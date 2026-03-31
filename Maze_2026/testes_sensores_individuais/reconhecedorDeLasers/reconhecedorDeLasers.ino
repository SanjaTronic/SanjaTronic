#include <Wire.h>
#include "Adafruit_VL53L0X.h"

#define TCA_ADDR 0x70

Adafruit_VL53L0X sensor0 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor1 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor2 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor3 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor4 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor5 = Adafruit_VL53L0X();


void tcaSelect(uint8_t i) {
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Sensor canal 0
  Serial.print("Lendo S0\t");
  tcaSelect(0);
  if (!sensor0.begin()) {
    Serial.println("Erro sensor 0");
    while (1);
  }

  // Sensor canal 1
  Serial.print("Lendo S1\t");
  tcaSelect(1);
  if (!sensor1.begin()) {
    Serial.println("Erro sensor 1");
    while (1);
  }

  Serial.println("Lendo S2\t");
  tcaSelect(2);
  if (!sensor2.begin()) {
    Serial.println("Erro sensor 2");
    while (1);
  }

  Serial.println("Lendo S3\t");
  tcaSelect(3);
  if (!sensor3.begin()) {
    Serial.println("Erro sensor 3");
    while (1);
  }

  Serial.println("Lendo S4\t");
  tcaSelect(4);
  if (!sensor4.begin()) {
    Serial.println("Erro sensor 4");
    while (1);
  }

  Serial.println("Lendo S5\t");
  tcaSelect(5);
  if (!sensor5.begin()) {
    Serial.println("Erro sensor 5");
    while (1);
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  // Sensor 0
  tcaSelect(0);
  sensor0.rangingTest(&measure, false);
  Serial.print("S0: ");
  Serial.print(measure.RangeMilliMeter / 10);
  Serial.print(" cm\t ");

  // Sensor 1
  tcaSelect(1);
  sensor1.rangingTest(&measure, false);
  Serial.print("S1: ");
  Serial.print(measure.RangeMilliMeter / 10);
  Serial.print(" cm\t ");

  // Sensor 2
  tcaSelect(2);
  sensor2.rangingTest(&measure, false);
  Serial.print("S2: ");
  Serial.print(measure.RangeMilliMeter / 10);
  Serial.print(" cm\t ");

  //Sensor 3
  tcaSelect(3);
  sensor3.rangingTest(&measure, false);
  Serial.print("S3: ");
  Serial.print(measure.RangeMilliMeter / 10);
  Serial.print(" cm\t ");

  //Sensor 4
  tcaSelect(4);
  sensor4.rangingTest(&measure, false);
  Serial.print("S4: ");
  Serial.print(measure.RangeMilliMeter / 10);
  Serial.print(" cm\t ");

  //Sensor 5
  tcaSelect(5);
  sensor5.rangingTest(&measure, false);
  Serial.print("S5: ");
  Serial.print(measure.RangeMilliMeter / 10);
  Serial.println(" cm\t ");
  delay(1000);
}