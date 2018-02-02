/*
  ESP32/Arduino powered geiger couter with RadiationD

  Using ESP32 or an Arduino + RadiationD geiger counter it
  reads and displays radiation.

  The circuit:
  * RadiationD 5V to VCC, GND to GND and pulse output to D13

  Created 02 02 2017
  By Dejan Noveski
  Modified 02 02 2017
  By Dejan Noveski

  https://github.com/dekomote/iot

*/

#define GEIGER_INPUT_PIN 13
#define LOG_PERIOD 20000
#define MINUTE 60000

unsigned long counts = 0; 
unsigned long cpm = 0;
unsigned long previousMillis = 0;

void tube_impulse() { // Captures count of events from Geiger counter board
  counts++;
}
 
void setup() {
  Serial.begin(115200);
  pinMode(GEIGER_INPUT_PIN, INPUT);
  interrupts(); // Enable interrupts (in case they were previously disabled)
  attachInterrupt(digitalPinToInterrupt(GEIGER_INPUT_PIN), tube_impulse, FALLING); // Define external interrupts
}
 
void loop() {
  unsigned long currentMillis = millis();
  unsigned long diffMillis = currentMillis - previousMillis;
  if(diffMillis >= LOG_PERIOD) {
    previousMillis = currentMillis;
    cpm = counts * diffMillis / MINUTE;
    Serial.println(cpm);
    counts = 0;
  }
}
