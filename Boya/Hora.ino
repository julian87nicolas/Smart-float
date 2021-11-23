#include <NTPClient.h> //importamos la librería del cliente NTP
#include <ESP8266WiFi.h> //librería necesaria para la conexión wifi
#include <WiFiUdp.h> // importamos librería UDP para comunicar con 
                     // NTP

String hora_local() {

  String hora;
  
  WiFiUDP ntpUDP;

  NTPClient timeClient(ntpUDP, "0.south-america.pool.ntp.org",-10800,6000);

  timeClient.begin(); 

  timeClient.update(); //sincronizamos con el server NTP

  hora = timeClient.getFormattedTime();

  return hora;
}
