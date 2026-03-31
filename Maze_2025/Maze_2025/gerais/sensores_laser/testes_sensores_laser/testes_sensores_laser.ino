#include <Wire.h>                  // Comunicação I2C
#include <Adafruit_VL53L0X.h>     // Biblioteca do sensor VL53L0X

// Endereços I2C dos multiplexadores e do sensor laser
#define TCA1_END 0x70
#define VL53L0X_END 0x29

// Canais do multiplexador 1 onde os lasers estão conectados
#define END_PORTA_LASER1 0x04
#define END_PORTA_LASER2 0x08
#define END_PORTA_LASER3 0x10
#define END_PORTA_LASER4 0x20
#define END_PORTA_LASER5 0x40
#define END_PORTA_LASER6 0x80

// Instâncias dos sensores VL53L0X
Adafruit_VL53L0X laser1 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser2 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser3 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser4 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser5 = Adafruit_VL53L0X();
Adafruit_VL53L0X laser6 = Adafruit_VL53L0X();

// Sessão do modo serial
#define modoSerial true // Ligar  ou desligar o modo serial para habilitar os diganósticos durante o código

#if modoSerial
  #define s_begin(x)  Serial.begin(x)
  #define s_print(x)  Serial.print(x)
  #define s_println(x) Serial.println(x)
#else
  #define s_begin(x)
  #define s_print(x)
  #define s_println(x)
#endif

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(1000); // Aguarda estabilização do barramento I2C

  iniciaLasers(); // Inicializa todos os sensores VL53L0X
}

void loop() {
  // Exemplo de leitura de todos os sensores
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  Serial.print("Distância Laser 1: ");
  Serial.println(leituraDistancia(laser1));
  delay(200);
  
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  Serial.print("Distância Laser 1: ");
  Serial.println(leituraDistancia(laser2));
  delay(200);

  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  Serial.print("Distância Laser 1: ");
  Serial.println(leituraDistancia(laser3));
  delay(200);
  
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  Serial.print("Distância Laser 1: ");
  Serial.println(leituraDistancia(laser4));
  delay(200);

  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  Serial.print("Distância Laser 1: ");
  Serial.println(leituraDistancia(laser5));
  delay(200);
  
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  Serial.print("Distância Laser 1: ");
  Serial.println(leituraDistancia(laser6));
  delay(200);
}

// Seleciona o canal do multiplexador
void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t canal) {
  Wire.beginTransmission(endereco_multiplex);
  Wire.write(canal);
  Wire.endTransmission();
}

void iniciaLasers() // Função que realiza as configurações iniciais dos sensores lasers conectados ao multiplexador i2c
{
    // Inicializando o primeiro sensor VL53L0X (Canal 2)
  s_println("Ativando o canal 2 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);  // Canal 2 (SD2 E SCL2)

  if (!laser1.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar o VL53L0X no Canal 2.");
    while (1); // Fica travado se o sensor falhar
  }
  s_println("Sensor VL53L0X 1 inicializado com sucesso!");

  // Inicializando o segundo sensor VL53L0X (Canal 3)
  s_println("Ativando o canal 3 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER2);  // Canal 3 (SDA3, SCL3)

  if (!laser2.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar o VL53L0X no Canal 1.");
    while (1); // Fica travado se o sensor falhar
  }
  s_println("Sensor VL53L0X 2 inicializado com sucesso!");

  // Inicializando o terceiro sensor VL53L0X (Canal 4)
  s_println("Ativando o canal 4 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER3);  // Canal 4 (SDA4, SCL4)

  if (!laser3.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar o VL53L0X no Canal 4.");
    while (1); // Fica travado se o sensor falhar
  }
  s_println("Sensor VL53L0X 3 inicializado com sucesso!");
  
  // Inicializando o quarto sensor VL53L0X (Canal 5)
  s_println("Ativando o canal 5 do PCA9548A");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER4);  // Canal 5 (SDA5, SCL5)

  if (!laser4.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar o VL53L0X no Canal 5.");
    while (1); // Fica travado se o sensor falhar
  }
  s_println("Sensor VL53L0X 4 inicializado com sucesso!");

  // Inicializando o quinto sensor VL53L0X (Canal 4)
  s_println("Ativando o canal 6 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER5);  // Canal 6 (SDA6, SCL6)

  if (!laser5.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar o VL53L0X no Canal 6.");
    while (1); // Fica travado se o sensor falhar
  }
  s_println("Sensor VL53L0X 5 inicializado com sucesso!");

  // Inicializando o sexto sensor VL53L0X (Canal 5)
  s_println("Ativando o canal 7 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER6);  // Canal 7 (SDA7, SCL7)

  if (!laser6.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar o VL53L0X no Canal 7.");
    while (1); // Fica travado se o sensor falhar
  }
  s_println("Sensor VL53L0X 6 inicializado com sucesso!");
  
}

// Realiza a leitura da distância de um sensor laser
float leituraDistancia(Adafruit_VL53L0X &sensor) {
  VL53L0X_RangingMeasurementData_t medida;
  sensor.rangingTest(&medida, false);

  if (medida.RangeStatus != 4) {
    return medida.RangeMilliMeter / 10.0; // Retorna em centímetros
  } else {
    return -999; // Erro na medição
  }
}
