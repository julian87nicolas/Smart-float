//Librerias necesarias para la comunicacion wifi

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <StreamString.h>

// Funciones
void inicializar_Wifi();
void postear_temperatura(String valor);
void postear_humedad(String valor1);
void postear_luz(String valor2);
