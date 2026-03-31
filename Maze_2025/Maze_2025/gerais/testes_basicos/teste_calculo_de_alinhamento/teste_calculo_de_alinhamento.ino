/*
====================================================================== TESTE CÁLCULO DE ALINHAMENTO ====================================================================================
Autor: Murilo
Data da criação: 10/07/2025
Data da última modificação: 10/07/2025

Campo de observações:
DSP -> Distância sensor parede
DCS -> Distância centro do robô até o sensor laser da lateral
DCP -> Distância centro parede
DSCV -> Distância centro sensor vertical
SCLV -> Distância sensor centro ladrilho vertical
========================================================================================================================================================================================
*/

#include <math.h> // Biblioteca para uso de funções matemáticas no arduino

// Variáveis para a calibração inicial
const float DSP = 6.5;
const float DCS = 8.0;
const float DCP = DCS + DSP;
const float DCSV = 9.25;
const float SCLV = 30 - DCSV; // Guardar como padrão

// Variáveis para o cálculo de correção
float desvio = 1; //"média distância da direita"
float DVT = DCP - ((desvio + 30) + DCS);
float tangenteX = 30 / DVT;
/*
// Variáveis de cálculo de correção para deslocamento
float desvioEsquerda = // colocar aqui o valor recebido pela média dos lasers do lado esquerdo do robô
float desvioDireita = // Colocar aqui o valor recebido pela média dos lasers do lado direito do robô 
*/

void setup() 
{
  // put your setup code here, to run once:
  

}

void loop() 
{
  // put your main code here, to run repeatedly:

}
