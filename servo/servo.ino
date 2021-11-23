#include <Servo.h>
 
// Declaramos la variable para controlar el servo
Servo servoMotor;
 
void setup() {
  Serial.begin(9600);
  servoMotor.attach(4);
}
 
void loop() {
  
  // Desplazamos a la posición 0º
  servoMotor.write(0);
  // Esperamos 1 segundo
  delay(1000);

  // Desplazamos a la posición 180º
  servoMotor.write(90);
  // Esperamos 1 segundo
  delay(1000);
}
