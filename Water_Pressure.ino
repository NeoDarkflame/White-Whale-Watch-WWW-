const float OffSet = 0.483;
float V, P;
void setup() {
  Serial.begin(9600);
}

void loop() {
  V = analogRead(0)*5.00/1024;// Receive values from pressure sensors
  P = (V-OffSet)*400;// Convert to kilopascal

  Serial.print(V, 3);
  Serial.println("V");// Display V value to Serial Monitor

  Serial.print(P, 1);
  Serial.println("KPa");// Display P value to Serial Monitor
  Serial.println();

  delay(500);
}
