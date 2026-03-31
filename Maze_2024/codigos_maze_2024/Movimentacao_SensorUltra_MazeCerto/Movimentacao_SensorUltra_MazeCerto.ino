#include <NewPing.h>

// Define os pinos conectados aos motores
#define pinMotor1 3  // Motor traseiro direito (Laranja)
#define pinMotor2 5  // Motor dianteiro direito (Branco)
#define pinMotor3 6  // Motor dianteiro esquerdo (Verde)
#define pinMotor4 9  // Motor traseiro esquerdo (Cinza)

// Define os pinos para controle da velocidade dos motores
#define pinspeed_R 10 // INA (Verde) - controla a velocidade do motor direito
#define pinspeed_L 11 // INB (Cinza) - controla a velocidade do motor esquerdo

// Define os pinos dos sensores ultrassônicos
#define TRIGGER_PIN1  13
#define ECHO_PIN1     2
#define TRIGGER_PIN2  22
#define ECHO_PIN2   24
#define TRIGGER_PIN3  26
#define ECHO_PIN3     28

#define MAX_DISTANCE 200 // Distância máxima que o sensor pode medir (em cm)

// Cria objetos NewPing para os sensores ultrassônicos
NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);

// Define as velocidades dos motores
int M1_Speed = 5; // Velocidade do motor 1
int LeftSpeed = 55;  // Velocidade para movimento para frente e curva à esquerda
int RightSpeed = 50; // Velocidade para movimento para frente e curva à direita
int CurvaLeftSpeed = 175;  // Velocidade do motor esquerdo para curva à esquerda
int CurvaRightSpeed = 170; // Velocidade do motor direito para curva à direita

void setup() {
  // Configura os pinos dos motores como saídas
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotor3, OUTPUT);
  pinMode(pinMotor4, OUTPUT);
}

void loop() {
  // Obtém a distância medida pelo sensor ultrassônico 1
  int distance1 = sonar1.ping_cm();

  // Se a distância for maior que 5 cm, o robô avança
  if (distance1 > 5){
    paraFrente(150); // Move para frente por 150 milissegundos
  } else {
    // Se o obstáculo estiver muito perto, mede as distâncias com os sensores 2 e 3
    int distance2 = sonar2.ping_cm();
    int distance3 = sonar3.ping_cm();

    // Compara as distâncias dos sensores 2 e 3 para decidir a direção
    if (distance2 > distance3) {
      virarEsquerda(900); // Vira à esquerda por 900 milissegundos
      delay(10);          // Aguarda 10 milissegundos
      paraTras(1000);    // Move para trás por 1000 milissegundos
    } else {
      virarDireita(900); // Vira à direita por 900 milissegundos
      delay(10);        // Aguarda 10 milissegundos
      paraTras(1000);  // Move para trás por 1000 milissegundos
    }
  }
}

// Função para mover o robô para frente
void paraFrente(int duration){
  digitalWrite(pinMotor1, HIGH);   // Liga o motor traseiro direito
  digitalWrite(pinMotor2, LOW);    // Desliga o motor dianteiro direito
  digitalWrite(pinMotor3, LOW);    // Desliga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, HIGH);   // Liga o motor traseiro esquerdo

  // Define a velocidade dos motores
  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
  delay(duration);  // Aguarda pelo tempo especificado
}

// Função para mover o robô para trás
void paraTras(int duration2){
  digitalWrite(pinMotor1, LOW);    // Desliga o motor traseiro direito
  digitalWrite(pinMotor2, HIGH);   // Liga o motor dianteiro direito
  digitalWrite(pinMotor3, HIGH);   // Liga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, LOW);    // Desliga o motor traseiro esquerdo

  // Define a velocidade dos motores
  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
  delay(duration2);  // Aguarda pelo tempo especificado
}

// Função para virar o robô para a esquerda
void virarEsquerda(int duration3){
  digitalWrite(pinMotor1, HIGH);   // Liga o motor traseiro direito
  digitalWrite(pinMotor2, LOW);    // Desliga o motor dianteiro direito
  digitalWrite(pinMotor3, HIGH);   // Liga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, LOW);    // Desliga o motor traseiro esquerdo

  // Define a velocidade dos motores para curva à esquerda
  analogWrite(pinspeed_R, CurvaLeftSpeed);
  analogWrite(pinspeed_L, CurvaRightSpeed);
  delay(duration3);  // Aguarda pelo tempo especificado
}

// Função para virar o robô para a direita
void virarDireita(int duration4){
  digitalWrite(pinMotor1, LOW);    // Desliga o motor traseiro direito
  digitalWrite(pinMotor2, HIGH);   // Liga o motor dianteiro direito
  digitalWrite(pinMotor3, LOW);    // Desliga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, HIGH);   // Liga o motor traseiro esquerdo

  // Define a velocidade dos motores para curva à direita
  analogWrite(pinspeed_R, CurvaLeftSpeed);
  analogWrite(pinspeed_L, CurvaRightSpeed);
  delay(duration4);  // Aguarda pelo tempo especificado
}

void Parar(int duration5){
  digitalWrite(pinMotor1,LOW); // Desliga o motor traseiro direito
  digitalWrite(pinMotor2,LOW); // Desliga o motor dianteiro direito  
  digitalWrite(pinMotor3,LOW); // Desliga o motor dianteiro esquerdo
  digitalWrite(pinMotor4,LOW); // Desliga o motor traseiro esquerdo
  
  // Define a velocidade dos motores para o desligamento
  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
  delay(duration5); // Aguarda pelo tempo especificado
}