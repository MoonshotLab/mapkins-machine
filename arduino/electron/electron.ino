#include "Particle.h"

// shouts to https://github.com/rickkas7/serial_tutorial

// Constants
const unsigned long SEND_INTERVAL_MS = 7500;
const size_t NUM_STEPPERS = 4;

// Global variables
int currentStepper = 1;
unsigned long lastSend = 0;
int ledPin = D7;


void setup() {
  Serial.begin(9600);

  // Serial1 available on TX / RX pins
  // TX -> Arduino RX
  // RX -> Arduino TX
  Serial1.begin(9600);

  pinMode(ledPin, OUTPUT);

  Particle.function("dispense", dispense);
}

void loop() {
  return;
  // testLoop();
}

int dispense(String stepperNum) {
  digitalWrite(ledPin, HIGH); // turn on led
  Serial1.println(stepperNum);
  Particle.publish("dispense", stepperNum);
  delay(500);
  digitalWrite(ledPin, LOW); // turn off led
  return 1;
}

void testLoop() {
  if (millis() - lastSend >= SEND_INTERVAL_MS) {
    if (currentStepper > NUM_STEPPERS) {
      currentStepper = 1;
    }

    lastSend = millis();
    dispense((String)currentStepper);
    currentStepper++;
  }
}
