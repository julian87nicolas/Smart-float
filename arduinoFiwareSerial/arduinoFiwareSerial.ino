//      FIWARE FOR SERIAL COMMUNICATION
//
//      POST EXAMPLE 'http://68.183.112.17:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=BDTempCasa001#t|30\\'
//      GET EXAMPLE  'http://68.183.112.17:1026/v2/entities/urn:ngsd-ld:BDTempCasa:001?options=values&attrs=measure'

int data = 0;
const char POSTADRESS[] = "http://fiware-iot.ddns.net:7896/iot/d?k=";
const char GETADRESS[] =  "http://fiware-iot.ddns.net:1026/v2/entities/urn:ngsd-ld:";
const char APIKEY[] = "2tggokgpepnvsb2uv4s40d59oc";
const char SENSORNAME[] = "TempCasa";
const char OBJECT_ID = 't';
char temp[100];

void setup() {
  Serial.begin(9600);
  data = 20;
}

void loop() {

  data++;

  // POST
  sprintf(temp, "%s%s&i=%s#%c|%d",
                  POSTADRESS,
                  APIKEY,
                  SENSORNAME,
                  OBJECT_ID,
                  data);
  Serial.println(temp);

  delay(1000);
  // GET
  sprintf(temp, "%s%s?options=values&attrs=measure",
                GETADRESS,
                SENSORNAME);
  Serial.println(temp);
  
  if( data >= 30)
    data = 20;
  delay(5000);
  
}
