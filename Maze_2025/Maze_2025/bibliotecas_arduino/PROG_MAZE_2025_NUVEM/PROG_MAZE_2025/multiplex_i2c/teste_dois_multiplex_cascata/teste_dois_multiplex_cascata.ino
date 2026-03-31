/*
==================================================================== TESTE DOIS MULTIPLEXADORES I2C =======================================================================================
Autor: Murilo
Data da criação: 16/04/2025
Data da última modificação: 16/04/2025

Campo de observações:
endereços portas I2C do multiplexador PCA9458A:
Canal | Hexadecimal
0     |  0x01
1     |  0x02
2     |  0x04
3     |  0x08
4     |  0x10
5     |  0x20
6     |  0x40
7     |  0x80
===========================================================================================================================================================================================
*/

#include <Wire.h> // Biblioteca para uso do I2C
#include "mpu6050.h" // Biblioteca para uso do sensor giroscópio mpu6050

// Definição de endereços I2C
#define TCA1_END 0x70 // Endereço I2C do multiplexador 1
#define TCA2_END 0x71 // Endereço I2C do multiplexador 2

void setup() {

  Serial.begin(9600); // Inicia a comunicação serial
  Wire.begin(); // Inicia o barramento I2C

  // Ativa canal 7 do multiplexador A
  seleciona_canal_multiplex(TCA1_END, 0x80);

  // Ativa o canal 1 do multiplexador B
  seleciona_canal_multiplex(TCA2_END, 0x02);

  mpu_begin(); // Inicia o giroscópio
  mpu_calibrate(200); // Calibra o grioscópio para uso
  mpu_reset(); // Reseta o ângulo do giroscópio
  
}
void loop(){

  // Seleciona o canal 1 do multiplexador B
  seleciona_canal_multiplex(TCA1_END, 0x80);
  seleciona_canal_multiplex(TCA2_END, 0x02);
  
  mpu_loop(); // Executa a lógica do mpu

  Serial.println(getAngleZ()); // Exibe o ângulo do giroscópio no monitor serial  

}

void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t canal) {

  Wire.beginTransmission(muxAddr);
  Wire.write(channel); // ativa apenas o canal desejado
  Wire.endTransmission();

}
