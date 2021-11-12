#include "Arduino.h"
#include "luz.h"

#define SENSORLUZ A0  //pin analogico utililizado para el sensor

//FUNCIONES DEL SENSOR DE LUZ

void iniciar_sens_luz(){
	pinMode (SENSORLUZ, INPUT);  //se declara el pin analogico a usar por el sensor
}
	
int medicion_luz(){
	int luzMedida=analogRead(SENSORLUZ);
	int luz=luzMedida*0.0976; //para convertir el valor leido por el sensor en un porcentaje de luz que esta recibiendo
	return luz;
}
