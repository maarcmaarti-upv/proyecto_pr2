void on_setup() {

  pinMode(PIN_CAJA, INPUT_PULLUP);
  pinMode(PIN_PAQ, INPUT_PULLUP);
  pinMode(PIN_STOP, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  setInternalLed(1);

  attachInterrupt(PIN_STOP, isr_stop, FALLING);

  xTaskCreatePinnedToCore(tareaLecturaSensores, "LecturaSensores", 5000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(tareaEventos, "Eventos", 4000, NULL, 2, NULL, 1);

  infoln("Tareas creadas correctamente");

  String hello_msg = String("Hola Mundo! Desde dispositivo ") + deviceID;

  JsonDocument doc;
  doc["message"] = hello_msg;
  doc["luminosidad"] = 450;
  doc["temperatura"] = 21.5;

  String hello_msg_json;
  serializeJson(doc, hello_msg_json);

  enviarMensajePorTopic(HELLO_TOPIC, hello_msg_json);
}
