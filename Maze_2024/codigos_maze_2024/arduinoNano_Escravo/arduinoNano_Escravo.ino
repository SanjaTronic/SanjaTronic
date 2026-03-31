/*Inicialização: No setup(), chamamos Wire.begin(8) para configurar o Arduino Nano como um escravo
 com o endereço 8 na comunicação I2C. Em seguida, usamos Wire.onReceive(receiveEvent)
  para configurar a função receiveEvent() para lidar com dados recebidos.

Loop principal: O loop() está vazio e apenas contém um pequeno atraso com delay(100) para permitir
 que o Arduino Nano processe outras tarefas.

Recebimento de dados: Quando dados são recebidos pelo Arduino Nano, a função receiveEvent(int bytes)
 é chamada automaticamente. Dentro dessa função, utilizamos um loop while (Wire.available())
  para verificar se há dados disponíveis para leitura. Se houver, usamos Wire.read()
   para ler o caractere recebido e o imprimimos na porta serial com Serial.print(c).
*/
#include <Wire.h>

void setup() {
  Wire.begin(8);                // Define o endereço do escravo como 8
  Wire.onReceive(receiveEvent); // Configura a função para receber dados
  Serial.begin(9600);           // Inicializa a comunicação serial
}

void loop() {
  delay(100); // Espera um curto período para a comunicação
}

void receiveEvent(int bytes) {
  while (Wire.available()) { // Enquanto houver dados disponíveis
    char c = Wire.read();    // Lê o caractere recebido
    Serial.print(c);         // Mostra o caractere na porta serial
  }
}

