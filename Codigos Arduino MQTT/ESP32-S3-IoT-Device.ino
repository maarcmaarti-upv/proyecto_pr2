#include "Config.h"

#include <WiFi.h>
#ifdef SSL_ROOT_CA
  #include <WiFiClientSecure.h>
#endif
#include <PubSubClient.h>
#include <ArduinoJson.h>

String deviceID = String("giirobpr2-device-") + String(DEVICE_GIIROB_PR2_ID);

void setup() {
#ifdef LOGGER_ENABLED
  Serial.begin(BAUDS);
  delay(1000);
  Serial.println();
#endif

  wifi_connect();
  mqtt_connect(deviceID);

  suscribirseATopics();
  on_setup();
}

void loop() {
  wifi_loop();
  mqtt_loop();
  on_loop();
}
