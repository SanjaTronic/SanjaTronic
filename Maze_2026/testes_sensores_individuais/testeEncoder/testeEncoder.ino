/*
============================= TESTE ENCODER ====================================
Autor: Murilo Siqueira Santos
Data da criação: 09/04/2026
Data da última modificação: 12/05/2026

Campo de observações:
  . uma volta da roda equivale a 40 recortes
  . um ladrilho percorrido equivale a 46 recortes
================================================================================
*/

int sensorPin = 8; 
int leituraSensor; 
int leituraAnterior = 0;  // guarda o estado anterior
int contagem = 0;
int voltaRoda = 0;

void setup() 
{
  Serial.begin(9600); 
  Serial.println("Santos futebol clube");
  pinMode(sensorPin, INPUT);
}

void loop() 
{
  leituraSensor = digitalRead(sensorPin);

  // Detecta quando o sensor muda de 0 para 1 (objeto passando)
  if (leituraSensor == 1 && leituraAnterior == 0)
  {
    contagem++;


    if(contagem % 46 == 0)
    {
      voltaRoda++;
      //Serial.print("Numero de voltas da roda: ");
      Serial.print("números de ladrilhos percorridos: ");
      Serial.println(voltaRoda);
    }
  }

  // Atualiza o estado anterior
  leituraAnterior = leituraSensor;
}
