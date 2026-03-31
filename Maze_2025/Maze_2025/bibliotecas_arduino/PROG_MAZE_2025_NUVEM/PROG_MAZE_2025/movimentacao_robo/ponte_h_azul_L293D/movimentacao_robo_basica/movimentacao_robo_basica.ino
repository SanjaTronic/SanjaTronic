/*
================================================= CÓDIGO DE MOVIMENTAÇÃO SIMPLES ============================================================================
Autor: Murilo
Data da criação: 12/03/2025
Data da última modificação: 12/03/2025
Campo de observações:
=====================================================================================================================================================================================================
*/

// Definição de pinos
#define TCA_ADDR 0X70  // ENDEREÇO I2C DO MULTIPLEXADOR DE PORTAS 

// Pinos relacionados aos motores
#define PINO_ENA 4  // Pino para controle de velocidade dos motores do lado esquerdo da ponte H
#define PINO_ENB 9  // Pino para controle de velocidade dos motores do lado direito da ponte H

// Pinos relacionados aos motores conectados a ponte H. Cada pino é referente a um motor da ponte H
#define PINO_IN1 5
#define PINO_IN2 6
#define PINO_IN3 7
#define PINO_IN4 8

// Declaração de variáveis relacionadas as velocidades dos motores conectados a ponte H
int velocidadeMotores = 130;
int velocidadeCurva = 110;

// Variáveis de tempo de rotação dos motores
unsigned long tempoDeInicio;  // Armazena o tempo do inicio das rotações
unsigned long tempoDeRotacao = 3000;  // tempo que o robô vai andar (em milisegundos)

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial

  // Configuração dos pinos dos motores como saída
  pinMode(PINO_ENA, OUTPUT);
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);
  }

void loop() {

  paraFrente();

  // Verifica se o tempo de movimento foi alcançado
  if (millis() - tempoDeInicio >= tempoDeRotacao) {

    pararMotores();  // Para os motores quando o tempo de movimento for alcançado
    delay(5000);  // Faz o robô aguardar 5 segundos parado antes de ir à próxima ação
    tempoDeInicio = millis();  // Armazena o tempo de inicio
    
  }


}
void paraFrente() {
 
  // Configura os motores para o sentido horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotores);
  analogWrite(PINO_ENB, velocidadeMotores);

  //tempoDeInicio = millis();  // Armazena o tempo de inicio

}

void paraTras() {
  // Configura os motores para girar no sentido anti-horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeMotores);
  analogWrite(PINO_ENB, velocidadeMotores);
}

void virarDireita() {
  // Configura 2 motores para girar no sentido anti-horário e 2 para girar sentido horário
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores
  analogWrite(PINO_ENA, velocidadeCurva);
  analogWrite(PINO_ENB, velocidadeCurva);
}

void virarEsquerda() {
  // Configura 2 motores para o sentido horário e 2 para o sentido anti-horário
  digitalWrite(PINO_IN1, HIGH); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);

  // Configura a velocidade dos motores sendo 70
  analogWrite(PINO_ENA, velocidadeCurva);
  analogWrite(PINO_ENB, velocidadeCurva);
}

void pararMotores() {
  // Configura os 4 motores para pararem de girar
  digitalWrite(PINO_IN1, LOW);
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);

  // Configura a velocidade dos motores como 0
  analogWrite(PINO_ENA, 0);
  analogWrite(PINO_ENB, 0);
}



