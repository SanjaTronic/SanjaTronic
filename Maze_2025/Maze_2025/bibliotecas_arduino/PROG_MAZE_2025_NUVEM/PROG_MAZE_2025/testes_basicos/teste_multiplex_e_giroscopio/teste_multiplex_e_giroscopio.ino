/*
========================================================================= CAMPO DE OBSERVAÇÕES ===============================================================================================
Informações sobre o acelerômetro e o giroscópio:
  getAngleX(); Captura o ângulo do eixo X do acelerômetro (rotações para cima ou para baixo)
  getAngleZ(); Captura o ângulo do eixo Z do giroscópio (rotações à esquerda ou à direita)

Robô de teste:
  motores 1 e 4 sempre reotaciona-los no sentido contrário dos motores 2 e 3

Endereços multiplexadro i2c:
Canal |Hexadecimal
0     | 0x01
1     | 0x02
2     | 0x04
==============================================================================================================================================================================================
*/

// Inclusão de bibliotecas
#include <Wire.h> // Biblioteca para uso da comunicação i2c
#include "mpu6050.h" // Biblioteca para uso do giroscópio
#include <AFMotor.h> // Biblioteca para uso da ponte H L293D

// Definição de pinos
#define TCA_END 0x70 // Endereço I2C do multiplexador
#define ACELEROMETRO 0x01 // Endereço do canal SD0 e SC0 do multiplexador
#define GIROSCOPIO 0x02 // Endereço do canal SD1 e SC1 do multiplexador

// Inicializa os motores conectados na ponte H
AF_DCMotor motor1(1); // Motor conectado na porta M1 da shield
AF_DCMotor motor2(2); // Motor conectado na porta M2 da shield
AF_DCMotor motor3(3); // Motor conectado na porta M3 da shield
AF_DCMotor motor4(4); // Motor conectado na porta M4 da shield

// definição de váriáveis relacionadas a velocidade dos motores 
int velocidadeM1 = 73; // Variável com a velocidade do motor conectado a porta M1 da ponte H
int velocidadeM2 = 93; // Váriavel com a velocidade do motor conectado à porta M2 da ponte H
int velocidadeM3 = 73; // Variável com a velocidade do motor conectado à porta M3 da ponte H
int velocidadeM4 = 120; // Variável com a velocidade do motor conectado à porta M4 da ponte H

// definição de variáveis relacionadas a velocidade dos motores durante o momento da curva
int velocidadeCurvaM1 = 120; // Variável com a velocidade do motor 1 para uma curva
int velocidadeCurvaM2 = 120; // Variável com a velocidade do motor 2 para uma curva
int velocidadeCurvaM3 = 120; // Variável com a velocidade do motor 3 para uma curva
int velocidadeCurvaM4 = 120; // Variável com a velocidade do motor 4 para uma curva

void setup() {
  
  //configura_tudo(); // Chama pela função que realiza as configurações iniciais dos sensores
  Serial.begin(9600); // Inicializa o monitor serial
  Wire.begin(); // Inicia o barramento I2C

  Serial.println("Iniciando sensores...");
  delay(1500); // Atraso de 2 segundos para garantir que a comunicação i2c esteja pronta

  // Configura o acelerômetro na porta 0 do multiplexador
  seleciona_canal_multiplex(TCA_END, ACELEROMETRO); // Seleciona o canal do multiplexador onde o acelerômetro está conectado
  mpu_begin(); // Inicia o acelerômetro
  mpu_calibrate(200); // Calibra o acelerômetro para uso
  mpu_reset(); // Reseta o ângulo do acelerômetro para 0

  delay(1000); // ESpera 1 segundo antes de calibrar o outro sensor

  // Configura o giroscópio na porta 1 do multiplexador
  seleciona_canal_multiplex(TCA_END, GIROSCOPIO); // Seleciona o canal do multilexador onde o giroscópio está concetado 
  mpu_begin(); // Inicia o giroscópio
  mpu_calibrate(200); // Calibra o giroscópio para uso 
  mpu_reset(); // Reseta o ângulo do giroscópio para 0

  //Serial.println("Todos os sensores ocnfigurados com sucesso");

}

void loop() {

  seleciona_canal_multiplex(TCA_END, ACELEROMETRO); // Seleciona o canal do multiplex do acelerometro
  delay(20); // Pequeno atraso para não sobrecarregar os sensores
  mpu_loop(); // Executa a lógica do acelerômetro

  Serial.print("Acelerôemtro: ");
  Serial.println(getAngleX());

  seleciona_canal_multiplex(TCA_END, GIROSCOPIO); // Seleciona o canal do multiplex do giroscópio
  delay(20); // Pequeno atraso para não sobrecarregar os sensores
  mpu_loop(); // Executa a lógica do giroscópio

  Serial.print("Giroscópio: ");
  Serial.println(getAngleZ());

  delay(300); // Espera meio segundo para facilitar a leitura


}

// Declaração de funções

void configura_tudo(){

  Serial.begin(9600); // Inicializa o monitor serial
  Wire.begin(); // Inicia o barramento I2C

  delay(2000); // Atraso de 2 segundos para garantir que a comunicação i2c esteja pronta

  // Configura o acelerômetro na porta 0 do multiplexador
  seleciona_canal_multiplex(TCA_END, ACELEROMETRO); // Seleciona o canal do multiplexador onde o acelerômetro está conectado
  mpu_begin(); // Inicia o acelerômetro
  mpu_calibrate(200); // Calibra o acelerômetro para uso
  mpu_reset(); // Reseta o ângulo do acelerômetro para 0

  // Configura o giroscópio na porta 1 do multiplexador
  seleciona_canal_multiplex(TCA_END, GIROSCOPIO); // Seleciona o canal do multilexador onde o giroscópio está concetado 
  mpu_begin(); // Inicia o giroscópio
  mpu_calibrate(200); // Calibra o giroscópio para uso 
  mpu_reset(); // Reseta o ângulo do giroscópio para 0

}

void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t endereco_canal) {

  Wire.beginTransmission(endereco_multiplex);
  Wire.write(endereco_canal); // ativa apenas o canal desejado
  Wire.endTransmission(); // Encerra a atividade do canal

}

void paraFrente(int velM1, int velM2, int velM3, int velM4) {

  motor1.run(BACKWARD); // Gira o motor 1 no sentido horário
  motor2.run(FORWARD);  // Gira o motor 2 no sentido horário
  motor3.run(BACKWARD);  // Gira o motor 3 no sentido horário
  motor4.run(FORWARD); // Gira o motor 4 no sentido horário

  // Define a velocidade que os motores irão rotacionar
  motor1.setSpeed(velM1);
  motor2.setSpeed(velM2);
  motor3.setSpeed(velM3);
  motor4.setSpeed(velM4);

}

void pararMotores(){

  // Desliga os 4 motores
  motor1.run(RELEASE);
  motor2.run(RELEASE); 
  motor3.run(RELEASE);
  motor4.run(RELEASE);

}

void teste_rampa(){

  seleciona_canal_multiplex(TCA_END, ACELEROMETRO); // Seleciona a porta do multiplex onde o acelerômetro está conectado
  mpu_loop(); // Executa a lógica do acelerômetro

  Serial.print("acelerômetro: ");
  Serial.println(getAngleX()); // Exibe o ângulo do giroscópio no monitor serial

  paraFrente(velocidadeM1, velocidadeM2, velocidadeM3, velocidadeM4);
  
  while(getAngleX() > 21){ // Enquanto o ângulo do eixo X do acelerômetro for maior do que 21 graus

    seleciona_canal_multiplex(TCA_END, ACELEROMETRO); // Seleciona a porta do multiplex onde o acelerômetro está conectado
    mpu_loop(); // Executa a lógica do mpu

    Serial.println(getAngleX()); // Exibe informações sobre o ângulo do eixo X do acelerômetro

    paraFrente(velocidadeCurvaM1, velocidadeCurvaM2, velocidadeCurvaM3, velocidadeCurvaM4);

    // Caso o ângulo do eixo X do acelerômetro seja menor do que 21
    if(getAngleX() < 21){

      Serial.println("Robô em terreno plano, diminuindo velocidade dos motores...");
      pararMotores();
      delay(4000); // Espera 4 segundos antes de continuar 
      break; // Quebra o laço do while

    }

  }

  // Delay para ão sobrecarregar a comunicação serial
  delay(150);

}
