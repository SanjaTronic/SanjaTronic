#include <Ultrasonic.h>

// Declaração dos pinos utilizados para controlar os motores
#define PINO_ENA 180
#define PINO_ENB 191
#define PINO_IN1 16
#define PINO_IN2 14
#define PINO_IN3 15
#define PINO_IN4 17

Ultrasonic ultrasonic(18, 19);  // Definindo os pinos do sensor ultrassônico (Trig, Echo)
int distance;                    // Distância medida pelo sensor ultrassônico
int qntdLadrilho;              // Quantidade de ladrilhos percorridos
int ladrilhosFrente;           // Quantidade de ladrilhos inicialmente medida
bool verificaLadrilho = true;    // Controle de quando medir o primeiro ladrilho

// Declaração das variáveis de controle da velocidade dos motores
int velMotoresEsq = 150;
int velMotoresDir = 180;
const int velMotoresEsqCurva = 200;
const int velMotoresDirCurva = 230;

void setup() {
  Serial.begin(9600);
  
  // Configuração dos pinos como saída
  pinMode(PINO_ENA, OUTPUT); 
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);

  // Inicia os motores parados
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
  digitalWrite(PINO_ENA, LOW);
  digitalWrite(PINO_ENB, LOW);
}

void loop() {

  distance = ultrasonic.read();

  Serial.print("Distância: ");
  Serial.println(distance);
  delay(50);  // Delay para estabilizar a leitura do sensor

}

void paraFrente()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsq);
  analogWrite(PINO_ENB, velMotoresDir);

  //configura os motores para o sentido horario
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void paraTras() 
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsq);
  analogWrite(PINO_ENB, velMotoresDir);

  //configura os motores para o sentido anti-horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);
}
void virarEsquerda()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsqCurva);
  analogWrite(PINO_ENB, velMotoresDirCurva);

  //configura os motores para 2 girarem no sentido horário e 2 no anti-horário (curva)
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void virarDireita() 
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsqCurva);
  analogWrite(PINO_ENB, velMotoresDirCurva);

  //configura os motores para 2 girarem no sentido horário e 2 no anti-horário (curva)
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);
}
void pararMotores()
{
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
}
