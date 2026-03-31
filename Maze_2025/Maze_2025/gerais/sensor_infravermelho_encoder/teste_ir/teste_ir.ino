#define PinSensor 12 // Entrada digital do Arduino conectado ao pino OUT do Sensor
#define PINO_ENA 9
#define PINO_ENB 10
#define PINO_IN3 7
#define PINO_IN4 8
#define pinLed 4

int velMotoresEsq = 150;
int velMotoresDir = 180;

int LeituraSensor; // Váriavel que irá armazenar os valores de leitura do sensor ir
int estadoAnterior = 0;     // Guarda o valor anterior lido do sensor
int contador = 0;           // Contador de mudanças (bordas)

void setup() 
{
  Serial.begin(9600); //Inicializa a comunicação serial
  pinMode(PinSensor, INPUT); // Declara o pino do sensor como entrada (INPUT)

  //configuração dos pinos como saida
  pinMode(PINO_ENA, OUTPUT); 
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);

  //pinMode(pinLed, OUTPUT);

  //inicia o codigo com os motores parados
  digitalWrite(PINO_IN3, LOW); 
  digitalWrite(PINO_IN4, LOW);
  digitalWrite(PINO_ENA, LOW);
  digitalWrite(PINO_ENB, LOW);

  estadoAnterior = digitalRead(PinSensor);

  //digitalWrite(pinLed, HIGH);;
}

void loop() 
{

  paraFrente();

  LeituraSensor = digitalRead(PinSensor);


  if (LeituraSensor != estadoAnterior) 
  {
    contador++;
    estadoAnterior = LeituraSensor;

    Serial.print("Borda detectada. Contador: ");
    Serial.println(contador);

    if (contador == 8)
    {
      Serial.println("8 bordas detectadas, motores parando...");
      pararMotores();
      delay(5000);
      contador = 0; // Retoma a variável de quantidade de mudança de valores do ir para 0 para executar a lógica novamente
    }
  }

  delay(10);
}



void paraFrente()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsq);
  analogWrite(PINO_ENB, velMotoresDir);

  //configura os motores para o sentido horario
  digitalWrite(PINO_IN3, HIGH); 
  digitalWrite(PINO_IN4, LOW);
}
void pararMotores()
{
  digitalWrite(PINO_IN3, LOW); 
  digitalWrite(PINO_IN4, LOW);
}