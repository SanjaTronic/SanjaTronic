/*
 * PROGRAMA SEMAFORO
 * ELABORADO POR
 * DATA
 * 
 */
 
 void setup() {
  // put your setup code here, to run once:

  pinMode(8, OUTPUT); // LED VERDE
  pinMode(9, OUTPUT); //LED AMARELO
  pinMode(10, OUTPUT); //LED VERMELHO
  pinMode(11, OUTPUT); // LED VERMELHO
  pinMode(12, OUTPUT); // LED AMARELO
  pinMode(13, OUTPUT); //LED VERDE
} 

void loop() {
  // put your main code here, to run repeatedly:   
  
   digitalWrite(8,HIGH);// ACENDE O LED VERDE 1
   digitalWrite(11,HIGH);// ACENDE O LED VERMELHO 2
   delay(5000); 
   digitalWrite(8,LOW); // APAGA O LED 1
   digitalWrite(9,HIGH); // ACENDE O LED AMARELO 1
   delay(2000);
   digitalWrite(9,LOW); //APAGA LED AMARELO 1 
   digitalWrite(10,HIGH); // ACENDE O LED VERMELHO 1
   digitalWrite(11,LOW); //APAGA O LED VERMELHO 2
   digitalWrite(13,HIGH); //ACENDE LED VERDE 2
   delay(5000);
   digitalWrite(13,LOW);//APAGA LED VERDE 2
   digitalWrite(12,HIGH);// ACENDE O LED AMARELO 2
   delay(1000);
  digitalWrite(12,LOW); // APAGA LED AMARELO 2
  digitalWrite(11,HIGH);// ACENDE O LED VERMELHO 2
  digitalWrite(10,LOW); // APAGA O LED VERMELHO 1
}
