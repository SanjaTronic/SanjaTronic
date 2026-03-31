#include <Wire.h>

// Endereço I2C do MMA8452Q
#define Addr 0x1C

void setup() {
  Serial.begin(9600);
    // Inicializa a comunicação I2C como MASTER
    Wire.begin();

    // Configura o modo ativo
    Wire.beginTransmission(Addr);
    Wire.write(0x2A); // Registrador de controle
    Wire.write(0x01); // Modo ativo
    Wire.endTransmission();

    // Configura a faixa de medição para +/- 2g
    Wire.beginTransmission(Addr);
    Wire.write(0x0E); // Registrador de controle
    Wire.write(0x00); // Faixa de medição
    Wire.endTransmission();

    delay(300);
}

void loop() {
    unsigned int data[7];

    // Solicita 7 bytes de dados
    Wire.requestFrom(Addr, 7);

    if (Wire.available() == 7) {
        data[0] = Wire.read(); // Status
        data[1] = Wire.read(); // xAccl LSB
        data[2] = Wire.read(); // xAccl MSB
        data[3] = Wire.read(); // yAccl LSB
        data[4] = Wire.read(); // yAccl MSB
        data[5] = Wire.read(); // zAccl LSB
        data[6] = Wire.read(); // zAccl MSB

        // Processa os dados conforme necessário
        // ...

        // Exemplo: exibe a aceleração no eixo X
        delay(2000);
        int xAccl = (data[2] << 8) | data[1];
        Serial.print("Aceleração no eixo X: ");
        Serial.println(xAccl);
    }
}

