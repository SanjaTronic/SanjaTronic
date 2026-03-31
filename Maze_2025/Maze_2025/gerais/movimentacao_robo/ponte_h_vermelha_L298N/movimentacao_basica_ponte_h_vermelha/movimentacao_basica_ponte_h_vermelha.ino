/*
========================================================================= TESTE PONTE H ROBÔ DEFINITIVO MAZE V0.1 ========================================================================================
Autor: Murilo
Data da criação: 13/06/2025
Data da última modificação: 13/06/2025

Campo de observações:
os comandos para girar os motores devem ser invertidos. Exemplo: paraFrente tem que ser paraTras 
===========================================================================================================================================================================================================
*/

//declaracao dos pinos utilizados para controlar a velocidade de rotacao
#define PINO_ENA 7 //12
#define PINO_IN1 16 //16
#define PINO_IN2 15 //14

#define PINO_ENB 11 // 7
#define PINO_IN3 17 //15
#define PINO_IN4 14 //17

// Declaração de variáveis que serão correspondentes a velocidade dos motores
int velMotoresEsq = 130; // 150, 200, 130
int velMotoresDir = 135; // 160, 215, 135
int velMotoresEsqCurva = 200;
int velMotoresDirCurva = 200;  

void setup() 
{

  //configuração dos pinos como saida
  pinMode(PINO_ENA, OUTPUT); 
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);

  //inicia o codigo com os motores parados
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
  digitalWrite(PINO_ENA, LOW);
  digitalWrite(PINO_ENB, LOW);

}

void loop() 
{
  /*for(int i = 100; i < 250; i = i + 10)
  {
  analogWrite(ENA_I, velMotoresEsq);
  analogWrite(ENB_I, velMotoresDir);

  digitalWrite(IN1_I, HIGH);
  digitalWrite(IN2_I, LOW);

  delay(1000);
  }*/

  /*testaMotorIndividual(120, 120);
  delay(5000);
  pararMotores();
  delay(3000);
  testaMotorIndividual(200, 200);
  delay(5000);
  pararMotores();
  delay(3000);
  */
  paraFrente();
  delay(3000);
  paraTras();
  delay(3000);
  virarEsquerda();
  delay(3000);
  virarDireita();
  delay(3000);
    
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
}/*
void testaMotorIndividual(int velE, int velD)
{
  analogWrite(ENA, velE);
  analogWrite(ENB, velD);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

}*/