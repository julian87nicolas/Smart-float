#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <NTPClient.h> //importamos la librería del cliente NTP
#include <Servo.h>

WiFiUDP ntpUDP; // cliente UDP para solicitar la hora

NTPClient timeClient(ntpUDP, "0.south-america.pool.ntp.org",-10800,6000);
Servo servoMotor;

extern char *entityIP;
extern char *sensorIP;
extern char *suscIP;

int paso = millis();
void setup() {
  delay(2000);
  timeClient.begin();
  pinMode(A0, INPUT);     // Sensor de radiacion UV
  servoMotor.attach(4);   // Servomotor para apertura de cloro
    
  WiFiManager wifi;      // Conexion Wifi
  //wifi.resetSettings();
  wifi.autoConnect("BOYA");
  
  Serial.begin(115200);
  
  creaEntidad(entityIP);      

  registraSensores(sensorIP);

  quantumLeap(suscIP);

  Serial.print("Hora de inicio: ");
  Serial.println(hora_local(timeClient));
}

void loop() {
  int temp = temperatura(), rad = radiacion();
  String hora;
  if( paso + 3000 <= millis()){  // Efectuando posteo de datos cada 30000 milisegundos (30 segundos)
    Serial.print("Temperatura: ");
    Serial.println(temp);
    Serial.print("Radiacion UV: ");
    Serial.println(rad);
    
    enviarDato(temp, 2);  // enviarDato(int valor, int sensor) (1 para radUV - 2 para TempAgua)
    enviarDato(rad, 1);
    paso = millis();
    Serial.println(hora_local(timeClient));
  }
  if( hora_local(timeClient) == "22:00:00" || hora_local(timeClient) == "22:00:01"){  // Se activa el servo por dos segundos a las 22 horas
                                                                                      // las dos comparaciones son para asegurar que se cumpla
                                                                                      // ya que el reloj online es impreciso.
    Serial.print("Abriendo compuerta de cloro, hora ");
    Serial.println(hora_local(timeClient));
    servoMotor.write(90);
    delay(2000);
    Serial.println("Cerrando compuerta.");
    servoMotor.write(0);
  }
 
  
}
