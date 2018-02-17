/*
  MSP430 powered moisture sensor

  Using MSP430 + YL-69 it reads the soil moisture and displays it on 3 LEDs.

  Created 18 02 2017
  By Dejan Noveski
  Modified 18 02 2017
  By Dejan Noveski

  https://github.com/dekomote/iot

*/


#define SOIL_PIN 5
#define R_LED 6
#define Y_LED 7
#define G_LED 8



int thresholdUp = 900; // Tweak this for better accuracy
int thresholdDown = 600; // Tweak this for better accuracy

 
void setup() {
  // Set LED pins as outputs
  pinMode(R_LED, OUTPUT);
  pinMode(Y_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  // Set sensor as input
  pinMode(SOIL_PIN, INPUT);
}
 
void loop() {
  int sensorValue = readSoil();
  if(sensorValue > thresholdUp) {
    digitalWrite(G_LED, LOW);
    digitalWrite(Y_LED, LOW);
    digitalWrite(R_LED, HIGH);
  }
  else if(sensorValue < thresholdDown){
    digitalWrite(R_LED, LOW);
    digitalWrite(Y_LED, LOW);
    digitalWrite(G_LED, HIGH);
  }
  else {
    digitalWrite(R_LED, LOW);
    digitalWrite(G_LED, LOW);
    digitalWrite(Y_LED, HIGH);
  }
}

int readSoil()
{
    return analogRead(SOIL_PIN); // Read the sensor value
}
