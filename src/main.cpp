#include <Arduino.h>
#include "detector.h"

u32 t1;
u32 t2;

bool stop = false;

detector* Detector1;
void setup() {
  Serial.begin(9600);
Detector1 = new detector(A1, 10, 5.0);
}

void loop() {
// write your code here
  if (stop) {
    return;
  } else {
    t1 = millis();
    for (u8 i = 0; i < 50; ++i) {
      Detector1->readSensor();
      stop = true;
    }
    t2 = millis();
    Serial.println((t2-t1));

  }
}