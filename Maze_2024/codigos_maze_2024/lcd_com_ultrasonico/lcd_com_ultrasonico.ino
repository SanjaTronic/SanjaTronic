/*#include "LiquidCrystal_I2C.h"
#include "Wire.h" 
#include "Ultrasonic.h"

LiquidCrystal_I2C lcd(0x27,16,2);   //Configura o display
HC_SR04 sensor1(12,13);             //Configura os pinos sensor ultrassonico (Trigger,Echo)
float dist = sensor1.distance();

void setup() {
  lcd.init();                       // Inicializa o LCD
  lcd.backlight();                  // Liga o backlight do LCD
}

void loop() {
  if(dist > 1){
  lcd.print("  detectado  ");
  //lcd.print(sensor1.distance());    //Exibe no display as medidas
  //lcd.print(" cm");
  delay(3000);
  lcd.clear();                      //Apaga o que foi escrito no displa
  }
}*/
//Carrega a biblioteca do sensor ultrassonico
#include <HCSR04.h>

#define p_trigger 12
#define p_echo 13
UltraSonicDistanceSensor distanceSensor(p_trigger , p_echo);

dist = distanceSensor.measureDistanceCm();
 
void setup()
{
  
}
 
void loop()
{
  
}
