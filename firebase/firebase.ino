#include <Adafruit_MLX90614.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <String.h>


Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int heart = A0;
float glucose = 0.0;

#define FB_HOST "fir-e9314-default-rtdb.firebaseio.com"
#define FB_AK "622yJVjuazbxIwtagNFLPcJbPYUpm2b0QL2QtRyX"
#define WIFI_NAME "hornor"
#define WIFI_PASS "ennatha solla"

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Adafruit MLX90614 test");

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  }

  pinMode(heart, INPUT);

  Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
  Serial.println("================================================");

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
  // Read and display MLX90614 sensor data
  float ambientTempC = mlx.readAmbientTempC();
  float objectTempC = mlx.readObjectTempC();
  // Serial.print("Ambient = "); Serial.print(ambientTempC);
  // Serial.print("*C\tObject = "); Serial.print(objectTempC); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  int pulseoxi=0;
  


  // Read and display heart rate data
  int hdata = analogRead(heart);
  delay(500);
  int bdata = analogRead(heart);
  
  String hout = String(hdata);
  int bpm=(bdata)/10;
  String finalbpm = hout.substring(0, 2);
  Serial.print("Heart Rate: ");
  Serial.print(finalbpm);
  Serial.println(" BPM");
  

  int babyRate =bpm;
  
  Serial.print("Baby's Heart Rate: ");
  Serial.print(bpm);
  Serial.println(" BPM");

  // Calculate and print the average as "glucose"
  // glucose = ( pulseoxi + objectTempC + hdata) / 10.0;
  // Serial.print("Glucose level: ");
  // String glu=String(glucose);
  // Serial.print(glu);
  // Serial.println();
  

    // Check if the heart rate is normal (between 110 and 160)
  int heartRate = finalbpm.toInt();

  // if (glucose<=160) {
  //   Serial.println("Glucose level is normal.");
  // }

  // else{
  //   Serial.println("Glucose level is not normal.");
  // }


  
   if ( babyRate >= 35 && babyRate <=175)
  {
    Serial.println("baby's Rate is normal.");
  }
  else
    {
    Serial.println("baby's Rate is not normal.");
  }

  if (heartRate >= 60 && heartRate <= 100) {
    Serial.println("Women's Heart Rate is normal.");
  }

  else{
    Serial.println("Women's Heart Rate is not normal.");
  }
delay(2000); // Adjust the delay as needed


  String temperature=String(mlx.readObjectTempF());
  String baby=String(babyRate);
  // Update Firebase with temperature, heart rate, and glucose values
  // Firebase.setString("temperature/ambient", ambientTempC);
  // Firebase.setString("Glucose", glu);
  Firebase.setString("HeartBeat", finalbpm);
  Firebase.setString("BabyHeartBeat", baby);
  Firebase.setString("Temperature", temperature);
  delay(2000); // Adjust the delay as needed
}

