// INTEGRADO (Puxando a Temperatura do LM35 e Umidade do DHT11)  
#include "DHT.h" //biblioteca do DHT11 
#define dht_type DHT11 //define um valor constante para o DHT11 


//variáveis LM35 - temperatura 
int pinoSensorTemperaturaLM = A5; // Saída do sensor no arduíno.  
int valorLido = 0; //Variável auxiliar.  
float temperaturaLM = 0; //Variável que armazenará a temperatura lida, float armazena valores reais ou flutuantes, que contém casas decimais. 


//variáveis DHT - umidade 
int dht_pino = A1; //Saída do sensor no arduíno 
DHT dht_1 = DHT(dht_pino, dht_type); // função da biblioteca que configura o objeto dht_1 com as informações do pino e do tipo do sensor. 


//INICIAR PROGRAMA  
void setup() {  
  Serial.begin(9600); // função que inicia a comunicação entre o Arduino e o computador. O valor 9600 informa a velocidade de transmissão dos dados, portanto, 9600 bits/s (baudes) 
  dht_1.begin(); // Inicializa a função 
}  


// looping para ler para sempre  
void loop() { //Função que será executada continuamente.  
valorLido = analogRead(pinoSensorTemperaturaLM); //Leitura analógica da porta A5 
temperaturaLM = (valorLido * 0.00488); // 5 volts/ 1023 « 0,0048 precisão do A/D  
temperaturaLM = temperaturaLM * 100; // converte milivolts para celsius - cada 18MV == 1 grau C  
float umidade = dht_1.readHumidity(); // lê a umidade do sensor DHT e armazena o valor em uma variável chamada umidade 


// testa se o retorno da umidade é válido, caso contrário tem algo errado e uma mensagem de erro será exibida 
  if(isnan(umidade)){  
    Serial.println("Erro ao ler umidade") 
  
  } else { 
    Serial.print(umidade); //imprime a umidade do sensor DHT11 
    Serial.print(" ; "); //imprime um “;” para separar a umidade da temperatura 
  } 

 
  Serial.println(temperaturaLM); //imprime a temperatura do sensor LM35 e pula linha 
  delay(1000); // Intervalo de 1 segundo antes de pular linha 
} 
