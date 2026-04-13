int sensorPin = 8; 
int leituraSensor; 
int leituraAnterior = 0;  // guarda o estado anterior
int contagem = 0;
int voltaRoda = 0;

void setup() 
{
  Serial.begin(9600); 
  pinMode(sensorPin, INPUT);
}

void loop() 
{
  leituraSensor = digitalRead(sensorPin);

  // Detecta quando o sensor muda de 0 para 1 (objeto passando)
  if (leituraSensor == 1 && leituraAnterior == 0)
  {
    contagem++;


    if(contagem % 40 == 0)
    {
      voltaRoda++;
      Serial.print("Numero de voltas da roda: ");
      Serial.println(voltaRoda);
    }
  }

  // Atualiza o estado anterior
  leituraAnterior = leituraSensor;
}
