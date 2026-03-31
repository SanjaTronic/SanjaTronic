const int pinIRd = 8;
const int pinIRa = A0;
int IRvalueA = 0;
int IRvalueD = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(pinIRd, INPUT);
  pinMode(pinIRa, INPUT); 
}

void loop() {
  //IRvalueA = analogRead(pinIRa);
  IRvalueD = digitalRead(pinIRd);
  //Serial.print("Analog Reading=");
 // Serial.print(IRvalueA);
  //delay(2000);
  Serial.print("\t Digital Reading=");
  Serial.print(IRvalueD);
}
