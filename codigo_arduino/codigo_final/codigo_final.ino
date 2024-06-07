// INTEGRADO (Puxando a Temperatura do LM35 e Umidade do DHT11)  
#include "DHT.h" // --biblioteca que contém os códigos necessários para trabalhar com sensores de temperatura e umidade.
#define dht_type DHT11 //define um valor constante para o DHT11


//variáveis LM35 - temperatura 
int sensorTemperaturaLM = A2; // Saída do sensor no arduíno.  
float temperaturaReal = 0; //Variável que armazenará a temperatura lida, float armazena valores reais ou flutuantes, que contém casas decimais. 


int dht_pin = A1; //-- entrada analógica
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

  // Gerar dados fictícios adicionando ou subtraindo valores aleatórios
  float temperaturaFicticia1 = temperaturaReal + random(-5,5); // Variaçãp de -5 e 5
  float temperaturaFicticia2 = temperaturaReal + random(-10,10);
  float temperaturaFicticia3 = temperaturaReal + random(-3,3);


  float umidadeFicticia1 = umidadeReal + random(-10,10); // Variaçãp de -10 e 10
  float umidadeFicticia2 = umidadeReal + random(-15,15);
  float umidadeFicticia3 = umidadeReal + random(-5,5);


  if(isnan(temperaturaReal) or isnan(umidadeReal)){
    Serial.println("Falha na leitura do sensor"); 
    return;
  } else {
   // Exibe os dados no monitor serial
  Serial.print(temperaturaReal);
  Serial.print(",");
  Serial.print(temperaturaFicticia1);
  Serial.print(",");
  Serial.print(temperaturaFicticia2);
  Serial.print(",");
  Serial.println(temperaturaFicticia3);
  Serial.print(umidadeReal);
  Serial.print(",");
  Serial.print(umidadeFicticia1);
  Serial.print(",");
  Serial.print(umidadeFicticia2);
  Serial.print(",");
  Serial.println(umidadeFicticia3);
  }

  delay(5000); //Intervalo de 5 segundos antes de pular linha
}