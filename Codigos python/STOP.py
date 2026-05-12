from robodk import robolink

RDK = robolink.Robolink()

programas = RDK.ItemList(robolink.ITEM_TYPE_PROGRAM)

for prog in programas:
    if prog.Busy():
        prog.Stop()

