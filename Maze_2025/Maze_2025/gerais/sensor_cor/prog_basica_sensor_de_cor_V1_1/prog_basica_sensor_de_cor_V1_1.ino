// Definição de pinos sensor de cor
#define PinOUT 36 //Definição do Pino OUT na entrada digital 36
#define PinS2  38 //Definição do Pino S2 na entrada digital 38
#define PinS3 40 //Definição do Pinto S3 na entrada digital 40

int red;//Declaração da variável que representará a cor vermelha
int green; //Declaração da variável que representará a cor verde
int blue; // Declaração da variável que representará a cor azul

void setup() {

  Serial.begin(9600); //Inicia o monitor Serial com velocidade de 9600

  pinMode(PinOUT, INPUT); //Definição do PinOUT como sendo um pino de entrada
  pinMode(PinS2, OUTPUT); //Definição do Pino S2 como sendo um pino de saída
  pinMode(PinS3, OUTPUT); //Definição do Pino S3 como sendo um pino de saída  

}

void loop() {

  //paraFrente();
  leituraCores(); // Chama pela função que lÊ a escala de cores do sensor de cor

}

void cores() { // funçao responsavel por definir a cor que o sensor de luminosidade está lendo

  if (blue < 20 && red < 20 && green < 20) { //detecção da cor branca
    Serial.println("Branco");
  }
  else if ((red > 32 && red < 70) && (green > 31 && green < 60) && (blue > 22 && blue < 38)) { // detecção da cor preta
    Serial.println("PRETO");
    /*
    pararMotores();
    paraTras();
    delay(3000);
    */
  }

  else if((red > 27 && red < 42) && (green > 20 && green < 35) && (blue > 12 && blue < 20)) { // detecção da cor azul
    Serial.println("AZUL");
    /*
    pararMotores();
    delay(5000);
    */
  }

  else if (red < blue && red < green && red < 100) { //detecção da cor vermelha
    Serial.println("Vermelho");
    // Lógica da zona de perigo
  }
}

void leituraCores(){

  digitalWrite(PinS2, LOW); // Aciona um valor LOW ao Pino S2
  digitalWrite(PinS3, LOW); // Aciona um valor LOW ao Pino S3
  red = pulseIn(PinOUT, LOW); // define red como sendo responsável por ler a informação de pulso LOW do pino out

  Serial.print(" R: "); // Mostra a letra R no monitor Serial, representando red
  Serial.print(red); // Mostra o valor lido no PulseIn

  delay(15); // delay de 15 milissegundos até o próximo comando


  digitalWrite(PinS2, HIGH); // Aciona um valo high ao Pino S2
  digitalWrite(PinS3, HIGH); // Aciona um valo high ao Pino S3
  green = pulseIn(PinOUT, LOW); // define green como sendo responsável por ler a informação de pulso low no pino out

  Serial.print(" G: "); // Mostra a letra R no monitor Serial, representando green
  Serial.print(green); // Mostra o valor lido no PulseIn

  delay(15); // delay de 15 milissegundos até o próximo comando


  digitalWrite(PinS2, LOW);// Aciona um valor loq ao Pino S2
  digitalWrite(PinS3, HIGH); // Aciona um valor high ao Pino S3
  blue = pulseIn(PinOUT, LOW);// define blue como sendo responsável por ler a informação de pulso low no pino out

  Serial.print(" B: "); // Mostra a letra B no monitor Serial, representando blue
  Serial.println(blue); // Mostra o valor lido no PulseIn

  delay(15); // delay de 15 milissegundos até o próximo comando

  cores(); //chamada da função cores()

  delay(1000);

}