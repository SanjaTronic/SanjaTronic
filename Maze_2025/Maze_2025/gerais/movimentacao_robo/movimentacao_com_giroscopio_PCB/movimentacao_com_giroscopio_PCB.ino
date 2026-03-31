/*
=================================================================== TESTE LÓGICA DE ISOLAMENTO DE CURVA ========================================================================================
Autor: Murilo
Data da criação: 26/06/2025
Data da última modificação: 26/06/2025

Campo de observações:

giroscópio:
Direita -> Positivo (soma o ângulo)
Esquerda -> Negativo (subtrai o ângulo) 
===========================================================================================================================================================================================================
*/

// Inclusão de bibliotecas
#include <Wire.h> // Biblioteca para uso do I2C
#include <Adafruit_VL53L0X.h> // Biblioteca para uso dos sensores lasers
#include "mpu6050.h" // Biblioteca para uso do giroscópio e do acelerôemtro

// Declaração de pinos
// Declaracao dos pinos utilizados para controlar a velocidade de rotacao
#define PINO_ENA 18
#define PINO_ENB 19
#define PINO_IN1 16
#define PINO_IN2 14
#define PINO_IN3 15
#define PINO_IN4 17

// Declaração de pinos relacionados ao multiplexador I2C os sensores conectados a ele
#define TCA1_END 0x70      // Endereço I2C do multiplexador 1
#define VL53L0X_END 0x29  // Endereço I2C do sensor VL53L0X

// Declaração de endereços i2c das portas dos multiplexadores
#define END_PORTA_GIROSCOPIO 0x02
#define END_PORTA_LASER1 0x04
#define END_PORTA_LASER2 0x08
#define END_PORTA_LASER3 0x10
#define END_PORTA_LASER4 0x20
#define END_PORTA_LASER5 0x40
#define END_PORTA_LASER6 0x80

// Varáveis
// Declaração de variáveis que serão correspondentes a velocidade dos motores
const int velMotoresEsq = 150;
const int velMotoresDir = 150;
const int velMotoresEsqCurva = 180;
const int velMotoresDirCurva = 180;

// Variáveis das distâncias dos lasers
float dist1;
float dist2;
float dist3;
float dist4;
float dist5;
float dist6;

// Instâncias para os sensores
Adafruit_VL53L0X laser1 = Adafruit_VL53L0X();  // Sensor VL53L0X 1
Adafruit_VL53L0X laser2 = Adafruit_VL53L0X();  // Sensor VL53L0X 2
Adafruit_VL53L0X laser3 = Adafruit_VL53L0X();  // Sensor VL53L0X 3
Adafruit_VL53L0X laser4 = Adafruit_VL53L0X();  // Sensor VL53L0X 4
Adafruit_VL53L0X laser5 = Adafruit_VL53L0X();  // Sensor VL53L0X 5
Adafruit_VL53L0X laser6 = Adafruit_VL53L0X();  // Sensor VL53L0X 6

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

void setup() 
{

  s_begin(9600); // Inicializa o monitor serial
  Wire.begin(); // Inicializa o barramento i2c
  delay(1000); // Espera de 1 segundo para garantir que a comunicação i2c esteja pronta
  
  s_println("iniciando o multiplex e sensores...");

  iniciaLasers(); // Chama pela função que inicializa os sensores VL53L0X
  iniciaGiroscopio(); // Chama pela função que inicializa o sensor giroscópio conectado ao multiplex

  //configuração dos pinos como saida
  pinMode(PINO_ENA, OUTPUT); 
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);

  //inicia o codigo com os motores parados
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
  digitalWrite(PINO_ENA, LOW);
  digitalWrite(PINO_ENB, LOW);

}

void loop() 
{
  paraFrente();
  delay(2000);
  virarEsquerda90G();
  virarDireita90G();
}

// Funções
void iniciaGiroscopio()
{
  // Inicializando o MPU6050 via multiplexador (Canal 4)
  s_println("Inicializando o MPU6050 via multiplex...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO);  // Canal 4 (SDA4, SCL4)
  mpu_begin();  // Inicializa o MPU6050
  mpu_calibrate(200);  // Calibra o giroscópio para uso
  mpu_reset();  // Reseta o MPU6050
  s_println("MPU6050 inicializado com sucesso!");
}

void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t canal) {

  Wire.beginTransmission(endereco_multiplex);
  Wire.write(canal); // ativa apenas o canal desejado
  Wire.endTransmission();

}

// Função para ler e imprimir a distância do sensor
float leituraDistancia(Adafruit_VL53L0X &sensor) 
{
    VL53L0X_RangingMeasurementData_t medir;
    
    // Realiza a medição de distância
    sensor.rangingTest(&medir, false);
    
    // Verifica se a medição foi bem-sucedida
    if (medir.RangeStatus != 4) // Se o status da medição não for erro
    {  
        return medir.RangeMilliMeter / 10.0; // Retorna em centímetros
        s_print("Distância: ");
        s_print(medir.RangeMilliMeter / 10.0);  // Converte de mm para cm
        s_println(" cm");
    } 
    else // Caso o status de medição seja mal sucedido
    {
      s_println("Erro ao medir a distância.");
      return -1; // valor de erro
    }
}

void iniciaLasers()
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

void paraFrente()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsq);
  analogWrite(PINO_ENB, velMotoresDir);

  //configura os motores para o sentido horario
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void paraTras()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsq);
  analogWrite(PINO_ENB, velMotoresDir);

  //configura os motores para o sentido anti-horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);
}
void virarEsquerda()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsqCurva);
  analogWrite(PINO_ENB, velMotoresDirCurva);

  //configura os motores para 2 girarem no sentido horário e 2 no anti-horário (curva)
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);
}
void virarDireita()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsqCurva);
  analogWrite(PINO_ENB, velMotoresDirCurva);

  //configura os motores para 2 girarem no sentido horário e 2 no anti-horário (curva)
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void virarEsquerda90G()
{
  seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO); // Chama pela função que prepara o giroscópio do multiplex para uso
  mpu_reset(); // Reseta o ângulo do giroscópio

  while(true) // Inicia um loop para isolar a execução do giroscópio
  {
    mpu_loop(); // Executa a lógica do giroscópio

    // Verifica a angulação do giorscópio
    if(getAngleZ() < -85) // Caso o giroscópio ultrapasse 90 graus negativo (finaliza uma curva a esquerda)
    {
      s_println("o ângulo ultrapassou -85 graus, resetando o giroscópio...");
      pararMotores();
      delay(50);
      break; // Sai do loop do while
    }
    else // Caso o ângulo do giroscópio ainda não tenha 
    {
      s_println(getAngleZ()); // Exibe a posição atual do giroscópio
      delay(10);
      virarEsquerda();    
    }

  }
}

void virarDireita90G()
{
  seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO); // Chama pela função que prepara o giroscópio do multiplex para uso
  mpu_reset(); // Reseta o ângulo do giroscópio

  while(true) // Inicia um loop para isolar a execução do giroscópio
  {
    mpu_loop(); // Executa a lógica do giroscópio

    // Verifica a angulação do giroscópio
    if(getAngleZ() > 85) // Caso o giroscópio ultrapasse 90 graus negativo (finaliza uma curva a direita)
    {
      s_print("o ângulo ultrapassou 85 graus, resetando...");
      pararMotores();
      delay(50);
      break; // Sai do loop do while
    }
    else // Caso o ângulo do giroscópio ainda não tenha chegado a 90 graus
    {
      s_println(getAngleZ()); // Exibe a psoição giroscópio
      delay(10);
      virarDireita();    
    }

  }
}
void pararMotores()
{
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
}
void testeGeral()
{
  paraFrente();
  delay(3000);
  pararMotores();
  delay(1000);
  paraTras();
  delay(3000);
  pararMotores();
  delay(1000);
  virarEsquerda();
  delay(3000);
  pararMotores();
  delay(1000);
  virarDireita();
  delay(3000);
  pararMotores();
  delay(1000);
}