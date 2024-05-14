
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
  int i = 10;
  NODEMCU.print(i);
  NODEMCU.println("\n");
  delay(1000);
  i++;
}