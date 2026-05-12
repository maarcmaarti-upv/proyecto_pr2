from robodk import robolink

RDK = robolink.Robolink()

# Detiene todos los programas en ejecución
RDK.StopAll()

print("Todos los programas han sido detenidos.")
