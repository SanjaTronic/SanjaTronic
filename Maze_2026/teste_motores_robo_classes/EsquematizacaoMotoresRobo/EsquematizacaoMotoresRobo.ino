class Motores 
{  
  int in1, in2, in3, in4, ena, enb;
  int velocidadeE = 255;
  int velocidadeD = 255;
  int velocidadeCurvaEsq = 255;
  int velocidadeCurvaDir = 255;

  public:  
  
    void definirPinosMotores(int in1, int in2, int in3, int in4, int ena, int enb)
    {
      this->in1 = in1;
      this->in2 = in2;
      this->in3 = in3;
      this->in4 = in4;
      this->ena = ena;
      this->enb = enb;

      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
      pinMode(in3, OUTPUT);
      pinMode(in4, OUTPUT);
      pinMode(ena, OUTPUT);
      pinMode(enb, OUTPUT);
    }   
    void setVelocidadeMotores(int velocidadeE, int velocidadeD)
    {
      this->velocidadeE = velocidadeE;
      this->velocidadeD = velocidadeD;
    }
    void configurarMotores(int velocidadeE, int velocidadeD, bool ligDesM1, bool ligDesM2, bool ligDesM3, bool ligDesM4)
    {
      // Configura a velocidadeocidade dos motores
      analogWrite(ena, velocidadeE);
      analogWrite(enb, velocidadeD);

      // configura o sentido de rotacao dos motores
      digitalWrite(in1, ligDesM1);
      digitalWrite(in2, ligDesM2);
      digitalWrite(in3, ligDesM3);
      digitalWrite(in4, ligDesM4);
    }     
    void moverFrente()
    { 
      configurarMotores(this->velocidadeE, this->velocidadeD, 0, 1, 0, 1);
    }   
    void moverTras()
    {
      configurarMotores(this->velocidadeE, this->velocidadeD, 1, 0, 1, 0);
    }
    void virarEsquerda()
    {
      configurarMotores(velocidadeCurvaEsq, velocidadeCurvaDir, 1, 0, 0, 1);
    }
    void virarDireita()
    {
      configurarMotores(velocidadeCurvaEsq, velocidadeCurvaDir, 0, 1, 1, 0);
    }
    void parar()
    {
      configurarMotores(0, 0, 0, 0, 0, 0);
    }
  };

   Motores Motores;

void setup() 
{
  Motores.definirPinosMotores(16, 15, 17, 14, 7, 11);
  Motores.setVelocidadeMotores(130, 130);
}
void loop() 
{
  Motores.moverFrente();
  delay(2000);
  Motores.moverTras();
  delay(2000);
  Motores.virarEsquerda();
  delay(2000);
  Motores.virarDireita();
  delay(2000);
}