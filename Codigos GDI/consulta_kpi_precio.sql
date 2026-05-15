-- Precio medio de pallet por material

SELECT 
    material,
    ROUND(AVG(precio), 2) AS precio_medio
FROM pimientos.pallet
GROUP BY material;