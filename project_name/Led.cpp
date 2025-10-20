/*********************************************************************
 * @file  Led.cpp
 * @author 
 * @brief Implementation file for the Led class
 *********************************************************************/
#include "Led.h"
#include <Arduino.h>

//#define LED_PIN D5

/**
 * @brief Constructor for the Led class
 * @param pin The pin number to which the LED is connected
 */
Led::Led(int pin) : Peripheral("Led"), pin(pin) {}

/**
 * @brief Initializes the LED
 * Sets the pin mode to OUTPUT and ensures the LED is turned off by default.
 */
void Led::init() {
  Serial.begin(115200);        // Initialize serial communication at 115200 baud
  pinMode(pin, OUTPUT);        // Configure the pin as an output
  digitalWrite(pin, LOW);      // Turn the LED off by default
}

/**
 * @brief Turns the LED off
 */
void Led::low() {
  digitalWrite(pin, LOW);      // Turn the LED off
}

/**
 * @brief Turns the LED on
 */
void Led::high() {
  digitalWrite(pin, HIGH);     // Turn the LED on
}

void Led::increaseBrightness(int led_brightness){
  if(led_brightness <= 255){
    analogWrite(pin, led_brightness);
  }
}

void Led::decreaseBrightness(int led_brightness){
  if(led_brightness >= 0){
    analogWrite(pin, led_brightness);
  }
}
