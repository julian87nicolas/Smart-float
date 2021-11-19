// Librerias de wifi esp8266
#include <ESP8266WiFi.h>

// WifiManager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

// crear entidad de sensores en crate

HTTPClient http;
WiFiClient client;

void creaEntidad() {
  String host = "http://147.182.194.244:1026/v2/entities";
  String postData = '{
                        "id": "utn:ngsi-Id:Boyadarmedebaja:001",
                        "type": "Boya"
                      }';
  String payload;
  int httpCode;              

  http.begin(host);
  delay(1000);

  http.addHeader("Content-Type", "application/json");
  httpCode = http.POST(postData);
  payload = http.getString();
  Serial.println(httpCode);
  Serial.println(payload);

  http.end();
  
}



void setup() {
  // Conectar a wifi con WifiManager
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  wifiManager.autoConnect();
  // Obtener parametro WiFiClient de WifiManager
  client = wifiManager.getWiFiClient();


  Serial.begin(115200);
  inicializar_Wifi();
  creaEntidad();
}

void loop() {
  // Pedir valor por puerto serie y bloquear hasta que se reciba un valor
  int valor = 0;
  while (valor == 0) {
    valor = Serial.parseInt();
  }
  

}