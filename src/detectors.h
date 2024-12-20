//
// Created by Jordi on 3-12-2024.
//

#ifndef METALDETECTOR_DETECTORS_H
#define METALDETECTOR_DETECTORS_H

#include "arduino.h"
#include "detector.h"

typedef u8 pin;

class detectors {

    // Fields
  private:
    // Detector fields
    u8 amount;
    u8 measurementResolution;
    float maxVoltage;
    u16* detectorThresholds;

    // Detectors fields
    detector** detectors_p;
    u16* detectorsData;
    u16 detectorsVerticalSeparation = 0; // Vertical distance between the detectors in mm
    u16 detectorsHorizontalSeparation = 0;  // Horizontal distance between the detectors in mm

    // Length fields
    u16 length = 0; // Length in mm

    // Speed fields
    u16 speed = 0; // Speed in mm/s

    // Width fields
    u16 width = 0; // Width in mm

    // Methods
  public:
    /**
     * @brief Constructor for the detectors class.
     *
     * @param amount The amount of detectors.
     * @param measurementResolution The resolution of the measurements. (Default: 10)
     * @param maxVoltage The maximum voltage that can be read by the arduino. (Default: 5.0)
     * @param detectorThresholds The thresholds for the detectors. (Default: nullptr)
     * @param detectorsVerticalSeparation The vertical separation between the detectors. (Default: 100)
     * @param detectorsHorizontalSeparation The horizontal separation between the detectors. (Default: 100)
     */
    detectors(u8 amount, u8 measurementResolution = 10, float maxVoltage = 5.0, u16* detectorThresholds = nullptr,
              u16 detectorsVerticalSeparation = 100, u16 detectorsHorizontalSeparation = 100);

    /**
      * @brief Destructor for the detectors class.
      */
    ~detectors();

    //Getters

    u16 getLength();

    u16 getSpeed();

    u16 getWidth();

    /**
     * @brief Read the sensors connected to the arduino.
     *
     * @note Run this inside of a loop in the main function.
     */
    void readSensors();

  private:
    /**
     * @brief Check speed of the belt.
     * @note This method may take more than 1 loop to detect the speed.
     */
    void speedCheck();

    /**
     * @brief Check the length of the object.
     * @note This method may take more than 1 loop to detect the length.
     */
    void lengthCheck();

    void widthCheck();
};


#endif //METALDETECTOR_DETECTORS_H
