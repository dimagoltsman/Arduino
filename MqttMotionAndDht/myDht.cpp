#include <Arduino.h>
#include <myDht.h>

int pinDHT11 = D6;
char* dhtTopic = "dht11/bathroom";
char dhtMsg[200];
SimpleDHT11 dht11;

void handleDht(PubSubClient client){
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    // Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  snprintf (dhtMsg, 200, "{\n  \"temp\" : %ld,\n  \"humid\" : %ld \n}", (int)temperature, (int)humidity);
  Serial.print("DHT: ");
  Serial.print(dhtMsg);
  Serial.print("\n");
  client.publish(dhtTopic, dhtMsg);

}