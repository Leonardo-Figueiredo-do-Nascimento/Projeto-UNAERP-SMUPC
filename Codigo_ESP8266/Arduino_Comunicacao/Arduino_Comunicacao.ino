#include <SoftwareSerial.h>

SoftwareSerial Arduino(2, 3); // Cria uma instância de comunicação serial com o Arduino

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial com o computador (para debug)
  Arduino.begin(4800); // Inicia a comunicação serial com o Arduino
}

void loop() {
  while(Arduino.available()>0){
    float val = Arduino.parseFloat();
    if(Arduino.read()=='\n'){
      Serial.println(val);
    }
  }
  delay(1000);
}