void setup() {
  // put your setup code here, to run once:

 pinMode(10,OUTPUT);

 pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

 digitalWrite(10,HIGH);
 digitalWrite(2,HIGH);
 delay(250);
 digitalWrite(10,LOW);
 digitalWrite(2,LOW);
 delay(250);
}
