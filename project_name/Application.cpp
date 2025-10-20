/*********************************************************************
 * @file  Apllication.cpp
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"
#include "Peripheral.h"
#include "Led.h"


Application::Application()
{}
  
Application::~Application()
{}  

void Application::init(void)
{
   Serial.begin(921600);   // Open serial communication at 115200 baud
   Serial.println("Initialisation réussie");
}


void Application::run(void)
{
  Led myLed(D5);
  myLed.init();
  
  myLed.high();
  delay(2000);
  myLed.low();
  delay(2000);
}
