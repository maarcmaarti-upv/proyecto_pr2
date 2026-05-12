from robodk import robolink
from robodk import robomath

RDK = robolink.Robolink()

Cinta = RDK.Item('CAma')
INCREMENTO_MM = 190
Pimiento = RDK.Item('PiAma')
SistRefCinta = RDK.Item('PAma')
Pimiento.setVisible(False)
if Cinta.Valid():
    
    Cinta.MoveJ(Cinta.Joints() + INCREMENTO_MM+190)


    Pimiento.Copy()
    PimientoCopia = RDK.Paste(SistRefCinta)
    PimientoCopia.setName('PiRojoB')
    PimientoCopia.setVisible(True)
    # Leer contador
    nPimiento = RDK.getParam('num_Pimiento_Ama')
    if nPimiento is None:
        nPimiento = 0

    nPimiento += 1

    pose_pim_en_refcinta = (
        SistRefCinta.PoseAbs().inv() *
        Pimiento.PoseAbs()
    )

    pose_final = (pose_pim_en_refcinta *robomath.transl(INCREMENTO_MM * nPimiento*2, 0, 850))

    PimientoCopia.setPose(pose_final)

    RDK.setParam('num_Pimiento_Ama', nPimiento)
