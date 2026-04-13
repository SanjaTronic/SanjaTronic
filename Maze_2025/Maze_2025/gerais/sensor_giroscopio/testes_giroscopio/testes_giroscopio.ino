/*
============================================================================= CAMPO DE OBSERVAÇÕES =====================================================================================
Sobre o giroscópio:
  ao virar à direita, o ângulo somado a ele é negativo
  ao virar à esquerda, o ângulo somado a ele é positivo

Canal |   binário  |Hexadecimal
0     | 0b00000001 | 0x01
1     | 0b00000010 | 0x02
2     | 0b00000100 | 0x04
3     | 0b00001000 | 0x08
4     | 0b00010000 | 0x10
5     | 0b00100000 | 0x20
6     | 0b01000000 | 0x40
7     | 0b10000000 | 0x80

========================================================================================================================================================================================
*/

// Inclusão de bibliotecas
/*#include <Wire.h>     // Biblioteca para uso da comunicação I2C
#include "mpu6050.h"  // Biblioteca para uso do sensor giroscópio mpu6050

// Definição de pinos
#define TCA_END_I2C 0x70 // Endereço I2C do PCA9458A
#define GIROSCOPIO_END_PORTA 0x02 // Endereço do canal SDO0 e SC0 do multiplex i2c 

void setup() {

  Serial.begin(9600); // Inicializa a comunicação serial
  Wire.begin(); // Inicia o barramento I2C

  delay(2000); // Atraso de 2 segundos para garantir que a comunicação esteja pronta

  Serial.println("Iniciando giroscópio...");

  tca_select(0X02); // 0x10 ativa o canal 4 (SDA4, SCL4)
  mpu_begin();  // Inicia o giroscópio

  mpu_calibrate(200); // Calibra o giroscópio para uso 

  mpu_reset();  // Reseta o grioscópio

  Serial.println("Giroscópio iniciado com sucesso");

  delay(500); // Espera meio segundo para dar tempo de ler as mensagens de diagnostico
  
}

void loop() {

  // Executa a lógica do MPU6050
  //tca_select(0X02);
  mpu_loop();

  Serial.println(getAngleZ());  // Exibe as informações sobre a posição atual do giroscópio no monitor serial

  // Verifica o ângulo no eixo Z
  if(getAngleZ() > 66 || getAngleZ() < -66){
    Serial.println("O ângulo ultrapassou 90 graus, resetando...");
    delay(4500); // Aguarda 2 segundos antes de resetar

    // Reseta o MPU6050
    mpu_reset();
  }

  // Delay para ão sobrecarregar a comunicação serial
  delay(100);

}

// Definições de funções
void tca_select(uint8_t port) {

  Wire.beginTransmission(TCA_END_I2C);  // Inicilaiza a comunicação da porta do pca com o endereço especificado
  Wire.write(port);  // Envia o byte para selecionar o canal
  Wire.endTransmission();  // Encerra a comunicação com o pca

}
*/
#include <Wire.h>
#include "mpu6050.h"

// Endereço do multiplexador
#define TCA1_END 0x70

// Canal do giroscópio no multiplexador
#define END_PORTA_GIROSCOPIO 0x02

// ================= SETUP =================
void setup() 
{
  Serial.begin(9600);
  Wire.begin();

  delay(100);

  Serial.println("Inicializando MPU6050...");
  iniciaGiroscopio();
}

// ================= LOOP =================
void loop() 
{
  //seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO);

  mpu_loop(); // Atualiza os dados do sensor

  float anguloZ = getAngleZ();

  Serial.print("Angulo Z: ");
  Serial.println(anguloZ);

  delay(100);
}

// ================= FUNÇÕES =================

// Seleciona canal do multiplexador
void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t canal) 
{
  Wire.beginTransmission(endereco_multiplex);
  Wire.write(canal);
  Wire.endTransmission();
}

// Inicializa o MPU6050
void iniciaGiroscopio() 
{
  Serial.println("Selecionando canal do MPU...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO);

  mpu_begin();       // inicia MPU
  mpu_calibrate(200); // calibra
  mpu_reset();        // zera ângulo

  Serial.println("MPU6050 pronto!");
}


