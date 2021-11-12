#include <DHT.h>     //Libreria propia del sensor

//FUNCIONES INICIO DE SENSOR (una sola porque el mismo sensor hace las dos mediciones)
void iniciar_sens_tempyhum();

//FUNCIONES A REALIZAR CON EL SENSOR (medicion)
int medicion_temp();
int medicion_hum();
