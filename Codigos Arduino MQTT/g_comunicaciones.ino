void suscribirseATopics() {
  mqtt_subscribe(CAJA_TOPIC);
  mqtt_subscribe(PAQ_TOPIC);
  mqtt_subscribe(STOP_TOPIC);
}

// Necesaria para que compile la librería MQTT
void alRecibirMensajePorTopic(char* topic, String incomingMessage) {
  // No usamos recepción MQTT en este proyecto
}

void enviarMensajePorTopic(const char* topic, String outgoingMessage) {
  mqtt_publish(topic, outgoingMessage.c_str());
}
