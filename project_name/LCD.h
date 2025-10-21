/*********************************************************************
 * @file  LCD.h
 * @author 
 * @brief Header file for the LED class representing a peripheral LED
 *********************************************************************/
#ifndef LCD_H_
#define LCD_H_

#include "Peripheral.h"

/**
 * @class LCD
 * @brief Class representing an LCD connected to a specified pin
 */
class LCD : public Peripheral {
private:
    int pin;  // Pin connected to the LCD
public:
    /**
     * @brief Constructor for the LCD class
     * @param pin The pin number where the LCD is connected
     */
    Led(int pin);

    /**
     * @brief Destructor for the LCD class
     */
    ~Led() {};

    /**
     * @brief Initializes the LCD
     * Sets the LCD pin as an OUTPUT and turns it OFF by default.
     */
    void init() override;
};

#endif 
