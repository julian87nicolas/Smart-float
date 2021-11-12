#include <DallasTemperature.h>
#include <OneWire.h>

const int pinDatosDQ = 4;

OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);



void setup() {
  Serial.begin(9600);
  sensorDS18B20.begin();
  pinMode(A0, INPUT);
}

void loop() {
  // Mandamos comandos para toma de temperatura a los sensores
    Serial.println("Mandando comandos a los sensores");
    sensorDS18B20.requestTemperatures();
 
    // Leemos y mostramos los datos de los sensores DS18B20
    Serial.print("Temperatura: ");
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.println(" C");
    Serial.print("Radiacion UV: ");
    Serial.println(analogRead(A0));
    delay(1000); 
}
