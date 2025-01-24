//
// Created by Jordi on 3-12-2024.
//

#include "detectors.h"

detectors::detectors(u8 amount, u16* detectorThresholds,u16 detectorsVerticalSeparation,
              u16 detectorsHorizontalSeparation, u8 measurementResolution, float maxVoltage) {
  // Initialize the fields.
  this->amount = amount;  // Limit amount to 4 detectors
  this->measurementResolution = measurementResolution;
  this->maxVoltage = maxVoltage;
  this->detectorThresholds = detectorThresholds;
  this->detectorsVerticalSeparation = static_cast<u32>(detectorsVerticalSeparation) * 1000;
  this->detectorsHorizontalSeparation = detectorsHorizontalSeparation;

  detectorsData = new u16[amount]; // Create an array to store the sensor values.

  detectors_p = new detector*[amount]; // Create a new array of detector pointers.
  // Create detector objects and store them in the array.
  for (u8 i = 0; i < amount; i++) {
    detectors_p[i] = new detector(A0 + i, measurementResolution, maxVoltage);
  }
}

detectors::~detectors() {
    // Delete the detector objects.
    for (u8 i = 0; i < amount; i++) {
      delete detectors_p[i];
    }
    // Delete the array of detector pointers.
    delete[] detectors_p;
}

bool detectors::readSensors() {
  // Read the sensor values into data array.
  for (u8 i = 0; i < amount; i++) {
    detectorsData[i] = detectors_p[i]->readSensor();
  }

  // Check if there is a speed value
  if (speed != 0) {
    lengthCheck();
    if (length != 0) {
      // If there are length and speed values, return true
      return true;
    }
    // Otherwise measure speed
  } else {
    speedCheck();
  }
    // If there are no length and speed values, return false
  return false;
}

void detectors::reset() {
  // Reset the length, speed and width values
  length = 0;
  speed = 0;
  width = 0;
  length_detected = false;
  speed_detected = false;
  length_timeDetected = 0;
  speed_timeDetected = 0;
}

void detectors::speedCheck() {
  // Check if speed detection is active
  if (speed_detected) {
    // If active, check if object is under the back detector
    if (detectorsData[2] >= detectorThresholds[2] + 100) {
      speed_detected = false; // Flag speed detection as not started
      speed = detectorsVerticalSeparation / (millis() - speed_timeDetected); // V = s / △t
      speed_timeDetected = 0;
    }
  }
  // If not active, check if object is under the front speed detector
  else if (detectorsData[0] >= detectorThresholds[0] + 100) {
    speed_detected = true;  // Flag speed detection started
    speed_timeDetected = millis();  // Store time of detection
  }

}

void detectors::lengthCheck() {
  // Check if the object has been under the length detector
  if (length_detected) {
    // If active, check if object is no longer under the length detector
    if (detectorsData[2] < detectorThresholds[2]) {
      length_detected = false; // Flag length detection as not started
      length = (speed * ((millis() - length_timeDetected)/100)) / 10;  // s = V * △t
      length_timeDetected = 0;
    }
    // When the length detection is active, also check the width
    widthCheck();
  }
  // If not active, check if object is under the length detector
  else if (detectorsData[2] >= detectorThresholds[2] + 100) {
    length_detected = true; // Flag length detection started
    length_timeDetected = millis(); // Store time of detection
  }
}

void detectors::widthCheck() {
  // Data for the width detector
  u16 currWidth = 0; // Current width of the object

  // Throw error for not enough detectors for width
  if (amount < 3) {
    printf("Not enough detectors to check width");
  }
  // Algorithm for 3 sensors
  else if (amount == 3) {
    // Check if the object is under the length sensor and the width sensor
    if (detectorsData[2] >= detectorThresholds[2] && detectorsData[1] >= detectorThresholds[1]) {
      currWidth = detectorsHorizontalSeparation;
    }
  }
  // Algorithm for 4 sensors
  else {
    // Check if the object is under the length sensor and both width sensor
    if (detectorsData[2] >= detectorThresholds[2] && detectorsData[1] >= detectorThresholds[1] && detectorsData[3] >= detectorThresholds[3]) {
      currWidth = detectorsHorizontalSeparation * 2;
    }
    // Check if the object is under the length sensor and the first width sensor
    else if (detectorsData[2] >= detectorThresholds[2] && detectorsData[1] >= detectorThresholds[1]) {
      currWidth = detectorsHorizontalSeparation;
    }
    // Check if the object is under the length sensor and the second width sensor
    else if (detectorsData[2] >= detectorThresholds[2] && detectorsData[3] >= detectorThresholds[3]) {
      currWidth = detectorsHorizontalSeparation;
    }
  }

  // Check if the current width is larger than the maximum width
  if (currWidth > width) {
    width = currWidth; // Make current width maximum width
  }
}

u16 detectors::getLength() {
  return length;
}

u16 detectors::getSpeed() {
  return speed;
}

u16 detectors::getWidth() {
  return width;
}