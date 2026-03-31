void setup() {
// Declara a função de cada pino como input(entrada de dados)
  pinMode(3, INPUT);
  pinMode(7, INPUT);
  // Inicializa a comunicação serial com velocidade de 9600 bps
  Serial.begin(9600);
}

void loop() {
  // Declara cada o valor de cada variável como a leitura dos senore
  int sensorValue1 = digitalRead(3);
  int sensorValue2 = digitalRead(7);
  
  // Imprime o valor lido do sensor 1 no monitor serial 
  Serial.print("Valor do sensor 1: ");
  Serial.println(sensorValue1);

  // Imprime o valor lido do sensor 2 no monitor serial 
  Serial.print("Valor do sensor 2: ");
  Serial.println(sensorValue2);
  
  // Aguarda um pequeno intervalo antes de ler novamente
  delay(500);
}
