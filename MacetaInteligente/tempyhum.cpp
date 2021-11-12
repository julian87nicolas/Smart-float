#include "tempyhum.h"

//DEFINICIONES
#define DHTPIN 2       //se define el pin de arudino a utilizar para la recepcion de datos
#define DHTTYPE DHT11  //se define concretamente el sensor que se esta usando

DHT dht(DHTPIN, DHTTYPE);

//PROCESOS A REALIZAR CON EL SENSOR

void iniciar_sens_tempyhum(){
	dht.begin();     //se inicia el sensor
}

//En ambas funciones se usan las funciones que vienen en la libreria propia del sensor  
int medicion_temp(){
	int temp_celsius = dht.readTemperature(); //Leemos la temperatura en grados Celsius
	return temp_celsius;
}
	
int medicion_hum(){
	int humedad=dht.readHumidity();  //Leemos la humedad en porcentaje
	return humedad;
}
