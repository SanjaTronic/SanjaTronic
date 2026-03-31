#include <Wire.h>
#include <VL53L0X.h>

// Criar instâncias para cada sensor
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;

#define TCA_ADDR 0x70  // Endereço do PCA9548A

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Inicializa os sensores via multiplexador
  inicia_lasers();

  // Configuração de modo de medição contínua
  tca_select(0x02);  // Ativa canal do sensor 1
  sensor1.startContinuous();

  tca_select(0x04);  // Ativa canal do sensor 2
  sensor2.startContinuous();

  tca_select(0x08);  // Ativa canal do sensor 3
  sensor3.startContinuous();
}

void loop() {
  tca_select(0x02);  // Ativa canal do sensor 1
  Serial.print("Sensor 1: ");
  Serial.print(sensor1.readRangeContinuousMillimeters() / 10.0);
  Serial.print(" cm\t");

  tca_select(0x04);  // Ativa canal do sensor 2
  Serial.print("Sensor 2: ");
  Serial.print(sensor2.readRangeContinuousMillimeters() / 10.0);
  Serial.print(" cm\t");

  tca_select(0x08);  // Ativa canal do sensor 3
  Serial.print("Sensor 3: ");
  Serial.print(sensor3.readRangeContinuousMillimeters() / 10.0);
  Serial.println(" cm");

  delay(100);
}

// Função para selecionar o canal do PCA9548A
void tca_select(uint8_t canal) {
  Wire.beginTransmission(TCA_ADDR);
  //Wire.write(1 << canal);  // Ativa apenas o canal desejado
  Wire.endTransmission();
}

// Função para inicializar os sensores via multiplexador
void inicia_lasers() {
  tca_select(0x02);  // Ativa canal do sensor 1
  if (!sensor1.init()) {
    Serial.println("Falha ao iniciar o Sensor 1");
  }

  tca_select(0x04);  // Ativa canal do sensor 2
  if (!sensor2.init()) {
    Serial.println("Falha ao iniciar o Sensor 2");
  }

  tca_select(0x08);  // Ativa canal do sensor 3
  if (!sensor3.init()) {
    Serial.println("Falha ao iniciar o Sensor 3");
  }
}
