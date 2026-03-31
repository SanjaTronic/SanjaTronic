#include <MPU9250.h>
#include <NewPing.h>

// Define os pinos conectados aos motores
#define pinMotor1 3  // Motor traseiro direito (Laranja)
#define pinMotor2 5  // Motor dianteiro direito (Branco)
#define pinMotor3 6  // Motor dianteiro esquerdo (Verde)
#define pinMotor4 9  // Motor traseiro esquerdo (Cinza)
#define pinspeed_R 10 // INA (Verde) - controla a velocidade do motor direito
#define pinspeed_L 11 // INB (Cinza) - controla a velocidade do motor esquerdo

// Define os pinos dos sensores ultrassônicos
#define TRIGGER_PIN1  7
#define ECHO_PIN1     6
#define TRIGGER_PIN2  5
#define ECHO_PIN2   4
#define TRIGGER_PIN3  22
#define ECHO_PIN3     24

#define MAX_DISTANCE 200 // Distância máxima que o sensor pode medir (em cm)
// Cria objetos NewPing para os sensores ultrassônicos
NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);

// declaração de variáveis constantes para representar as direções
const int NORTE = 1;
const int LESTE = 2;
const int SUL = 3;
const int OESTE = 4;

int direcaoAtual = NORTE; // variável que representa a direção atual do robô (muda de acordo com a posição do robô)

// Define as velocidades dos motores
int RightSpeed = 60;  // Velocidade para movimento para frente e curva à esquerda
int LeftSpeed = 66; // Velocidade para movimento para frente e curva à direita
int CurvaRightSpeed = 136;  // Velocidade do motor esquerdo para curva à esquerda
int CurvaLeftSpeed = 130; // Velocidade do motor direito para curva à direita

MPU9250 mpu;

void setup() {
  // Configura os pinos dos motores como saídas
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotor3, OUTPUT);
  pinMode(pinMotor4, OUTPUT);

  Wire.begin();
}
void loop() {
  paraFrente();
}
/*
void loop() {
  // Obtém a distância medida pelo sensor ultrassônico 1
  int distance1 = sonar1.ping_cm();
    
  if (distance1 > 5){
    paraFrente(); // Move para frente
    delay(150);
  } 
  else {
    // Se o obstáculo estiver muito perto, mede as distâncias com os sensores 2 e 3
    int distance2 = sonar2.ping_cm();
    int distance3 = sonar3.ping_cm();

    // Compara as distâncias dos sensores 2 e 3 para decidir a direção
    if (distance2 > distance3) {
      virarEsquerda(); 
      delay(900);          
      paraTras();    
      delay(1000);
    } else {
      virarDireita(); 
      delay(900);        
      paraTras(); 
      delay(1000);
    }
  }
}
*/
// Função para mover o robô para frente
void paraFrente(){
  digitalWrite(pinMotor1, HIGH);   // Liga o motor traseiro direito
  digitalWrite(pinMotor2, LOW);    // Desliga o motor dianteiro direito
  digitalWrite(pinMotor3, LOW);    // Desliga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, HIGH);   // Liga o motor traseiro esquerdo

  // Define a velocidade dos motores
  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
  
}

// Função para mover o robô para trás
void paraTras(){
  digitalWrite(pinMotor1, LOW);    // Desliga o motor traseiro direito
  digitalWrite(pinMotor2, HIGH);   // Liga o motor dianteiro direito
  digitalWrite(pinMotor3, HIGH);   // Liga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, LOW);    // Desliga o motor traseiro esquerdo

  // Define a velocidade dos motores
  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
  
}

// Função para virar o robô para a esquerda
void virarEsquerda(){
  digitalWrite(pinMotor1, HIGH);   // Liga o motor traseiro direito
  digitalWrite(pinMotor2, LOW);    // Desliga o motor dianteiro direito
  digitalWrite(pinMotor3, HIGH);   // Liga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, LOW);    // Desliga o motor traseiro esquerdo

  // Define a velocidade dos motores para curva à esquerda
  analogWrite(pinspeed_R, CurvaLeftSpeed);
  analogWrite(pinspeed_L, CurvaRightSpeed);
  delay(2000);
  
}

// Função para virar o robô para a direita
void virarDireita(){
  digitalWrite(pinMotor1, LOW);    // Desliga o motor traseiro direito
  digitalWrite(pinMotor2, HIGH);   // Liga o motor dianteiro direito
  digitalWrite(pinMotor3, LOW);    // Desliga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, HIGH);   // Liga o motor traseiro esquerdo

  // Define a velocidade dos motores para curva à direita
  analogWrite(pinspeed_R, CurvaLeftSpeed);
  analogWrite(pinspeed_L, CurvaRightSpeed);
  delay(2200);  
}

void Parar(){
  digitalWrite(pinMotor1,LOW); // Desliga o motor traseiro direito
  digitalWrite(pinMotor2,LOW); // Desliga o motor dianteiro direito  
  digitalWrite(pinMotor3,LOW); // Desliga o motor dianteiro esquerdo
  digitalWrite(pinMotor4,LOW); // Desliga o motor traseiro esquerdo
  
  // Define a velocidade dos motores para o desligamento
  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
  
}