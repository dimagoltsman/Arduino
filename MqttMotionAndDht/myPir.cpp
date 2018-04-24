#include <myPir.h>
#include <Arduino.h>

int pirPin = D7;
int val;

char*  topic = "pir/bathroom";
char msg[200];

void handlePir(PubSubClient client) {

    val = digitalRead(pirPin);

    if (val == LOW){
       digitalWrite(LED_BUILTIN, HIGH);
        // Serial.println("No motion");
     } else{
     // Serial.println("Motion detected  ALARM");
      digitalWrite(LED_BUILTIN, LOW);
     }

    snprintf (msg, 200, "%ld", val);
    Serial.print("PIR: ");
    Serial.println(msg);
    client.publish(topic, msg);

}