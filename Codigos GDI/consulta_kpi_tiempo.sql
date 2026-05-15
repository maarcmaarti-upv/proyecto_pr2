-- Tiempo medio de todos los pallets(en horas)

SELECT 
    ROUND(AVG(tiempo), 2) AS tiempo_medio
FROM pimientos.pallet;