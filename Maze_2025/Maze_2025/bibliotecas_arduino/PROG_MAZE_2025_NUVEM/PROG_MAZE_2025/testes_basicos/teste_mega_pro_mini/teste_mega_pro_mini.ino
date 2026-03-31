/*



*/
// Inclusão de bilbiotecas
#include "mpu6050.h" // Biblioteca para uso do giroscópio
#include <Wire.h> // Biblioteca para uso da comunicação I2C
#include <Adafruit_VL53L0X.h> // Biblioteca para uso do sensor laser

// Definição de endereços
#define TCA_END_I2C 0x70 // Endereços I2C do pca9548A
#define VL53L0X_ADDR 0x29  // Endereço I2C do VL53L0X

// Instâncias para os sensores
Adafruit_VL53L0X laser1 = Adafruit_VL53L0X();  // Sensor VL53L0X 1

void setup(){

  Serial.begin(9600); // Inicializa a comunicação serial
  Wire.begin(); // Inicia o barramento I2C

  delay(2000);

  Serial.println("Iniciando o multiplex e sensores...");
  
  initVL53L0X(); // Chama pela função que inicializa o sensor laser

}

void loop() {

    // Leitura do primeiro sensor (Canal 1)
    tca_select(0x01);  // Canal 1 (SDA1, SCL1)
    //Serial.println("Lendo distância do Sensor 1...");
    printDistance(laser1);  // Lê e imprime a distância do primeiro sensor



  // Delay para ão sobrecarregar a comunicação serial
  delay(100);


}

void initVL53L0X() {

  // Inicializando o primeiro sensor VL53L0X (Canal 1)
  Serial.println("Ativando o canal 0 do PCA9548A...");
  tca_select(0x01);  // Canal 1 (SDA1, SCL1)

  if (!laser1.begin(VL53L0X_ADDR)) {
    Serial.println("Falha ao inicializar o VL53L0X no Canal 1.");
    while (1)
      ;  // Fica travado se o sensor falhar
  }

}

// Função para ler e imprimir a distância do sensor
void printDistance(Adafruit_VL53L0X &sensor) {
  VL53L0X_RangingMeasurementData_t dist;

  // Realiza a medição de distância
  sensor.rangingTest(&dist, false);

  // Verifica se a medição foi bem-sucedida
  if (dist.RangeStatus != 4) {  // Se o status da medição não for erro
    Serial.print("Distância: ");
    Serial.print(dist.RangeMilliMeter / 10.0);  // Converte de mm para cm
    Serial.println(" cm");
  } else {
    Serial.println("Erro ao medir a distância.");
  }
}

// Função para selecionar o canal do PCA9548A
void tca_select(uint8_t port) {
  Wire.beginTransmission(TCA_END_I2C);
  Wire.write(port);  // Envia o byte para selecionar o canal
  Wire.endTransmission();
}