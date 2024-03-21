// INTEGRADO (TESTAR!!!!) (puxa apenas a temperatura do LM35) 
#include "DHT.h" 
#define dht_type DHT11 

 
//variaveis LM35 
int pinoSensorTemperaturaLM = A5; // Saída do sensor na A0. 
int valorLido = 0; //Variável auxiliar. 
float temperaturaLM = 0; //Variável que armazenará a temperatura lida 
int linha =0; //variavel que se refere as linhas do excel 

  
//variaveis DHT 
int dht_pino = A1; 
DHT dht_1 = DHT(dht_pino, dht_type); 


//INICIAR PROGRAMA 
void setup() { 
  Serial.begin(9600); 
  dht_1.begin(); 
} 


// looping para ler para sempre LM35  
void loop() {//Função que será executada continuamente. 
valorLido = analogRead(pinoSensorTemperaturaLM); //Leitura analógica da porta A0 
temperaturaLM = (valorLido * 0.00488);// 5 volts/ 1023 « 0,0048 precisão do A/D 
temperaturaLM = temperaturaLM * 100;// converte milivolts para celsius - cada 18MV == 1 grau C 
linha++; //incrementa linha para que a leitura pule linha PARA FICAR MAIS BONITO 

// Serial.print("DATA, TIME, "); //inicia a impressão dos dados, fica sempre iniciando 
Serial.println(temperaturaLM); 
Serial.print(","); 
//Serial.println(linha); 

 
// looping para ler para sempre DHT11 
  float umidade = dht_1.readHumidity(); 
  float temperatura = dht_1.readTemperature(); 

  if(isnan(temperatura) or isnan(umidade)){ 
    Serial.println("Erro ao ler");  
  } else { 

    // Serial.print("Umidade: "); 
    Serial.print(umidade); 

    // Serial.print(" % "); 
    Serial.print(" ; "); 

   // Serial.print(" Temperatura: "); 
   // Serial.print(temperatura); 
   //Serial.println(" ºC"); 
  } 

  delay(500); 
} 