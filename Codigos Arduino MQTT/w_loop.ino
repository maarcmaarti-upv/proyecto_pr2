long now, lastMsg = 0;
long sensorsUpdateInterval = 5000; // tiempo de actualización de los sensores

// Definiciones
bool ultimoEstadoCaja = HIGH;
bool ultimoEstadoPaq = HIGH;
bool ultimoEstadoStop = HIGH;

const int sensor_caja = 4;
const int sensor_paq = 5; 
const int sensor_stop = 6; 

void on_loop() {
  // Definición variables de estado de sensores
  bool estadoActualCaja = digitalRead(sensor_caja);
  bool estadoActualPaq = digitalRead(sensor_paq);
  bool estadoActualStop = digitalRead(sensor_stop);

  // Estado del sensor de las cajas
  if (estadoActualCaja != ultimoEstadoCaja)
  {
    delay(50);  //antirrebote
    estadoActualCaja = digitalRead(sensor_caja);
    if(estadoActualCaja == LOW)
    {
      enviarMensajePorTopic(CAJA_TOPIC,"caja");
    }
    // Actualiza estado
    ultimoEstadoCaja = estadoActualCaja;
  }
  // Estado del sensor de los paquetes
  if (estadoActualPaq != ultimoEstadoPaq)
  {
    delay(50);  //antirrebote
    estadoActualPaq = digitalRead(sensor_paq);
    if(estadoActualPaq == LOW)
    {
      enviarMensajePorTopic(PAQ_TOPIC,"paquete");
    }
    // Actualiza estado
    ultimoEstadoPaq = estadoActualPaq;
  }
  if (estadoActualStop != ultimoEstadoStop)
  {
    delay(50);  //antirrebote
    estadoActualStop = digitalRead(sensor_stop);
    if(estadoActualStop == LOW)
    {
      enviarMensajePorTopic(STOP_TOPIC,"stop");
    }
    // Actualiza estado
    ultimoEstadoStop = estadoActualStop;
  }
}