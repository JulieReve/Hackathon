#include <Arduino.h>
#include "json.h"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Configuration WiFi
const char* ssid = "Pctom";
const char* password = "12345678";

// Configuration serveur
const char* serverBaseURL = "http://192.168.37.127:50000"; // Base du serveur
const char* postEndpoint = "/data"; // Endpoint POST
const char* deleteEndpoint = "/data"; // Endpoint DELETE

void initjson(){
  WiFi.begin(ssid, password);
   Serial.print("Connexion au WiFi");

   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
}

bool sendJSON(String json) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String fullURL = String(serverBaseURL) + String(postEndpoint);

    if (http.begin(client, fullURL)) {
      http.addHeader("Content-Type", "application/json");

      int httpResponseCode = http.POST(json);

      Serial.print("Code HTTP (POST): ");
      Serial.println(httpResponseCode);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("Réponse du serveur: ");
        Serial.println(response);
      }

      http.end();
      return (httpResponseCode == 201);
    }
  }
  return false;
  }

bool deleteData(String id) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
 
    // Construire l'URL avec l'id
    String fullURL = String(serverBaseURL) + "/data/" + id;
    Serial.print(fullURL);
  
    if (http.begin(client, fullURL)) {
      int httpResponseCode = http.sendRequest("DELETE");
  
      Serial.print("Code HTTP (DELETE): ");
      Serial.println(httpResponseCode);
 
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("Réponse du serveur: ");
        Serial.println(response);
      }

      http.end();
      return (httpResponseCode == 200 || httpResponseCode == 204);
    }
  }
  return false;
}
