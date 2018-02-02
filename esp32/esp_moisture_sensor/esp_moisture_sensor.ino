/*
  ESP32 powered moisture sensor

  Using ESP32 + YL-69 it reads the soil moisture and writes via serial.
  The status of the plants will be posted on the internet.
  TODO: Post it to the internet

  The circuit:
  * list the components attached to each input
  * list the components attached to each output

  Created 02 02 2017
  By Dejan Noveski
  Modified 02 02 2017
  By Dejan Noveski

  https://github.com/dekomote/iot

*/
#include <WiFi.h>

#define SOIL_PIN 34
#define SOIL_POWER_PIN 23
#define LED 2
#define SSID "your-ssid-here"
#define PASS "your-passwd-here"

int thresholdUp = 250;
int thresholdDown = 80;

 
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(SOIL_POWER_PIN, OUTPUT);
  
  digitalWrite(SOIL_POWER_PIN, LOW); // Don't enable the sensor yet;
  
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  digitalWrite(LED, HIGH);
  Serial.println("Connected to the WiFi network");
}
 
void loop() {
  int sensorValue = readSoil();
  if(sensorValue > thresholdUp) {
    Serial.println("DRY AS FUCK");
  }
  else if(sensorValue < thresholdDown){
    Serial.println("WET WET WET!");  
  }
  delay(5000);
}

void blinkLed(){
  for(int i=0;i<=5;i++){
    digitalWrite(LED, LOW);
    delay(100);
    digitalWrite(LED, HIGH);
    delay(100);
  }
}

int readSoil()
{
    blinkLed();
    digitalWrite(SOIL_POWER_PIN, HIGH); // Power up the sensor
    delay(5000); // Wait for it to stabilize
    int val = analogRead(SOIL_PIN); // Read the sensor value
    digitalWrite(SOIL_POWER_PIN, LOW); // Disable the sensor
    return val;
}
