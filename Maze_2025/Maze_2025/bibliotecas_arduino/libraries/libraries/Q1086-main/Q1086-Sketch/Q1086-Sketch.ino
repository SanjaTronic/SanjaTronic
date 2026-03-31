/* 
*/
// Inclusão de bibliotecas
#include "mpu6050.h" // Biblioteca para uso do acelrômetro e giroscópio mpu6050

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial

  mpu_begin(); // Inicializa o acelerômetro e giroscópio

  mpu_reset(); // Reseta a posição do giroscópio
}

void loop() {
  mpu_loop(); // Faz o mpu capturar o angulo a todo momento

  Serial.println(getAngleZ()); // Captura a posição do eixo Z do giroscópio e exibe eles em graus
  
  // Verifica se o ângulo do giroscópio é maior que 90, se for, ele reseta o giroscópio
  if(getAngleZ() > 92 || getAngleZ() < -92){
    mpu_reset(); // Reseta a posição do girocópio
  }
}
