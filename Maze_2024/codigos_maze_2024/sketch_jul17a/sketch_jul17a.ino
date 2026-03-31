#include <SharpIR.h>

#define IR_PIN A2
#define MODEL 1080  

SharpIR mySensor(IR_PIN, MODEL);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  int distance = mySensor.getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}
