#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  
  // Inicializa o MPU6050
  Wire.begin();
  mpu.initialize();
  
  // Configura o intervalo de leitura do giroscópio
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
}

void loop() {
  // Lê os valores do giroscópio
  int16_t gyroX, gyroY, gyroZ;
  mpu.getRotation(&gyroX, &gyroY, &gyroZ);
  
  // Calcula a angulação nos eixos X e Y
  float anguloX = gyroX / 131.0; // Sensibilidade do giroscópio para o intervalo de ±250°/s
  float anguloY = gyroY / 131.0;
  
  // Exibe os valores no monitor serial
  Serial.print("Angulo X: ");
  Serial.print(anguloX);
  Serial.print(" | Angulo Y: ");
  Serial.println(anguloY);
  
  // Aguarda um curto intervalo de tempo antes da próxima leitura
  delay(100);
}

