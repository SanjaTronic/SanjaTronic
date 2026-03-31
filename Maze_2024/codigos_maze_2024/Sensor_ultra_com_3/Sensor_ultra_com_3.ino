#include <NewPing.h>

#define TRIGGER_PIN1  7
#define ECHO_PIN1     6
#define TRIGGER_PIN2  5
#define ECHO_PIN2   4
#define TRIGGER_PIN3  47 // azul
#define ECHO_PIN3     49 // roxo
#define MAX_DISTANCE 200

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);  

  // Sensor 1
  int distance1 = sonar1.ping_cm();
  Serial.print("Distance Sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  // Sensor 2
  int distance2 = sonar2.ping_cm();
  Serial.print("Distance Sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Sensor 3
  int distance3 = sonar3.ping_cm();
  Serial.print("Distance Sensor 3: ");
  Serial.print(distance3);
  Serial.println(" cm");

  delay(1000);  
}
