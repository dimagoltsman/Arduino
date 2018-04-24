#include <ESP8266WiFi.h>
#include <WiFiConnector.h>

#ifndef WIFI_SSID
  #define WIFI_SSID       "MySSID"
  #define WIFI_PASSPHRASE "MyPass"
#endif

WiFiConnector wifi(WIFI_SSID, WIFI_PASSPHRASE);

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

  wifi.connect();
}