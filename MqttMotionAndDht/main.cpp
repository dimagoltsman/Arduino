#include <Arduino.h>

#include <myDht.h>
#include <myPir.h>
#include <myWifi.h>
#include <myMqtt.h>
#include <main.h>

PubSubClient mqttClient;

void setup() {
    init_hardware();
    init_wifi();
    
    delay(5000);
    mqttClient = mqttClientConfigure();
}

void loop() {
    reconnectMqtt();
    handlePir(mqttClient);
    handleDht(mqttClient);
    delay(500);  
}

void init_hardware(){
    Serial.begin(9600);
    delay(10);
    pinMode(LED_BUILTIN, OUTPUT);
    delay(1000);
}


