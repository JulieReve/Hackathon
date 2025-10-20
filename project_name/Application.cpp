/*********************************************************************
 * @file  Apllication.cpp
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"
#include "Peripheral.h"
#include "Led.h"
#include "Ultrasonic.h"
#include "json.h"


Application::Application()
{}
  
Application::~Application()
{}  

void Application::init(void)
{
   Serial.begin(115200);   // Open serial communication at 115200 baud
   initjson();
   Serial.println("Initialisation réussie");
}


void Application::run(void)
{
  Led myLed(D5);
  Ultrasonic myUltra(D6);
  myLed.init();
  myUltra.init();
  int led_brightness = 0;
  bool dataPresentNotSend = true;
  bool dataNobodyNotSend = true;

  // Données JSON à envoyer
  String jsonData = "{\"nom\": \"Dudu\", \"email\": \"j@e.com\"}";

  while(true){
    Serial.println("The distance to obstacles in front is: ");
    //long RangeInCentimeters = myUltra.MeasureInCentimeters(); // two measurements should keep an interval
    long RangeInMillimeters = myUltra.MeasureInMillimeters();
    Serial.print(RangeInMillimeters);
    Serial.println(" mm");
    if (RangeInMillimeters < 1000 and led_brightness < 255){
      myLed.increaseBrightness(led_brightness);
      led_brightness = led_brightness + 10;

      if (dataPresentNotSend){
        if (sendJSON(jsonData)) {
          Serial.println("✅ Données envoyées avec succès !");
        } else {
          Serial.println("❌ Erreur lors de l'envoi !");
        }
        dataPresentNotSend = false;
        dataNobodyNotSend = true;
      }
     }
     if (RangeInMillimeters > 1000 and led_brightness >= 0){
      myLed.decreaseBrightness(led_brightness);
      led_brightness = led_brightness - 10;

      if(dataNobodyNotSend){
        if (deleteData("1")) { // supprime l'élément avec id = 1
          Serial.println("✅ Donnée supprimée avec succès !");
        } else {
          Serial.println("❌ Erreur lors de la suppression !");
        }
        dataNobodyNotSend = false;
        dataPresentNotSend = true;
      }
     }
     Serial.println(led_brightness);
    delay(250);
  }
}
