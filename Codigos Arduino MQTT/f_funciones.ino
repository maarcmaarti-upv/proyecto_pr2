#include <Arduino.h>
#include "Config.h"
#include "buffer_circ.h"

// Pines
#define PIN_CAJA 4
#define PIN_PAQ 5
#define PIN_STOP 6

// Códigos de evento para el buffer
#define EVT_CAJA   1
#define EVT_PAQ    2
#define EVT_STOP   3

volatile bool PARAR = false;
volatile bool stopEvent = false;

bool lastCaja = HIGH;
bool lastPaq = HIGH;

uint8_t ledStatus = 0;

// Buffer FIFO compartido
Buffer_Circ bufferEventos;

// Control del LED del pin 2
void setInternalLed(uint8_t status) {
  if (ledStatus == status)
    return;

  ledStatus = status;

  if (status) {
    infoln("Led: on");
    digitalWrite(PIN_LED, HIGH);
  } else {
    infoln("Led: off");
    digitalWrite(PIN_LED, LOW);
  }
}

// ISR del botón STOP
void IRAM_ATTR isr_stop() {
  push(&bufferEventos, EVT_STOP);
  stopEvent = true;
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
        push(&bufferEventos, EVT_CAJA);
      }
      lastCaja = c;
    }

    if (p != lastPaq) {
      vTaskDelay(50 / portTICK_PERIOD_MS);  // antirrebote
      p = digitalRead(PIN_PAQ);
      if (p == LOW) {
        push(&bufferEventos, EVT_PAQ);
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

      push(&bufferEventos, EVT_STOP);
      PARAR = true;
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }

  infoln("TareaEventos finalizada");
  vTaskDelete(NULL);
}
void tareaConsumidor(void* parameter) {
    int evt;

    while (true) {
        if (pop(&bufferEventos, &evt) == 0) {

            switch(evt) {
                case EVT_CAJA:
                    enviarMensajePorTopic(CAJA_TOPIC, "caja");
                    break;

                case EVT_PAQ:
                    enviarMensajePorTopic(PAQ_TOPIC, "paquete");
                    break;

                case EVT_STOP:
                    enviarMensajePorTopic(STOP_TOPIC, "stop");
                    break;
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

