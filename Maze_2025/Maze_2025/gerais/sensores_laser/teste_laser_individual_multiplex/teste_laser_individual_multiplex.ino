/*
laser1 -> ok
laser2 -> esquerda parte da frente
laser3 -> erro
laser4 -> frente direita
laser5 -> erro
laser6 -> direita parte de trás

*/

#include <Wire.h>                  // Comunicação I2C
#include <Adafruit_VL53L0X.h>      // Biblioteca do sensor VL53L0X

// Endereço I2C do multiplexador e do sensor VL53L0X
#define TCA1_END 0x70
#define VL53L0X_END 0x29

// Canal do multiplexador onde o sensor está conectado
#define END_PORTA_LASER1 0x04
#define END_PORTA_LASER2 0x08
#define END_PORTA_LASER3 0x10
#define END_PORTA_LASER4 0x20
#define END_PORTA_LASER5 0x40
#define END_PORTA_LASER6 0x80

// Instância do único sensor
Adafruit_VL53L0X laser1 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser2 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser3 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser4 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser5 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser6 = Adafruit_VL53L0X();

// Serial debugging (opcional)
#define modoSerial true

#if modoSerial
  #define s_begin(x)     Serial.begin(x)
  #define s_print(x)     Serial.print(x)
  #define s_println(x)   Serial.println(x)
#else
  #define s_begin(x)
  #define s_print(x)
  #define s_println(x)
#endif

void setup() {
  s_begin(9600);
  Wire.begin();
  delay(1000); // Aguarda estabilização do barramento I2C

  iniciaLasers(); // Inicializa o sensor único
}

void loop() {
  seleciona_canal_multiplex(TCA1_END, 0x40); // Seleciona o canal do sensor
  float distancia = leituraDistancia(laser5);
  
  s_print("Distância Laser 3: ");
  s_print(distancia);
  s_println(" cm");

  delay(60);
  /*seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1); // Seleciona o canal do sensor
  float distancia = leituraDistancia(laser1);
  
  s_print("Distância Laser 1: ");
  s_print(distancia);
  s_println(" cm");

  delay(60);*/

  /*seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER2); // Seleciona o canal do sensor
  float distancia2 = leituraDistancia(laser2);
  
  s_print("Distância Laser 2: ");
  s_print(distancia2);
  s_println(" cm");

  delay(60);*/

  /*seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER3); // Seleciona o canal do sensor
  float distancia3 = leituraDistancia(laser3);
  
  s_print("Distância Laser 3: ");
  s_print(distancia3);
  s_println(" cm");

  delay(60);*/
}

// Seleciona o canal do multiplexador
void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t canal) {
  Wire.beginTransmission(endereco_multiplex);
  Wire.write(canal);
  Wire.endTransmission();
}

void iniciaLasers() {
  // Sensor 1 - Canal 2
  s_println("Ativando canal 2 do PCA9548A (Laser 1)...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  if (!laser1.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar VL53L0X no canal 2 (Laser 1).");
    while (1);
  }
  s_println("Laser 1 inicializado com sucesso!");

  // Sensor 2 - Canal 3
  s_println("Ativando canal 3 do PCA9548A (Laser 2)...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER2);
  if (!laser2.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar VL53L0X no canal 3 (Laser 2).");
    while (1);
  }
  s_println("Laser 2 inicializado com sucesso!");

  // Sensor 3 - Canal 4
  /*s_println("Ativando canal 4 do PCA9548A (Laser 3)...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER3);
  if (!laser3.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar VL53L0X no canal 4 (Laser 3).");
    while (1);
  }
  s_println("Laser 3 inicializado com sucesso!");*/
  
  // Sensor 4 - Canal 5
  s_println("Ativando canal 5 do PCA9548A (Laser 4)...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER4);
  if (!laser4.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar VL53L0X no canal 5 (Laser 4).");
    while (1);
  }
  s_println("Laser 4 inicializado com sucesso!");

  // Sensor 5 - Canal 6
  /*s_println("Ativando canal 6 do PCA9548A (Laser 5)...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER5);
  if (!laser5.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar VL53L0X no canal 6 (Laser 5).");
    while (1);
  }
  s_println("Laser 5 inicializado com sucesso!");*/

  // Sensor 6 - Canal 7
  s_println("Ativando canal 7 do PCA9548A (Laser 6)...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER6);
  if (!laser6.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar VL53L0X no canal 7 (Laser 6).");
    while (1);
  }
  s_println("Laser 6 inicializado com sucesso!");
}


// Realiza a leitura da distância
float leituraDistancia(Adafruit_VL53L0X &sensor) {
  VL53L0X_RangingMeasurementData_t medida;
  sensor.rangingTest(&medida, false);

  if (medida.RangeStatus != 4) {
    return medida.RangeMilliMeter / 10.0; // Retorna em centímetros
  } else {
    return -999; // Erro na leitura
  }
}
