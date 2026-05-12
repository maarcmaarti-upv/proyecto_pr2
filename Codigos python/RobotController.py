from robodk import robolink

# Conexión con RoboDK
RDK = robolink.Robolink()

# Contador de paquetes
contador_paq_robot = 0


def handle_message(mqttc, topic, payload):
    global contador_paq_robot

    payload = payload.strip().lower()

    # Cuando recibe en el topic "pr2/sahuquillers/paq" -> "paquete"
    if topic == "pr2/sahuquillers/paq" and payload == "paquete":

        contador_paq_robot += 1

        ejecutar_pp_paq()

        # Cada 6 paquetes ejecuta cajas
        if contador_paq_robot == 6:
            ejecutar_cajas()
            contador_paq_robot = 0

    # Cuando recibe en el topic "pr2/sahuquillers/caja" -> "caja"
    elif topic == "pr2/sahuquillers/caja" and payload == "caja":
        print("-> Evento caja recibido")
        ejecutar_paletizado()

    # Cuando recibe en el topic "pr2/sahuquillers/stop" -> "stop"
    elif topic == "pr2/sahuquillers/stop" and payload == "stop":
        print("-> STOP recibido, ejecutando script STOP")
        ejecutar_stop()


# Programas de RoboDK

# pick and place de paquetes
def ejecutar_pp_paq():
    programa = RDK.Item("P&P_Paq", robolink.ITEM_TYPE_PROGRAM)

    if programa.Valid():
        if not programa.Busy():   # evita solapamientos
            programa.RunProgram()
    else:
        print("No se encontró el programa P&P_Paq en la estación.")

# paletizado de cajas
def ejecutar_paletizado():
    programa = RDK.Item("P&P_CajaCerrada")

    if programa.Valid():
        if not programa.Busy():
            programa.RunProgram()
    else:
        print("No se encontró el programa P&P_CajaCerrada en la estación.")

# cinta de cajas
def ejecutar_cajas():
    programa = RDK.Item("Cajas", robolink.ITEM_TYPE_PROGRAM)

    if programa.Valid():
        if not programa.Busy():
            programa.RunProgram()
    else:
        print("No se encontró el programa P&P_CajaCerrada en la estación.")

# parada de emergencia
def ejecutar_stop():
    programa = RDK.Item("STOP")

    if programa.Valid():
        programa.RunProgram()
    else:
        print("No se encontró el script STOP en la estación.")


