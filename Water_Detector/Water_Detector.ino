#include <Tone.h>

int waterSensor = A0;    // Water sensor analog pin
int relayPin = 8;        // Relay control pin
int threshold = 600;     // Adjust based on sensor readings

Tone buzzer;             // Create Tone object

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Relay OFF initially
  buzzer.begin(9);              // Buzzer connected to pin 9
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(waterSensor);
  Serial.print("Water Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue > threshold) {
    // Water detected
    digitalWrite(relayPin, HIGH);

    // Play alert sound (frequency 1000 Hz)
    buzzer.play(1000, 500); // frequency, duration (ms)

    Serial.println("WATER DETECTED → Relay ON");
  } 
  else {
    // No water detected
    digitalWrite(relayPin, LOW);

    // Ensure buzzer is silent
    buzzer.stop();

    Serial.println("NO WATER → Relay OFF");
  }

  delay(500);
}
