// Define os pinos de controle//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define S0 22 //28
#define S1 24 //24
#define S2 26
#define S3 28
#define OUT A7
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // Inicia comunicação serial
  Serial.begin(9600);

  // Define os pinos de controle como saídas
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  // Configura a escala de frequência do TCS3200
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void loop() {
  // Lê os valores das cores
  int red = readColor(LOW, LOW);   // Filtro de vermelho
  int green = readColor(HIGH, HIGH); // Filtro de verde
  int blue = readColor(LOW, HIGH);  // Filtro de azul

  // Imprime os valores das cores no Monitor Serial para ajuste
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(" Green: ");
  Serial.print(green);
  Serial.print(" Blue: ");
  Serial.println(blue);

  // Determina a cor detectada
  if (isBlue(red, green, blue)) {
    Serial.println("Azul detectado");
  } else if (isBlack(red, green, blue)) {
    Serial.println("Preto detectado");
  } else if (isSilver(red, green, blue)) {
    Serial.println("Prata detectado");
  } else {
    Serial.println("Nenhuma cor detectada");
  }

  delay(500); // Aguarda meio segundo
}

// Função para ler a cor com base em filtros de cor
int readColor(int s2, int s3) {
  // Configura o filtro de cor
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);

  // Mede o tempo que leva para o sinal de saída passar por um intervalo
  unsigned long duration = pulseIn(OUT, LOW);

  // Converte o tempo para uma leitura de cor
  return duration;
}

// Função para detectar se a cor é azul
bool isBlue(int red, int green, int blue) {
  // Ajuste os valores de limiar conforme necessário
  return (blue > 68) && (blue < 105) && (red > 135) && (red < 200) && (green > 118) && (green < 170);
}

// Função para detectar se a cor é preta
bool isBlack(int red, int green, int blue) {
  // Preto deve ter valores baixos em todas as cores
  return (red > 180) && (green > 171) && (blue > 155);
}

// Função para detectar se a cor é prata
bool isSilver(int red, int green, int blue) {
  // Prata deve ter valores relativamente altos em todas as cores
  return (red > 5 && red < 14) &&
         (green > 5 && green < 14) &&
         (blue > 4 && blue < 14);
}