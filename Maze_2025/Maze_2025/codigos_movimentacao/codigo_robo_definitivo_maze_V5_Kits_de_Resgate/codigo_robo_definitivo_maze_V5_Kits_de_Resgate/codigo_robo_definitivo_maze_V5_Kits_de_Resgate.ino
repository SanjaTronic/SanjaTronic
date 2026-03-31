/*
========================================================================= ROBÔ DEFINITIVO MAZE V5.0 ========================================================================================
Autor: Murilo
Data da criação: 21/07/2025
Data da última modificação: 02/09/2025

Campo de observações:

pares de velocidades dos motores:
lado esquerdo | lado direito
    130       |     135
    150       |     160
    200       |     215
===========================================================================================================================================================================================================
*/

// Inclusão de bibliotecas
#include <Wire.h> // Biblioteca para uso do I2C
#include <Adafruit_VL53L0X.h> // Biblioteca para uso dos sensores lasers
#include "mpu6050.h" // Biblioteca para uso do giroscópio e do acelerôemtro
#include <Ultrasonic.h> // Biblioteca para uso do sensor ultrasônico
#include <Servo.h> // Biblioteca para uso do servo motor dos kits de resgate
#include <Adafruit_NeoPixel.h> // Biblioteca para uso do LED

// Declaração dos pinos utilizados para controlar a velocidade de rotação
#define PINO_ENA 7
#define PINO_IN1 16 
#define PINO_IN2 15 

#define PINO_ENB 11 
#define PINO_IN3 17 
#define PINO_IN4 14 

// Declaração de pinos relacionados ao multiplexador I2C os sensores conectados a ele
#define TCA1_END 0x70      // Endereço I2C do multiplexador 1
//#define TCA2_END 0x71      // Endereço I2C do multiplexador 2
#define VL53L0X_END 0x29  // Endereço I2C do sensor VL53L0X

// Declaração de endereços i2c das portas dos multiplexadores
#define END_PORTA_GIROSCOPIO 0x02
//#define END_PORTA_ACELEROMETRO 0x02 // no multiplex 2  
#define END_PORTA_LASER1 0x08
#define END_PORTA_LASER2 0x20
#define END_PORTA_LASER3 0x80
#define END_PORTA_MULTIPLEX2 0x01

// Definição de pinos sensor de cor
#define PinOUT 36 //Definição do Pino OUT na entrada digital 36
#define PinS2  38 //Definição do Pino S2 na entrada digital 38
#define PinS3 40 //Definição do Pinto S3 na entrada digital 40

// Definição dos pinos da fita LED
#define PIN 3 // Porta do arduino onde o led está conectado
#define NUMLED 8 // Números de led que há na fita
#define DELAYLOOP 100 // Intervalo entre as piscadas do led
Adafruit_NeoPixel pixels(NUMLED, PIN, NEO_GRB + NEO_KHZ800);

Servo myservo;  // cria um objeto para controlar o servo

// Declaração de variáveis que serão correspondentes a velocidade dos motores
int velMotoresEsq = 120; // 130
int velMotoresDir = 145; // 155
const int velMotoresEsqCurva = 250;
const int velMotoresDirCurva = 245;

// Declaração de variáveis correspondentes ao tempo de delay
const int tempoDelayLeituraLasers = 80;
const int tempoDelayRecuo = 120;
const int tempoDelayPausa = 50;
//const int tempoDelayVitimas = 1400;
const int distanciaRoboParede = 4;

// Variáveis que representam a ângulagem do giroscópio
const int grausGiroE = -83;
const int grausGiroD = 83;
const int grausCentro = 0;
int tolerancia = 0; // Variável para controlar a repetição de movimentos iguais do robô
int auxiliarFrente = 0;

// Variáveis das distâncias dos lasers
float dist1;
float dist2;
float dist3;

//variáveis sensor de cor
int red;//Declaração da variável que representará a cor vermelha
int green; //Declaração da variável que representará a cor verde
int blue; // Declaração da variável que representará a cor azul
bool corAzulDetectada = false;

int distUltrasonico = 0;

bool curvaFrente = true;

// Instâncias para os sensores lasers
Adafruit_VL53L0X laser1 = Adafruit_VL53L0X();  // Sensor VL53L0X 1
Adafruit_VL53L0X laser2 = Adafruit_VL53L0X();  // Sensor VL53L0X 2
Adafruit_VL53L0X laser3 = Adafruit_VL53L0X();  // Sensor VL53L0X 3

Ultrasonic ultrasonic(18, 19);  // Definindo os pinos do sensor ultrassônico (Trig, Echo)
int distUltrasonicoInicial;  // Distância inicial do sensor ultrasonico
bool inicioMov = false;      // Verifica se o robô começou a andar

// Sessão do modo serial
#define modoSerial false // Ligar  ou desligar o modo serial para habilitar os diganósticos durante o código

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

  Serial.begin(9600); //Inicia o monitor Serial com velocidade de 9600

  // Sensor cor
  pinMode(PinOUT, INPUT); //Definição do PinOUT como sendo um pino de entrada
  pinMode(PinS2, OUTPUT); //Definição do Pino S2 como sendo um pino de saída
  pinMode(PinS3, OUTPUT); //Definição do Pino S3 como sendo um pino de saída

  myservo.attach(44); // Atribui o servo na porta 44
  pixels.begin(); // Inicializa o LED
  pixels.clear();
  pixels.show();

  // Configuração dos pinos dos motores como saida
  pinMode(PINO_ENA, OUTPUT); 
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);

  // Inicia o codigo com os motores parados
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
  digitalWrite(PINO_ENA, LOW);
  digitalWrite(PINO_ENB, LOW);
}

void loop() 
{
  // ====== LEITURAS INICIAIS ======
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER2);
  float frente = leituraDistancia(laser2);

  float soma = 0;
  for (int i = 0; i < 3; i++) 
  {
    soma += ultrasonic.read();
    delay(5);
  }
  distUltrasonico = soma / 3.0;

  // ====== VERIFICAÇÃO PRINCIPAL ======
  if (frente < 0 || distUltrasonico < 0) 
  { 
    paraFrente();
    delay(1000);
    pararMotores();
    delay(1000);
    leituraCores();
    verificaVitimas();
    return;
  }

  if (distUltrasonico > distanciaRoboParede && frente > distanciaRoboParede) 
  {
    if (!inicioMov) 
    {
      distUltrasonicoInicial = distUltrasonico;
      inicioMov = true;
      leituraCores();
      verificaVitimas();
    }
    if (distUltrasonicoInicial - distUltrasonico >= 26 || distUltrasonico < distanciaRoboParede) 
    {
      leituraCores();
      verificaVitimas();
      s_println("Robô andou 30 cm");
      pararMotores();  // Para os motores
      delay(1000);     // Espera 5 segundos antes de parar completamente
      inicioMov = false; // Reinicia o processo
    } 
    else
    {
      leituraCores(); // Chama pela função que lÊ a escala de cores do sensor de cor
      verificaVitimas(); // Chama pela função que verifica os bytes enviados pela raspbeery via serial
      paraFrente();
    }
  }

  // ====== PAREDE À FRENTE - VERIFICAR LADOS ======
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  float esquerda = leituraDistancia(laser1);

  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER3);
  float direita = leituraDistancia(laser3);

  if (distUltrasonico < distanciaRoboParede || frente < distanciaRoboParede) 
  {
    pararMotores();

    if ((esquerda > 7 && esquerda > direita) || esquerda == -999)
    {
      pararMotores();
      delay(1000);
      virarEsquerda90G();
      pararMotores();
      delay(1000);
    } 
    else if ( (direita > 7 && direita > esquerda) || direita == -999) 
    {
      pararMotores();
      delay(1000);
      virarDireita90G();
      pararMotores();
      delay(1000);
    }
    else
    {
      virarDireita90G();
      pararMotores();
    }
  }
}


// Declaração de funções auxiliares
void depositaKit(int qntdKit) 
{
  // Pisca os LEDs 5 vezes
  for (int j = 0; j < 5; j++) 
  {
    // Acende todos os LEDs em branco
    for (int i = 0; i < NUMLED; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // branco
    }
    pixels.show();
    delay(500);

    // Apaga todos os LEDs
    pixels.clear();
    pixels.show();
    delay(500);
  }

  // Garante que os LEDs fiquem desligados após os 5 piscos
  pixels.clear();
  pixels.show();

  // Gira o servo para depositar os kits de resgate 
  for (int i = 0; i < qntdKit; i++) 
  {
    myservo.write(35);   // Posição inicial
    delay(1500);         // Tempo para chegar
    myservo.write(119);  // Posição final
    delay(2000);         // Tempo para chegar
  }
}

void limpaBuffer()
{
  while (Serial.available() > 0) 
  {
    Serial.read(); // descarta byte a byte
    pararMotores();
  }
}
void verificaVitimas()
{
  // Verifica se há bytes disponíveis armazenados no buffer serial
  if (Serial.available() > 0) 
  {  
    pararMotores();

    byte byte_recebido = Serial.read(); // Recebe o byte enviado pela raspbeery na variável byte_recebido

    // Verifica qual byte foi recebido
    if (byte_recebido == 'o') 
    {
      leituraCores();
      s_println("Cor: verde");
      //paraFrente();
      //delay(tempoDelayVitimas);
      pararMotores();
      depositaKit(0);
      limpaBuffer();
    } 
    else if (byte_recebido == 'v') 
    {
      leituraCores();
      s_println("Cor: Vermelho");
      //paraFrente();
      //delay(tempoDelayVitimas);
      pararMotores();
      depositaKit(2); 
      limpaBuffer();
    } 
    else if (byte_recebido == 'a') 
    {
      leituraCores();
      s_println("Cor: amarelo");  
      //paraFrente();
      //delay(tempoDelayVitimas);
      pararMotores();
      depositaKit(1);
      limpaBuffer();
    } 
    /*else if (byte_recebido == 'h') 
    {
      s_println("Letra: H");
      //paraFrente();
      //delay(tempoDelayVitimas);
      pararMotores();
      depositaKit(2); 
      limpaBuffer();
    }
    else if (byte_recebido == 's') 
    {
      leituraCores();
      s_println("Letra: S");
      //paraFrente();
      //delay(tempoDelayVitimas);
      pararMotores();
      depositaKit(1); 
      limpaBuffer();
    } 
    else if (byte_recebido == 'u') 
    {
      leituraCores();
      s_println("Letra: U");
      //paraFrente();
      //delay(tempoDelayVitimas);
      pararMotores();
      depositaKit(0);
      limpaBuffer();
    } */
    /*else 
    {
      s_println("Letra ou cor desconhecida");
      limpaBuffer();
    }*/
  }

}
void iniciaGiroscopio() // Função que realiza as configurações iniciais do sensor giroscópio
{
  // Inicializando o MPU6050 via multiplexador (Canal 4)
  s_println("Inicializando o MPU6050 via multiplex...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO);  // Canal 4 (SDA4, SCL4)
  mpu_begin();  // Inicializa o MPU6050
  mpu_calibrate(200);  // Calibra o giroscópio para uso
  mpu_reset();  // Reseta o MPU6050
  s_println("MPU6050 inicializado com sucesso!");
}

void seleciona_canal_multiplex(uint8_t endereco_multiplex, uint8_t canal) // Função que realiza a comunicação com os sensores conectados aos multiplexadores i2c 
{
  Wire.beginTransmission(endereco_multiplex);
  Wire.write(canal); // ativa apenas o canal desejado
  Wire.endTransmission();
}

float leituraDistancia(Adafruit_VL53L0X &sensor) // Função para ler e imprimir a distância do sensor
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
      return -999; // valor de erro
    }
}

void iniciaLasers() // Função que realiza as configurações iniciais dos sensores lasers conectados ao multiplexador i2c
{
    // Inicializando o primeiro sensor VL53L0X (Canal 2)
  s_println("Ativando o canal 3 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);  // Canal 2 (SD2 E SCL2)

  if (!laser1.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar o VL53L0X no Canal 3.");
    while (1); // Fica travado se o sensor falhar
  }
  s_println("Sensor VL53L0X 1 inicializado com sucesso!");

  // Inicializando o segundo sensor VL53L0X (Canal 3)
  s_println("Ativando o canal 4 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER2);  // Canal 3 (SDA3, SCL3)

  if (!laser2.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar o VL53L0X no Canal 4.");
    while (1); // Fica travado se o sensor falhar
  }
  s_println("Sensor VL53L0X 2 inicializado com sucesso!");

  // Inicializando o terceiro sensor VL53L0X (Canal 4)
  s_println("Ativando o canal 6 do PCA9548A...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER3);  // Canal 4 (SDA4, SCL4)

  if (!laser3.begin(VL53L0X_END)) {
    s_println("Falha ao inicializar o VL53L0X no Canal 6.");
    while (1); // Fica travado se o sensor falhar
  }
  s_println("Sensor VL53L0X 3 inicializado com sucesso!");
}

void virarEsquerda90G() // Função para realizar uma curva à esquerda em 90 graus a partir do sensor giroscópio
{
  s_println("preparando o giroscópio para a curva...");
  seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO); // Chama pela função que prepara o giroscópio do multiplex para uso
  mpu_reset(); // Reseta o ângulo do giroscópio
  delay(100); // Espera para o sensor estabilizar

  while(true) // Inicia um loop para isolar a execução do giroscópio
  {
    mpu_loop(); // Executa a lógica do giroscópio
    float anguloE = getAngleZ();

    // Verifica a angulação do giorscópio
    if(anguloE < grausGiroE) // Caso o giroscópio ultrapasse 90 graus negativo (finaliza uma curva a esquerda)
    {
      s_println("o ângulo ultrapassou -85 graus, resetando o giroscópio...");
      pararMotores();
      delay(50);
      tolerancia = tolerancia - 1;
      break; // Sai do loop do while
    }
      s_println(anguloE); // Exibe a posição atual do giroscópio
      delay(10);
      virarEsquerda();    
  }

  // Verifica se o robô virou à esquerda 5 vezes seguidas (robô está preso em um loop)
  if(tolerancia == -7)
  {
    virarDireita90G();
    virarDireita90G();
    pararMotores();
    tolerancia = 0; // Reseta a variável para reinicializar o processo de verificação
  }
}

void virarDireita90G() // Função para realizar uma curva à direita em 90 graus a partir do sensor giroscópio
{
  seleciona_canal_multiplex(TCA1_END, END_PORTA_GIROSCOPIO); // Chama pela função que prepara o giroscópio do multiplex para uso
  mpu_reset(); // Reseta o ângulo do giroscópio
  delay(100); // Espera para o sensor establizar

  while(true) // Inicia um loop para isolar a execução do giroscópio
  {
    mpu_loop(); // Executa a lógica do giroscópio
    float anguloD = getAngleZ();

    // Verifica a angulação do giroscópio
    if(anguloD > grausGiroD) // Caso o giroscópio ultrapasse 90 graus (finaliza uma curva a direita)
    {
      s_print("o ângulo ultrapassou 85 graus, resetando...");
      pararMotores();
      delay(50);
      tolerancia = tolerancia + 1; // Soma 1 para indicar que o robô virou à direita
      break; // Sai do loop do while
    }
    s_println(anguloD); // Exibe a psoição giroscópio
    delay(10);
    virarDireita();    
  }

  // Verifica se o robô virou à direita 5 vezes seguidas (robô está preso em um loop)
  if(tolerancia == 7)
  {
    virarEsquerda90G();
    virarEsquerda90G();
    pararMotores();
    tolerancia = 0; // Reseta a variável para repetir o processo
  }
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
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void virarDireita() 
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
void pararMotores()
{
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
}
void cores() 
{
  if ((red > 25 && red < 40) && (green > 25 && green < 40) && (blue > 15 && blue < 25)) 
  {
    s_println("PRETO");
    paraTras();
    delay(400);
    
    seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER2);
    float frenteInicial = leituraDistancia(laser2);

    float distInicial = ultrasonic.distanceRead();
    s_print("Distância inicial (ultrassônico): ");
    s_println(distInicial);

    while (true) 
    {
      paraTras();
      delay(650);

      float distAtual = ultrasonic.distanceRead();
      s_print("Distância atual: ");
      s_println(distAtual);

      seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER2);
      float frenteAtual = leituraDistancia(laser2);

      if ((distAtual - distInicial >= 10) || (frenteAtual - frenteInicial >= 10)) 
      {
        paraTras();
        delay(500);
        pararMotores();
        delay(500);
        virarParaMaiorLadoLaserLadrilhosColoridos();
      }
      break;
    }
  }    
  else if ((red > 20 && red < 32) && (green > 20 && green < 30) && (blue > 5 && blue < 15)) 
  {
    s_println("AZUL");
    paraFrente();
    delay(800);
    pararMotores();
    delay(7000);
    //corAzulDetectada = true;
    if(corAzulDetectada == false)
    {
      virarParaMaiorLadoLaserLadrilhosColoridos();
      corAzulDetectada = true;
    }
  }
  else if (blue < 20 && red < 20 && green < 20) 
  {
    s_println("Branco");
    corAzulDetectada = false;
  }
  /*else if (red < blue && red < green && red < 100) 
  {
    s_println("Vermelho");
    
  }*/
}
void leituraCores()
{
  digitalWrite(PinS2, LOW); // Aciona um valor LOW ao Pino S2
  digitalWrite(PinS3, LOW); // Aciona um valor LOW ao Pino S3
  red = pulseIn(PinOUT, LOW); // define red como sendo responsável por ler a informação de pulso LOW do pino out

  s_print(" R: "); // Mostra a letra R no monitor Serial, representando red
  s_print(red); // Mostra o valor lido no PulseIn

  delay(15); // delay de 15 milissegundos até o próximo comando


  digitalWrite(PinS2, HIGH); // Aciona um valo high ao Pino S2
  digitalWrite(PinS3, HIGH); // Aciona um valo high ao Pino S3
  green = pulseIn(PinOUT, LOW); // define green como sendo responsável por ler a informação de pulso low no pino out

  s_print(" G: "); // Mostra a letra R no monitor Serial, representando green
  s_print(green); // Mostra o valor lido no PulseIn

  delay(15); // delay de 15 milissegundos até o próximo comando


  digitalWrite(PinS2, LOW);// Aciona um valor loq ao Pino S2
  digitalWrite(PinS3, HIGH); // Aciona um valor high ao Pino S3
  blue = pulseIn(PinOUT, LOW);// define blue como sendo responsável por ler a informação de pulso low no pino out

  s_print(" B: "); // Mostra a letra B no monitor Serial, representando blue
  s_println(blue); // Mostra o valor lido no PulseIn

  delay(15); // delay de 15 milissegundos até o próximo comando

  cores(); // chama a função que realiza a leitura da escala de cores do sensor de cor

  delay(100);

}

void virarParaMaiorLadoLaser() 
{
  // Leitura dos sensores laser
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  float esquerda = leituraDistancia(laser1);

  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER3);
  float direita = leituraDistancia(laser3);

  s_print("Laser Esquerda: ");
  s_println(esquerda);
  s_print("Laser Direita: ");
  s_println(direita);

  // Verifica qual lado tem mais espaço e vira para ele
  if (direita > esquerda || direita > 4 || direita == -999) 
  {
    s_println("Virando para a DIREITA");
    virarDireita90G();
  } 
  else if(esquerda > direita || esquerda > 4 || esquerda == -999)
  {
    s_println("Virando para a ESQUERDA");
    virarEsquerda90G();
  }

  pararMotores();
  delay(500);  // Tempo de estabilização
}
void virarParaMaiorLadoLaserLadrilhosColoridos()
{
  // Leitura dos sensores laser
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  float esquerda = leituraDistancia(laser1);

  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER3);
  float direita = leituraDistancia(laser3);

  s_print("Laser Esquerda: ");
  s_println(esquerda);
  s_print("Laser Direita: ");
  s_println(direita);

  // Verifica qual lado tem mais espaço e vira para ele
  if (direita > esquerda) 
  {
    s_println("Virando para a DIREITA");
    virarDireita90G();
  } 
  else if(esquerda > direita)
  {
    s_println("Virando para a ESQUERDA");
    virarEsquerda90G();
  }

  pararMotores();
  delay(500);  // Tempo de estabilização

}
/*void confirmacaoVitimaProxima()
{
    // Leitura dos sensores laser
  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER1);
  float esquerda = leituraDistancia(laser1);

  seleciona_canal_multiplex(TCA1_END, END_PORTA_LASER3);
  float direita = leituraDistancia(laser3);

  s_print("Laser Esquerda: ");
  s_println(esquerda);
  s_print("Laser Direita: ");
  s_println(direita);

  pararMotores();
  delay(500);  // Tempo de estabilização

}*/