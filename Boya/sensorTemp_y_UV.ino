#include <DallasTemperature.h>
#include <OneWire.h>

const int pinDatosDQ = 2;
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

int temperatura(){
  sensorDS18B20.requestTemperatures();
  return sensorDS18B20.getTempCByIndex(0);
}

int radiacion(){
  int r = analogRead(A0);
  int val = 0;
  if(r < 50){
    val = 0;
  }
  else{
    if(r < 227){
      return 1;
    }
    else{
      if(r < 318){
        val =  2;
      }
      else{
        if( r < 418){
          val =  3;
        }
        else{
          if(r > 503){
            val =  4;
          }
          else{
            if(r > 606){
              val =  5;
            }
            else{
              if( r > 696){
                val =  6;
              }
              else{
                if(r > 795){
                  val =  7;
                }
                else{
                  val =  8;
                }
              }
            }
          }
        }
      }
    }
  }
  return val;
}
