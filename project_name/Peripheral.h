/*********************************************************************
 * @file  Peripheral.h
 * @author 
 * @brief Header file for the base class of all peripherals
 *********************************************************************/
#ifndef PERIPHERAL_H_
#define PERIPHERAL_H_

#include <Arduino.h>
#include <string>

/**
 * @class Peripheral
 * @brief Base class for all peripherals
 */
class Peripheral {
protected:
    String name;  // Name or identifier of the peripheral

public:
    /**
     * @brief Constructor for the Peripheral class
     * @param name The name or identifier of the peripheral
     */
    Peripheral(String name) : name(name) {}

    /**
     * @brief Destructor for the Peripheral class
     */
    virtual ~Peripheral() {}

    /**
     * @brief Pure virtual method for initializing peripherals
     */
    virtual void init() = 0;
};

#endif
