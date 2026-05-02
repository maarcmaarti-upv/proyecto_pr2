from robodk import robolink

RDK = robolink.Robolink()

def handle_message(mqttc, topic, payload):

    payload = payload.strip().lower()

    if topic == "pr2/sahuquillers/caja":
        if payload == "caja":
            ejecutar_paletizado()

    elif topic == "pr2/sahuquillers/pim":
        if payload == "pim":
            ejecutar_pp_rojo()


def ejecutar_pp_rojo():
    programa2 = RDK.Item("P&P_Rojo", robolink.ITEM_TYPE_PROGRAM)

    if programa2.Valid():
        programa2.RunProgram()
    else:
        print("ERROR: No se encontró el programa P&P_Rojo en la estación.")


def ejecutar_paletizado():
    programa1 = RDK.Item("P&P_CajaCerrada", robolink.ITEM_TYPE_PROGRAM)

    if not programa1.Valid():
        raise Exception("No se encontró el programa P&P_CajaCerrada en la estación.")

    programa1.RunProgram()
