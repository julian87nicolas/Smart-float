// Librerias de wifi esp8266
#include <ESP8266WiFi.h>

// WifiManager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

void crearSensores() {
  http.begin(TEMPERATURA);
  http.addHeader("Content-Type", "application/json");
  http.POST("{\"name\":\"StempMaceta\",\"type\":\"temperature\",\"unit\":\"C\"}");
  http.end();
  http.begin(HUMEDAD);
  http.addHeader("Content-Type", "application/json");
  http.POST("{\"name\":\"ShumMaceta\",\"type\":\"humidity\",\"unit\":\"%\"}");
  http.end();
  http.begin(LUZ);
  http.addHeader("Content-Type", "application/json");
  http.POST("{\"name\":\"SluzMaceta\",\"type\":\"light\",\"unit\":\"%\"}");
  http.end();
}

void setup() {
  // Inicializacion de la placa
    Serial.begin(115200);
}

void loop(){

}
