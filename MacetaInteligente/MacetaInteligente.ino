//Se incluyen las librerias creadas para las funciones de los sensores
#include "tempyhum.h" 
#include "luz.h"

String mensaje;  // Usado para transmitir informacion por puerto serie al esp8266

void setup() {
  Serial.begin(115200);  //Inicia comunicacion serial, usada para pasar informacion al modulo wifi
  
  //Se llaman a las funciones de configuracion de los sensores
  iniciar_sens_tempyhum();
  iniciar_sens_luz();

}

void loop() {

    //Medicion de datos por los sensores
      int  temp_celsius = medicion_temp();
      int  humedad = medicion_hum();
      int  luz = medicion_luz();

 mensaje=String(temp_celsius)+String(',')+String(humedad)+String(',')+String(luz)+String('>');  //Se colocan todos los datos en una unica variable
 
 Serial.println(mensaje);  //Se envian los datos recolectados al modulo wifi (esp 8266)

 delay(600000);  //se repite el envio de datos cada 10 minutos 
}
