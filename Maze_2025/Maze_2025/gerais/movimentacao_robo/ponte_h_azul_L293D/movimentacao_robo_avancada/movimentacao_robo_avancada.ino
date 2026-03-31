// Inclusão de bibliotecas
#include <Wire.h>     // Biblioteca para uso da comunicação I2C
#include "mpu6050.h"  // Biblioteca para uso do sensor giroscópio mpu6050
#include <Adafruit_VL53L0X.h>  // Biblioteca para uso dos sensores lasers VL53L0X

// Definição de pinos
#define TCA_ADDR 0x70 // Endereço I2C do PCA9458A
#define VL53L0X_ADDR 0x29     // Endereço I2C do VL53L0X

// Pinos relacionados aos motores
#define PINO_ENA 4  // Pino para controle de velocidade dos motores do lado esquerdo da ponte H
#define PINO_ENB 9  // Pino para controle de velocidade dos motores do lado direito da ponte H

// Pinos relacionados aos motores conectados a ponte H. Cada pino é referente a um motor da ponte H
#define PINO_IN1 5
#define PINO_IN2 6
#define PINO_IN3 7
#define PINO_IN4 8

// Declaração de variáveis
int velocidadeMotorA = 111; // Motores do Lado direito do robô
int velocidadeMotorB = 103; // Motores do lado esquerdo do robô
int velocidadeCurva = 103;  // Velocidade padrão 100 ou 110

// Instâncias para os sensores
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();  // Sensor VL53L0X 1
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();  // Sensor VL53L0X 2
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();  // Sensor VL53L0X 3

// Variáveis para controlar o tempo
unsigned long previousMillis = 0;
const long interval = 1000;  // Intervalo de 1 segundo para leitura dos sensores

void setup() {

  Serial.begin(9600); // Inicializa a comunicação serial
  Wire.begin(); // Inicia o barramento I2C
  delay(2000); // Atraso de 2 segundos para garantir que a comunicação esteja pronta

  initVL53L0X();

  tca_select(0x10); // 0x10 ativa o canal 4 (SDA4, SCL4)
  mpu_begin();  // Inicia o giroscópio

  mpu_calibrate(200); // Calibra o giroscópio para uso

  delay(2000);

  mpu_reset();  // Reseta o grioscópio

  // Configuração dos pinos dos motores como saída
  pinMode(PINO_ENA, OUTPUT);
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);
  
}

void loop() {

  unsigned long currentMillis = millis();

  VL53L0X_RangingMeasurementData_t measure1;
  VL53L0X_RangingMeasurementData_t measure2;
  VL53L0X_RangingMeasurementData_t measure3;

    if (currentMillis - previousMillis >= interval) {

    // Atualiza o tempo da última leitura
    previousMillis = currentMillis;

    // Executa a lógica do MPU6050
    mpu_loop();

      float distancia1 = measure1.RangeMilliMeter / 10.0;
      float distancia2 = measure2.RangeMilliMeter / 10.0;
      float distancia3 = measure3.RangeMilliMeter / 10.0;

      
      Serial.print("Distancia1: ");
      Serial.println(distancia1);
      Serial.print(" Distancia2: ");
      Serial.println(distancia2);
      Serial.print(" Distancia3: ");
      Serial.println(distancia3);
      Serial.print("Ângulo: ");
      Serial.println(getAngleZ());
      
      if ((distancia1 < 500) && (distancia2 > distancia3)) {

        pararMotores();
        delay(200);
        paraTras();
        delay(250);
        virarDireitaGiroscopio();

      } else if ((distancia1 < 500) && (distancia3 > distancia2)) {

        pararMotores();
        delay(200);
        paraTras();
        delay(250);
        virarEsquerdaGiroscopio();

      } else if((distancia2 > distancia3) && (distancia2 > distancia1)){

        pararMotores();
        delay(200);
        virarDireitaGiroscopio();
        paraFrente();
        //delay(2650);
        pararMotores();
        delay(100);

      } else if((distancia3 > distancia2) && (distancia3 > distancia1)){

        pararMotores();
        delay(200);
        //virarEsquerdaGiroscopio();
        paraFrente();
        //delay(2650);
        pararMotores();
        delay(100);

      }
      else {

        paraFrente();
        //delay(2650);
        pararMotores();
        //delay(2000);

      }
    }
    }  
// Definições de funções
void tca_select(uint8_t port) {

  Wire.beginTransmission(TCA_ADDR);  // Inicilaiza a comunicação da porta do pca com o endereço especificado
  Wire.write(port);  // Envia o byte para selecionar o canal
  Wire.endTransmission();  // Encerra a comunicação com o pca

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

void paraFrente() {  
  // Configura os motores para o sentido horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotorA);
  analogWrite(PINO_ENB, velocidadeMotorB);
}

void paraTras() {
  // Configura os motores para girar no sentido anti-horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotorA);
  analogWrite(PINO_ENB, velocidadeMotorB);
}

void virarDireita() {
  // Configura 2 motores para girar no sentido anti-horário e 2 para girar sentido horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotorA);
  analogWrite(PINO_ENB, velocidadeMotorB);
}

void virarEsquerda() {
  // Configura 2 motores para o sentido horário e 2 para o sentido anti-horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotorA);
  analogWrite(PINO_ENB, velocidadeMotorB);
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
void virarDireitaGiroscopio() {
  while(true) {
    tca_select(0x10);  // Seleciona o canal 4 (SDA4, SCL4)
    mpu_loop();        // Atualiza os dados do MPU6050

    // Exibe o valor do ângulo Z no monitor serial
    Serial.print("Angulo Z: ");
    Serial.println(getAngleZ());

    // Verifica o ângulo no eixo Z
    if(getAngleZ() > 66 || getAngleZ() < -66){
      //Serial.println("O ângulo ultrapassou 90 graus, resetando...");
      pararMotores();
      delay(100);        
      mpu_reset();
      delay(50);
      break; 
    } else{
      virarDireita();
    }


  }
}

void virarEsquerdaGiroscopio() {
  while(true) {
    tca_select(0x10);  // Seleciona o canal 4 (SDA4, SCL4)
    mpu_loop();        // Atualiza os dados do MPU6050

    // Exibe o valor do ângulo Z no monitor serial
    Serial.print("Angulo Z: ");
    Serial.println(getAngleZ());

    // Verifica o ângulo no eixo Z
    if(getAngleZ() > 66 || getAngleZ() < -66){
      //Serial.println("O ângulo ultrapassou 90 graus, resetando...");
      pararMotores();
      delay(100);        
      mpu_reset();
      delay(50);
      break; 
    } else{
      virarEsquerda();
    }


  }
}