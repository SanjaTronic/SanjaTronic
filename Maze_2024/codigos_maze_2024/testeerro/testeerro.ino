
#define pinMotor1 3  //Atras Direita
#define pinMotor2 5  //Frente Direita
#define pinMotor3 6  //Frente Esquerda
#define pinMotor4 9  //Atras Esquerda
#define pinspeed_R 10
#define pinspeed_L 11
#define DigitalSE 7
#define DigitalSD 4

void setup() {
  // put your setup code here, to run once:
  int erro = 0;
  int M1_Speed = 55;  // speed of motor 1
  //int M2_Speed = 60; // speed of motor 2
  //int Turn_Speed = 100;
  int LeftSpeed = 100;   // Left Rotation Speed 340
  int RightSpeed = 100;  // Right Rotation Speed

  int valorLinhaEsq;  // = 0;
  int valorLinhaDir;  // = 0;


  if (erro == 0) {
    Front();
    delay(500);
    erro = erro + 1;
  }
  while (erro == 1) {
    Back();
    delay(500);
    erro = erro - 1;
  }
 
     void Front() {
    digitalWrite(pinMotor1, LOW);
    digitalWrite(pinMotor2, HIGH);
    digitalWrite(pinMotor3, HIGH);
    digitalWrite(pinMotor4, LOW);
    analogWrite(pinspeed_R, LeftSpeed);
    analogWrite(pinspeed_L, RightSpeed);
  }

  void Back() {
    digitalWrite(pinMotor1, HIGH);
    digitalWrite(pinMotor2, LOW);
    digitalWrite(pinMotor3, LOW);
    digitalWrite(pinMotor4, HIGH);
    analogWrite(pinspeed_R, M1_Speed);
    analogWrite(pinspeed_L, M1_Speed);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
}
