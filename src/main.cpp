#include <Arduino.h>
#include <detectors.h>

#include "detector.h"

#define DETECTORS_AMOUNT 1  // Amount of detectors
#define UPDATE_RATE 10  // Update rate in ms
#define SEND_RATE 1000  // Send rate in ms

u32 lastUpdate = 0; // Last time sensors updated
u32 lastSend = 0; // Last time data sent

u16 speed, length, width; // Variables for the speed, length and width of the object
u16 lastSpeed, lastLength, lastWidth; // Variables for the last speed, length and width of the object

u16 thresholds[1] = {100}; // Detectors thresholds

bool enabled = false; // Flag to enable/disable the system

detectors* Detectors;
void setup() {
  Serial.begin(9600);
  Detectors = new detectors(DETECTORS_AMOUNT, thresholds);
}

void loop() {
  // Read serial commands
  if (Serial.available() > 0) {
    if (Serial.read() == '!') {
      switch (Serial.read()) {

        default:
          break;
      }
    }
  }

  if (enabled) {
    // Update measurements based on update rate
    if (millis() - lastUpdate >= UPDATE_RATE) {
      Detectors->readSensors();
      speed = Detectors->getSpeed();
      length = Detectors->getLength();
      width = Detectors->getWidth();
      lastUpdate = millis();
    }

    // Send data based on send rate
    if (millis() - lastSend >= SEND_RATE) {
      // Print serial data
      if (lastSpeed != speed) {

      }
      if (lastLength != length) {

      }
      if (lastWidth != width) {

      }
    }
  }
}