/*********************************************************************
 * @file  Ultrasonic.h
 * @author 
 * @brief Header file for the Ultrasonic class representing a peripheral Ultrasonic
 *********************************************************************/
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "Peripheral.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

/**
 * @class Led
 * @brief Class representing an Ultrasonic connected to a specified pin
 */
class Ultrasonic : public Peripheral {
private:
    int pin;  // Pin connected to the Ultrasonic

public:
    /**
     * @brief Constructor for the Ultrasonic class
     * @param pin The pin number where the Ultrasonic is connected
     */
    Ultrasonic(int pin);

    /**
     * @brief Destructor for the Ultrasonic class
     */
    ~Ultrasonic() {};

    /**
     * @brief Initializes the Ultrasonic
     * Sets the Ultrasonic pin as an OUTPUT and turns it OFF by default.
     */
    void init() override;

    long MeasureInCentimeters(uint32_t timeout = 1000000L);
    long MeasureInMillimeters(uint32_t timeout = 1000000L);
    long duration(uint32_t timeout = 1000000L);

};

#endif 
