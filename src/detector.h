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
    /**
     * @brief Converts the bits to voltage.
     *
     * @param bits value in bits to convert to voltage
     *
     * @return Voltage level for the given bits
     */
    float bitsToVoltage(u16 bits);

  public:
    /**
    * @brief Constructor for the detector class.
    *
    * @param sensorPin The pin to which the sensor is connected.
    * @param sensorResolution The bit-resolution of the sensor.
    * @param maxSensorVoltage The maximum voltage that can be read by the arduino.
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
    * @param sensorPin The new pin to which the sensor will be connected.
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

    /**
     * @brief Changes the max sensor voltage.
     *
     * @param maxSensorVoltage change the max sensor voltage
     */
    void setMaxSensorVoltage(float maxSensorVoltage);

    /**
     * @brief Changes the sensor resolution.
     *
     * @param sensorResolution change the sensor resolution
     */
    void setSensorResolution(u8 sensorResolution);

    /**
     * @brief Get the sensor max voltage.
     *
     * @return The max sensor voltage.
     */
    float getSensorMaxVoltage();

    /**
     * @brief Get the sensor resolution.
     *
     * @return The sensor resolution.
     */
    u8 getSensorResolution();

    /**
     * @brief Get the sensor pin.
     *
     * @return The sensor pin.
     */
    u8 getSensorPin();

    /**
     * @brief Read the sensor voltage.
     *
     * @return The sensor voltage.
     */
    float readSensorVoltage();
};
#endif //DETECTOR_H
