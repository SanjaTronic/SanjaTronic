#include <SFE_MMA8452Q.h> //Biblioteca para giroscópio
#include <NewPing.h> // Biblioteca para uso do sensor ultrassônico
#include <Wire.h>    // Biblioteca para comunicação I2C
#include <Servo.h>   // Biblioteca para uso do servo motor

// Define os pinos conectados aos motores
#define pinMotor1 11  // Motor traseiro direito (Laranja)
#define pinMotor2 10  // Motor dianteiro direito (Branco)
#define pinMotor3 9  // Motor dianteiro esquerdo (Verde)
#define pinMotor4 8  // Motor traseiro esquerdo (Cinza)
#define pinspeed_R 13 // INA (Verde) - controla a velocidade do motor direito
#define pinspeed_L 12 // INB (Cinza) - controla a velocidade do motor esquerdo

// Define os pinos conectados ao sensor de cor
#define S0 22
#define S1 24
#define S2 26
#define S3 28
#define OUT A15

#define LED_PIN 53 // Define o pino 53 como o pino do LED

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

int auxLed;
int auxCurva;

// Define as velocidades dos motores
int RightSpeed = 60;  // Velocidade para movimento para frente e curva à esquerda // vel padrão 60
int LeftSpeed = 100; // Velocidade para movimento para frente e curva à direita   // vel padrão 100
int CurvaRightSpeed = 128;  // Velocidade do motor esquerdo para curva à esquerda
int CurvaLeftSpeed = 124; // Velocidade do motor direito para curva à direita

Servo meuServo;

// Variáveis para armazenar o número de bytes recebidos e o tempo do último byte recebido
int bytesReceived = 0;
unsigned long lastReceivedTime = 0;
//const unsigned long displayDelay = 2000; // 2 segundos de atraso

MMA8452Q acelerometro(0x1C);

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  acelerometro.init();

  meuServo.attach(3); // Pino digital 3 para o sinal do servo

  pinMode(LED_PIN, OUTPUT); // Define o pino 53 como saída

  // Configura os pinos dos motores como saídas
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotor3, OUTPUT);
  pinMode(pinMotor4, OUTPUT);

  // Define os pinos de controle do sensor de cor como saídas
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  
  // Configura a escala de frequência do TCS3200
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Wire.begin();
}
void loop() {
  // Lê os valores das cores
  int red = readColor(LOW, LOW); // Filtro de vermelho
  int green = readColor(HIGH, HIGH); // Filtro de verde
  int blue = readColor(LOW, HIGH); // Filtro de azul

  // Determina a cor detectada
  if (isBlue(red, green, blue)) {
    Parar();
    delay(5000);
  } else if (isBlack(red, green, blue)) {
    paraTras();
  } else if (isSilver(red, green, blue)) {
    Parar();
    delay(500);
  } else if (Serial.available()) {
    // Lê o byte recebido
    byte receivedByte = Serial.read();

    // Incrementa o número de bytes recebidos
    bytesReceived++;

    int delayTime = 0;

    if (receivedByte == 1) {
      // Letra H detectada
      Parar();
      piscaLed();
      delayTime = 310;  // Tempo para 2 kits
    } else if (receivedByte == 2) {
      // letra S detectada
      Parar();
      piscaLed();
      delayTime = 155;  // Tempo para 1 kit
    } else if (receivedByte == 3) {
      // Letra U detectada
      Parar();
      piscaLed();
    } else if (receivedByte == 4) {
      // Cor vermelha detectada
      Parar();
      piscaLed();
      delayTime = 310;  // Tempo para 2 kits
    } else if (receivedByte == 5) {
      // Cor amarela detectada
      Parar();
      piscaLed();
      delayTime = 155;  // Tempo para 1 kit
    } else if (receivedByte == 6) {
      // Cor verde detectada
      Parar();
      piscaLed();
    }

    // Gira o servo com base no número de kits a serem depositados
    if (delayTime > 0) {
      meuServo.write(0);    // Gira no sentido horário
      delay(delayTime);     // Aguarda pelo tempo necessário
      meuServo.write(90);   // Para o servo
    }

    // Atualiza o tempo do último byte recebido
    lastReceivedTime = millis();

}
  // Um pequeno delay para não sobrecarregar a comunicação serial
  delay(100);

    if (acelerometro.available()) {
    //Efetua a leitura dos dados do sensor
    acelerometro.read();

    byte pl = acelerometro.readPL();

    // Tomar decisões com base na maior distância
if ((distance1 > distance2) && (distance1 > distance3)) {
    // Se a maior distância for do sensor da frente, seguir em frente
    paraFrente();
    delay(3000);
    Parar();
} else if ((distance2 > distance1) && (distance2 > distance3)) {
    // Se a maior distância for do sensor da esquerda, virar para a direita
    virarDireita();
    delay(3000);
    Parar();
    paraFrente();
} else if ((distance3 > distance1) && (distance3 > distance2)) {
    // Se a maior distância for do sensor da direita, virar para a esquerda
    virarEsquerda();
    delay(3000);
    Parar();
    paraFrente();
} else {
    // Caso algo inesperado aconteça, parar e recuar
    Parar();
    paraTras();
    delay(3000);
}

  if(pl == "LANDSCAPE_L"){
  RightSpeed = 120;  
  LeftSpeed = 200;
  }
}

// Obtém a distância medida pelos sensores ultrassônicos
int distance1 = sonar1.ping_cm(); // Sensor da frente
int distance2 = sonar2.ping_cm(); // Sensor da esquerda
int distance3 = sonar3.ping_cm(); // Sensor da direita

// Encontrar a maior distância entre os três sensores
//int maxDistance = max(distance1, max(distance2, distance3));

// Tomar decisões com base na maior distância
if ((distance1 > distance2) && (distance1 > distance3)) {
    // Se a maior distância for do sensor da frente, seguir em frente
    paraFrente();
    delay(3000);
    Parar();
} else if ((distance2 > distance1) && (distance2 > distance3)) {
    // Se a maior distância for do sensor da esquerda, virar para a direita
    virarDireita();
    delay(3000);
    Parar();
    paraFrente();
} else if ((distance3 > distance1) && (distance3 > distance2)) {
    // Se a maior distância for do sensor da direita, virar para a esquerda
    virarEsquerda();
    delay(3000);
    Parar();
    paraFrente();
} else {
    // Caso algo inesperado aconteça, parar e recuar
    Parar();
    paraTras();
    delay(3000);
}

}

// Função para ler a cor com base em filtros de cor
int readColor(int s2, int s3){
  // Configura o filtro de cor
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);

  // Mede o tempo que leva para o sinal de saída passar por um intervalo
  unsigned long duration = pulseIn(OUT, LOW);

  // Converte o tempo para uma leitura de cor
  return duration;
}

// Função para detectar se a cor é azul
bool isBlue(int red, int green, int blue) {
   return (blue > 67) && (blue < 105) && (red > 135) && (red < 200) && (green > 118) && (green < 170);
}

// Função para detectar se a cor é preto
bool isBlack(int red, int green, int blue) {
  // Preto deve ter valores baixos em todas as cores
  return (red > 180) && (green > 171) && (blue > 155);
}

// Função para detectar se a cor é prata
bool isSilver(int red, int green, int blue) {
  // Prata deve ter valores relativamente altos em todas as cores
  return (red > 5 && red < 14) && (green > 5 && green < 14) && (blue > 4 && blue < 14);
}
// Função para mover o robô para frente
void paraFrente(){
  digitalWrite(pinMotor1, HIGH);   // Liga o motor traseiro direito
  digitalWrite(pinMotor2, LOW);    // Desliga o motor dianteiro direito
  digitalWrite(pinMotor3, HIGH);    // Desliga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, LOW);   // Liga o motor traseiro esquerdo

  // Define a velocidade dos motores
  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
  
}

// Função para mover o robô para trás
void paraTras(){
  digitalWrite(pinMotor1, LOW);    // Desliga o motor traseiro direito
  digitalWrite(pinMotor2, HIGH);   // Liga o motor dianteiro direito
  digitalWrite(pinMotor3, LOW);   // Liga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, HIGH);    // Desliga o motor traseiro esquerdo

  // Define a velocidade dos motores
  analogWrite(pinspeed_R, LeftSpeed);
  analogWrite(pinspeed_L, RightSpeed);
  
}

// Função para virar o robô para a esquerda
void virarDireita(){
  digitalWrite(pinMotor1, LOW);   // Liga o motor traseiro direito
  digitalWrite(pinMotor2, HIGH);    // Desliga o motor dianteiro direito
  digitalWrite(pinMotor3, HIGH);   // Liga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, LOW);    // Desliga o motor traseiro esquerdo

  // Define a velocidade dos motores para curva à esquerda
  analogWrite(pinspeed_R, CurvaLeftSpeed);
  analogWrite(pinspeed_L, CurvaRightSpeed);
  
  direcaoAtual = (direcaoAtual - 2 + 4) % 4 + 1; // ajusta a variavel da direção do robô após a curva à
  
}

// Função para virar o robô para a direita
void virarEsquerda(){
  digitalWrite(pinMotor1, HIGH);    // Desliga o motor traseiro direito
  digitalWrite(pinMotor2, LOW);   // Liga o motor dianteiro direito
  digitalWrite(pinMotor3, LOW);    // Desliga o motor dianteiro esquerdo
  digitalWrite(pinMotor4, HIGH);   // Liga o motor traseiro esquerdo

  // Define a velocidade dos motores para curva à direita
  analogWrite(pinspeed_R, CurvaLeftSpeed);
  analogWrite(pinspeed_L, CurvaRightSpeed);

  direcaoAtual = (direcaoAtual % 4) + 1; // ajusta a variavel da direção do robô após a curva à direita
}

void Parar(){
  digitalWrite(pinMotor1,LOW); // Desliga o motor traseiro direito
  digitalWrite(pinMotor2,LOW); // Desliga o motor dianteiro direito  
  digitalWrite(pinMotor3,LOW); // Desliga o motor dianteiro esquerdo
  digitalWrite(pinMotor4,LOW); // Desliga o motor traseiro esquerdo 
  delay(300);
}

void piscaLed(){
  for(auxLed = 0; auxLed < 5; auxLed++){
  digitalWrite(LED_PIN, HIGH); // Liga o LED
  delay(500); // Espera meio segundo (500 milissegundos)
  digitalWrite(LED_PIN, LOW);  // Desliga o LED
  delay(500); // Espera meio segundo (500 milissegundos)
 }
}