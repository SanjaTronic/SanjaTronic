#include <Wire.h>        
#include "mpu6050.h" 
#include <Adafruit_VL53L0X.h>    

#define TCA1_END 0x70  
#define TCA2_END 0x71  

#define END_PORTA_MULTIPLEX2 0x80
#define END_PORTA_LASER   0x02 

#define VL53L0X_ADDR 0x29

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();  // Sensor VL53L0X 1

void setup() {
  Serial.begin(9600);     
  Wire.begin();           

  seleciona_canal_multiplex(TCA1_END, END_PORTA_MULTIPLEX2);
  delay(10);
  Serial.println("Iniciando o PCA9548A e sensores...");
  delay(10);
  initVL53L0X();
}

void loop() {
  seleciona_canal_multiplex(TCA1_END, END_PORTA_MULTIPLEX2);
  delay(10);
  seleciona_canal_multiplex(TCA2_END, END_PORTA_LASER);
  leituraDistancia(lox1);
  delay(500);
}

bool seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t canal) {
  Wire.beginTransmission(endereco_multiplex);
  Wire.write(canal);
  return (Wire.endTransmission() == 0);
}

void trava_com_erro(const char* mensagem) {
  Serial.println(mensagem);
  Serial.println("Sistema travado. Verifique conexões e reinicie o dispositivo.");
  while (true);
}

void initVL53L0X() {
  if (!lox1.begin(VL53L0X_ADDR)) {
    trava_com_erro("Erro ao inicializar o sensor VL53L0X");
  }
  Serial.println("VL53L0X inicializado com sucesso.");
}

float leituraDistancia(Adafruit_VL53L0X &sensor) {
  VL53L0X_RangingMeasurementData_t medir;
  sensor.rangingTest(&medir, false);

  if (medir.RangeStatus != 4) {
    float distancia_cm = medir.RangeMilliMeter / 10.0;
    Serial.print("Distância: ");
    Serial.print(distancia_cm);
    Serial.println(" cm");
    return distancia_cm;
  } else {
    Serial.println("Erro ao medir a distância.");
    return -999;
  }
}
