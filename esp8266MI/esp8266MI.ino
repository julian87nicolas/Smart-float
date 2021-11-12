#include "StringSplitter.h" //Se utiliza para separar los datos que llegan por el puerto serie
#include "wifi.h"

String msjEntrada;  //Se guardan todos los datos recibidos por puerto serie en una sola variable
String temperatura,humedad,luz;  //Se separan los datos y se guardan en la variable que corresponde

void setup() {
  Serial.begin(115200);  //Se establece la comunicacion con el arduino a traves de puerto seriae
 
 //Se inicia la conexion wifi del modulo con la red
 inicializar_Wifi(); 
}

void loop() {

if (Serial.available() > 0) {  //Se checkea el puerto serie y se guardan los datos recibidos
 msjEntrada = Serial.readStringUntil('\n');

StringSplitter *recibido = new StringSplitter(msjEntrada,',',3);  //Se establece la forma de diferenciar los datos y se guarda cada uno en su variable correpondiente
temperatura = recibido->getItemAtIndex(0);
humedad = recibido->getItemAtIndex(1);
luz = recibido->getItemAtIndex(2);
}

if(WiFi.status() == WL_CONNECTED){   //Chequea el estado de la conexion de Wifi

   //Envio de datos 
   postear_temperatura(temperatura); 
   postear_humedad(humedad);
   postear_luz(luz);

}
}
