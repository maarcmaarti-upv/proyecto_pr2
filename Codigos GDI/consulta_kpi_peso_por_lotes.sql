-- Peso total procesado por lotes
SELECT 
    numero AS lote,
    SUM(peso) AS peso_total
FROM pimientos.lote_pimientos
GROUP BY numero
ORDER BY peso_total DESC;
