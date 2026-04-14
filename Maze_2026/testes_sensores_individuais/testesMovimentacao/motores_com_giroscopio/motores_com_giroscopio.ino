#include "Motores.h"
#include "mpu6050.h"
#include "MultiplexI2C.h"

MultiplexI2C multiplex(0x70);

void setup() 
{
  multiplex.begin();
  Serial.begin(9600);
  iniciarGiroscopio();

  
}

void loop() 
{

}

// Funções auxiliares
void iniciarGiroscopio()
{
  multiplex.selecionarCanal(1);
  Serial.println("Selecionando canal do MPU...");
  multiplex.selecionarCanal(1);
  
  mpu_begin();       
  mpu_calibrate(200); 
  mpu_reset();        

  Serial.println("MPU6050 pronto!");
}
