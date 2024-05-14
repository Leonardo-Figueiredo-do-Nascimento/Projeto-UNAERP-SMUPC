int pinoSensor = A3;

void setup() {
    Serial.begin(9600);

}

void loop() {
  int terra1 = analogRead(pinoSensor);
  int umidade1 = map(terra1,1023,0,0,100);
  Serial.println(umidade1);
  delay(1000);
  
}
