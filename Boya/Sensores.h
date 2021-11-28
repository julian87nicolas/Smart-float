
// Entidad
char *entityIP = "http://147.182.194.244:1026/v2/entities";
char *entity = "{\"id\": \"urn:ngsi-Id:Boyadarmedebaja:001\",\"type\": \"Boya\"}";

// Sensores
char *sensorIP = "http://147.182.194.244:4041/iot/devices";
char *temp = "{\"devices\":[{\"device_id\":\"TempAgua\",\"entity_name\":\"urn:ngsi-Id:TempAgua:001\",\"entity_type\":\"Sensor\",\"timezone\":\"America/BuenosAires\",\"attributes\":[{\"object_id\":\"t\",\"name\":\"measure\",\"type\":\"Integer\"}],\"static_atributtes\":[{\"name\":\"refStore\",\"type\":\"Relationship\",\"value\":\"urn:ngsi-Id:Boyadarmedebaja:001\"}]}]}";
char *radUV =  "{\"devices\":[{\"device_id\":\"RadUV\",\"entity_name\":\"urn:ngsi-Id:RadUV:001\",\"entity_type\":\"Sensor\",\"timezone\":\"America/BuenosAires\",\"attributes\":[{\"object_id\":\"r\",\"name\":\"measure\",\"type\":\"Integer\"}],\"static_atributtes\":[{\"name\":\"refStore\",\"type\":\"Relationship\",\"value\":\"urn:ngsi-Id:Boyadarmedebaja:001\"}]}]}";

// Suscripcion a QL
char *suscIP = "http://147.182.194.244:1026/v2/subscriptions/";
char *suscTemp = "{\"description\": \"Notify Quantum Leap about TempAgua.*\",\"subject\": {\"entities\": [{\"idPattern\": \"TempAgua.*\"}],\"condition\": {\"attrs\": [\"measure\"]}},\"notification\": {\"http\": {\"url\": \"http://quantum-leap:8668/v2/notify\"},\"attrs\": [\"measure\"],\"metadata\": [\"dateCreated\",\"dateModified\"]}}";
char *suscRadUV = "{\"description\": \"Notify Quantum Leap about RadUV.*\",\"subject\": {\"entities\": [{\"idPattern\": \"RadUV.*\"}],\"condition\": {\"attrs\": [\"measure\"]}},\"notification\": {\"http\": {\"url\": \"http://quantum-leap:8668/v2/notify\"},\"attrs\": [\"measure\"],\"metadata\": [\"dateCreated\",\"dateModified\"]}}";
