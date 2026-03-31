/*
============================================================== PROGRAMAÇÃO TESTE BÁSICO DA PONTE H ROBÔ DEFINITIVO MAZE V0.1 ==============================================================================
Autor: Murilo
Data da criação: 13/06/2025
Data da última modificação: 13/06/2025

Campo de observações:
analogWrite() é usado para definir a velocidade dos motores da ponteH
digitalWrite() usado para definir se o motor ficará ligado ou desligado
===========================================================================================================================================================================================================
*/


// Classe para facilitar o uso dos motores do robô
class motorRobo {  
  int velMotoresEsq = 150; // Velocidade motores lado esquerdo robô
  int velMotoresDir = 150; // Velocidade motores lado direito robô
  int pin1, pin2, pin3, pin4; // Define os que irão representar os pinos in1, in2, in3 e in4 dentro do método pinout na classe
  
  public:  
  
    void Pinout(int in1, int in2, int in3, int in4) // Pinout é o método para a declaração dos pinos que vão controlar o objeto motor
    {
      pin1 = in1;
      pin2 = in2;
      pin3 = in3;
      pin4 = in4;

      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      pinMode(pin3, OUTPUT);
      pinMode(pin4, OUTPUT);

    }   
    void velocidade(int in1E2, int in3E4) // Speed é o método que irá ser responsável por salvar a velocidade de atuação do motor
    { 
      velMotoresEsq = in1E2;
      velMotoresDir = in3E4;
    }     
    void paraFrente() // Forward é o método para fazer o motor girar para frente
    { 
      analogWrite(pin1, velMotoresEsq);
      analogWrite(pin2, velMotoresEsq);
      analogWrite(pin3, velMotoresDir);
      analogWrite(pin4, velMotoresDir);

      digitalWrite(pin1, velMotoresEsq);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, velMotoresDir);
      digitalWrite(pin4, LOW);
    }   
    void paraTras() // Backward é o método para fazer o motor girar para trás
    { 
      analogWrite(pin1, velMotoresEsq);
      analogWrite(pin2, velMotoresEsq);
      analogWrite(pin3, velMotoresDir);
      analogWrite(pin4, velMotoresDir);

      digitalWrite(pin1, velMotoresEsq);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, velMotoresDir);
      digitalWrite(pin4, LOW);
    }
    void pararMotores() // Stop é o metodo para fazer o motor ficar parado.
    { 
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
    }

   };

   motorRobo Motor1, Motor2; // Criação de dois objetos motores, já que usaremos dois motores, e eles já estão prontos para receber os comandos já configurados acima. 

void setup() 
{
  Motor1.Pinout(5,6); // Seleção dos pinos que cada motor usará, como descrito na classe.
  Motor2.Pinout(9,10); 
}

void loop() 
{
  Motor1.Speed(200); // A velocidade do motor pode variar de 0 a 255, onde 255 é a velocidade máxima.
  Motor2.Speed(200);
  
  Motor1.Forward(); // Comando para o motor ir para frente
  Motor2.Forward();
  delay(1000);
  Motor1.Backward(); // Comando para o motor ir para trás
  Motor2.Backward();
  delay(1000);
  Motor1.Stop(); // Comando para o motor parar
  Motor2.Stop();
  delay(500);
}