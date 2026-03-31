const int PINO_SENSOR_S0 = 22;  // Pino 8 da BlackBoard conectado ao pino S0 do TCS230
const int PINO_SENSOR_S1 = 24; // Pino 9 da BlackBoard conectado ao pino S1 do TCS230
const int PINO_SENSOR_S2 = 23; // Pino 12 da BlackBoard conectado ao pino S2 do TCS230
const int PINO_SENSOR_S3 = 28; // Pino 11 da BlackBoard conectado ao pino S3 do TCS230
const int PINO_SENSOR_OUT = A7; // Pino 10 da BlackBoard conectado ao pino OUT do TCS230

long vermelho, azul, verde;

void setup() {
  Serial.begin(9600); // Inicializa o monitor serial
  pinMode(PINO_SENSOR_S0, OUTPUT); // Pino S0 configurado como saída
  pinMode(PINO_SENSOR_S1, OUTPUT); // Pino S1 configurado como saída
  pinMode(PINO_SENSOR_S2, OUTPUT); // Pino S2 configurado como saída
  pinMode(PINO_SENSOR_S3, OUTPUT); // Pino S3 configurado como saída
  pinMode(PINO_SENSOR_OUT, INPUT); // Pino OUT configurado como entrada

  digitalWrite(PINO_SENSOR_S0, HIGH); // Inicia o código com o pino S0 em nível alto
  digitalWrite(PINO_SENSOR_S1, LOW);  // Inicia o código com o pino S1 em nível baixo
}

void loop() {
  leitura_cores(); // Chama a rotina que lê as cores
  identificarCor(); // Identifica e mostra a cor no monitor serial
  delay(1000);
}

void leitura_cores() {
  digitalWrite(PINO_SENSOR_S2, LOW); // Pino S2 em nível baixo
  digitalWrite(PINO_SENSOR_S3, LOW); // Pino S3 em nível baixo

  // Leitura da cor vermelha
  vermelho = pulseIn(PINO_SENSOR_OUT, digitalRead(PINO_SENSOR_OUT) == HIGH ? LOW : HIGH);

  digitalWrite(PINO_SENSOR_S3, HIGH); // Pino S3 em nível alto

  // Leitura da cor azul
  azul = pulseIn(PINO_SENSOR_OUT, digitalRead(PINO_SENSOR_OUT) == HIGH ? LOW : HIGH);

  digitalWrite(PINO_SENSOR_S2, HIGH); // Pino S2 em nível alto

  // Leitura da cor verde
  verde = pulseIn(PINO_SENSOR_OUT, digitalRead(PINO_SENSOR_OUT) == HIGH ? LOW : HIGH);
}

void identificarCor() {
  // Exibe os valores lidos no monitor serial
  Serial.print("Vermelho: ");
  Serial.print(vermelho);
  Serial.print(" | Verde: ");
  Serial.print(verde);
  Serial.print(" | Azul: ");
  Serial.println(azul);
}

  // Determina a cor predominante
  /*if (vermelho < azul && vermelho < verde) {
    Serial.println("Cor detectada: Vermelho");
  } else if (verde < vermelho && verde < azul) {
    Serial.println("Cor detectada: Verde");
  } else if (azul < vermelho && azul < verde) {
    Serial.println("Cor detectada: Azul");
  } else {
    Serial.println("Cor indeterminada ou branca");
  }
}*/
