/*********************************************************************
 * @file  LCD.cpp
 * @author 
 * @brief Implementation file for the LCD class
 *********************************************************************/
#include "LCD.h"
#include <Arduino.h>

//#define LED_PIN D5

/**
 * @brief Constructor for the Led class
 * @param pin The pin number to which the LEDLCDis connected
 */
LCD::LCD(int pin) : Peripheral("LCD"), pin(pin) {}

/**
 * @brief Initializes the LCD
 * Sets the pin mode to OUTPUT and ensures the LCD is turned off by default.
 */
void Led::init() {
  Serial.begin(115200);        // Initialize serial communication at 115200 baud
}
