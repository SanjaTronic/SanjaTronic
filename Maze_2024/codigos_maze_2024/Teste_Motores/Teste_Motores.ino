#define pinMotor1 3  //Atras Direita Laranja
#define pinMotor2 5  //Frente Direita \branco
#define pinMotor3 6  //Frente Esquerda Verde
#define pinMotor4 9  //Atras Esquerda Cinza
#define pinspeed_R 10 // INA Verde
#define pinspeed_L 11 // INB \cinza

int valorLinhaEsq;
int valorLinhaDir;
int valorLinhaCEsq;
int valorLinhaCDir;

int LeftSpeed = 35;  // Left Rotation Speed 340
int RightSpeed = 35; // Right Rotation Speed
int velCurvaEsq = 200; // velocidade para a curva dos motores do lado esquerdo do robô
int velCurvaDir = 200; // velocidade para a curva dos motores do lado direito do robô

void setup() {
  // put your setup code here, to run once:
 pinMode(pinMotor1, OUTPUT);
 pinMode(pinMotor2, OUTPUT);
 pinMode(pinMotor3, OUTPUT);
 pinMode(pinMotor4, OUTPUT);

 Virar90gE(1500);
 Parar();
}

void loop() {
  // put your main code here, to run repeatedly:

  
}

void paraTras(){
  digitalWrite(pinMotor1,LOW);
  digitalWrite(pinMotor2,HIGH);
  digitalWrite(pinMotor3,HIGH);
  digitalWrite(pinMotor4,LOW);

  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
}
void paraFrente(){
  digitalWrite(pinMotor1,HIGH);
  digitalWrite(pinMotor2,LOW);
  digitalWrite(pinMotor3,LOW);
  digitalWrite(pinMotor4,HIGH);

  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
}
void Virar90gD(int duration){
  digitalWrite(pinMotor3,HIGH);
  analogWrite(pinMotor2,LOW);
  digitalWrite(pinMotor4,HIGH);
  analogWrite(pinMotor1,LOW);

  digitalWrite(pinspeed_R, LeftSpeed);
  digitalWrite(pinspeed_L, RightSpeed);

  delay(duration);
}
void Virar90gE(int duration2){
  digitalWrite(pinMotor3,LOW);
  digitalWrite(pinMotor2,HIGH);
  analogWrite(pinMotor4,LOW); 
  digitalWrite(pinMotor1,HIGH);

  analogWrite(pinspeed_R, RightSpeed);
  analogWrite(pinspeed_L, LeftSpeed);

  delay(duration2); 
}
void Parar(){
  digitalWrite(pinMotor1,LOW);
  digitalWrite(pinMotor2,LOW);
  digitalWrite(pinMotor3,LOW);
  digitalWrite(pinMotor4,LOW);

  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
}
