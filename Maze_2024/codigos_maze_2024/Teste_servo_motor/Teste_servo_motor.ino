#include <Servo.h>

Servo meuServo;  // Cria um objeto Servo para controlar o servo motor
unsigned long duracaoGiro = 5000;  // Duração do giro do motor em milissegundos (5 segundos)

void setup() {
  meuServo.attach(9);  // Define o pino digital 9 como o pino de controle do servo
  Serial.begin(9600);  // Inicializa a comunicação serial com a taxa de 9600 bps
  Serial.println("Pronto para receber comandos...");
}

void loop() {
  if (Serial.available() > 0) {  // Verifica se há dados disponíveis para leitura
    int comando = Serial.parseInt();  // Lê o comando do monitor serial
    
    // Verifica o comando recebido
    if (comando == 1) {
      // Gira o motor por um tempo determinado
      meuServo.write(90);  // Define uma posição intermediária (90 graus), mas não é crucial para o funcionamento baseado no tempo
      delay(duracaoGiro);  // Mantém o servo nessa posição pelo tempo especificado
      
      // Para o motor
      meuServo.detach();  // Desliga o servo para economizar energia
      
      // Mensagem de feedback no monitor serial
      Serial.println("Motor girou por tempo determinado.");
    } else {
      Serial.println("Comando inválido.");
    }
    
    // Limpa o buffer serial para garantir que não haja dados residuais
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
