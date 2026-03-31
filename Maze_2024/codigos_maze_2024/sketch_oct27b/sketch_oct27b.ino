int SensorE = 11;
int ValorSensor = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SensorE, INPUT);
 }

void loop() {
  // put your main code here, to run repeatedly:
  ValorSensor = digitalRead(SensorE);
  if (digitalRead(SensorE) == HIGH){
  Serial.println(ValorSensor);
  Serial.print("Preto");
  delay(250);
}
 else if (digitalRead(SensorE) == LOW){
  Serial.println(ValorSensor);
  Serial.print("Branco");
  delay(250);
   }
 }
