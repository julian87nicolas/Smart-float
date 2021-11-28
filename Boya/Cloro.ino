/*bool controlCloro(String HoraAp; NTPClient timeClient){

//  char hour[] = hora_local(timeClient).substring(0,2);
//  char minutes[] = hora_local(timeClient).substring(3,5);
//  char sec[] = hora_local(timeClient).substring(6,8);
  
  if(horaApertura == timeClient.getHours()){
    
    if(minApertura == timeClient.getMinutes()){
      
      if(timeClient.getSeconds() >= segApertura && timeClient.getSeconds() < segApertura+2){
        return true;        
      }
      else{
        return false;
      }
      
    }
    
    else{
      return false;
    }
    
  }
  else{
    return false;
  }
  
}
*/
