// Inclusão de bibliotecas
#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include "mpu6050.h"

// Definições do endereço I2C do PCA9548A e dos sensores
#define TCA_ADDR 0x70          // Endereço I2C do PCA9548A
#define VL53L0X_ADDR 0x29     // Endereço I2C do VL53L0X

// Pinos relacionados aos motores
#define PINO_ENA 4  // Pino para controle de velocidade dos motores do lado esquerdo da ponte H
#define PINO_ENB 9  // Pino para controle de velocidade dos motores do lado direito da ponte H

// Pinos relacionados aos motores conectados a ponte H. Cada pino é referente a um motor da ponte H
#define PINO_IN1 5
#define PINO_IN2 6
#define PINO_IN3 7
#define PINO_IN4 8

// Instâncias para os sensores
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();  // Sensor VL53L0X 1
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();  // Sensor VL53L0X 2
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();  // Sensor VL53L0X 3

// Variáveis para controlar o tempo
unsigned long previousMillis = 0;
const long interval = 1000;  // Intervalo de 1 segundo para leitura dos sensores

int velocidadeMotores = 130;
int velocidadeCurva = 110;

void setup() {

  configuraTudo(); // Chama pela função que realiza a configuração inicial dos pinos e funções

  calibraGiroscopio(); // Chama pela função que configura e calibra o giroscópio para uso

  // Inicializando os sensores VL53L0X
  initVL53L0X();

}

void loop() {
  unsigned long currentMillis = millis();

  tca_select(0x10);
  mpu_loop();

  Serial.println(getAngleZ());

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

    Serial.println(getAngleZ());
   
    // Verifica o ângulo no eixo Z
    if(getAngleZ() > 66 || getAngleZ() < -66){

    Serial.println("O ângulo ultrapassou 90 graus, resetando...");
    delay(4500); // Aguarda 2 segundos antes de resetar

    // Reseta o MPU6050
    tca_select(0x10);
    mpu_reset();
    }

    delay(600);

    //paraFrente();

}

void configuraTudo(){

  Serial.begin(9600);  // Inicializa a comunicação serial

  Wire.begin();  // Inicializa o barramento I2C

  delay(2000);  // Espera 2 segundos para garantir que a comunicação serial e i2c estejam prontas

  // Configuração dos pinos dos motores como saída
  pinMode(PINO_ENA, OUTPUT);
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);

}

void calibraGiroscopio(){

  tca_select(0x10);
  mpu_begin();

  mpu_calibrate(200);

  mpu_reset();

  Serial.println("Iniciando o PCA9548A e sensores...");

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

void paraFrente() {

  // Declaração de variáveis
  unsigned long tempoDeInicioMotor;
  unsigned long tempoDeRotacao = 3000;
 
  // Configura os motores para o sentido horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotores);
  analogWrite(PINO_ENB, velocidadeMotores);
/*
    // Verifica se o tempo de movimento foi alcançado
  if (millis() - tempoDeInicioMotor >= tempoDeRotacao) {

    pararMotores();  // Para os motores quando o tempo de movimento for alcançado
    Serial.println("motores parados!!!");
    delay(2500);  // Faz o robô aguardar 5 segundos parado antes de ir à próxima ação
    tempoDeInicioMotor = millis();  // Armazena o tempo de inicio
    
  }
  */

}

void paraTras() {
  // Configura os motores para girar no sentido anti-horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotores);
  analogWrite(PINO_ENB, velocidadeMotores);
}

void virarDireita() {
  // Configura 2 motores para girar no sentido anti-horário e 2 para girar sentido horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeCurva);
  analogWrite(PINO_ENB, velocidadeCurva);
}

void virarEsquerda() {
  // Configura 2 motores para o sentido horário e 2 para o sentido anti-horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);

  // Configura a velocidade dos motores sendo 70
  analogWrite(PINO_ENA, velocidadeCurva);
  analogWrite(PINO_ENB, velocidadeCurva);
}

void pararMotores() {
  // Configura os 4 motores para pararem de girar
  digitalWrite(PINO_IN1, LOW);
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores como 0
  analogWrite(PINO_ENA, 0);
  analogWrite(PINO_ENB, 0);
}