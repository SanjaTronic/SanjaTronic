int IN1 = 3;
int IN2 = 4;
int IN3 = 5;
int IN4  = 6;

//#define velocidade 100

void setup() {
  // define os pinos como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //define a velocidade dos motores
  #define pinspeed_R 3
  #define pinspeed_L 5
  #define DigitalSE 3
  #define DigitalSD 5

}

void loop() {
  andar_para_frente();
}
void andar_para_frente(){
  analogWrite(IN1, 100);
  analogWrite(IN2, 0);
  analogWrite(IN3, 122);
  analogWrite(IN4, 0);
  
}
