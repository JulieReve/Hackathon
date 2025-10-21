/*********************************************************************
 * @file  Ultrasonic.cpp
 * @author 
 * @brief Implementation file for the Ultrasonic class
 *********************************************************************/
#include "Ultrasonic.h"
#include <Arduino.h>

/**
 * @brief Constructor for the Ultrasonic class
 * @param pin The pin number to which the Ultrasonic is connected
 */
Ultrasonic::Ultrasonic(int pin) : Peripheral("Ultrasonic"), pin(pin) {}

/**
 * @brief Initializes the Ultrasonic
 * Sets the pin mode to OUTPUT and ensures the Ultrasonic is turned off by default.
 */
void Ultrasonic::init() {
  Serial.begin(115200);        // Initialize serial communication at 115200 baud
}

long Ultrasonic::duration(uint32_t timeout) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);
    long duration;
    duration = pulseIn(pin, HIGH, timeout);
    return duration;
}

/*The measured distance from the range 0 to 400 Centimeters*/
long Ultrasonic::MeasureInCentimeters(uint32_t timeout) {
    long RangeInCentimeters;
    RangeInCentimeters = duration(timeout) / 29 / 2;
    return RangeInCentimeters;
}

/*The measured distance from the range 0 to 4000 Millimeters*/
long Ultrasonic::MeasureInMillimeters(uint32_t timeout) {
    long RangeInMillimeters;
    RangeInMillimeters = duration(timeout) * (10 / 2) / 29;
    return RangeInMillimeters;
}
