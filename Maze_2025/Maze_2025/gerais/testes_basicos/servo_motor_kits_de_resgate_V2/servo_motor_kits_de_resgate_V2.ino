/*
================================================================ PROGRAMAÇÃO SERVO MOTOR KITS DE RESGATE =================================================================================================
Autor: Murilo
Data da criação: 23/07/2025
Data da última modificação: 12/08/2025

Campo de observações:
N\A
============================================================================================================================================================================================================
*/

// Inclusão de bibliotecas
#include <Servo.h> // Biblioteca para uso do servo motor SG90
#include <Adafruit_NeoPixel.h> // Biblioteca para uso do LED

#define PIN 3 // Porta do arduino onde o led está conectado
#define NUMLED 8 // Números de led que há na fita
#define DELAYLOOP 100 // Intervalo entre as piscadas do led

Adafruit_NeoPixel pixels(NUMLED, PIN, NEO_GRB + NEO_KHZ800);
Servo myservo;  // cria um objeto para controlar o servo

void setup() 
{
  Serial.begin(9600); // Inicializa a comunicação serial
  myservo.attach(44); // Atribui o servo na porta 44
  pixels.begin(); // Inicializa o LED
}

void loop() 
{
  depositaKit(15);
  // Verifica se existe pelo menos 1 byte disponível para leitura
  /*if (Serial.available() > 0) 
  {  
    byte byte_recebido = Serial.read();  // Lê o byte recebido

    // Verificar a cor/letra detectada pela Raspberry
    if (byte_recebido == 0x03) { // Cor verde
      Serial.println("Cor: verde");
    } 
    else if (byte_recebido == 0x05) { // Cor vermelho
      Serial.println("Cor: vermelho");
      depositaKit(2); // Deposita 2 kits
    } 
    else if (byte_recebido == 0x07) { // Cor amarelo
      Serial.println("Cor: amarelo");  
      depositaKit(1); // Deposita 1 kit
    } 
    else if (byte_recebido == 0x09) { // Letra H
      Serial.println("Letra: H");
      depositaKit(2); // Deposita 2 kits
    }
    else if (byte_recebido == 0x11) { // Letra S
      Serial.println("Letra: S");
      depositaKit(1); // Deposita 1 kit
    } 
    else if (byte_recebido == 0x13) { // Letra U
      Serial.println("Letra: U");
    } 
    else { // Valor inválido
      Serial.println("Letra ou cor desconhecida");
    }

    limpaBuffer(); // Limpa bytes restantes do buffer
  }*/
}

// Funções auxiliares
void depositaKit(int qntdKit) 
{
  // Pisca os LEDs 5 vezes
  for (int j = 0; j < 5; j++) 
  {
    // Acende todos os LEDs em branco
    for (int i = 0; i < NUMLED; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // branco
    }
    pixels.show();
    delay(500);

    // Apaga todos os LEDs
    pixels.clear();
    pixels.show();
    delay(500);
  }

  // Garante que os LEDs fiquem desligados após os 5 piscos
  pixels.clear();
  pixels.show();

  // Gira o servo para depositar os kits de resgate
  for (int i = 0; i < qntdKit; i++) 
  {
    myservo.write(35);   // Posição inicial
    delay(1200);         // Tempo para chegar
    myservo.write(120);  // Posição final
    delay(1200);         // Tempo para chegar
  }
}

void limpaBuffer()
{
  while (Serial.available() > 0) 
  {
    Serial.read(); // descarta byte a byte
  }
}
