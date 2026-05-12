from robodk import robolink, robomath
import time

RDK = robolink.Robolink()

BasePim = RDK.Item('BasePim')

INCREMENTO_MM = 1200
TIEMPO_STEP = 0.5

# Lista de pimientos conocidos
pimientos = []
num_anterior = 0

while True:

    # -----------------------------
    # 1. Detectar pimientos actuales
    # -----------------------------
    actuales = []
    for obj in RDK.ItemList(robolink.ITEM_TYPE_OBJECT):
        try:
            if obj.Valid() and obj.Name().startswith('PiRojoB'):
                if obj.Parent() == BasePim:
                    actuales.append(obj)
        except:
            continue

    # Limpiar inválidos
    actuales = [p for p in actuales if p.Valid()]

    num_actual = len(actuales)

    # -----------------------------
    # 2. Detectar si hay NUEVOS
    # -----------------------------
    if num_actual > num_anterior:

        # Actualizar lista interna
        pimientos = actuales

        # Pose inversa
        try:
            base_pose_inv = BasePim.PoseAbs().inv()
        except:
            time.sleep(TIEMPO_STEP)
            continue

        # -----------------------------
        # 3. Mover TODOS una vez
        # -----------------------------
        for pim in pimientos:

            try:
                if not pim.Valid() or not pim.Visible():
                    continue
            except:
                continue

            try:
                pos_abs = pim.PoseAbs().Pos()
            except:
                continue

            # Movimiento en Y
            nueva_pose_abs = robomath.transl(
                pos_abs[0],
                pos_abs[1] + INCREMENTO_MM,
                pos_abs[2]
            )

            try:
                pim.setPoseAbs(nueva_pose_abs)
            except:
                continue

            # -----------------------------
            # 4. Comprobar límite en X
            # -----------------------------
            try:
                pose_rel = base_pose_inv * pim.PoseAbs()
                x_rel = pose_rel.Pos()[0]
            except:
                continue

            if x_rel > 0:
                try:
                    pim.setVisible(False)
                except:
                    continue

        # Actualizar contador
        num_anterior = num_actual

    # -----------------------------
    # Espera
    # -----------------------------
    time.sleep(TIEMPO_STEP)
