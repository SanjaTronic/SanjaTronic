// Incluindo Bibliotecas 
#include "Motores.h"
#include "Giroscopio.h"
#include "Lasers.h"
#include "MultiplexI2C.h"

// Criando objetos
MultiplexI2C mux(0x70);
Giroscopio giro(&mux, 1);
Motores motores;
Lasers lasers(&mux);

// Definindo constantes
#define laserDir 2
#define laserEsq 3
#define laserFrtN2 4
#define laserFrtN1 5

void setup() 
{
  Serial.begin(9600);

  // Inicializa o multiplex e o I2C
  mux.begin();
  delay(1000);

  // inicializa o sensor giroscopio
  giro.begin();

  // Configurando os motores
  motores.definirPinosMotores(16, 15, 17, 14, 7, 11);
  motores.setVelocidadeMotores(130, 130);

  lasers.iniciaLaser(laserDir);
  lasers.iniciaLaser(laserEsq);
  lasers.iniciaLaser(laserFrtN2);

}

void loop() 
{
  motores.moverFrente();
  delay(2000);

}
