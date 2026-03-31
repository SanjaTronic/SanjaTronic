#include <Ultrasonic.h>

//declaracao dos pinos utilizados para controlar a velocidade de rotacao
#define PINO_ENA 7 //12
#define PINO_IN1 16 //16
#define PINO_IN2 15 //14

#define PINO_ENB 11 // 7
#define PINO_IN3 17 //15
#define PINO_IN4 14 //17

Ultrasonic ultrasonic(18, 19);  // Definindo os pinos do sensor ultrassônico (Trig, Echo)
int distUltrasonico;                    // Distância medida pelo sensor ultrassônico
int distUltrasonicoInicial;             // Distância inicial do sensor ultrasonico
bool inicioMov = false;      // Verifica se o robô começou a andar

// Declaração das variáveis de controle da velocidade dos motores
int velMotoresEsq = 150;
int velMotoresDir = 180;
const int velMotoresEsqCurva = 200;
const int velMotoresDirCurva = 230;

void setup() 
{
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

void loop() 
{  
  // Média de 3 leituras do sensor ultrassônico para estabilizar a leitura
  float soma = 0;

  for (int i = 0; i < 3; i++) 
  {
    soma += ultrasonic.read();
    delay(20);  // Pequeno delay para estabilizar a leitura
  }

  distUltrasonico = soma / 3.0;  // Distância média

  // Exibe a distância medida no serial
  Serial.print("Distância média: ");
  Serial.println(distUltrasonico);

  // Se o robô ainda não começou a se mover, armazena a distância inicial
  if (inicioMov == false) 
  { 
    distUltrasonicoInicial = distUltrasonico;  // Armazena a distância inicial
    inicioMov = true;        // Marca que o robô começou a andar
    Serial.print("Distância inicial armazenada: ");
    Serial.println(distUltrasonicoInicial);
  }

  // Verifica se a distância inicial diminuiu em 30 cm
  if (distUltrasonicoInicial - distUltrasonico >= 26 || distUltrasonico < 10) 
  {
    Serial.println("Robô andou 30 cm");
    pararMotores();  // Para os motores
    delay(5000);     // Espera 5 segundos antes de parar completamente
    inicioMov = false; // Reinicia o processo
  } 
  else 
  {
    paraFrente();  // Move o robô para frente
  }
  
  delay(50);  // Pequeno delay entre as verificações de distância
  
}

void paraFrente()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsq);
  analogWrite(PINO_ENB, velMotoresDir);

  //configura os motores para o sentido horario
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void paraTras() 
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsq);
  analogWrite(PINO_ENB, velMotoresDir);

  //configura os motores para o sentido anti-horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);
}
void virarEsquerda()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsqCurva);
  analogWrite(PINO_ENB, velMotoresDirCurva);

  //configura os motores para 2 girarem no sentido horário e 2 no anti-horário (curva)
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void virarDireita() 
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsqCurva);
  analogWrite(PINO_ENB, velMotoresDirCurva);

  //configura os motores para 2 girarem no sentido horário e 2 no anti-horário (curva)
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
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
