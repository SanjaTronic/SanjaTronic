#define END_PORTA_GIROSCOPIO 1

#include "mpu6050.h"
#include "MultiplexI2C.h"

MultiplexI2C multiplex(0x70);

void setup() {
  multiplex.begin();
  delay(1000);

  Serial.begin(9600);
  iniciaGiroscopio();
}

void loop() {
  //multiplex.selecionarCanal(1);
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
void iniciaGiroscopio() // Função que realiza as configurações iniciais do sensor giroscópio
{
  // Inicializando o MPU6050 via multiplexador (Canal 4)
  Serial.println("Inicializando o MPU6050 via multiplex...");
  multiplex.selecionarCanal(1);
  mpu_begin();  // Inicializa o MPU6050
  mpu_calibrate(200);  // Calibra o giroscópio para uso
  mpu_reset();  // Reseta o MPU6050
  Serial.println("MPU6050 inicializado com sucesso!");
}