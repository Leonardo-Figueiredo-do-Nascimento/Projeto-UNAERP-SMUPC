#define BLYNK_TEMPLATE_ID "TMPL2zdzg_C1t"
#define BLYNK_TEMPLATE_NAME "Projeto SMUPC"
#define BLYNK_AUTH_TOKEN "325XLy2cNZTlvpSFxY5_Z6Ds770586Ho" //Coloca o token do blynk enviado por email

#include <SoftwareSerial.h> //Biblioteca para a comunicação serial entre arduino e Esp8266
#include <ESP8266WiFi.h> //Biblioteca que permite o Esp8266 de se comunicar com o Wifi
#include <BlynkSimpleEsp8266.h> //Biblioteca que permite a interação do aplicativo Blynk com o Esp8266 para enviar dados

int D7 = 13,D8 = 15; // Pinos da comunicação sendo D7 o receptor e D8 o transmissor

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "#######"; //Nome do wifi
char pass[] = "#######"; // Senha do Wifi

SoftwareSerial NODEMCU(D7, D8); // Cria uma instância de comunicação serial com o Arduino

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial com o computador (para debug)
  NODEMCU.begin(4800); // Inicia a comunicação serial com o Arduino
  pinMode(D8,OUTPUT);
  pinMode(D7,INPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); //Estabelece a conexão com o Blynk passando os dados
}

void loop() {
  Blynk.run(); //Inicia o aplicativo Blynk
  while(NODEMCU.available()>0){
    
    String receivedData = NODEMCU.readStringUntil('\n'); // Lê até o fim da linha

    int firstDelimiterIndex = receivedData.indexOf(','); // Encontra a primeira vírgula
    int secondDelimiterIndex = receivedData.indexOf(',', firstDelimiterIndex + 1); // Encontra a segunda vírgula

    if (firstDelimiterIndex != -1 && secondDelimiterIndex != -1) {
      String val1 = receivedData.substring(0, firstDelimiterIndex); // Primeiro valor 
      String val2 = receivedData.substring(firstDelimiterIndex + 1, secondDelimiterIndex); // Segundo valor
      String val3 = receivedData.substring(secondDelimiterIndex + 1); // Terceiro valor

      Serial.println("Valores recebidos do Sensor Arduino 1: " + val1);
      Serial.println("Valores recebidos do Sensor Arduino 2: " + val2);
      Serial.println("Valores recebidos do Sensor Arduino 3: " + val3);

      int um1 = val1.toInt();
      int um2 = val2.toInt();
      int um3 = val3.toInt();

      Blynk.virtualWrite(V0,um1);
      Blynk.virtualWrite(V1,um2);
      Blynk.virtualWrite(V2,um3);

      if((um1<10 && um2<10) || (um2<10 && um3<10) || (um1<10 && um3<10) || (um1<10 && um2<10 && um3<10)){
        Blynk.virtualWrite(V3,"Campo com escassez de umidade. \nHidratação necessária para plantio e colheita.");
      }

      if((um1<50 && um2<50) || (um2<50 && um3<50) || (um1<50 && um3<50) || (um1<50 && um2<50 && um3<50)){
        Blynk.virtualWrite(V3,"Campo com níveis adequados de umidade. \nPlantio ou colheita possíveis.");
      } else{
        Blynk.virtualWrite(V3,"Campo com excesso de umidade. \n Aguarde a diminuição da umidade do campo.");
      }
    }
  }
}