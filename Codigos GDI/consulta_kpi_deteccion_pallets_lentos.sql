-- Tiempo total por pallet (detección de pallets lentos)

SELECT 
    codigo,
    tiempo
FROM pimientos.pallet
ORDER BY tiempo DESC;
