/*
================================================= CÓDIGO DE MOVIMENTAÇÃO DO ROBÔ COM SENSORES LASERS E SENSOR GIROSCÓPIO ============================================================================
Autor: Murilo
Data da criação: 12/2024
Data da última modificação: 12/2024
Campo de observações:
=====================================================================================================================================================================================================
*/

// Inclusão de bibliotecas
#include <Wire.h>     // Biblioteca para uso da comunicação I2C
#include "mpu6050.h"  // Biblioteca para uso do sensor giroscópio mpu6050

// Definição de pinos
#define TCA_ADDR 0x70 // Endereço I2C do PCA9458A

// Pinos relacionados aos motores
#define PINO_ENA 4
#define PINO_ENB 9
#define PINO_IN1 5
#define PINO_IN2 6
#define PINO_IN3 7
#define PINO_IN4 8

// Declaração e definição de variáveis relacionadas a velocidades dos motores
int velocidadeMotores = 200;
int velocidadeCurva = 200;


void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  Wire.begin(); // Inicia o barramento I2C

  delay(2000); // Atraso de 2 segundos para garantir que a comunicação esteja pronta

  tca_select(0x10); // 0x10 ativa o canal 4 (SDA4, SCL4)
  mpu_begin();  // Inicia o giroscópio

  mpu_calibrate(200); // Calibra o giroscópio para uso 

  mpu_reset();  // Reseta o grioscópio
  
  // Configuração dos pinos dos motores como saída
  pinMode(PINO_ENA, OUTPUT); 
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);
}

void loop() {

  // Executa a lógica do MPU6050
  mpu_loop();

  Serial.println(getAngleZ());  // Exibe as informações sobre o ângulo atual do giroscópio no monitor serial

  virarDireita();

  // Verifica o ângulo no eixo Z
  if(getAngleZ() > 66 || getAngleZ() < -66){
    Serial.println("O ângulo ultrapassou 90 graus, resetando...");
    pararMotores();
    delay(4500); // Aguarda 4,5 segundos antes de reinicializar ângulo do giroscópio

    // Reseta o MPU6050
    mpu_reset();
  }

  // Delay para ão sobrecarregar a comunicação serial
  delay(100);

}

// Definições de funções
void tca_select(uint8_t port) {

  // Processo para endereçamento de sensores conectados ao expansor de portas I2C
  Wire.beginTransmission(TCA_ADDR);  // Inicializa o endereçamento do sensor con
  Wire.write(port);                  // Envia o byte para selecionar o canal
  Wire.endTransmission();            // Encerra o processo de endereçamento de portas i2c pelo expansor

}

void paraFrente() {  
  // Configura os motores para o sentido horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotores);
  analogWrite(PINO_ENB, velocidadeMotores);
}

void paraTras() {
  // Configura os motores para girar no sentido anti-horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotores);
  analogWrite(PINO_ENB, velocidadeMotores);
}

void virarDireita() {
  // Configura 2 motores para girar no sentido anti-horário e 2 para girar sentido horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeCurva);
  analogWrite(PINO_ENB, velocidadeCurva);
}

void virarEsquerda() {
  // Configura 2 motores para o sentido horário e 2 para o sentido anti-horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);

  // Configura a velocidade dos motores sendo 70
  analogWrite(PINO_ENA, velocidadeCurva);
  analogWrite(PINO_ENB, velocidadeCurva);
}

void pararMotores() {
  // Configura os 4 motores para pararem de girar
  digitalWrite(PINO_IN1, LOW);
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores como 0
  analogWrite(PINO_ENA, 0);
  analogWrite(PINO_ENB, 0);
}
