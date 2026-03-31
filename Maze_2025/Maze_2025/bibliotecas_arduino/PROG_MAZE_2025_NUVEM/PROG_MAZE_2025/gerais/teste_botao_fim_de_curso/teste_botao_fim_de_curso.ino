// Inclusão de bibliotecas
#include<Servo.h> // Biblioteca para uso do servo motor

// Definição de pinos
#define pinoServo 6

// Declaração de objteos
Servo s; // Objeto do tipo servo

// Declaração de variáveis
int pushbutton = 2; // declara o push button na porta 2
int contadorCliques = 0;
int btoPressionado = 0;
int pos; // Variável que armazena a posição do servo

void setup()
{

  configuraTudo(); // Chama pela função que realiza as configurações necessárias do void setup

}

void loop()
{

  testeBtoIf();

}

// Declaração de funções
void testeBtoIf(){

  if (digitalRead(pushbutton) == LOW) // Se o botão for pressionado
  {

    contadorCliques++; // Soma 1 à variável que armazena a quantidade de vezes que o botão foi pressionado

    Serial.println(contadorCliques);
    Serial.print("o botão foi pressionado! quantidade de vezes Pressionado: ");

    s.write(180);
    delay(1500);
    s.write(0);
    delay(1500);
         
  }

}

void testeBtoWhile(){
  
  while(digitalRead(pushbutton) == LOW) // Enquanto o botão estiver pressionado
  {

    contadorCliques++; // Soma 1 à variável que armazena a quantidade de vezes que o botão foi pressionado

    Serial.println(contadorCliques);
    Serial.print("o botão foi pressionado! quantidade de vezes Pressionado: ");

  }

}

void configuraTudo(){

  Serial.begin(9600); // Inicializa a comunicação

  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao como entrada

  s.attach(pinoServo); // Associa o pino digital do servo ao objeto Servo
  s.write(0); // Inicia o servo motor na posição 0

}