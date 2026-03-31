#include <Wire.h>
#include <SFE_MMA8452Q.h>

MMA8452Q acelerometro(0x1C);

void setup() {
  Serial.begin(9600);
  Serial.println("Teste de comunicação MMA8452");
  acelerometro.init();
}

void loop() {
  if (acelerometro.available()) {
    acelerometro.read();
    printCalculatedAccels();
    Serial.println();
  }
}

void printCalculatedAccels() {
  delay(1000);
  Serial.print("X: ");
  Serial.print(acelerometro.cx, 3);
  Serial.print("\tY: ");
  Serial.print(acelerometro.cy, 3);
  Serial.print("\tZ: ");
  Serial.print(acelerometro.cz, 3);
  delay(1000);
}

