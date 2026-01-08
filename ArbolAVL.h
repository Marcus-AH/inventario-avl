#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// --- COLORES ---
#define RESET   "\033[0m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Estructura del Producto
struct Producto {
    int id;
    string nombre;
    int cantidad;
    float precio; 
    float gananciasAcumuladas; // <--- NUEVO: Cuánto dinero ha generado este producto históricamente
};

// Estructura de Venta
struct Venta {
    int idProducto;
    string nombreProducto;
    int cantidadVendida;
    float totalVenta;
    string nombreCliente; // <--- NUEVO
    string dniCliente;    // <--- NUEVO
};

struct Nodo {
    Producto dato;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;
};

class ArbolAVL {
private:
    Nodo* raiz;
    vector<Venta> historialVentas;

    // Funciones internas AVL
    int obtenerAltura(Nodo* n);
    int obtenerBalance(Nodo* n);
    Nodo* rotarDerecha(Nodo* y);
    Nodo* rotarIzquierda(Nodo* x);
    Nodo* insertarNodo(Nodo* nodo, Producto p);
    Nodo* nodoValorMinimo(Nodo* nodo);
    Nodo* eliminarNodo(Nodo* raiz, int id);
    Nodo* buscarNodo(Nodo* raiz, int id);
    
    // Auxiliares
    void inOrden(Nodo* raiz);
    void guardarAux(Nodo* nodo, ofstream& archivo);
    void imprimirArbol(Nodo* raiz, int espacio);
    
    // Auxiliares Reportes
    void exportarCSVInventario(Nodo* nodo, ofstream& archivo);
    void reporteBajoStockAux(Nodo* nodo, bool& hayAlertas);
    void calcularValorTotalAux(Nodo* nodo, float& total);

public:
    ArbolAVL();
    
    // CRUD
    // Nota: 'ganancia' se inicializa en 0 al crear, pero se carga del archivo si existe
    void insertar(int id, string nombre, int cant, float precio, float ganancia = 0.0);
    void eliminar(int id);
    void buscar(int id);
    
    // Venta con Cliente
    void registrarVenta(int id, int cantidad, string cliente, string dni); // <--- ACTUALIZADO

    // Visualización
    void mostrarInventario();
    void verArbolGrafico();
    bool estaVacio();

    // Persistencia
    void guardarEnArchivo();
    void cargarDesdeArchivo();
    void guardarVentas();
    void cargarVentas();

    // Reportes
    void exportarExcel(); 
    void reporteBajoStock();
    void mostrarValorTotal();
};

#endif