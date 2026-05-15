-- Coste medio de transporte por cliente

SELECT 
    cliente,
    ROUND(AVG(km), 2) AS km_medios,
    ROUND(AVG(duracion), 2) AS duracion_media
FROM pimientos.comprado
GROUP BY cliente
ORDER BY km_medios DESC;
