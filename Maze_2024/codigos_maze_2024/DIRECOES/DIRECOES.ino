void setup() {
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
}

void loop() {
  left();
}

void left(){
  digitalWrite(3, HIGH);
  delay(800);                    
  digitalWrite(4, HIGH);
  delay(800);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}