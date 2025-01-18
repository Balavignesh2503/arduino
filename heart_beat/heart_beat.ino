#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

int heart = A0;

#define FB_HOST "https://fir-e9314-default-rtdb.firebaseio.com"
#define FB_AK "622yJVjuazbxIwtagNFLPcJbPYUpm2b0QL2QtRyX"
#define WIFI_NAME "Redmi Note 9"
#define WIFI_PASS "nandhini"

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(heart, INPUT);

  WiFi.begin(WIFI_NAME, WIFI_PASS);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("#");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected");
  Serial.println(WiFi.localIP());
  Firebase.begin(FB_HOST, FB_AK);
}

void loop() {
  // Read and display heart rate data
  int hdata = analogRead(heart);

  
  String hout = String(hdata);

  String finalbpm = hout.substring(0, 2);
  Serial.print("Heart Rate: ");
  Serial.print(finalbpm);
  Serial.println(" BPM");

  // Check if the heart rate is normal (between 110 and 160)
  int heartRate = finalbpm.toInt();

  if (heartRate >= 60 && heartRate <= 100) {
    Serial.println("Women's Heart Rate is normal.");
  }
  else {
    Serial.println("Women's Heart Rate is not normal.");
  }
   // Adjust the delay as needed

  // Update Firebase with heart rate values
  Firebase.setString("HeartBeat", finalbpm);
  delay(2000); // Adjust the delay as needed
}
