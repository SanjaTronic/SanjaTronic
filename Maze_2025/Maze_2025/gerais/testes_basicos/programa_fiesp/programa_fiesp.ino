/*
============================================================================ CÓDIGO VISITA FIESP ========================================================================================
Autor: Murilo Siqueira Santos
Data da criação: 18/05/2025
Data da última modificação: 21/05/2025

Campo de observações:
  Tempo de delay para o robô andar 1 ladrilho: delay(2100)
  Tempo de delay para o robô realizar uma "curva de 90 graus": delay(1050)
============================================================================================================================================================================================
*/

// Inclusão de bibliotecas
#include <AFMotor.h>  // Biblioteca para uso da shield da ponte H L293D

// Definição de pinos
#define TCA_ADDR 0x70 // Endereço I2C do PCA9458A

// Inicializa os motores conectados às portas M1, M2, M3 e M4
AF_DCMotor motor1(1); // Motor conectado na porta M1 da shield
AF_DCMotor motor2(2); // Motor conectado na porta M2 da shield
AF_DCMotor motor3(3); // Motor conectado na porta M3 da shield
AF_DCMotor motor4(4); // Motor conectado na porta M4 da shield

// definição de váriáveis relacionadas a velocidade dos motores 
int velocidadeM1 = 120; // Variável que contém a velocidade do motor conectado à porta M1
int velocidadeM2 = 173; // Váriavel que contém a velocidade do motor conectado à porta M2
int velocidadeM3 = 120; // Variável que contém a velocidade do motor conectado à porta M3
int velocidadeM4 = 173; // Variável que contém a velocidade do motor conectado à porta M4

// definição de variáveis relacionadas a velocidade dos motores durante o momento da curva
int velocidadeCurvaM1 = 190; // Variável que contém a velocidade do motor conectado à porta M1 da shield durante uma curva
int velocidadeCurvaM2 = 190; // Variável que contém a velocidade do motor conectado à porta M2 da shield durante uma curva
int velocidadeCurvaM3 = 190; // Variável que contém a velocidade do motor conectado à porta M3 da shield durante uma curva
int velocidadeCurvaM4 = 190; // Variável que contém a velocidade do motor conectado a porta M4 da shield ruante uma curva

const int tempoFrente = 1800;
const int tempoCurva = 1000;
int tempoFrenteX2 = tempoFrente * 2;
int tempoFrenteX3 = tempoFrente * 3;
int tempoFrenteX4 = tempoFrente * 4;
int tempoFrenteX5 = tempoFrente * 5;
int tempoFrenteX7 = tempoFrente * 7;
int tempoFrenteX8 = tempoFrente * 5;

void setup() {

  Serial.begin(9600); // Inicializa a comunicação serial

}

void loop() {

  movimentacao();
  //movimentacao2Rampa();  

}

void movimentacao(){

  paraFrente();
  delay(tempoFrenteX3);
  virarEsquerda(); // Primeira curva
  delay(tempoCurva);
  paraFrente();
  delay(tempoFrente);
  virarEsquerda(); // Segunda curva
  delay(900);
  paraFrente();
  delay(tempoFrente);
  virarDireita(); // Terceira curva
  delay(1000);
  paraFrente();
  delay(tempoFrenteX2);
  virarDireita(); // Quarta curva
  delay(tempoCurva);
  paraFrente();
  delay(3400);
  virarDireita(); // Quinta curva
  delay(1100);
  paraFrente();
  delay(5600);
  virarDireita(); // Sexta curva
  delay(tempoCurva);
  paraFrente();
  delay(tempoFrenteX8);
  pararMotores();
  delay(25000);


}

void movimentacao2Rampa(){

  paraFrente();
  delay(tempoFrenteX7);
  virarEsquerda();
  delay(1100);
  velocidadeM1 = 150;
  velocidadeM2 = 193; // Aumentar valor
  velocidadeM3 = 150;
  velocidadeM4 = 193; // Aumentar valor
  paraFrente();
  delay(tempoFrenteX4);
  velocidadeM1 = 120;
  velocidadeM2 = 173; // Aumentar valor
  velocidadeM3 = 120;
  velocidadeM4 = 173; // Aumentar valor
  virarEsquerda();
  delay(1000);
  paraFrente();
  delay(5200);
  pararMotores();
  delay(20000);

}

void paraFrente() {

  motor1.run(BACKWARD); // Gira o motor 1 no sentido horário
  motor2.run(FORWARD);  // Gira o motor 2 no sentido horário
  motor3.run(BACKWARD);  // Gira o motor 3 no sentido horário
  motor4.run(FORWARD); // Gira o motor 4 no sentido horário

  // Define a velocidade que os motores irão rotacionar
  motor1.setSpeed(velocidadeM1);
  motor2.setSpeed(velocidadeM2);
  motor3.setSpeed(velocidadeM3);
  motor4.setSpeed(velocidadeM4);

}

void pararMotores() {

  // Para de enviar energia aos quatro motores, parando sua rotação
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

}

void virarEsquerda() {

  motor1.run(FORWARD);  // Rotaciona o motor 1 no sentido anti-horário
  motor2.run(FORWARD);  // Rotaciona o motor 2 no sentido horário
  motor3.run(FORWARD);  // Rotaciona o motor 3 no sentido horário
  motor4.run(FORWARD);  // Rotaciona o motor 4 no sentido anti-horário

  // Define a velocidade dos motores durante o movimento de curva
  motor1.setSpeed(velocidadeCurvaM1); 
  motor2.setSpeed(velocidadeCurvaM2);   
  motor3.setSpeed(velocidadeCurvaM3);  
  motor4.setSpeed(velocidadeCurvaM4); 

}

// Função para virar à direita com maior velocidade
void virarDireita() {

  motor1.run(BACKWARD); // Rotaciona o motor 1 no sentido horário
  motor2.run(BACKWARD); // Rotaciona o motor 2 no sentido anti-horário 
  motor3.run(BACKWARD); // Rotaciona o motor 3 no sentido anti-horário
  motor4.run(BACKWARD); // Rotaciona o motor 4 no sentido horário

  // Define a velocidade dos motores durante o movimento de curva
  motor1.setSpeed(velocidadeCurvaM1);  
  motor2.setSpeed(velocidadeCurvaM2);  
  motor3.setSpeed(velocidadeCurvaM3); 
  motor4.setSpeed(velocidadeCurvaM4);

}


// Função para andar para trás
void paraTras() {

  motor1.run(FORWARD);  // Rotaciona o motor 1 no sentido anti-horário
  motor2.run(BACKWARD); // Rotaciona o motor 2 no sentido anti-horário
  motor3.run(FORWARD); // Rotaciona o motor 3 no sentido anti-horário
  motor4.run(BACKWARD);  // Rotaciona o motor 4 no sentido anti-horário

  // Define a velocidade dos motores durante o movimento da curva
  motor1.setSpeed(velocidadeM1);
  motor2.setSpeed(velocidadeM2);
  motor3.setSpeed(velocidadeM3);
  motor4.setSpeed(velocidadeM4);

}