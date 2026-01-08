# 🛒 Sistema de Gestión de Inventario y POS (Punto de Venta) con Árboles AVL

![C++](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg) ![Structure](https://img.shields.io/badge/Data%20Structure-AVL%20Tree-green.svg) ![Status](https://img.shields.io/badge/Build-Stable-success.svg) ![Export](https://img.shields.io/badge/Report-Excel%20CSV-orange.svg)

> **Trabajo Final de Organización de Archivos**
> Una solución integral de software para la administración de stock, facturación y análisis de ganancias, optimizada matemáticamente con árboles auto-balanceados para garantizar un rendimiento de búsqueda $O(\log n)$ y equipada con reportes de negocio avanzados.

---

## 📑 Tabla de Contenidos
1. [Descripción del Proyecto](#-descripción-del-proyecto)
2. [Características Técnicas del Sistema](#-características-técnicas-del-sistema)
3. [Estructura del Código](#-estructura-del-código)
4. [Roles y Aportes del Equipo](#-roles-y-aportes-del-equipo)
5. [Instalación y Ejecución](#-instalación-y-ejecución)

---

## 📖 Descripción del Proyecto
Este proyecto simula un software empresarial real. Su núcleo no es una lista simple, sino un **Árbol Binario de Búsqueda AVL (Adelson-Velsky y Landis)**. Esto permite que el sistema se reordene automáticamente mediante rotaciones matemáticas cada vez que se inserta o elimina un producto, asegurando que la búsqueda de información sea instantánea.

Además de la gestión de almacén, el sistema incluye un **Módulo de Ventas (POS)** capaz de registrar clientes (DNI/Nombre), calcular ganancias históricas por producto y exportar toda la información financiera a hojas de cálculo compatibles con Excel.

---

## 🚀 Características Técnicas del Sistema

### 1. Backend y Algoritmos (AVL Logic)
* **Autobalanceo Matemático:** Implementación de cálculo de `Factor de Equilibrio` y ejecución de las 4 rotaciones (Simple Izq/Der y Dobles) para mantener la eficiencia.
* **Búsqueda Logarítmica:** Acceso a cualquier producto en tiempo $O(\log n)$.
* **Eliminación Robusta:** Algoritmo capaz de reestructurar el árbol al eliminar nodos críticos (raíz o nodos intermedios).

### 2. Inteligencia de Negocios (Business Logic)
* **Facturación con Cliente:** Registro de ventas vinculadas a datos reales del cliente (Nombre y DNI/RUC).
* **Análisis de Rentabilidad:** Cada nodo del árbol rastrea cuánto dinero ha generado históricamente (`gananciasAcumuladas`).
* **Alertas de Stock:** Monitoreo en tiempo real para detectar productos con stock crítico (< 5 unidades).

### 3. Persistencia y Reportes (IO)
* **Persistencia Dual:** Uso de `fstream` para mantener dos bases de datos: `inventario.txt` (Stock y Ganancias) y `ventas.txt` (Bitácora de Transacciones).
* **Exportación Avanzada:** Generación de `ReporteCompleto.csv` con doble tabulación: Estado del Inventario y Historial de Ventas Detallado.

---

## 📂 Estructura del Código

El proyecto sigue un diseño modular estricto para facilitar el mantenimiento y la escalabilidad:

| Archivo | Responsabilidad Técnica |
| :--- | :--- |
| **`main.cpp`** | **Controlador:** Gestiona el bucle principal, menú interactivo y la limpieza de buffer (`cin.ignore`) para lectura de cadenas con espacios. |
| **`ArbolAVL.h`** | **Definiciones:** Contiene los `structs` clave (`Venta`, `Producto`, `Nodo`) y los prototipos de la clase `ArbolAVL`. |
| **`ArbolAVL.cpp`** | **Motor Lógico:** Implementa la recursividad, rotaciones, lógica de ventas, cálculo de ganancias y manejo de archivos. |
| **`inventario.txt`** | **Base de Datos 1:** Almacena el estado actual del árbol (ID, Nombre, Stock, Precio, Ganancia). |
| **`ventas.txt`** | **Base de Datos 2:** Registro histórico de todas las transacciones realizadas (Cliente, Monto, Fecha). |

---

## 🧪 Caso de Prueba: Guía Paso a Paso

Para demostrar la funcionalidad completa del sistema durante la exposición, siga este guion de prueba:

### Paso 1: Inicialización y Carga
Ejecute el programa. Si existen archivos previos (`inventario.txt`), el sistema mostrará un mensaje de carga silenciosa.

### Paso 2: Alta de Productos (Inserción AVL)
Ingrese a la **Opción [1]** y registre los siguientes datos (en este orden para probar el balanceo):
1.  **ID:** `100` | **Nombre:** `Laptop_Gamer` | **Stock:** `10` | **Precio:** `1500`
2.  **ID:** `50`  | **Nombre:** `Mouse_RGB`    | **Stock:** `20` | **Precio:** `50`
3.  **ID:** `150` | **Nombre:** `Teclado_Mec`  | **Stock:** `15` | **Precio:** `100`

> *Prueba Técnica:* Vaya a la **Opción [5] (Ver Árbol)**. Debería ver al ID `100` como raíz, `50` a la izquierda y `150` a la derecha (Balanceado).

### Paso 3: Realizar una Venta (POS)
Ingrese a la **Opción [6] (Nueva Venta)**:
* **ID Producto:** `100`
* **Cantidad:** `2`
* **Cliente:** `Juan Perez`
* **DNI:** `12345678`

> *Resultado:* El sistema mostrará "Venta Exitosa", cobrará `$3000` y el stock de la Laptop bajará a `8`.

### Paso 4: Generación de Reportes
Ingrese a la **Opción [9] (Exportar Excel)**.
* El sistema generará el archivo `ReporteCompleto.csv`.
* **Acción:** Abra este archivo en Excel. Verificará que existen dos tablas: una con el stock actualizado (8 Laptops) y otra con la venta registrada a nombre de "Juan Perez".

### Paso 5: Persistencia
Cierre el programa (**Opción [0]**) y vuélvalo a abrir.
* Vaya a la **Opción [4]**. Verifique que los productos y las ganancias siguen ahí.

---

## 👥 Roles y Aportes del Equipo

Para garantizar el cumplimiento de la rúbrica, el equipo se dividió en roles técnicos específicos:

| Integrante | Rol Técnico | Aportes Específicos al Código |
| :--- | :--- | :--- |
| **Amaya Herrera, Marco Valentín** | *Core Backend Developer* | Diseño de la estructura `struct Nodo` y `struct Producto`. Implementación de la lógica de **Inserción Recursiva** y la gestión de punteros del árbol. |
| **Fernandez Lara, Angie Elizabeth** | *Algorithm Specialist* | Desarrollo del motor matemático de **Auto-balanceo**. Responsable de las funciones de `rotarIzquierda`, `rotarDerecha` y cálculo de alturas dinámicas. |
| **Rodriguez Agreda, Fernando David** | *Backend Operations* | Implementación de los algoritmos de **Búsqueda Binaria** y la compleja lógica de **Eliminación** (búsqueda del sucesor in-order para nodos con dos hijos). |
| **Silva Sifuentes, Diego Joseph** | *Persistence & Reporting* | Desarrollo del sistema de archivos (`fstream`). Creación de la función `exportarExcel()` que genera el reporte CSV con múltiples tablas. |
| **Ruiz Bustamante, Adrien Mourice Ivan** | *POS System Architect* | Arquitectura del **Módulo de Ventas**. Implementación de `struct Venta`, lógica de descuento de stock, cálculo de `gananciasAcumuladas` por producto y registro de Clientes. |
| **Barrantes Juarez, Paolo Rai** | *Frontend & QA* | Diseño de la **Interfaz de Usuario**, visualizador gráfico del árbol (`verArbolGrafico`), validación de entradas robusta y control de calidad. |

---

## 🛠️ Instalación y Ejecución

### Requisitos Previos
* Compilador G++ (MinGW para Windows o nativo en Linux/Mac).
* Entorno de desarrollo recomendado: Visual Studio Code.

### Compilación
Abra la terminal en la carpeta del proyecto y ejecute:

```bash
g++ main.cpp ArbolAVL.cpp -o sistema_pos 
```
### Paso 2: Ejecución
Una vez que el comando anterior termine sin errores, inicia el programa con:
```bash
.\inventario.exe
```
