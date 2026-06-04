// se suscribe a los topics declarados en el config.h
void suscribirseATopics() {
  mqtt_subscribe(CAJA_TOPIC);
  mqtt_subscribe(PAQ_TOPIC);
  mqtt_subscribe(STOP_TOPIC);
}

void alRecibirMensajePorTopic(char* topic, String incomingMessage) {
}

//funcion para publicar mensajes en topics
void enviarMensajePorTopic(const char* topic, String outgoingMessage) {
  mqtt_publish(topic, outgoingMessage.c_str());
}
