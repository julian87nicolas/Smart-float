                     
String hora_local(NTPClient timeClient) {

  String hora = "hora", aux = "aux";

  timeClient.update(); //sincronizamos con el server NTP

  while(hora != aux){
    hora = timeClient.getFormattedTime();
    aux = timeClient.getFormattedTime();
  }
  
  return hora;
}
