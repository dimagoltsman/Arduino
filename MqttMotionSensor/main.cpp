#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiConnector.h>
#include <PubSubClient.h>

#ifndef WIFI_SSID
  #define WIFI_SSID       "DimaWifiSSID"
  #define WIFI_PASSPHRASE "SuperGreat"
#endif

char*  topic = "pir/bathroom";
char* server = "192.168.1.108";

int pirPin = D7;
int val;


void callback(char* topic, byte* payload, unsigned int length);
void callback(char* topic, byte* payload, unsigned int length){

}
WiFiConnector wifi(WIFI_SSID, WIFI_PASSPHRASE);

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void init_wifi();
void updatePir();
void init_wifi();
void init_hardware();
void mqttClientConnect();
void reconnect();



void setup() {
    init_hardware();
    init_wifi();
    wifi.connect();
    delay(10000);
    mqttClientConnect();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
    updatePir();

    snprintf (msg, 75, "%ld", val);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topic, msg);

     delay(500);  
}

void updatePir() {

val = digitalRead(pirPin);


  if (val == LOW){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("No motion");
  } else{
    Serial.println("Motion detected  ALARM");
    digitalWrite(LED_BUILTIN, LOW);
  }

}


void init_wifi() {
  WiFi.disconnect(true);
  wifi.init();
  wifi.on_connected([&](const void* message)
  {
    Serial.print("WIFI CONNECTED WITH IP: ");
    Serial.println(WiFi.localIP());
  });

  wifi.on_connecting([&](const void* message)
  {
    Serial.print("Connecting to ");
    Serial.println(wifi.get("ssid") + ", " + wifi.get("password"));
    delay(200);
  });
}

void init_hardware(){
    Serial.begin(9600);
    delay(10);

    pinMode(pirPin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    delay(1000);
    Serial.flush();
    Serial.println();
    Serial.println();
    Serial.println("will be started in 500ms..");
}


void mqttClientConnect(){
   client.setServer(server, 1883);
   client.setCallback(callback);
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "homeassistant", "HomeAssistantApiPassword")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}





