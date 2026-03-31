#include <Wire.h>
#include "mpu6050.h" // Biblioteca do giroscópio

// Endereços e definições do multiplexador e giroscópio
#define TCA1_END 0x70 // Endereço I2C do multiplexador
#define END_PORTA_GIROSCOPIO 0x02 // Canal do giroscópio no multiplexador

// Declaracao dos pinos utilizados para controlar a velocidade de rotacao
#define PINO_ENA 18
#define PINO_ENB 19
#define PINO_IN1 16
#define PINO_IN2 14
#define PINO_IN3 15
#define PINO_IN4 17

// Constantes de ângulo
const int grausGiroE = -85;
const int grausGiroD = 85;

// Declaração de variáveis que serão correspondentes a velocidade dos motores
const int velMotoresEsq = 140;
const int velMotoresDir = 250;
const int velMotoresEsqCurva = 200;
const int velMotoresDirCurva = 230;

// Serial debug
#define modoSerial true

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
  s_begin(9600);
  Wire.begin();
  delay(1000);
  iniciaGiroscopio(); // Inicializa o giroscópio

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

void loop() {
  seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO);

  mpu_loop();
  float anguloE = getAngleZ();
  s_print("Ângulo Z: ");
  s_println(anguloE);

  paraFrente();

  if(anguloE < -2)
  {
    virarDireita();
  }
  else if(anguloE > 2)
  {
    virarEsquerda();
  }

 

}

void iniciaGiroscopio() {
  s_println("Inicializando o MPU6050 via multiplex...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO);
  mpu_begin();
  mpu_calibrate(200);
  mpu_reset();
  s_println("MPU6050 inicializado com sucesso!");
}

void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t canal) {
  Wire.beginTransmission(endereco_multiplex);
  Wire.write(canal);
  Wire.endTransmission();
}

void paraFrente()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsq);
  analogWrite(PINO_ENB, velMotoresDir);

  //configura os motores para o sentido horario
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void paraTras()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsq);
  analogWrite(PINO_ENB, velMotoresDir);

  //configura os motores para o sentido anti-horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
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
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void virarDireita()
{
  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velMotoresEsqCurva);
  analogWrite(PINO_ENB, velMotoresDirCurva);

  //configura os motores para 2 girarem no sentido horário e 2 no anti-horário (curva)
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);
}
void pararMotores()
{
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
}