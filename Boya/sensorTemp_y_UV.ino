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
  if(r < 50){
    return 0;
  }
  else{
    if(r < 227){
      return 1;
    }
    else{
      if(r < 318){
        return 2;
      }
      else{
        if( r < 418){
          return 3;
        }
        else{
          if(r > 503){
            return 4;
          }
          else{
            if(r > 606){
              return 5;
            }
            else{
              if( r > 696){
                return 6;
              }
              else{
                if(r > 795){
                  return 7;
                }
                else{
                  return 8;
                }
              }
            }
          }
        }
      }
    }
  }
}