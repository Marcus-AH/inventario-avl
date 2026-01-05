# 📦 Sistema de Gestión de Inventario Inteligente (AVL)

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg) ![Estructura](https://img.shields.io/badge/Data%20Structure-AVL%20Tree-green.svg) ![Status](https://img.shields.io/badge/Status-Completed-success.svg)

> **Proyecto Final de Organización de Archivos** > Una solución robusta de consola para la gestión de inventarios empresariales, implementando **Árboles de Búsqueda AVL (Adelson-Velsky y Landis)** para garantizar una complejidad algorítmica de $O(\log n)$ en todas las operaciones críticas, junto con persistencia de datos y una interfaz de usuario mejorada.

---

## 📑 Tabla de Contenidos
1. [Descripción del Proyecto](#-descripción-del-proyecto)
2. [Características Técnicas](#-características-técnicas)
3. [Estructura del Código](#-estructura-del-código)
4. [Instalación y Ejecución](#-instalación-y-ejecución)
5. [Roles y Aportes del Equipo](#-roles-y-aportes-del-equipo-6-integrantes)
6. [Demostración Visual](#-demostración-visual)

---

## 📖 Descripción del Proyecto
Este software permite a una empresa gestionar su stock de productos de manera eficiente. A diferencia de las listas lineales o árboles binarios simples (BST), este sistema se **autobalancea**.

Si se ingresan productos con IDs consecutivos (ej. 10, 20, 30...), el sistema detecta el desequilibrio y realiza **rotaciones matemáticas automáticas** para reorganizar los nodos. Esto asegura que la búsqueda de un producto entre millones de registros sea instantánea. Además, cuenta con un sistema de archivos para que la información no se pierda al cerrar el programa.

---

## 🚀 Características Técnicas

### 1. Correctitud Funcional (Backend)
* **CRUD Completo:** Crear, Leer, Actualizar (balanceo) y Borrar productos.
* **Algoritmo AVL:** Implementación de cálculo de `Factor de Equilibrio` (Altura Izquierda - Altura Derecha).
* **Rotaciones:** Soporte para los 4 casos de reestructuración:
    * Rotación Simple Derecha (LL).
    * Rotación Simple Izquierda (RR).
    * Rotación Doble Izquierda-Derecha (LR).
    * Rotación Doble Derecha-Izquierda (RL).

### 2. Persistencia de Datos
* Uso de la librería `<fstream>` para serializar el árbol en un archivo `inventario.txt`.
* Carga automática (`Load on Startup`) y guardado automático (`Auto-Save`) tras cada modificación.

### 3. Interfaz de Usuario (UX/UI)
* **Visualizador Gráfico:** Algoritmo recursivo que imprime el árbol en consola mostrando la jerarquía visual de nodos.
* **Feedback Visual:** Uso de códigos ANSI para colores (Verde para éxitos, Rojo para errores).
* **Robustez:** Validación de `cin` para evitar crasheos por errores de tipo de dato (Input Sanitization).

---

## 📂 Estructura del Código

El proyecto sigue un diseño modular para cumplir con los estándares de **Calidad de Código**:

| Archivo | Responsabilidad |
| :--- | :--- |
| `main.cpp` | **Controlador:** Maneja el bucle principal, menú, validación de entradas y llamadas al backend. |
| `ArbolAVL.h` | **Cabecera:** Definición de estructuras (`struct Producto`, `struct Nodo`) y prototipos de la clase `ArbolAVL`. |
| `ArbolAVL.cpp` | **Lógica de Negocio:** Implementación de recursividad, inserción, eliminación compleja, rotaciones y manejo de archivos. |
| `Utils.h` / `Colors` | Definiciones de macros para el manejo de colores en consola y limpieza de pantalla multiplataforma. |
| `inventario.txt` | **Base de Datos:** Archivo de texto plano generado automáticamente para la persistencia. |

---

## 👥 Roles y Aportes del Equipo (6 Integrantes)

Para cumplir con el desarrollo integral, el equipo se dividió en células de trabajo especializadas:

### 🔹 Equipo de Arquitectura y Estructura (Backend Core)
* **[Amaya Herrea Marco Valentín]:** Diseño de la estructura `struct Nodo` y `class ArbolAVL`. Implementación de la lógica de **Inserción Recursiva** y cálculo de alturas dinámicas.
* **[Fernandez Lara Angie Elizabeth]:** Desarrollo de la lógica matemática de las **Rotaciones (Simples y Dobles)**. Responsable de asegurar que el árbol nunca pierda su propiedad AVL tras una inserción crítica.

### 🔹 Equipo de Operaciones Complejas (Backend Advanced)
* **[Rodriguez Agreda Fernando David]:** Implementación del algoritmo de **Eliminación (Delete)**. Manejo de los 3 casos borde: nodo hoja, nodo con 1 hijo, y nodo con 2 hijos (búsqueda del sucesor in-order).
* **[Silva Sifuentes Diego Joseph]:** Desarrollo del sistema de archivos (`fstream`). Creación de las funciones `guardarEnArchivo()` (serialización recursiva) y `cargarDesdeArchivo()` (parsing de texto a árbol).

### 🔹 Equipo de Frontend y Control de Calidad (UI/UX & QA)
* **[Ruiz Bustamante Adrien Mourice Ivan]:** Diseño del menú interactivo, implementación de colores ANSI y la función crítica `verArbolGrafico()` para visualizar la estructura del árbol en consola.
* **[Barrantes Juarez Paolo Rai]:** Validación de entradas (evitar bucles infinitos con `cin.fail`), pruebas de estrés (casos extremos), redacción del README y edición del video demostrativo.

---

## 🛠️ Instalación y Ejecución

### Requisitos Previos
* Compilador G++ (MinGW para Windows).
* Visual Studio Code (Recomendado).

### Paso 1: Compilación
Abre la terminal en la carpeta del proyecto y ejecuta el comando de enlazado:

```bash
g++ main.cpp ArbolAVL.cpp -o inventario 
```
### Paso 2: Ejecución
Una vez que el comando anterior termine sin errores, inicia el programa con:
```bash
.\inventario.exe
```