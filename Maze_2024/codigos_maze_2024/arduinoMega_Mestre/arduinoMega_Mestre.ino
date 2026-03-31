/*Inicialização: No setup(), chamamos Wire.begin() 
para inicializar a comunicação I2C e Serial.begin(9600) para inicializar a 
comunicação serial para fins de depuração.

Loop principal: Dentro do loop(), primeiro chamamos Wire.beginTransmission(8). 
Isso inicia uma transmissão I2C para o dispositivo com endereço 8, que é o 
Arduino Nano (escravo).

Envio de dados: Em seguida, usamos Wire.write("Hello Nano!") para enviar a mensagem
 "Hello Nano!" para o Nano.

Fechamento da transmissão: Após escrever os dados, chamamos Wire.endTransmission()
para encerrar a transmissão I2C.

Espera: Por fim, utilizamos delay(1000) para esperar 1 segundo antes de iniciar o
 próximo ciclo do loop, enviando novamente a mensagem "Hello Nano!".
*/
#include <Wire.h>

void setup() {
  Wire.begin();        // Inicializa a comunicação I2C
  Serial.begin(9600);  // Inicializa a comunicação serial
}

void loop() {
  Wire.beginTransmission(8); // Endereço do Arduino Nano (escravo)
  Wire.write("Hello Nano!"); // Envie dados para o Nano
  Wire.endTransmission(); // Encerra a transmissão
  
  delay(1000); // Espera 1 segundo antes de enviar novamente
}

