from robodk import robolink

RDK = robolink.Robolink()

RDK.setParam('SenyalSensor', 0)
RDK.setParam('num_Pimiento_Rojo', 0)
RDK.setParam('num_Pimiento_Ama', 0)
RDK.setParam('num_Pimiento_Verde', 0)

items = RDK.ItemList(robolink.ITEM_TYPE_OBJECT)
for item in items:
    if item.Name().startswith('PiRojoB'):
        item.Delete()

cintas = ['CRojo', 'CAma', 'CVerde', 'C1','CPaq','CRPaq']

for nombre in cintas:
    cinta = RDK.Item(nombre)
    if cinta.Valid():
        cinta.setJoints([0])
