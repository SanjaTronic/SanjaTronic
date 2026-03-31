#include <Wire.h>

#define TCA1_ADDR 0x70
#define TCA2_ADDR 0x71 // supondo que você mudou o endereço do segundo TCA

void selectChannel(uint8_t tcaAddr, uint8_t channelBit) {
  Wire.beginTransmission(tcaAddr);
  Wire.write(channelBit);
  Wire.endTransmission();
}

void scanI2C() {
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Dispositivo encontrado no endereço 0x");
      Serial.println(address, HEX);
    }
  }
}

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Ativa canal 7 do primeiro TCA
  selectChannel(TCA1_ADDR, 0x80); // Canal 7

  // Agora ativa canal 0 do segundo TCA (já conectado no canal 7 do primeiro)
  selectChannel(TCA2_ADDR, 0x01); // Canal 0 do segundo TCA

  delay(100);
  Serial.println("Escaneando dispositivos I2C...");
  scanI2C(); // Agora verá dispositivos conectados no canal 0 do segundo TCA
}

void loop() {}
