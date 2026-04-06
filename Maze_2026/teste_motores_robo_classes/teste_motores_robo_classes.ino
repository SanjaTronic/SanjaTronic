// Iremos fazer uma classe para facilitar o uso da ponte H L298N na manipulação dos motores na função Setup e Loop.

class MotoresRobo 
{  
  int in1, in2, in3, in4, ena, enb;
  int spdE = 255;
  int spdD = 255;

  
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
    void definirVelMotores(int velEsq, int velDir)
    {
      spdE = velEsq;
      spdD = velDir;
    }     
    void moverFrente()
    { 
      // Configura a velocidade dos motores
      analogWrite(ena, spdE);
      analogWrite(enb, spdD);

      //configura os motores para o sentido horario
      digitalWrite(in1, LOW); 
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }   
    void moverTras()
    {

    }
    void parar()
    { 

    }
  };

   MotoresRobo motoresRobo;

void setup() 
{
  motoresRobo.definirPinosMotores(16, 15, 17, 14, 7, 11);
  motoresRobo.definirVelMotores(130, 130);
}
void loop() 
{
  motoresRobo.moverFrente();
}