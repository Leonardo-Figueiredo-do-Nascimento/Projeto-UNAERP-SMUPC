
#include <SoftwareSerial.h>
int D7 = 13,D8 = 15;

SoftwareSerial NODEMCU(D7, D8); // Cria uma instância de comunicação serial com o Arduino

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial com o computador (para debug)
  NODEMCU.begin(4800); // Inicia a comunicação serial com o Arduino
  pinMode(D8,OUTPUT);
  pinMode(D7,INPUT);
}

void loop() {
  while(NODEMCU.available()>0){
    
    String receivedData = NODEMCU.readStringUntil('\n'); // Lê até o terminador de linha

    int firstDelimiterIndex = receivedData.indexOf(','); // Encontra a primeira vírgula
    int secondDelimiterIndex = receivedData.indexOf(',', firstDelimiterIndex + 1); // Encontra a segunda vírgula

    if (firstDelimiterIndex != -1 && secondDelimiterIndex != -1) {
      String val1 = receivedData.substring(0, firstDelimiterIndex); // Primeiro valor
      String val2 = receivedData.substring(firstDelimiterIndex + 1, secondDelimiterIndex); // Segundo valor
      String val3 = receivedData.substring(secondDelimiterIndex + 1); // Terceiro valor

      Serial.println("Valores recebidos do Sensor Arduino 1: " + val1);
      Serial.println("Valores recebidos do Sensor Arduino 2: " + val2);
      Serial.println("Valores recebidos do Sensor Arduino 3: " + val3);
    }
    /*int val = NODEMCU.parseInt();
    if(NODEMCU.read()=='\n'){
      Serial.println("Valores recebidos do arduino: "+ String(val));
    }*/
  }
  /*int i = 10;
  NODEMCU.print(i);
  NODEMCU.println("\n");
  delay(1000);
  i++;*/
}