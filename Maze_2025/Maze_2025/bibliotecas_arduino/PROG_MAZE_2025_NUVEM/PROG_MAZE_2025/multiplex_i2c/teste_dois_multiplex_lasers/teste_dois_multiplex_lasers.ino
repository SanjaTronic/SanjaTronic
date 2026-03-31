/*
==================================================================== TESTE DOIS MULTIPLEXADORES I2C =======================================================================================
Autor: Murilo
Data da criação: 16/04/2025
Data da última modificação: 16/04/2025

Campo de observações:
endereços portas I2C do multiplexador PCA9458A:
Canal | Hexadecimal
0     |  0x01
1     |  0x02
2     |  0x04
3     |  0x08
4     |  0x10
5     |  0x20
6     |  0x40
7     |  0x80
===========================================================================================================================================================================================
*/

// Inclusão de bibliotecas
#include <Wire.h> // Biblioteca para uso do I2C
#include <Adafruit_VL53L0X.h> // Biblioteca para uso do sensor laser VL53L0X

// Definição de endereços I2C
#define TCA1_END 0x70 // Endereço I2C do multiplexador 1
#define TCA2_END 0x71 // Endereço I2C do multiplexador 2
#define VL53L0X_END 0x29 // Endereço I2C do sensor laser

// Instâncias para os sensores lasers
Adafruit_VL53L0X laser1 = Adafruit_VL53L0X(); // Sensor VL53L0X 1
Adafruit_VL53L0X laser2 = Adafruit_VL53L0X(); // Sensor VL53L0X 2
Adafruit_VL53L0X laser3 = Adafruit_VL53L0X(); // Sensor VL53L0X 3
/*
Adafruit_VL53L0X laser4 = Adafruit_VL53L0X(); // Sensor VL53L0X 4
Adafruit_VL53L0X laser5 = Adafruit_VL53L0X(); // Sensor VL53L0X 5
Adafruit_VL53L0X laser6 = Adafruit_VL53L0X(); // Sensor VL53L0X 6
*/

// Sessão do modo de diagnostico
#define modo_diagnostico true // Ligar ou desligar o modo diagnostico, use false para desligar e true para ligar o modo diagnostico

#if modo_diagnostico
  #define diagnostico_begin(x) Serial.begin(x)
  #define diagnostico_print(x) Serial.print(x)
  #define diagnostico_println(x) Serial.println(x)
#else
  #define diagnostico_begin(x)
  #define diagnostico_print(x)
  #define diagnostico_println(x)
#endif

void setup() {

  diagnostico_begin(9600); // Inicia a comunicação serial
  Wire.begin(); // Inicia o barramento I2C

  inicia_lasers(); // Chama pela função que inicializa os sensores lasers
  
}
void loop(){

  leitura_distancia(laser1); // Chama pela função que mede e imprime a dsitÂncia do sensor laser no monitor serial

}

// Declaração de funções
void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t canal) {

  Wire.beginTransmission(endereco_multiplex);
  Wire.write(canal); // ativa apenas o canal desejado
  Wire.endTransmission();

}

// Função para ler e imprimir a distância do sensor
void leitura_distancia(Adafruit_VL53L0X &sensor) {
  VL53L0X_RangingMeasurementData_t medir;
  
  // Realiza a medição de distância
  sensor.rangingTest(&medir, false);
  
  // Verifica se a medição foi bem-sucedida
  if (medir.RangeStatus != 4) {  // Se o status da medição não for erro
    diagnostico_print("Distância: ");
    diagnostico_print(medir.RangeMilliMeter / 10.0);  // Converte de mm para cm
    diagnostico_println(" cm");
  } else {
    diagnostico_println("Erro ao medir a distância.");
  }
}

// Função para inicializar os sensores VL53L0X nos canais do PCA9548A
void inicia_lasers() {

  // Inicializando o primeiro sensor VL53L0X (Canal 0)
  diagnostico_println("Ativando o canal 0 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, 0x01);  // Canal 0 (SDA0, SCL0)

  if (!laser1.begin(VL53L0X_END)) {
    diagnostico_println("Falha ao inicializar o VL53L0X no Canal 0.");
    while (1); // Fica travado se o sensor falhar
  }
  diagnostico_println("Sensor VL53L0X 1 inicializado com sucesso!");

  // Inicializando o segundo sensor VL53L0X (Canal 1)
  diagnostico_println("Ativando o canal 1 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, 0x02);  // Canal 1 (SDA1, SCL1)

  if (!laser2.begin(VL53L0X_END)) {
    diagnostico_println("Falha ao inicializar o VL53L0X no Canal 1.");
    while (1); // Fica travado se o sensor falhar
  }
  diagnostico_println("Sensor VL53L0X 2 inicializado com sucesso!");

  // Inicializando o terceiro sensor VL53L0X (Canal 2)
  diagnostico_println("Ativando o canal 2 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, 0x04);  // Canal 2 (SDA2, SCL2)

  if (!laser3.begin(VL53L0X_END)) {
    diagnostico_println("Falha ao inicializar o VL53L0X no Canal 2.");
    while (1); // Fica travado se o sensor falhar
  }
  diagnostico_println("Sensor VL53L0X 3 inicializado com sucesso!");
  /*
  // Inicializando o quarto sensor VL53L0X (Canal 3)
  diagnostico_println("Ativando o canal 3 do PCA9548A");
  seleciona_canal_multiplex(TCA1_END, 0x08);  // Canal 3 (SDA3, SCL3)

  if (!laser4.begin(VL53L0X_END)) {
    diagnostico_println("Falha ao inicializar o VL53L0X no Canal 3.");
    while (1); // Fica travado se o sensor falhar
  }
  diagnostico_println("Sensor VL53L0X 4 inicializado com sucesso!");

  // Inicializando o quinto sensor VL53L0X (Canal 4)
  diagnostico_println("Ativando o canal 4 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, 0x10);  // Canal 4 (SDA4, SCL4)

  if (!laser5.begin(VL53L0X_END)) {
    diagnostico_println("Falha ao inicializar o VL53L0X no Canal 5.");
    while (1); // Fica travado se o sensor falhar
  }
  diagnostico_println("Sensor VL53L0X 4 inicializado com sucesso!");

  // Inicializando o sexto sensor VL53L0X (Canal 5)
  diagnostico_println("Ativando o canal 5 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, 0x20);  // Canal 5 (SDA5, SCL5)

  if (!laser6.begin(VL53L0X_END)) {
    diagnostico_println("Falha ao inicializar o VL53L0X no Canal 6.");
    while (1); // Fica travado se o sensor falhar
  }
  diagnostico_println("Sensor VL53L0X 6 inicializado com sucesso!");
  */

}
