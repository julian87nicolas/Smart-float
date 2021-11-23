#include <WiFiManager.h>

void setup() {

  pinMode(A0, INPUT);    //Sensor de radiacion UV
  
  WiFiManager wifi;      // Conexion Wifi
  //wifi.resetSettings();
  wifi.autoConnect("BOYA");
  
  Serial.begin(115200);
  creaEntidad();      

  registraSensores();

  quantumLeap();
}

void loop() {
  int temp = temperatura(), rad = radiacion();
  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.print("Radiacion UV: ");
  Serial.println(rad);
  enviarDato(temp, 2);  // enviarDato(int valor, int sensor) (1 para radUV - 2 para TempAgua)
  enviarDato(rad, 1);
  delay(2000);
}
