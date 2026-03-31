/*Conexões:
Conecte o pino VCC do MMA8452 ao 3.3V do Arduino.
Conecte o pino GND do MMA8452 ao GND do Arduino.
Conecte o pino SDA do MMA8452 ao pino A4 (SDA) do Arduino.
Conecte o pino SCL do MMA8452 ao pino A5 (SCL) do Arduino.
*/
#include <Wire.h>
#include <SFE_MMA8452Q.h>

MMA8452Q acelerometro(0x1C); // Endereço I2C padrão do MMA8452

int IN1 = 3;
int IN2 = 4;
int IN3 = 5;
int IN4 = 6;

void setup() {
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);

 #define pinspeed_R 3
#define pinspeed_L 5 
#define DigitalSE 3
#define DigitalSD 5

    Serial.begin(9600);
    Serial.println("Teste de comunicação MMA8452");
    acelerometro.init();
}

void loop() {
  andar_para_frente();

    if (acelerometro.available()) {
        acelerometro.read();
        printCalculatedAccels();
        printOrientation();
        Serial.println();
    }
}

void printCalculatedAccels() {
    Serial.print("X: ");
    Serial.print(acelerometro.cx, 1); // Exibe com 1 casa decimal
    Serial.print("\tY: ");
    Serial.print(acelerometro.cy, 1); // Exibe com 1 casa decimal
    Serial.print("\tZ: ");
    Serial.print(acelerometro.cz, 1); // Exibe com 1 casa decimal
}

void printOrientation() {
    byte pl = acelerometro.readPL();
    switch (pl) {
        case PORTRAIT_U:
            Serial.print("\tOrientação: Retrato Para Cima");
            break;
        case PORTRAIT_D:
            Serial.print("\tOrientação: Retrato Para Baixo");
            break;
        case LANDSCAPE_R:
            Serial.print("\tOrientação: Paisagem Direita");
            break;
        case LANDSCAPE_L:
            Serial.print("\tOrientação: Paisagem Esquerda");
            break;
        case LOCKOUT:
            Serial.print("\tOrientação: Plano");
            break;
    }
}
void andar_para_frente(){
 analogWrite(IN1, 100); //lado esquerdo
 analogWrite(IN2, 0);
 analogWrite(IN3, 122); //lado direito
 analogWrite(IN4, 0);
}
