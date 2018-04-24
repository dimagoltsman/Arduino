#include <PubSubClient.h>
#include <WiFiConnector.h>


WiFiClient espClient;
PubSubClient client(espClient);


char* server = "192.168.1.108";

void callback(char* topic, byte* payload, unsigned int length);
void callback(char* topic, byte* payload, unsigned int length){

}

PubSubClient mqttClientConfigure(){
   client.setServer(server, 1883);
   client.setCallback(callback);
   return client;
}

void reconnectMqtt() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), "homeassistant", "myPassWord")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}