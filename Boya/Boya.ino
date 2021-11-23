#include <WiFiManager.h>
#include <Servo.h>

Servo servoMotor;
int paso = millis();
void setup() {

  pinMode(A0, INPUT);    //Sensor de radiacion UV
  servoMotor.attach(4);
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
  String hora;
  if( paso + 3000 <= millis()){ 
    Serial.print("Temperatura: ");
    Serial.println(temp);
    Serial.print("Radiacion UV: ");
    Serial.println(rad);
    
    enviarDato(temp, 2);  // enviarDato(int valor, int sensor) (1 para radUV - 2 para TempAgua)
    enviarDato(rad, 1);
    paso = millis();
  }

  while(hora == hora_local());
  hora = hora_local();
  Serial.print("Hora: ");
  Serial.println(hora);

  if( hora == "19:52:00"){
    servoMotor.write(0);
    delay(2000);
    servoMotor.write(180);
    delay(2000);    
  }
}
