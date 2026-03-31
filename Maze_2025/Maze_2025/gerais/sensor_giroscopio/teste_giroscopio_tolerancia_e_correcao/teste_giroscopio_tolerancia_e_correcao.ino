#include <Wire.h>     // Biblioteca para uso da comunicação I2C
#include "mpu6050.h"  // Biblioteca para uso do sensor giroscópio mpu6050

#define TCA_END_I2C 0x70 // Endereço I2C do PCA9458A
#define GIROSCOPIO_END_PORTA 0x01 // Endereço do canal SDO0 e SC0 do multiplex i2c

float anguloAtual = 0;  // Variável para armazenar o ângulo absoluto do robô
float noventaGraus = 90;  // O ângulo desejado (90 graus)
float tolerancia = 3;  // Tolerância para considerar que a rotação foi concluída (em graus)
bool curva = false; // Variável que quando 'true' inicia a lógica da curva do robô

void setup() {

  Serial.begin(9600); // Inicializa a comunicação serial
  Wire.begin(); // Inicia o barramento I2C

  delay(2000); // Atraso de 2 segundos para garantir que a comunicação esteja pronta

  Serial.println("Iniciando giroscópio...");

  tca_select(0x02); // Seleciona o canal do PCA9458A
  mpu_begin();  // Inicia o giroscópio

  mpu_calibrate(200); // Calibra o giroscópio para uso 

  mpu_reset();  // Reseta o giroscópio (para limpar qualquer erro inicial)

  Serial.println("Giroscópio iniciado com sucesso");

  delay(500); // Espera meio segundo para dar tempo de ler as mensagens de diagnóstico
}

void loop() {

  // Executa a leitura do giroscópio
  tca_select(0x02);
  mpu_loop();
  
  // Obtém o ângulo atual do giroscópio
  anguloAtual = getAngleZ();  

  Serial.println(anguloAtual);  // Exibe a posição atual do giroscópio no monitor serial

  // Verifica se o robô completou uma rotação de 90° ou -90°
  if (anguloAtual >= noventaGraus - tolerancia) 
  {
    // Se a rotação foi concluída para a direita
    Serial.println("Rotação de 90° concluída para a direita.");
    
    // Ajusta para o ângulo relativo entre 0° e 360°
    anguloAtual = noventaGraus;  
  } 
  else if (anguloAtual <= -noventaGraus + tolerancia) 
  {
    // Se a rotação foi concluída para a esquerda
    
    Serial.println("Rotação de 90° concluída para a esquerda.");
    // Ajusta para o ângulo relativo entre 0° e 360°
    anguloAtual = -noventaGraus;  
  }
  else 
  {
    // Caso o ângulo não tenha atingido a posição desejada, faça a correção
    if (anguloAtual < noventaGraus - tolerancia) 
    {
      // O ângulo atual está a menos de 90°, então gira à direita
      while (anguloAtual < noventaGraus - tolerancia) 
      {
        virarDireita();  // Função para virar à direita
        anguloAtual = getAngleZ();  // Atualiza o ângulo atual
        Serial.println(anguloAtual);
      }
    } 
    else if (anguloAtual > noventaGraus + tolerancia) 
    {
      // O ângulo atual passou de 90°, então gira à esquerda
      while (anguloAtual > noventaGraus + tolerancia) {
        virarEsquerda();  // Função para virar à esquerda
        anguloAtual = getAngleZ();  // Atualiza o ângulo atual
        Serial.println(anguloAtual);
      }
    }
  }

  // Delay para evitar sobrecarga na comunicação serial
  delay(100);
}

// Função para virar à direita
void virarDireita() {
  // Lógica para virar à direita (ajuste conforme necessário)
  Serial.println("Girando à direita...");
  // Envie comandos para o motor ou controle de rotação
  // Aqui você deve colocar a lógica real de controle de motores
  // Exemplo: motorRight.setSpeed(255); (onde 255 é a velocidade máxima)
}

// Função para virar à esquerda
void virarEsquerda() {
  // Lógica para virar à esquerda (ajuste conforme necessário)
  Serial.println("Girando à esquerda...");
  // Envie comandos para o motor ou controle de rotação
  // Aqui você deve colocar a lógica real de controle de motores
  // Exemplo: motorLeft.setSpeed(255); (onde 255 é a velocidade máxima)
}

// Função para selecionar o canal do PCA9458A
void tca_select(uint8_t port) {
  Wire.beginTransmission(TCA_END_I2C);
  Wire.write(port);  // Envia o byte para selecionar o canal
  Wire.endTransmission();  // Encerra a comunicação com o PCA9458A
}
