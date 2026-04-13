// Incluindo biblotecas
#include "Motores.h"

// Criando objeto da classe Motores
Motores motores;

void setup() 
{
  motores.definirPinosMotores(16, 15, 17, 14, 7, 11);
  motores.setVelocidadeMotores(130, 130);
}

void loop() 
{
  motores.moverFrente();
  delay(2000);

  motores.moverTras();
  delay(2000);

  motores.virarEsquerda();
  delay(2000);

  motores.virarDireita();
  delay(2000);
}
