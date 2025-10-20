/*********************************************************************
 * @file  Apllication.cpp
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"
#include "Peripheral.h"
#include "Led.h"
#include "Ultrasonic.h"


Application::Application()
{}
  
Application::~Application()
{}  

void Application::init(void)
{
   Serial.begin(115200);   // Open serial communication at 115200 baud
   Serial.println("Initialisation réussie");
}


void Application::run(void)
{
  Led myLed(D5);
  Ultrasonic myUltra(D6);
  myLed.init();
  myUltra.init();
  int led_brightness = 0;

  
  //myLed.high();
  //delay(2000);
  //myLed.low();
  //delay(2000);

  while(true){
    Serial.println("The distance to obstacles in front is: ");
    //long RangeInCentimeters = myUltra.MeasureInCentimeters(); // two measurements should keep an interval
    long RangeInMillimeters = myUltra.MeasureInMillimeters();
    Serial.print(RangeInMillimeters);
    Serial.println(" mm");
    if (RangeInMillimeters < 2000 and led_brightness < 255){
      myLed.increaseBrightness(led_brightness);
      led_brightness = led_brightness + 10;
      }
     if (RangeInMillimeters > 2000 and led_brightness >= 0){
      myLed.decreaseBrightness(led_brightness);
      led_brightness = led_brightness - 10;
      }
     Serial.println(led_brightness);
    delay(250);
  }
}
