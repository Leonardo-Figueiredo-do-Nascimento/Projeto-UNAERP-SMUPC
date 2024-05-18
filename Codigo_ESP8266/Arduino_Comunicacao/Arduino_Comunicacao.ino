#include <SoftwareSerial.h>

SoftwareSerial Arduino(2, 3); // Cria uma instância de comunicação serial com o Arduino, cabo azul no D7, verde no D8
int pinoSensor1 = A2, pinoSensor2 = A3, pinoSensor3 = A4;

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial com o computador (para debug)
  Arduino.begin(4800); // Inicia a comunicação serial com o Esp8266
}

void loop() {
  
  int terra1 = analogRead(pinoSensor1);
  int umidade1 = map(terra1,1023,0,0,100);
  int terra2 = analogRead(pinoSensor2);
  int umidade2 = map(terra2,1023,0,0,100);
  int terra3 = analogRead(pinoSensor3);
  int umidade3 = map(terra3,1023,0,0,100);

  Arduino.print(umidade1);
  Arduino.print(","); // Separador
  Arduino.print(umidade2);
  Arduino.print(","); // Separador
  Arduino.println(umidade3); // Envia um '\n' como terminador de linha


  /*while(Arduino.available()>0){
    float val = Arduino.parseFloat();
    if(Arduino.read()=='\n'){
      Serial.println(val);
    }
  }*/
  delay(5000);
}