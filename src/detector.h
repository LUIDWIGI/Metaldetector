//
// Created by empir on 27-11-2024.
//

#ifndef DETECTOR_H
#define DETECTOR_H
#include "arduino.h"



class detector {
  // Fields
  private:
    u16 sensorPin;
    u16 sensorValue{};
    float sensorVoltage{};
    float maxSensorVoltage;
    u8 sensorResolution;


  // Methods
  private:

    float bitsToVoltage(u16 bits);

  public:
    /**
    * @brief Constructor for the detector class.
    *
    * @param sensorPin The pin number to which the sensor is connected.
    */
    detector(u16 sensorPin, u8 sensorResolution, float maxSensorVoltage);

    /**
    * @brief Destructor for the detector class.
    */
    ~detector();

    /**
    * @brief Changes the sensor pin.
    *
    * This method updates the sensor pin to a new specified pin.
    *
    * @param newSensorPin The new pin number to which the sensor will be connected.
    */
    void changePin(u16 sensorPin);

    /**
    * @brief Reads the sensor value.
    *
    * This method reads the value from the sensor connected to the specified pin.
    *
    * @return The value read from the sensor.
    */
    u16 readSensor();

    void setMaxSensorVoltage(float maxSensorVoltage);

    void setSensorResolution(u8 sensorResolution);

    float getSensorMaxVoltage();

    u8 getSensorResolution();

    u8 getSensorPin();

    float readSensorVoltage();
};



#endif //DETECTOR_H
