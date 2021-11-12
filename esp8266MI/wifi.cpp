#include "wifi.h"
// Datos
const char* SSIDRED = "FERNANDEZ";     //Enter SSID
const char* PASSWORD = "16642286";            //Enter Password
const String TEMPERATURA = "http://147.182.194.244:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=StempMaceta";
const String HUMEDAD = "http://147.182.194.244:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=ShumMaceta";
const String LUZ = "http://147.182.194.244:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=SluzMaceta";

HTTPClient http;
WiFiClient client;

void inicializar_Wifi(){
  WiFi.begin(SSIDRED, PASSWORD);   //WiFi connection
  while (WiFi.status() != WL_CONNECTED)//Wait for the WiFI connection completion 
  { 
    delay(500);

  }
}
//TEMPERATURA
void postear_temperatura(int valor){
   String data;
      //Declare object of class HTTPClient
   http.begin(client,TEMPERATURA);      //Manda a la ubicacion del sensor
 
   data = String("t|")+ String(valor);

   int httpCode = http.POST(data);   //Send the request
   String payload = http.getString();                  //Get the response payload

   http.end();  //Close connection

}
//SENSOR HUMEDAD
void postear_humedad(int valor1){
   String data;
      //Declare object of class HTTPClient
   http.begin(client,HUMEDAD);      //Manda a la ubicacion del sensor
 
   data = String("t|")+ String(valor1);

   int httpCode = http.POST(data);   //Send the request
   String payload = http.getString();                  //Get the response payload

   http.end();  //Close connection
}
//SENSOR LUZ
void postear_luz(int valor2){
   String data;
      //Declare object of class HTTPClient
   http.begin(client,LUZ);      //Manda a la ubicacion del sensor
 
   data = String("t|")+ String(valor2);

   int httpCode = http.POST(data);   //Send the request
   String payload = http.getString();                  //Get the response payload

 
   http.end();  //Close connection
}
