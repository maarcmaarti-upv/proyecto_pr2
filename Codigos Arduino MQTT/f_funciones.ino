#include <Arduino.h>
#include "Config.h"

// Pines
#define PIN_CAJA 4
#define PIN_PAQ 5
#define PIN_STOP 6

// Estado global de parada
volatile bool PARAR = false;
volatile bool stopEvent = false;

// Estados anteriores de sensores
bool lastCaja = HIGH;
bool lastPaq = HIGH;

// LED interno (por si quieres usarlo)
uint8_t ledStatus = 0;

void setInternalLed(uint8_t status) {
  if (ledStatus == status)
    return;

  ledStatus = status;

  if (status) {
    infoln("Led: on");
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    infoln("Led: off");
    digitalWrite(LED_BUILTIN, LOW);
  }
}

// ISR del botón STOP (evento HW)
void IRAM_ATTR isr_stop() {
  stopEvent = true;   // evento de parada
}

// Tarea de lectura de sensores (caja y paquete)
void tareaLecturaSensores(void* parameter) {
  infoln("TareaLecturaSensores iniciada");

  while (!PARAR) {
    bool c = digitalRead(PIN_CAJA);
    bool p = digitalRead(PIN_PAQ);

    if (c != lastCaja) {
      vTaskDelay(50 / portTICK_PERIOD_MS);  // antirrebote
      c = digitalRead(PIN_CAJA);
      if (c == LOW) {
        infoln("Evento: CAJA pulsado");
        enviarMensajePorTopic(CAJA_TOPIC, "caja");
      }
      lastCaja = c;
    }

    if (p != lastPaq) {
      vTaskDelay(50 / portTICK_PERIOD_MS);  // antirrebote
      p = digitalRead(PIN_PAQ);
      if (p == LOW) {
        infoln("Evento: PAQUETE pulsado");
        enviarMensajePorTopic(PAQ_TOPIC, "paquete");
      }
      lastPaq = p;
    }

    vTaskDelay(20 / portTICK_PERIOD_MS);
  }

  infoln("TareaLecturaSensores finalizada");
  vTaskDelete(NULL);
}

// Tarea de gestión de eventos de parada
void tareaEventos(void* parameter) {
  infoln("TareaEventos iniciada");

  while (!PARAR) {
    if (stopEvent) {
      stopEvent = false;
      infoln("Evento: STOP pulsado -> parada de emergencia");
      enviarMensajePorTopic(STOP_TOPIC, "stop");
      PARAR = true;
      digitalWrite(LED_BUILTIN, HIGH);
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }

  infoln("TareaEventos finalizada");
  vTaskDelete(NULL);
}
