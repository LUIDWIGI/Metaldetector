//
// Created by empir on 27-11-2024.
//

#include "detector.h"

detector::detector(u16 sensorPin, u8 sensorResolution, float maxSensorVoltage) {
  this->sensorPin = sensorPin;
  this->sensorResolution = sensorResolution;
  this->maxSensorVoltage = maxSensorVoltage;
  pinMode(sensorPin, INPUT);
  analogReference(DEFAULT);
}

detector::~detector() {
  // Destructor
}

u16 detector::readSensor() {
  u32 sensorValues = 0;

  for (uint_fast8_t i = 0; i < 5; i++) {
    sensorValues += analogRead(this->sensorPin);
  }
  this->sensorValue = sensorValues / 5;

  return this->sensorValue;
}

void detector::changePin(u16 sensorPin) {
  this->sensorPin = sensorPin;
  pinMode(sensorPin, INPUT);
}

void detector::setMaxSensorVoltage(float maxSensorVoltage) {
  this->maxSensorVoltage = maxSensorVoltage;
}

void detector::setSensorResolution(u8 sensorResolution) {
  this->sensorResolution = sensorResolution;
}

float detector::getSensorMaxVoltage() {
  return this->maxSensorVoltage;
}

u8 detector::getSensorResolution() {
  return this->sensorResolution;
}

u8 detector::getSensorPin() {
  return this->sensorPin;
}

float detector::readSensorVoltage() {
  this->sensorVoltage = analogRead(bitsToVoltage(this->sensorValue));
  return this->sensorVoltage;
}

float detector::bitsToVoltage(u16 bits) {
  return (bits * maxSensorVoltage) / (float)(2^sensorResolution);
}