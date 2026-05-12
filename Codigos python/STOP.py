from robodk import robolink
# Para simular la parada de emergencia setea la vel de simulacion a 0
# Para continuar la simulación, setear a vel normal(5) a mano o con ResetTotal
RDK = robolink.Robolink()
RDK.setSimulationSpeed(0)
