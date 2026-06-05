# PR2 Entrega 7 de mayo

Realizado por: Marc Martí, Daniel Dunca, Alejandro Aznar y Ian Francisco García.

Función: Claisifcación, empaquetado, encajado y paletizado de paquetes.

Hemos establecido la conexión vía MQTT entre la simulación completa de la planta y 2 robots ABB antropomórficos. Uno encargado de meter 6 paquetes en una caja, y el otro encargado de paletizar las cajas una vez estas sean transportadas y cerradas.
#
# Para poder visualizar correctamente la memoria y el layout del archivo .rdk es necesario descargar el archivo.

# Método de ejecución
Para ejecutar correctamente el código, se debe ejecutar el código de Arduino con la esp32s3 conectada, abrir el layout de RoboDK y dejar abiertos los scripts de MQTTListener y RobotController. Y por último ejecutar el código de MQTTListener.

El cableado de la esp32s3 es de tres botones, los tres conectados a GND y el boton que simula al sensor de presencia de los paquetes conectado por el otro lado al pin 5, el boton de las cajas al pin 4 y el de la parada de emergencia al pin 6.

Con todo esto, una vez pulsado el botón de los paquetes se inicia el programa de P&P_Paq que mueve el paquete y es introducido en la caja. Una vez se han introducido 6 paquetes, se inicia la cinta de la caja, entra en la cerradora de cajas y esta se cierra .Una vez llega al final de la cinta, se pulsa el botón de las cajas y se paletiza la caja.

En el github también se encuentran fotos tanto del layout con vista cenital cómo de el esquema eléctrico del circuito.

# Parte de GDI

Además, la parte de la entrega de GDI se encuentra en la carpeta codigos_gdi, y para que funcione se debe de crear la BD con los archivos .sql cómo hemos aprendido en las prácticas, luego ejecutar el programa de python mientras ejecutas de la forma anteriormente explicada los otros programas de RDK y Arduino.

# Parte de PRA

En el script de python de RoboDK, llamado P&P_CajaCerrada.py, se usa Divide y Vencerás para obtener las diferentes posiciones de las cajas en el palet.
Esto cumple la parte de la entrega sobre la asignatura de PRA.
