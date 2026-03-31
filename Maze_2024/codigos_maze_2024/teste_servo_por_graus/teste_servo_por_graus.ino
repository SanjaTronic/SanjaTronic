/*
======================================================================= OBSERVAÇÃO IMPORTANTE =======================================================================================
rotateServo(4); = ordena o servo a rotacionar de acordo com a velocidade pré-estabelecida dentro dos parenteses. exemplo: rotateServo(2), ordena o servo a rotacionar com velocidade
POSITIVA, isso é, rotacionar no sentido HORÁRIO.
exemplo no-2: rotateServo(-2), ordena o servo a rotacionar com velocidade NEGATIVA, ou seja, rotacionar no sentido ANTI-HORÁRIO.
=====================================================================================================================================================================================
*/

#include <Servo.h> // Inclui a biblioteca 'Servo.h' (biblioteca padrão do arduino, utilizada para controlar servos motores)

Servo myServo;  // Cria um objeto Servo para controlar o servo motor

void setup() {
  myServo.attach(9);  // Conecta o servo ao pino digital 9

  // Declara a função de cada pino como input(entrada de dados)
  pinMode(3, INPUT);
  pinMode(7, INPUT);
  
  // Inicializa a comunicação serial com velocidade de 9600 bps
  Serial.begin(9600);
}

void loop() {
  // Declara cada o valor de cada variável como a leitura dos senore
  int sensorValue1 = digitalRead(3);
  int sensorValue2 = digitalRead(7);
  
  // Imprime o valor lido do sensor 1 no monitor serial 
  Serial.print("Valor do sensor 1: ");
  Serial.println(sensorValue1);

  // Imprime o valor lido do sensor 2 no monitor serial 
  Serial.print("Valor do sensor 2: ");
  Serial.println(sensorValue2);
  
  // Aguarda um pequeno intervalo antes de ler novamente
  delay(300);



  // Se algum dos sensores IR retornarem valor 0, gira o servo no sentido horário com velocidade média

  if(!sensorValue1 || !sensorValue2){
  rotateServo(4); //rotaciona o servo motor no sentido horário com velocidade de 4x0
  delay(500);  // Espera 3 segundos
  stopServo();  // Para a rotação do servo motor (independentemente do sentido que ele está rotacionando)
  delay(500);  // Espera 5 segundos
  }

}

void rotateServo(float speed) {
  int speedValue = map(speed, -1, 1, 0, 180);  // Mapeia a velocidade para a faixa de 0 a 180
  
  // Define a velocidade do servo motor
  myServo.writeMicroseconds(1500 + speedValue);  // Ajusta a velocidade com base na velocidadeValue
}

void stopServo() {
  myServo.writeMicroseconds(1500);  // Envia um pulso neutro para parar o servo
}

