#include <Arduino.h>
#include <detectors.h>

u8 detectorsAmount = 0;  // Amount of detectors
#define UPDATE_RATE 10  // Update rate in ms

#define HORIZONTAL_SEPARATION 170  // Horizontal separation between detectors in mm
#define VERTICAL_SEPARATION 235  // Vertical separation between detectors in mm

u32 lastUpdate = 0; // Last time sensors updated
u32 lastSend = 0; // Last time data sent

u16 speed, length, width; // Variables for the speed, length and width of the object

u16 thresholds[1] = {100}; // Detectors thresholds

bool enabled = false; // Flag to enable/disable the system

detectors* Detectors;
void setup() {
  Serial.begin(9600);
  while (Serial.available() == 0) {}
  if (Serial.read() == '!') {
    if (Serial.read() == 'a') {
      detectorsAmount = Serial.read();
    }
  }
  Detectors = new detectors(detectorsAmount, thresholds, VERTICAL_SEPARATION, HORIZONTAL_SEPARATION);
}

void loop() {
  // Read serial commands
  if (Serial.available() > 0) {
    if (Serial.read() == '!') {
      switch (Serial.read()) {
        case 's':
          if (Serial.read() == '1') {
            enabled = true;
            Detectors->reset();
          } else if (Serial.read() == '0') {
            enabled = false;
          }
          break;
        default:
          break;
      }
    }
  }

  if (enabled) {
    // Update measurements based on update rate
    if (millis() - lastUpdate >= UPDATE_RATE) {
      if (Detectors->readSensors()) {
        speed = Detectors->getSpeed();
        length = Detectors->getLength();
        width = Detectors->getWidth();
        enabled = false;
        Serial.print("?s");
        Serial.println(speed);
        Serial.print("?l");
        Serial.println(length);
        Serial.println("?d");
        Serial.print("?w");
        Serial.println(width);
      }
      lastUpdate = millis();
    }
  }
}