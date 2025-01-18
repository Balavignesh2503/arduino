const int flameSensorPin = A0;  // Analog pin A0 for MQ-2 sensor

void setup() {
  Serial.begin(9600);
  pinMode(flameSensorPin, INPUT);
}

void loop() {
  // Read analog value from the flame sensor
  int sensorValue = analogRead(flameSensorPin);
  
  // Print the sensor value to the serial monitor
  Serial.println("Sensor Value: " + String(sensorValue));

  // Check if the sensor value exceeds a threshold (adjust this threshold according to your setup)
  if (sensorValue > 500) {
    Serial.println("Flame detected!");
  }

  delay(1000);  // Delay for stability, adjust as needed
}
