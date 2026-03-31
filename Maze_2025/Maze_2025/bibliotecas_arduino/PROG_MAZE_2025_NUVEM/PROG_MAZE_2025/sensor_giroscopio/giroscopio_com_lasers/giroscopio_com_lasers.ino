// Inclusão de bibliotecas
#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include "mpu6050.h"

// Definições do endereço I2C do PCA9548A e dos sensores
#define TCA_ADDR 0x70          // Endereço I2C do PCA9548A
#define VL53L0X_ADDR 0x29     // Endereço I2C do VL53L0X

// Instâncias para os sensores
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();  // Sensor VL53L0X 1
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();  // Sensor VL53L0X 2
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();  // Sensor VL53L0X 3

// Variáveis para controlar o tempo
unsigned long previousMillis = 0;
const long interval = 1000;  // Intervalo de 1 segundo para leitura dos sensores

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(2000); // Tempo para garantir que a comunicação I2C esteja pronta

  Serial.println("Iniciando o PCA9548A e sensores...");

  // Inicializando os sensores VL53L0X nos canais do PCA9548A
  initVL53L0X();

  // Inicializando o MPU6050 via multiplexador (Canal 4)
  Serial.println("Inicializando o MPU6050 via PCA9548A...");
  tca_select(0x10);  // Canal 4 (SDA4, SCL4)
  mpu_begin();  // Inicializa o MPU6050
  mpu_calibrate(200);  // Calibra o giroscópio para uso
  mpu_reset();  // Reseta o MPU6050
  Serial.println("MPU6050 inicializado com sucesso!");
}

void loop() {
  unsigned long currentMillis = millis();

  // Verifica se já passou o intervalo para ler os sensores
  if (currentMillis - previousMillis >= interval) {
    // Atualiza o tempo da última leitura
    previousMillis = currentMillis;

    // Leitura do primeiro sensor (Canal 1)
    tca_select(0x02);  // Canal 1 (SDA1, SCL1)
    Serial.println("Lendo distância do Sensor 1...");
    printDistance(lox1);  // Lê e imprime a distância do primeiro sensor

    // Leitura do segundo sensor (Canal 2)
    tca_select(0x04);  // Canal 2 (SDA2, SCL2)
    Serial.println("Lendo distância do Sensor 2...");
    printDistance(lox2);  // Lê e imprime a distância do segundo sensor

    // Leitura do terceiro sensor (Canal 3)
    tca_select(0x08);  // Canal 3 (SDA3, SCL3)
    Serial.println("Lendo distância do Sensor 3...");
    printDistance(lox3);  // Lê e imprime a distância do terceiro sensor

    // Leitura do MPU6050 via PCA9548A (Canal 4)
    tca_select(0x10);  // Canal 4 (SDA4, SCL4)
    Serial.println("Lendo ângulo do MPU6050...");
    mpu_loop();  // Executa o loop do MPU6050
    Serial.print("Ângulo Z: ");
    Serial.println(getAngleZ());  // Imprime o ângulo no eixo Z do MPU6050

    // Verifica se o ângulo ultrapassou os limites e reseta o MPU6050
    if (getAngleZ() > 66 || getAngleZ() < -66) {
      Serial.println("O ângulo ultrapassou 82 graus, resetando...");
      mpu_reset();  // Reset do MPU6050
      Serial.println("MPU6050 resetado.");
    }

  }
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
  tca_select(0x02);  // Canal 1 (SDA1, SCL1)

  if (!lox1.begin(VL53L0X_ADDR)) {
    Serial.println("Falha ao inicializar o VL53L0X no Canal 1.");
    while (1); // Fica travado se o sensor falhar
  }
  Serial.println("Sensor VL53L0X 1 inicializado com sucesso!");

  // Inicializando o segundo sensor VL53L0X (Canal 2)
  Serial.println("Ativando o canal 2 do PCA9548A...");
  tca_select(0x04);  // Canal 2 (SDA2, SCL2)

  if (!lox2.begin(VL53L0X_ADDR)) {
    Serial.println("Falha ao inicializar o VL53L0X no Canal 2.");
    while (1); // Fica travado se o sensor falhar
  }
  Serial.println("Sensor VL53L0X 2 inicializado com sucesso!");

  // Inicializando o terceiro sensor VL53L0X (Canal 3)
  Serial.println("Ativando o canal 3 do PCA9548A...");
  tca_select(0x08);  // Canal 3 (SDA3, SCL3)

  if (!lox3.begin(VL53L0X_ADDR)) {
    Serial.println("Falha ao inicializar o VL53L0X no Canal 3.");
    while (1); // Fica travado se o sensor falhar
  }
  Serial.println("Sensor VL53L0X 3 inicializado com sucesso!");
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

