/*
================================================================ PROGRAMAÇÃO SERVO MOTOR KITS DE RESGATE =================================================================================================
Autor: Murilo
Data da criação: 23/07/2025
Data da última modificação: 04/08/2025

Campo de observações:
N\A
============================================================================================================================================================================================================
*/

// Inclusão de bibliotecas
#include <Servo.h> // Biblioteca para uso do servo motor sg90

Servo myservo;  // cria um objeto para controlar o servo

void setup() 
{
  Serial.begin(9600); // Inicializa a comunicação serial

  myservo.attach(44);  // atribui o servo na porta 44
}

void loop() 
{
  /*Serial.println("depositando kits...");
  depositaKit(3);*/

  // Verifica se há pelo menos 3 bytes dipsoníveis para serem lidos no buffer da comunicação serial
  if (Serial.available() >= 3) 
  {  
    // Esperar dois bytes
    byte byte_recebido = Serial.read();  // Atribui o byte recebido na comunicação serial na variável byte_recebido

    // Verificar a cor/letra detectada pela câmera da raspbeery
    if (byte_recebido == 0x03) // Caso a cor identificada seja verde
    {
      Serial.println("Cor: verde");
      limpaBuffer();
    } 
    else if (byte_recebido == 0x05) // Caso a cor identificada seja vermelho
    {
      Serial.println("Cor: Vermelho");
      depositaKit(2); // Deposita 1 kit de resgate
      limpaBuffer();
    } 
    else if (byte_recebido == 0x07) // Caso a cor identificada seja amarelo
    {
      // Não é necessário depositar nenhum kit
      Serial.println("Cor: amarelo");  
      depositaKit(1);
      limpaBuffer();
    } 
    if (byte_recebido == 0x09) // Caso a letra identificada seja 'H'
    {
      Serial.println("Letra: H");
      depositaKit(2); // Deposita 2 kits de resgate
      limpaBuffer();
    }
    else if (byte_recebido == 0x11) // Caso a letra identificada seja 'S'
    {
      Serial.println("Letra: S");
      depositaKit(1); // Deposita 1 kit de resgate
      limpaBuffer();
    } 
    else if (byte_recebido == 0x13) // Caso a letra identificada seja 'U'
    {
      // Não é necessário depositar nenhum kit
      Serial.println("Letra: U");
      limpaBuffer();
    } 
    else // Caso o valor recebido de bytes não corresponda a nenhuma cor ou letra
    {
      Serial.println("Letra ou cor desconhecida");
      limpaBuffer();
    }
  }

}

// Funções
void depositaKit(int qntdKit) // Função para depositar os kits de resgate (movimentar o servo motor para a posição inicial e posição final) a quantidade vezes que esse processo será repetido é dado pelo número inserido como parâmetro (dentro dos paranteses) no momento de chamar a função 
{
  for(int i = 0; i < qntdKit; i++) // Laço de repetição que irá ciclar até que a variável i seja maior que o número estabelecido como qntdKit no momento de chamar a função no código principal
  {
    myservo.write(35); // Movimenta o servo motor para a posição de ângulo 35
    delay(1200); // Atraso de 1,2 segundos para garantir que o servo chegue à posição inicial
    myservo.write(120); // Movimenta o servo motor para à posição de ângulo 170
    delay(1200); // Atraso de 1,2 segundos para garantir que o servo chegue a posição final
  }
}
void limpaBuffer()
{
  while (Serial.available() > 0) 
  {
  Serial.read(); // descarta byte a byte
  }
}