#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
const int fatorCorrecao = 40; // Fator de correção, subtraindo 40mm de cada leitura

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  Wire.begin(); // Inicializa a comunicação I2C

  sensor.init(); // Inicializa o sensor
  sensor.setTimeout(500); // Define o tempo limite para leituras

  if (!sensor.init()) {
    Serial.println("Falha ao inicializar o sensor VL53L0X.");
    while (1);
  }

  sensor.startContinuous(); // Inicia leituras contínuas
}

void loop() {
  int distancia = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) {
    Serial.println("Tempo limite de leitura alcançado!");
  } else {
    // Aplica o fator de correção
    distancia -= fatorCorrecao;

    // Verifica se a distância corrigida é menor que 0
    if (distancia < 0) {
      distancia = 0;
    }

    Serial.print("Distância corrigida: ");
    Serial.print(distancia);
    Serial.println(" mm");
  }

  delay(100); // Espera 100 ms antes de realizar a próxima leitura
}
