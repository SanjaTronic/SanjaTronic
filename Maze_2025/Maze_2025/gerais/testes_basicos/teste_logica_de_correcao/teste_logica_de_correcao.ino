/*
========================================================================= CAMPO DE OBSERVAÇÕES ===============================================================================================
Informações sobre o acelerômetro e o giroscópio:
  getAngleX(); Captura o ângulo do eixo X do acelerômetro (rotações para cima ou para baixo)
  getAngleZ(); Captura o ângulo do eixo Z do giroscópio (rotações à esquerda ou à direita)

Robô de teste:
  motores 1 e 3 girar no sentido contrários dos demais motores, montagem invertida;
  teste de sentido dos motores: OK;
  teste do sensor giroscópio: OK;
  teste dos sensores lasers: Realizar;
  teste de movimentação "oficial": Realizar;

Informações sobre os sensores lasers:
  laser1 = laser na parte fronatl do robô
  laser2 = laser na parte esquerda do robô
  laser3 = laser na parte direita do robô

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
==============================================================================================================================================================================================
*/
// Inclusão de bibliotecas
#include <AFMotor.h>  // Biblioteca para uso da shield da ponte H L293D
#include <Wire.h> // Biblioteca para uso da comunicação i2c
#include "mpu6050.h" // Biblioteca para uso acelerômetro e giroscópio
#include <Adafruit_VL53L0X.h> // Biblioteca para uso do sensor laser VL53L0X

// Definição de endereços I2C
#define TCA1_END 0x70 // Endereço I2C do multiplexador
#define GIROSCOPIO 0x80 // Endereço do canal SD7 e SC7 do multiplexador
#define VL53L0X_END 0X29 // Endereço I2C do sensor laser
#define LASER1_END 0x01 // Endereços I2C da porta 0 do multiplexador
#define LASER2_END 0X02 // Endereço I2C da porta 1 do multiplexador
#define LASER3_END 0x04 // Endereço I2C da porta 2 do multiplexador

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

// Instâncias para os sensores lasers
Adafruit_VL53L0X laser1 = Adafruit_VL53L0X(); // Sensor laser 1
Adafruit_VL53L0X laser2 = Adafruit_VL53L0X(); // Sensor laser 2
Adafruit_VL53L0X laser3 = Adafruit_VL53L0X(); // Sensor laser 3

// Inicializa os motores conectados às portas M1, M2, M3 e M4
AF_DCMotor motor1(1); // Motor conectado na porta M1 da shield
AF_DCMotor motor2(2); // Motor conectado na porta M2 da shield
AF_DCMotor motor3(3); // Motor conectado na porta M3 da shield
AF_DCMotor motor4(4); // Motor conectado na porta M4 da shield

// definição de váriáveis relacionadas a velocidade dos motores 
int velocidadeM1 = 120; // Variável que contém a velocidade do motor conectado à porta M1
int velocidadeM2 = 180; // Váriavel que contém a velocidade do motor conectado à porta M2
int velocidadeM3 = 120; // Variável que contém a velocidade do motor conectado à porta M3
int velocidadeM4 = 180; // Variável que contém a velocidade do motor conectado à porta M4

// definição de variáveis relacionadas a velocidade dos motores durante o momento da curva
int velocidadeCurvaM1 = 190; // Variável que contém a velocidade do motor conectado à porta M1 da shield durante uma curva
int velocidadeCurvaM2 = 190; // Variável que contém a velocidade do motor conectado à porta M2 da shield durante uma curva
int velocidadeCurvaM3 = 190; // Variável que contém a velocidade do motor conectado à porta M3 da shield durante uma curva
int velocidadeCurvaM4 = 190; // Variável que contém a velocidade do motor conectado a porta M4 da shield durante uma curva

void setup() 
{
  
  configura_tudo(); // Chama pela função que realiza as configurações inicias dos componentes
  
}

void loop() 
{
  

}

// Declaração de funções
void configura_tudo()
{

  diagnostico_begin(9600); // Inicializa a comunicação serial
  Wire.begin(); // Inicia o barramento I2C

  // Configura o o giroscópio na porta 0 do multiplexador
  seleciona_canal_multiplex(TCA1_END, GIROSCOPIO); // Seleciona o canal do multiplex onde o giroscópio está conectado
  mpu_begin(); // Inicia o giroscópio
  mpu_calibrate(200); // Calibra o grioscópio para uso
  mpu_reset(); // Reseta o ângulo do giroscópio para 0

  delay(1000); // Espera 1 segundo antes de continuar o código

  inicia_lasers(); // Chama pela função que realiza as configurações iniciais dos sensores lasers

}

float leitura_distancia(Adafruit_VL53L0X &sensor) 
{

  VL53L0X_RangingMeasurementData_t medir;
  
  sensor.rangingTest(&medir, false);
  
  if (medir.RangeStatus != 4) 
  {
    return medir.RangeMilliMeter / 10.0;  // retorna a distância do laser em cm
  } 
  else 
  {
    return -1.0;  // Retorna -1 em caso de erro
  }

}

void paraFrente() 
{

  motor1.run(BACKWARD); // Gira o motor 1 no sentido horário
  motor2.run(FORWARD);  // Gira o motor 2 no sentido horário
  motor3.run(BACKWARD);  // Gira o motor 3 no sentido horário
  motor4.run(FORWARD); // Gira o motor 4 no sentido horário

  // Define a velocidade que os motores irão rotacionar
  motor1.setSpeed(velocidadeM1);
  motor2.setSpeed(velocidadeM2);
  motor3.setSpeed(velocidadeM3);
  motor4.setSpeed(velocidadeM4);

}

void pararMotores() 
{

  // Para de enviar energia aos quatro motores, parando sua rotação
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

}

void virarEsquerda() 
{

  motor1.run(FORWARD);  // Rotaciona o motor 1 no sentido anti-horário
  motor2.run(FORWARD);  // Rotaciona o motor 2 no sentido horário
  motor3.run(FORWARD);  // Rotaciona o motor 3 no sentido horário
  motor4.run(FORWARD);  // Rotaciona o motor 4 no sentido anti-horário

  // Define a velocidade dos motores durante o movimento de curva
  motor1.setSpeed(velocidadeCurvaM1); 
  motor2.setSpeed(velocidadeCurvaM2);   
  motor3.setSpeed(velocidadeCurvaM3);  
  motor4.setSpeed(velocidadeCurvaM4); 

}

// Função para virar à direita com maior velocidade
void virarDireita() 
{

  motor1.run(BACKWARD); // Rotaciona o motor 1 no sentido horário
  motor2.run(BACKWARD); // Rotaciona o motor 2 no sentido anti-horário 
  motor3.run(BACKWARD); // Rotaciona o motor 3 no sentido anti-horário
  motor4.run(BACKWARD); // Rotaciona o motor 4 no sentido horário

  // Define a velocidade dos motores durante o movimento de curva
  motor1.setSpeed(velocidadeCurvaM1);  
  motor2.setSpeed(velocidadeCurvaM2);  
  motor3.setSpeed(velocidadeCurvaM3); 
  motor4.setSpeed(velocidadeCurvaM4);

}

// Função para virar à esquerda de acordo com o giroscópio
void virarEsquerda90G()
{

  while(true)
  {

    seleciona_canal_multiplex(TCA1_END, GIROSCOPIO);
    mpu_loop(); // Executa a lógica do giroscópio

    // Verifica se o ângulo do giroscópio é menor ou igual a -90 graus
    if(getAngleZ() >= 80) // Caso o Ângulo do giroscópio seja menor ou igual a -90 graus
    { 

      diagnostico_println("o angulo passou de 90 graus, resetando...");
      pararMotores(); // Chama pela função que para os motores
      //delay(3000);
      seleciona_canal_multiplex(TCA1_END, GIROSCOPIO); // Seleciona o canal do multiplex onde o giroscópio está conectado
      mpu_reset(); // Reseta o ângulo do giroscópio para 0 graus
      break; // Sai do loop do while

    } 
    else // Caso o ângulo ainda não seja menor ou igual a -90 graus
    { 

      virarEsquerda();

      diagnostico_println(getAngleZ());
      
    }
  }

}

// Função para virar à direita de acordo com o giroscópio
void virarDireita90G()
{

  while(true)
  {

    seleciona_canal_multiplex(TCA1_END, GIROSCOPIO);
    mpu_loop(); // Executa a lógica do giroscópio

    // Verifica se o ângulo do giroscópio é menor ou igual a -90 graus
    if(getAngleZ() <= -80)
    { // Caso o Ângulo do giroscópio seja menor ou igual a -90 graus

      diagnostico_println("o angulo passou de menos 90 graus, resetando...");
      pararMotores(); // Chama pela função que para os motores
      //delay(3000);
      seleciona_canal_multiplex(TCA1_END, GIROSCOPIO); // Seleciona o canal do multiplex onde o giroscópio está conectado
      mpu_reset(); // Reseta o ângulo do giroscópio para 0 graus
      break;

    }
    else 
    { // Caso o ângulo ainda não seja menor ou igual a -90 graus

      virarDireita();

      diagnostico_println(getAngleZ());
      delay(50);

    }
  }

}

// Função para andar para trás
void paraTras() 
{

  motor1.run(FORWARD);  // Rotaciona o motor 1 no sentido anti-horário
  motor2.run(BACKWARD); // Rotaciona o motor 2 no sentido anti-horário
  motor3.run(FORWARD); // Rotaciona o motor 3 no sentido anti-horário
  motor4.run(BACKWARD);  // Rotaciona o motor 4 no sentido anti-horário

  // Define a velocidade dos motores durante o movimento da curva
  motor1.setSpeed(velocidadeM1);
  motor2.setSpeed(velocidadeM2);
  motor3.setSpeed(velocidadeM3);
  motor4.setSpeed(velocidadeM4);

}

void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t endereco_canal) 
{
  Wire.beginTransmission(endereco_multiplex);
  Wire.write(endereco_canal); // ativa apenas o canal desejado
  Wire.endTransmission(); // Encerra a atividade do canal
}

void inicia_lasers() 
{
  // Inicializando o primeiro sensor VL53L0X (Canal 0)
  diagnostico_println("Ativando o canal 0 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, 0x01);  // Canal 0 (SDA0, SCL0)

  if (!laser1.begin(VL53L0X_END)) 
  {
    diagnostico_println("Falha ao inicializar o VL53L0X no Canal 0.");
    while (1); // Fica travado se o sensor falhar
  }
  diagnostico_println("Sensor VL53L0X 1 inicializado com sucesso!");

  // Inicializando o segundo sensor VL53L0X (Canal 1)
  diagnostico_println("Ativando o canal 1 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, 0x02);  // Canal 1 (SDA1, SCL1)

  if (!laser2.begin(VL53L0X_END)) 
  {
    diagnostico_println("Falha ao inicializar o VL53L0X no Canal 1.");
    while (1); // Fica travado se o sensor falhar
  }
  diagnostico_println("Sensor VL53L0X 2 inicializado com sucesso!");

  // Inicializando o terceiro sensor VL53L0X (Canal 2)
  diagnostico_println("Ativando o canal 2 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, 0x04);  // Canal 2 (SDA2, SCL2)

  if (!laser3.begin(VL53L0X_END)) 
  {
    diagnostico_println("Falha ao inicializar o VL53L0X no Canal 2.");
    while (1); // Fica travado se o sensor falhar
  }
  diagnostico_println("Sensor VL53L0X 3 inicializado com sucesso!");

}
