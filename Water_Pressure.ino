const float OffSet = 0.483;
float V, P;
void setup() {
  Serial.begin(9600);
}

void loop() {
  V = analogRead(0) * 5.00 / 1024;
  P = (V-OffSet) * 400;

  Serial.print(V, 3);
  Serial.println("V");

  Serial.print(P, 1);
  Serial.println("KPa");
  Serial.println();

  delay(500);
}
