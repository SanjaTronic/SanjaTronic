/*
Canal | Hexadecimal
0      0x01
1      0x02
2      0x04
3      0x08
4      0x10
5      0x20
6      0x40
7      0x80
*/

// Inclusão de bibliotecas
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

// Definições do endereço I2C do PCA9548A e dos sensores
#define TCA_ADDR 0x70      // Endereço I2C do PCA9548A
#define VL53L0X_ADDR 0x29  // Endereço I2C do VL53L0X

// Instâncias para os sensores
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();  // Sensor VL53L0X 2

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(2000);  // Tempo para garantir que a comunicação I2C esteja pronta

  Serial.println("Iniciando o PCA9548A e sensores...");

  // Inicializando os sensores VL53L0X
  initVL53L0X();
}

void loop() {
    // Leitura do segundo sensor (Canal 2)
    tca_select(0x04);  // Canal 2 (SDA2, SCL2)
    Serial.println("Lendo distância do Sensor 2...");
    printDistance(lox2);  // Lê e imprime a distância do segundo sensor
    delay(500);

}

// Função para selecionar o canal do PCA9548A
void tca_select(uint8_t port) {
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(port);  // Envia o byte para selecionar o canal
  Wire.endTransmission();
}

// Função para inicializar os sensores VL53L0X nos canais do PCA9548A
void initVL53L0X() {
  // Inicializando o primeiro sensor VL53L0X (Canal 1)
  Serial.println("Ativando o canal 1 do PCA9548A...");
  tca_select(0x04); // Endereço sd2 sc2

  if (!lox2.begin(VL53L0X_ADDR)) {
    Serial.println("Falha ao inicializar o VL53L0X no Canal 1.");
    while (1)
      ;  // Fica travado se o sensor falhar
  }

}

// Função para ler e imprimir a distância do sensor
void printDistance(Adafruit_VL53L0X &sensor) {
  VL53L0X_RangingMeasurementData_t measure;

  // Realiza a medição de distância
  sensor.rangingTest(&measure, false);

  // Verifica se a medição foi bem-sucedida
  if (measure.RangeStatus != 4) {  // Se o status da medição não for erro
    Serial.print("Distância: ");
    Serial.print(measure.RangeMilliMeter / 10.0);  // Converte de mm para cm
    Serial.println(" cm");
  } else {
    Serial.println("Erro ao medir a distância.");
  }
}
