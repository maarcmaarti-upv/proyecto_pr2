
-- ============================================
-- PROVEEDORES
-- ============================================
INSERT INTO pimientos.proveedor (nombre, direccion, telefono) VALUES
('AgroSur S.L.', 'Sevilla', 954123456),
('Huerta Viva', 'Almería', 950987654),
('CampoFresco', 'Murcia', 968456789);

-- ============================================
-- CLIENTES
-- ============================================
INSERT INTO pimientos.cliente (nombre, direccion, telefono) VALUES
('Mercadona', 'Valencia', 961111111),
('Carrefour', 'Madrid', 911222222),
('Lidl', 'Barcelona', 931333333);

-- ============================================
-- PALLETS (30)
-- ============================================
INSERT INTO pimientos.pallet (codigo, tamano, material, precio, tiempo) VALUES
('PAL001', 120.00, 'Plástico', 15.00, 3.5),
('PAL002', 121.00, 'Madera', 24.00, 3.6),
('PAL003', 122.00, 'Metal', 42.00, 3.5),
('PAL004', 123.00, 'Plástico', 16.00, 3.4),
('PAL005', 124.00, 'Madera', 25.00, 3.6),
('PAL006', 125.00, 'Metal', 43.00, 3.5),
('PAL007', 126.00, 'Plástico', 17.00, 3.5),
('PAL008', 127.00, 'Madera', 26.00, 3.6),
('PAL009', 128.00, 'Metal', 44.00, 3.5),
('PAL010', 129.00, 'Plástico', 18.00, 3.4),
('PAL011', 130.00, 'Madera', 27.00, 3.6),
('PAL012', 131.00, 'Metal', 45.00, 3.5),
('PAL013', 132.00, 'Plástico', 19.00, 3.5),
('PAL014', 133.00, 'Madera', 28.00, 3.6),
('PAL015', 134.00, 'Metal', 46.00, 3.5),
('PAL016', 135.00, 'Plástico', 20.00, 3.4),
('PAL017', 136.00, 'Madera', 29.00, 3.6),
('PAL018', 137.00, 'Metal', 47.00, 3.5),
('PAL019', 138.00, 'Plástico', 21.00, 3.5),
('PAL020', 139.00, 'Madera', 30.00, 3.6),
('PAL021', 140.00, 'Metal', 48.00, 3.5),
('PAL022', 141.00, 'Plástico', 22.00, 3.4),
('PAL023', 142.00, 'Madera', 31.00, 3.6),
('PAL024', 143.00, 'Metal', 49.00, 3.5),
('PAL025', 144.00, 'Plástico', 23.00, 3.5),
('PAL026', 145.00, 'Madera', 32.00, 3.6),
('PAL027', 146.00, 'Metal', 50.00, 3.5),
('PAL028', 147.00, 'Plástico', 24.00, 3.4),
('PAL029', 148.00, 'Madera', 33.00, 3.6),
('PAL030', 149.00, 'Metal', 51.00, 3.5);

-- ============================================
-- CAJAS
-- 12 por pallet
-- ============================================

INSERT INTO pimientos.caja (codigo, tamano, material, codigo_pallet) VALUES
('CAJ0001', 50.00, 'Cartón', 'PAL001'),
('CAJ0002', 51.00, 'Plástico', 'PAL001'),
('CAJ0003', 52.00, 'Madera', 'PAL001'),
('CAJ0004', 53.00, 'Cartón', 'PAL001'),
('CAJ0005', 54.00, 'Plástico', 'PAL001'),
('CAJ0006', 55.00, 'Madera', 'PAL001'),
('CAJ0007', 56.00, 'Cartón', 'PAL001'),
('CAJ0008', 57.00, 'Plástico', 'PAL001'),
('CAJ0009', 58.00, 'Madera', 'PAL001'),
('CAJ0010', 59.00, 'Cartón', 'PAL001'),
('CAJ0011', 60.00, 'Plástico', 'PAL001'),
('CAJ0012', 61.00, 'Madera', 'PAL001'),

('CAJ0013', 50.00, 'Cartón', 'PAL002'),
('CAJ0014', 51.00, 'Plástico', 'PAL002'),
('CAJ0015', 52.00, 'Madera', 'PAL002'),
('CAJ0016', 53.00, 'Cartón', 'PAL002'),
('CAJ0017', 54.00, 'Plástico', 'PAL002'),
('CAJ0018', 55.00, 'Madera', 'PAL002');

-- hasta llegar a CAJ0360 para PAL030

-- ============================================
-- PAQUETES
-- 6 por caja
-- ============================================

INSERT INTO pimientos.paquete (codigo, tamano, material, codigo_caja) VALUES
('PAQ00001', 10.00, 'Plástico', 'CAJ0001'),
('PAQ00002', 11.00, 'Cartón', 'CAJ0001'),
('PAQ00003', 12.00, 'Madera', 'CAJ0001'),
('PAQ00004', 13.00, 'Plástico', 'CAJ0001'),
('PAQ00005', 14.00, 'Cartón', 'CAJ0001'),
('PAQ00006', 15.00, 'Madera', 'CAJ0001'),

('PAQ00007', 10.00, 'Plástico', 'CAJ0002'),
('PAQ00008', 11.00, 'Cartón', 'CAJ0002'),
('PAQ00009', 12.00, 'Madera', 'CAJ0002'),
('PAQ00010', 13.00, 'Plástico', 'CAJ0002'),
('PAQ00011', 14.00, 'Cartón', 'CAJ0002'),
('PAQ00012', 15.00, 'Madera', 'CAJ0002');

-- Continuar el mismo patrón hasta PAQ02160

-- ============================================
-- LOTES
-- ============================================

INSERT INTO pimientos.lote_pimientos
(numero, color, peso, procedencia, precio, codigo_paquete)
VALUES
('LOT00001', 'Rojo', 100.50, 'Almería', 1.20, 'PAQ00001'),
('LOT00002', 'Verde', 101.00, 'Murcia', 1.25, 'PAQ00002'),
('LOT00003', 'Amarillo', 102.00, 'Sevilla', 1.30, 'PAQ00003'),
('LOT00004', 'Rojo', 103.00, 'Granada', 1.35, 'PAQ00004'),
('LOT00005', 'Verde', 104.00, 'Valencia', 1.40, 'PAQ00005');

-- Continuar hasta LOT02160

-- ============================================
-- ALBARANES PROVEEDOR
-- ============================================

INSERT INTO pimientos.albaran_proveedor (nombre, albaran) VALUES
('AgroSur S.L.', 'ALB-P-001'),
('AgroSur S.L.', 'ALB-P-002'),
('Huerta Viva', 'ALB-P-003'),
('CampoFresco', 'ALB-P-004');

-- ============================================
-- ALBARANES CLIENTE
-- ============================================

INSERT INTO pimientos.albaran_cliente (nombre, albaran) VALUES
('Mercadona', 'ALB-C-001'),
('Mercadona', 'ALB-C-002'),
('Carrefour', 'ALB-C-003'),
('Lidl', 'ALB-C-004');

-- ============================================
-- VENDEN
-- ============================================

INSERT INTO pimientos.venden
(proveedor, lote, transporte, km, duracion)
VALUES
('AgroSur S.L.', 'LOT00001', 'Camión', 200.5, 3.5),
('AgroSur S.L.', 'LOT00002', 'Camión', 180.0, 3.0),
('Huerta Viva', 'LOT00003', 'Furgoneta', 150.0, 2.5),
('CampoFresco', 'LOT00004', 'Tren', 300.0, 5.0),
('CampoFresco', 'LOT00005', 'Camión', 250.0, 4.2);

-- Continuar hasta LOT02160 alternando proveedores

-- ============================================
-- COMPRADO
-- ============================================

INSERT INTO pimientos.comprado
(cliente, pallet, transporte, km, duracion)
VALUES
('Mercadona', 'PAL001', 'Camión', 250.0, 4.0),
('Mercadona', 'PAL002', 'Camión', 270.0, 4.2),
('Carrefour', 'PAL003', 'Tren', 400.0, 6.0),
('Carrefour', 'PAL004', 'Furgoneta', 180.0, 3.0),
('Lidl', 'PAL005', 'Camión', 350.0, 5.0),
('Lidl', 'PAL006', 'Tren', 420.0, 6.5),
('Mercadona', 'PAL007', 'Camión', 390.0, 5.8),
('Mercadona', 'PAL008', 'Camión', 240.0, 4.1),
('Carrefour', 'PAL009', 'Furgoneta', 310.0, 5.0),
('Lidl', 'PAL010', 'Camión', 280.0, 4.5);

-- Continuar mezclando clientes y pallets