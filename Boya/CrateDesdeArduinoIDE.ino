
#include <ESP8266WiFi.h>

#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include "Sensores.h" // json de creacion de los sensores de temperatura y radiacion UV, ubicados en Sensores.h


extern char *temp;
extern char *radUV;
extern char *entity;
extern char *suscTemp;
extern char *suscRadUV;

int repeat[] ={0,0} ;

HTTPClient http1, http2, http3, http4;
WiFiClient cliente;

String ssid, pass;

void creaEntidad(String host) {
  //String host = "http://147.182.194.244:1026/v2/entities";    // direccion entidad
  String payload;
  int httpCode;              

  Serial.println("Creacion de entidad");
  http1.begin(cliente,host);

  http1.addHeader("Content-Type", "application/json");
  httpCode = http1.POST(entity);
  payload = http1.getString();                                // respuesta del servidor al post
  Serial.print("Respuesta del servidor: ");
  Serial.println(payload);

  http1.end();                                                // cierre de conexion http

  Serial.println("Fin  de la creacion de entidad");
}

void registraSensores(String host){
  //String host = "http://147.182.194.244:4041/iot/devices";
  String payload;
  int httpCode;

  http2.begin(cliente, host);

  http2.addHeader("fiware-service", "openiot");
  http2.addHeader("fiware-servicepath", "/");
  http2.addHeader("Content-Type", "application/json");
  httpCode = http2.POST(temp);
  payload = http2.getString();
  Serial.println("Creando Sensor 1");
  Serial.print("Respuesta del servidor al crear sensor de Temperatura: ");
  Serial.println(payload);

  if(payload.indexOf("DUPLICATE_DEVICE_ID") > 0){ // Verifica si el servidor devuelve error
    repeat[0] = 1;
    Serial.print("Sensor TempAgua repetido. ");
  }

  http2.addHeader("fiware-service", "openiot");
  http2.addHeader("fiware-servicepath", "/");
  http2.addHeader("Content-Type", "application/json");
  httpCode = http2.POST(radUV);
  payload = http2.getString();
  Serial.println("Creando Sensor 2");
  Serial.print("Respuesta del servidor al crear sensor de Radiacion UV: ");
  Serial.println(payload);
  
  if(payload.indexOf("DUPLICATE_DEVICE_ID") > 0){ // Verifica si el servidor devuelve error
    repeat[1] = 1;
    Serial.print("Sensor RadUV repetido. ");
  }
  
  http2.end();
  Serial.println("Fin  de la creacion de sensores");
  
}

void quantumLeap(String host){
  //String host = "http://147.182.194.244:1026/v2/subscriptions/";
  int httpCode;
  String payload;
  http3.begin(cliente, host);
  
  if(repeat[0] == 0){
    http3.addHeader("fiware-service", "openiot");
    http3.addHeader("fiware-servicepath", "/");
    http3.addHeader("Content-Type", "application/json");
  
    httpCode = http3.POST(suscTemp);
    Serial.println("Suscripcion a quantum leap Temperatura.");
    Serial.print("Respuesta del servidor: ");
    payload = http3.getString();
    Serial.println(payload);
  }
  else{
    Serial.println("Sensor TempAgua repetido, suscripcion a Quantum Leap abortada.");
  }
  if(repeat[1] == 0){
    http3.addHeader("fiware-service", "openiot");
    http3.addHeader("fiware-servicepath", "/");
    http3.addHeader("Content-Type", "application/json");
    httpCode = http3.POST(suscRadUV);
    Serial.println("Suscripcion a quantum leap Radiacion UV.");
    Serial.print("Respuesta del servidor: ");
    payload = http3.getString();
    Serial.println(payload);
  }
  else{
    Serial.println("Sensor RadUV repetido, suscripcion a Quantum Leap abortada.");
  }
  
  http3.end();  
}

void enviarDato(int valor, int sensor){
  // URL de cada sensor
  String RadUV = "http://147.182.194.244:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=RadUV";
  String TempAgua = "http://147.182.194.244:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=TempAgua";
  String data;
  int httpCode;
  
  Serial.print("Posteando: ");
  
  if(sensor == 1){
    http4.begin(cliente, RadUV);
    data = String("r|") + String(valor);
  }
  if(sensor == 2){
    http4.begin(cliente, TempAgua);
    data = String("t|") + String(valor);
  }
  Serial.println(data);
  httpCode = http4.POST(data);
  
}
