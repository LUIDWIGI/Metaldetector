//
// Created by Jordi on 3-12-2024.
//

#include "detectors.h"

detectors::detectors(u8 amount, u8 measurementResolution, float maxVoltage, u16* detectorThresholds
                     , u16 detectorsVerticalSeparation, u16 detectorsHorizontalSeparation) {
  // Initialize the fields.
  this->amount = amount ? amount > 4 : amount;  // Limit amount to 4 detectors
  this->measurementResolution = measurementResolution;
  this->maxVoltage = maxVoltage;
  this->detectorThresholds = detectorThresholds;
  this->detectorsVerticalSeparation = detectorsVerticalSeparation;
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

void detectors::readSensors() {
  // Read the sensor values into data array.
  for (u8 i = 0; i < amount; i++) {
    detectorsData[i] = detectors_p[i]->readSensor();
  }
  speedCheck();
  if (speed != 0) {
    lengthCheck();
  }
}

void detectors::speedCheck() {
  // Data for the speed detector
  static bool speed_detected = false;
  static u32 speed_timeDetected = 0;

  // Check if speed detection is active
  if (speed_detected) {
    // If active, check if object is under the lower detector
    if (detectorsData[2] >= detectorThresholds[2]) {
      speed_detected = false;
      speed = detectorsHorizontalSeparation / (millis() - speed_timeDetected); // V = s / t
    }
  }
  // If active, check if object is under the speed detector
  else if (detectorsData[0] >= detectorThresholds[0]) {
    speed_detected = true;
    speed_timeDetected = millis();  // Store time of detection
  }

}

void detectors::lengthCheck() {
  // Data for the length detector
  static bool length_detected = false;
  static u32 length_timeDetected = 0;

  // Check if the object is under the length detector
  if (length_detected) {
    // If active, check if object is not under the length detector
    if (detectorsData[2] < detectorThresholds[2]) {
      length_detected = false;
      length = speed * (millis() - length_timeDetected);  // s = V * t
    }
  }
  // Check if object is under the length detector
  else if (detectorsData[2] >= detectorThresholds[2]) {
    length_detected = true;
    length_timeDetected = millis(); // Store time of detection
  }
}

void detectors::widthCheck() {
  // Data for the width detector

  if (amount < 3) {
    printf("Not enough detectors to check width");
  }
  if (detectorsData[2] >= detectorThresholds[2] && detectorsData[1] >= detectorThresholds[1]) {
    width = detectorsHorizontalSeparation;
  }
  else if ((detectorsData[2] >= detectorThresholds[2] && detectorsData[1] >= detectorThresholds[1]) &&
    (detectorsData[2] >= detectorThresholds[2] && detectorsData[3] >= detectorThresholds[3])) {
    width = detectorsHorizontalSeparation * 2;
  }
  // // Algorithm for 3 sensors
  // else if (amount == 3) {
  //   if (detectorsData[2] >= detectorThresholds[2] && detectorsData[1] >= detectorThresholds[1]) {
  //     currWidth = detectorsData[2] - detectorsData[1];
  //     if (currWidth < maxWidth) {
  //       maxWidth = currWidth;
  //       width = map(maxWidth, 0, 2 ^ measurementResolution,
  //                   0, detectorsHorizontalSeparation); // Map the width measurement to the actual width in mm
  //     }
  //   }
  //   //Algorithm for 4 sensors
  // } else {
  //   // Check if the object is under the middle sensor and triggers the right sensor
  //   if (detectorsData[2] == (2^measurementResolution) && detectorsData[1] >= detectorThresholds[1]) {
  //     currWidth = 2^measurementResolution - detectorsData[1];
  //     if (currWidth < maxWidth) {
  //       maxWidth = currWidth;
  //       width = map(maxWidth, 0, 2 ^ measurementResolution,
  //                   0, detectorsHorizontalSeparation); // Map the width measurement to the actual width in mm
  //     }
  //     // Check if the object is under the middle sensor and triggers the left sensor
  //   } else if (detectorsData[2] == (2^measurementResolution) && detectorsData[3] >= detectorThresholds[3]) {
  //     currWidth = 2^measurementResolution - detectorsData[3];
  //     if (currWidth < maxWidth) {
  //       maxWidth = currWidth;
  //       width = map(maxWidth, 0, 2 ^ measurementResolution,
  //                   0, detectorsHorizontalSeparation); // Map the width measurement to the actual width in mm
  //     }
  //     // Check if the object is under the left sensor and triggers the right sensor
  //   } else if (detectorsData[1] >= (2^measurementResolution) && detectorsData[3] >= detectorThresholds[3]) {
  //     currWidth = detectorsData[1] - detectorsData[3];
  //     if (currWidth < maxWidth) {
  //       maxWidth = currWidth;
  //       width = map(maxWidth, 0, 2 ^ measurementResolution,
  //                   0, 2*detectorsHorizontalSeparation); // Map the width measurement to the actual width in mm
  //     }
  //  }
  //}
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