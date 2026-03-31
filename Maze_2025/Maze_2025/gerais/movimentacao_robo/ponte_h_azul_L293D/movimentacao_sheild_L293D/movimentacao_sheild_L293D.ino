/*
========================================================= CÓDIGO TESTE SERVOS MOTORES COM SHIELD L293D ARDUINO =============================================================================
Autores: Caio Souza Branze, Israel da Silva Santiago e Murilo Siqueira Santos
Data da criação: 07/04/2025. Segunda-Feira
Data da última modificação: 09/04/2025. Quarta-Feira

Campo de observações:
  observação 1:
    motor 1 e motor 4 devem ser configurados de maneira inversa aos motores 2 e 3. Exemplo: motor2.run(FORWARD); e/ou  motor3.run(FORWARD); então 
    motor1.run(BACKWARD); e/ou motor4.run(BACKWARD);
  observação 2:
    localização dos motores:
      motor1, é o motor localizado a parte inferior esquerda do robô
      motor2, é o motor localizado a parte inferior direita do robô
      motor3, é o motor localizado a parte superior direita do robô
      motor4, é o motor localizado a parte superior esquerda do robô
============================================================================================================================================================================================
*/

// Inclusão de bibliotecas
#include <AFMotor.h>  // Biblioteca para uso da shield da ponte H L293D

// Inicializa os motores conectados às portas M1, M2, M3 e M4
AF_DCMotor motor1(1); // Motor conectado na porta M1 da shield
AF_DCMotor motor2(2); // Motor conectado na porta M2 da shield
AF_DCMotor motor3(3); // Motor conectado na porta M3 da shield
AF_DCMotor motor4(4); // Motor conectado na porta M4 da shield

// definição de váriáveis relacionadas a velocidade dos motores 
int velocidadeM1 = 150; // Variável que contém a velocidade do motor conectado à porta M1
int velocidadeM2 = 150; // Váriavel que contém a velocidade do motor conectado à porta M2
int velocidadeM3 = 150; // Variável que contém a velocidade do motor conectado à porta M3
int velocidadeM4 = 150; // Variável que contém a velocidade do motor conectado à porta M4

// definição de variáveis relacionadas a velocidade dos motores durante o momento da curva
int velocidadeCurvaM1 = 190; // Variável que contém a velocidade do motor conectado à porta M1 da shield durante uma curva
int velocidadeCurvaM2 = 190; // Variável que contém a velocidade do motor conectado à porta M2 da shield durante uma curva
int velocidadeCurvaM3 = 190; // Variável que contém a velocidade do motor conectado à porta M3 da shield durante uma curva
int velocidadeCurvaM4 = 190; // Variável que contém a velocidade do motor conectado a porta M4 da shield ruante uma curva

void setup() {

  Serial.begin(9600); // Inicializa a comunicação serial
  
}

void loop() {
  
  // Realiza um teste para verificar se todos os motores estão funcionanado corretamente
  paraFrente();
  delay(3000); 
  paraTras();
  delay(3000);
  virarEsquerda();
  delay(3000);
  virarDireita();
  delay(3000);
  pararMotores();
  delay(3000);
  

}

// Declaração de funções
// Função para testar os motores um por um
void testaMotorIndividual(){

  // Define a velocidade dos motores
  motor1.setSpeed(velocidadeM1);
  motor2.setSpeed(velocidadeM2);
  motor3.setSpeed(velocidadeM3);
  motor4.setSpeed(velocidadeM4);
  
  // Gira o motor 1 no sentido horário por 3 segundos
  motor1.run(BACKWARD);
  delay(3000);
  motor1.run(RELEASE);

  // Gira o motor 2 no sentido horário por 3 segundos
  motor2.run(FORWARD);
  delay(3000);
  motor2.run(RELEASE);

  // Gira o motor 3 no sentido horário por 3 segundos
  motor3.run(FORWARD);
  delay(3000);
  motor3.run(RELEASE);

  // Gira o motor 4 no sentido horário por 3 segundos
  motor4.run(BACKWARD);
  delay(3000);
  motor4.run(RELEASE);

}


void paraFrente() {

  motor1.run(BACKWARD); // Gira o motor 1 no sentido horário
  motor2.run(FORWARD);  // Gira o motor 2 no sentido horário
  motor3.run(FORWARD);  // Gira o motor 3 no sentido horário
  motor4.run(BACKWARD); // Gira o motor 4 no sentido horário

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
  motor3.run(BACKWARD); // Rotaciona o motor 3 no sentido anti-horário
  motor4.run(FORWARD);  // Rotaciona o motor 4 no sentido anti-horário

  // Define a velocidade dos motores durante o movimento da curva
  motor1.setSpeed(velocidadeCurvaM1);
  motor2.setSpeed(velocidadeCurvaM2);
  motor3.setSpeed(velocidadeCurvaM3);
  motor4.setSpeed(velocidadeCurvaM4);

}