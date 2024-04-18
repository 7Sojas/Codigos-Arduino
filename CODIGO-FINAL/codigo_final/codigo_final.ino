#include "DHT.h" 
// --biblioteca que contém os códigos necessários para trabalhar com sensores de temperatura e umidade.

#define dht_type DHT11
// -- definindo o especificador do tipo do sensor que está sendo utilizado

int dht_pin = A0; //-- entrada analógica
DHT dht_1 = DHT(dht_pin, dht_type); 
// -- criando um objeto com o tipo e o pin


const int LM35 = A1; // Define o pino que lerá a saída do LM35
float temperatura2; // Variável que armazenará a temperatura medida


//Função que será executada uma vez quando ligar ou resetar o Arduino
void setup() {
  Serial.begin(9600);
  dht_1.begin();
}
 // -- comunicação serial
 
void loop() {
  float umidade = dht_1.readHumidity();
  float temperatura = dht_1.readTemperature();
  // --utilizamos o objeto criado para realizar a leitura
  temperatura2 = (float(analogRead(LM35))*5/(1023))/0.01;
    Serial.print(temperatura2);
  if(isnan(temperatura) or isnan(umidade)){
    Serial.println("Erro ao ler"); 
  } else {
     Serial.print(";");
    Serial.println(umidade);

    
  }

  delay(500);
}