#include <Arduino.h>
#include <detectors.h>

u8 detectorsAmount = 4;  // Amount of detectors
#define UPDATE_RATE 5  // Update rate in ms

#define HORIZONTAL_SEPARATION 170  // Horizontal separation between detectors in mm
#define VERTICAL_SEPARATION 375  // Vertical separation between detectors in mm

u32 lastUpdate = 0; // Last time sensors updated

bool started = false;

u16 speed, length, width; // Variables for the speed, length and width of the object

u16 thresholds[4] = {300, 400, 100, 400}; // Detectors thresholds

bool enabled = false; // Flag to enable/disable the system

detectors* Detectors;
void setup() {
  // Enable serial communication and initialize the detectors
  Serial.begin(9600);
  Detectors = new detectors(detectorsAmount, thresholds, VERTICAL_SEPARATION, HORIZONTAL_SEPARATION);
}

void loop() {

  // Read serial commands
  if (Serial.available() > 2) {
    char check = Serial.read();
    if (check == '!') { // Check if the command is valid
      char cmd = Serial.read();
      switch (cmd) { // Check the command
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
  // Check if the sensors should be enabled
  if (enabled) {
    // Update measurements based on update rate
    if (millis() - lastUpdate >= UPDATE_RATE) {
      // Check if there are new measurements to be sent
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