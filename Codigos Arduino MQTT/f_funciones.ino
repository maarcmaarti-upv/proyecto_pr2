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

volatile bool PARAR = false;        // Señal global para detener tareas de forma coordinada
volatile bool stopEvent = false;    // Bandera que indica que la ISR ha detectado un STOP

bool lastCaja = HIGH;               // Estados previos para detección por flanco
bool lastPaq = HIGH;

uint8_t ledStatus = 0;

// Buffer FIFO compartido
Buffer_Circ bufferEventos;

// Control del LED del pin 2(no usado)
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
  push(&bufferEventos, EVT_STOP);   // El ISR solo encola,no ejecuta lógica pesada
  stopEvent = true;
}

// Tarea de lectura de sensores (caja y paquete)
void tareaLecturaSensores(void* parameter) {
  infoln("TareaLecturaSensores iniciada");

  while (!PARAR) {                  // Se detiene cuando el sistema entra en modo emergencia
    bool c = digitalRead(PIN_CAJA);
    bool p = digitalRead(PIN_PAQ);

    if (c != lastCaja) {            // Detección por flanco para evitar lecturas continuas
      vTaskDelay(50 / portTICK_PERIOD_MS);  // Antirrebote por software
      c = digitalRead(PIN_CAJA);
      if (c == LOW) {
        push(&bufferEventos, EVT_CAJA);     // Se delega el procesamiento al consumidor
      }
      lastCaja = c;                 // Actualiza estado para futuros flancos
    }

    if (p != lastPaq) {             // Misma lógica para sensor de paquete
      vTaskDelay(50 / portTICK_PERIOD_MS);
      p = digitalRead(PIN_PAQ);
      if (p == LOW) {
        push(&bufferEventos, EVT_PAQ);
      }
      lastPaq = p;
    }

    vTaskDelay(20 / portTICK_PERIOD_MS);    // delay de ritmo estable
  }

  infoln("TareaLecturaSensores finalizada");
  vTaskDelete(NULL);                // Finalización ordenada al activarse PARAR
}

// Tarea de gestión de eventos de parada
void tareaEventos(void* parameter) {
  infoln("TareaEventos iniciada");

  while (!PARAR) {
    if (stopEvent) {
      stopEvent = false;

      push(&bufferEventos, EVT_STOP); // Se asegura que el consumidor procese el STOP
      PARAR = true;                   // Señal global para detener el sistema
    }

    vTaskDelay(10 / portTICK_PERIOD_MS); // Frecuencia alta para reaccionar rápido al STOP
  }

  infoln("TareaEventos finalizada");
  vTaskDelete(NULL);
}

void tareaConsumidor(void* parameter) {
    int evt;

    while (true) {
        if (pop(&bufferEventos, &evt) == 0) {   // se procesan los eventos

            switch(evt) {
                case EVT_CAJA:
                    enviarMensajePorTopic(CAJA_TOPIC, "caja");     // dependiendo del case hace una publicacion o otra
                    break;

                case EVT_PAQ:
                    enviarMensajePorTopic(PAQ_TOPIC, "paquete");
                    break;

                case EVT_STOP:
                    enviarMensajePorTopic(STOP_TOPIC, "stop");
                    break;
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);    // delay
    }
}
