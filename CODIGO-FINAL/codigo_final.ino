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

    Serial.println("Erro ao ler umidade");

  } else { 
 
    String texto_MAXIMOumi = "MAXIMO_Umidade:";
    Serial.print(texto_MAXIMOumi + ((umidade * 0) + 70));
    Serial.print(" ");

   String texto_umidadeS1 = "Umidade_Silo1:";
    Serial.print(texto_umidadeS1 + (umidade + 10)); //imprime a umidade do sensor DHT11 NO SILO 1 
    Serial.print(" "); //imprime um “;” para separar a umidade da temperatura 

    String texto_MINIMOumi = "MINIMO_Umidade:";
    Serial.print(texto_MINIMOumi + ((umidade * 0) + 60));
    Serial.print(" ");
   
  }

  String texto_MAXIMOtemp = "MAXIMO_Temperatura:";
  Serial.print(texto_MAXIMOtemp + ((temperaturaLM * 0) + 35));
   Serial.print(" ");


  String texto_temperaturaS1 = "Temperatura_Silo1:";
  Serial.println(texto_temperaturaS1 + temperaturaLM);
  Serial.print(" "); //imprime a temperatura do sensor LM35 NO SILO 1 e pula linha 
  

     String texto_MINIMOtemp = "MINIMO_Temperatura:";
    Serial.print(texto_MINIMOtemp + ((temperaturaLM * 0) + 15));
    Serial.print(" ");


  delay(2000); // Intervalo de 1 segundo antes de pular linha 
  
} 