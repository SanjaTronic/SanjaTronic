#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>

class Motores 
{  
  private:
    int in1, in2, in3, in4, ena, enb;
    int velocidadeE = 255;
    int velocidadeD = 255;
    int velocidadeCurvaEsq = 255;
    int velocidadeCurvaDir = 255;

  public:  
    void definirPinosMotores(int in1, int in2, int in3, int in4, int ena, int enb);
    void setVelocidadeMotores(int velocidadeE, int velocidadeD);
    void configurarMotores(int velocidadeE, int velocidadeD, bool ligDesM1, bool ligDesM2, bool ligDesM3, bool ligDesM4);

    void moverFrente();
    void moverTras();
    void virarEsquerda();
    void virarDireita();
    void parar();
};

#endif
