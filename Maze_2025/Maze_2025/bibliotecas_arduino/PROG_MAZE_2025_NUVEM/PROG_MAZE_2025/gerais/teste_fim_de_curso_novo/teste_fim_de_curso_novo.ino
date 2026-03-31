const int limitswitchPin = 3; // Declara o pino onde está conectado o fim de curso

void setup() {
  pinMode(limitswitchPin, INPUT_PULLUP); // Configura o pino como entrada com resistor pull-up interno
  Serial.begin(9600); // Inicia a comunicação serial para o monitor serial
}

void loop() {
  // Verifica se o fim de curso está pressionado (nível LOW)
  if (digitalRead(limitswitchPin) == LOW) {
    Serial.println("Fim de curso pressionado!"); // Exibe mensagem no monitor serial
  } else {
    Serial.println("Fim de curso livre..."); // Exibe mensagem no monitor serial
  }
  delay(200); // Aguarda 200 ms para evitar leituras muito rápidas
