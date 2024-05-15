#include <ESP32Servo.h>
#define sensorPin 18

Servo servo;

void setup() {
  servo.attach(21);
  servo.write(90);
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  if (digitalRead(sensorPin)) {
    for (int pos = 0; pos <= 180; pos += 1) {
      servo.write(pos);
      delay(15);
    }
  }
}