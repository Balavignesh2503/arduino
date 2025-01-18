const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

void setup() {
  Serial.begin(9600);
}
void loop() {
  int flameSensor = analogRead(A0);
  int range = map(flameSensor, sensorMin, sensorMax, 0, 3);

  // range value:
  switch (range) {
  case 0:
    Serial.println("Fire within 40cm");
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("Fire between 40cm - 1m");
    break;
  case 2:    // No fire detected.
    Serial.println("No Fire");
    break;
  }
  delay(1000);  // 1 second be
}

