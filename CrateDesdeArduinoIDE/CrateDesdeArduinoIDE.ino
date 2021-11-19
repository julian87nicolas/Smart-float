// Librerias de wifi esp8266
#include <ESP8266WiFi.h>

// WifiManager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <StreamString.h>
#include "Sensores.h" // json de creacion de los sensores de temperatura y radiacion UV, ubicados en Sensores.h


extern char *temp;
extern char *radUV;
extern char *entity;
extern char *suscTemp;
extern char *suscRadUV;

HTTPClient http1, http2, http3, http4;
WiFiClient cliente;

String ssid, pass;

void creaEntidad() {
  String host = "http://147.182.194.244:1026/v2/entities";
  String payload;
  int httpCode;              

  http1.begin(cliente,host);
  delay(1000);

  http1.addHeader("Content-Type", "application/json");
  httpCode = http1.POST(entity);
  payload = http1.getString();
  //Serial.println(httpCode);
  Serial.println("Entidad creada.");
  Serial.print("Respuesta del servidor: ");
  Serial.println(payload);

  http1.end();

  Serial.println("Fin  de la creacion de entidad");
}

void registraSensores(){
  String host = "http://147.182.194.244:4041/iot/devices";
  String payload;
  int httpCode;

  http2.begin(cliente, host);
  delay(1000);

  http2.addHeader("fiware-service", "openiot");
  http2.addHeader("fiware-servicepath", "/");
  http2.addHeader("Content-Type", "application/json");
  httpCode = http2.POST(temp);
  payload = http2.getString();
  Serial.println("Creando Sensor 1");
  Serial.print("Respuesta del servidor al crear sensor de Temperatura: ");
  Serial.println(payload);

  http2.addHeader("fiware-service", "openiot");
  http2.addHeader("fiware-servicepath", "/");
  http2.addHeader("Content-Type", "application/json");
  httpCode = http2.POST(radUV);
  payload = http2.getString();
  Serial.println("Creando Sensor 2");
  Serial.print("Respuesta del servidor al crear sensor de Radiacion UV: ");
  Serial.println(payload);

  http2.end();
  Serial.println("Fin  de la creacion de sensores");
  
}

void quantumLeap(){
  String host = "http://147.182.194.244:1026/v2/subscriptions/";
  int httpCode;
  String payload;
  http3.begin(cliente, host);
    
  http3.addHeader("fiware-service", "openiot");
  http3.addHeader("fiware-servicepath", "/");
  http3.addHeader("Content-Type", "application/json");

  httpCode = http3.POST(suscTemp);
  Serial.println("Suscripcion a quantum leap Temperatura.");
  Serial.print("Respuesta del servidor: ");
  payload = http3.getString();
  Serial.println(payload);

  http3.addHeader("fiware-service", "openiot");
  http3.addHeader("fiware-servicepath", "/");
  http3.addHeader("Content-Type", "application/json");
  httpCode = http3.POST(suscRadUV);
  Serial.println("Suscripcion a quantum leap Radiacion UV.");
  Serial.print("Respuesta del servidor: ");
  payload = http3.getString();
  Serial.println(payload);
  
  http3.end();  
}

void enviarDato(int valor, int sensor){
  String RadUV = "http://147.182.194.244:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=RadUV";
  String Temp = "http://147.182.194.244:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=TempAgua";
  String data;
  String seleccion[2] = ["TempAgua", "RadUV"];
  int httpCode;
  
  Serial.print("Posteando: ");
  Serial.println(data);
  Serial.print("En el sensor: ");
  Serial.println(seleccion[sensor]);
  
  if(sensor == 1){
    http4.begin(cliente, RadUV);
    data = String("r|") + String(valor);
  }
  if(sensor == 2){
    http4.begin(cliente, TempAgua);
    data = String("t|") + String(valor);
  }

  httpCode = http4.POST(data);
  
}

void setup() {
  WiFiManager wifi;
  //wifi.resetSettings();
  delay(1000);
  wifi.autoConnect("BOYA");
  
  Serial.begin(115200);
  creaEntidad();

  registraSensores();

  quantumLeap();
}

void loop() {
  int valor = 0, seleccion = 0;
  Serial.print("Ingrese un valor a enviar");
  while(valor == 0){
    valor = Serial.parseInt();
  }
  Serial.println("Seleccione un sensor:");
  Serial.println("1 - RadUv");
  Serial.println("2 - TempAgua");
  while(seleccion != 1 || seleccion !=2){
    seleccion = Serial.parseInt();
  } 
  
  enviarDato(valor, seleccion);
}