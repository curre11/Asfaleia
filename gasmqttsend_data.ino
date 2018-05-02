#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "TP-LINK_4E0C";
const char* password =  "maxblaze007";
const char* mqttServer = "192.168.1.102";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 pinMode(16, INPUT);
   Serial.begin(115200);
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2);
 
    }
  }
  while(true){
 if (digitalRead(16) == HIGH) {
  client.publish("esp/tes", "1");
  client.subscribe("esp/tes");
  digitalWrite(2,HIGH);
  delay(1000);
  }
  else{
  client.publish("esp/tes", "0");
  client.subscribe("esp/tes");
  Serial.print(digitalRead(16));
  }}
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
}