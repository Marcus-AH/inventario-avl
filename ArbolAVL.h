#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

// Colores para la consola (Funcionan en VS Code)
#define RESET   "\033[0m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

struct Producto {
    int id;
    string nombre;
    int cantidad;
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

    int obtenerAltura(Nodo* n);
    int obtenerBalance(Nodo* n);
    Nodo* rotarDerecha(Nodo* y);
    Nodo* rotarIzquierda(Nodo* x);
    Nodo* insertarNodo(Nodo* nodo, Producto p);
    Nodo* nodoValorMinimo(Nodo* nodo);
    Nodo* eliminarNodo(Nodo* raiz, int id);
    void inOrden(Nodo* raiz);
    Nodo* buscarNodo(Nodo* raiz, int id);
    void guardarAux(Nodo* nodo, ofstream& archivo);
    
    // Nueva función para imprimir el árbol bonito
    void imprimirArbol(Nodo* raiz, int espacio);

public:
    ArbolAVL();
    void insertar(int id, string nombre, int cant);
    void eliminar(int id);
    void buscar(int id);
    void mostrarInventario(); // Lista tabla
    void verArbolGrafico();   // Dibujo del árbol
    bool estaVacio();
    void guardarEnArchivo();
    void cargarDesdeArchivo();
};

#endif