#include "DHT.h" // --biblioteca que contém os códigos necessários para trabalhar com sensores de temperatura e umidade.
#define dht_type DHT11 //define um valor constante para o DHT11

//variáveis LM35 - temperatura 
int sensorTemperaturaLM = A1; // Saída do sensor no arduíno.  
float temperaturaReal = 0; //Variável que armazenará a temperatura lida, float armazena valores reais ou flutuantes, que contém casas decimais. 

int dht_pin = A3; //-- entrada analógica
DHT dht_1 = DHT(dht_pin, dht_type); 
// -- criando um objeto com o tipo e o pin

//Função que será executada uma vez quando ligar ou resetar o Arduino
void setup() {
  Serial.begin(9600);
  dht_1.begin();
}
 // -- comunicação serial
 
void loop() {
  // Leitura do valor analógico do sensor
  int valorAnalogico = analogRead(sensorTemperaturaLM);

  // Converte o valor analógico para tensão (em volts)
  float tensao = valorAnalogico * (5.0 / 1023.0);

  // Converte a tensão para temperatura em graus
  temperaturaReal = tensao * 100;

  float umidadeReal = dht_1.readHumidity();

  if(isnan(temperaturaReal) or isnan(umidadeReal)){
    Serial.println("Falha na leitura do sensor"); 
    return;
  } else {
   // Envia os dados reais para a porta serial
    Serial.print(temperaturaReal);
    Serial.print(",");
    Serial.println(umidadeReal);
  }

  delay(5000); //Intervalo de 5 segundos antes de pular linha
}