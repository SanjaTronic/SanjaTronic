#include "LiquidCrystal_I2C.h"
#include "Wire.h" 
#include "Ultrasonic.h"

LiquidCrystal_I2C lcd(0x27,16,2);   //Configura o display
HC_SR04 sensor1(12,13);             //Configura os pinos sensor ultrassonico (Trigger,Echo)

void setup() {
  lcd.init();                       // Inicializa o LCD
  lcd.backlight();                  // Liga o backlight do LCD
}

void loop() {
  lcd.print("      ");
  lcd.print(sensor1.distance());    //Exibe no display as medidas
  lcd.print(" cm");
  delay(100);
  lcd.clear();                      //Apaga o que foi escrito no display
}
