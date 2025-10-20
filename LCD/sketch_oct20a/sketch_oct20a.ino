#include <Wire.h>
#include "rgb_lcd.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

rgb_lcd lcd;
//Connexion au réseau
const char *ssid = "Pctom";
const char *password = "12345678";

//Création du client réseau
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org");

//Tableau Horaire des bus des ligne 44 et L7
struct Horaire {
  int heure;
  int minute;
};

Horaire bus44[] = {
  {6, 15}, {6, 24}, {6, 42}, {6, 56},
  {7, 12}, {7, 32}, {7, 47}, {7, 55},
  {8, 0},  {8, 20}, {8, 35}, {8, 55},
  {9, 14}, {9, 26}, {9, 40}, {9, 56},
  {10, 9}, {10, 26}, {10, 48}, {10, 57},
  {11, 15}, {11, 32}, {11, 48}, {11, 54},
  {12, 0}, {12, 20}, {12, 33}, {12, 57},
  {13, 9}, {13, 28}, {13, 37}, {13, 54},
  {14, 12}, {14, 28}, {14, 44}, {14, 50},
  {15, 0}, {15, 16}, {15, 33}, {15, 50},
  {16, 6}, {16, 22}, {16, 38}, {16, 55},
  {17, 6}, {17, 25}, {17, 41}, {17, 57},
  {18, 10}, {18, 27}, {18, 40}, {18, 53},
  {19, 8}, {19, 21}, {19, 35}, {19, 50},
  {20, 5}, {20, 23}, {20, 44}, {20, 50},
  {21, 6}, {21, 28}, {21, 50},
  {22, 17}, {22, 55},
  {23, 34},
  {0, 9}, {0, 46}
};
Horaire busL7[] = {
  {6, 3}, {6, 35}, {6, 50},
  {7, 16}, {7, 38}, {7, 51},
  {8, 6}, {8, 23}, {8, 42}, {8, 51},
  {9, 5}, {9, 18}, {9, 34}, {9, 49},
  {10, 2}, {10, 18}, {10, 29}, {10, 44},
  {11, 5}, {11, 18}, {11, 32}, {11, 46},
  {12, 1}, {12, 12}, {12, 31}, {12, 50},
  {13, 2}, {13, 23}, {13, 42}, {13, 57},
  {14, 12}, {14, 27}, {14, 42}, {14, 57},
  {15, 17}, {15, 37}, {15, 52}, {15, 57},
  {16, 7}, {16, 23}, {16, 38}, {16, 53},
  {17, 8}, {17, 25}, {17, 40}, {17, 53},
  {18, 8}, {18, 23}, {18, 37}, {18, 52},
  {19, 7}, {19, 22}, {19, 35}, {19, 50},
  {20, 4}, {20, 18}, {20, 33}, {20, 52},
  {21, 11}, {21, 41},
  {22, 11}, {22, 41},
  {23, 11}, {23, 41},
  {0, 9}, {0, 38}
};
const int nbbus44 = sizeof(bus44)/sizeof(bus44[0]);
const int nbbusL7 = sizeof(busL7)/sizeof(busL7[0]);

//On convertit toutes les heures en minutes pour faciliter les calculs
int conversion_min(const Horaire &h){
  return h.heure*60+ h.minute;
}

//Destinations: 
String ps = "Paul-Sab";
String empalot ="Empalot";
String storens = "Saint-Orens";
String nombus44 ="44";
String nombusL7 ="L7";

int pos = 0;

int prochainBus(const Horaire h[], int nbbus) {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  int currentHour = (epochTime % 86400L) / 3600;
  int currentMinute = (epochTime % 3600) / 60;
  int now = currentHour * 60 + currentMinute;
  for(int i = 0; i < nbbus;i++){
    int bustime = conversion_min(h[i]);
    if(bustime >= now){
      int diff = bustime - now;
      Serial.printf("\nprochain bus dans %d min",diff);
      return diff;
    }
  }
  return -1;
}

void setup() {
  Serial.begin(115200);

  lcd.begin(16, 2);  // Écran 16 colonnes, 2 lignes

  //Connect wifi
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    lcd.print(".");
    Serial.print(WiFi.status());
  }
  Serial.println("\nWiFi connecté !");
  lcd.print("Connected to ");lcd.print(ssid);
  delay(1000);
  lcd.clear();   
  //NTPClient
  timeClient.begin();
  timeClient.setTimeOffset(7200);

}

void loop() {
  timeClient.update();
  String formattedTime = timeClient.getFormattedTime().substring(0,5);

  String info1 = nombus44 + " " + ps + " " + String(prochainBus(bus44, nbbus44)) + "min";
  String info2 = nombusL7 + " " + ps + " " + String(prochainBus(busL7, nbbusL7)) + "min";
  String ligne1 = info1.substring(pos, pos + 16);
  String ligne2 = info2.substring(pos, pos + 16);
  lcd.setCursor(0,0);
  lcd.print(ligne1);
  lcd.setCursor(0,1);
  lcd.print(ligne2);
  delay(00);
  pos++;
  if (pos > max(info1.length(), info2.length()) - 16) {
    
    delay(3000);
    lcd.clear();
    pos = 0;
    lcd.setCursor(5,0);
    lcd.print(formattedTime);
    delay(3000);
    lcd.clear();
  }
  

  /*
  for (int i = 0; i < info1.length(); i++) {
    lcd.print(info1[i]);
    delay(700);
  }
   for (int i = 0; i < info2.length(); i++) {
    lcd.print(info2[i]);
    delay(700);
  }*/
  //lcd.printf("%s-%s %d min",nombus44,ps, prochainBus(bus44,nbbus44));delay(2000);
  //lcd.noAutoscroll();
  //lcd.setCursor(0,1);
  //lcd.autoscroll();
  //lcd.printf("%s - %s - %d min ;",nombusL7,ps, prochainBus(busL7,nbbusL7));delay(6000);
}
