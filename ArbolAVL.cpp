#include "ArbolAVL.h"

// --- IMPLEMENTACIÓN BÁSICA ---
ArbolAVL::ArbolAVL() { raiz = nullptr; }

int ArbolAVL::obtenerAltura(Nodo* n) {
    if (n == nullptr) return 0;
    return n->altura;
}

int ArbolAVL::obtenerBalance(Nodo* n) {
    if (n == nullptr) return 0;
    return obtenerAltura(n->izquierda) - obtenerAltura(n->derecha);
}

// --- ROTACIONES ---
Nodo* ArbolAVL::rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;
    x->derecha = y;
    y->izquierda = T2;
    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    return x;
}

Nodo* ArbolAVL::rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;
    y->izquierda = x;
    x->derecha = T2;
    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    return y;
}

// --- INSERTAR ---
Nodo* ArbolAVL::insertarNodo(Nodo* nodo, Producto p) {
    if (nodo == nullptr) {
        Nodo* nuevo = new Nodo();
        nuevo->dato = p;
        nuevo->izquierda = nullptr;
        nuevo->derecha = nullptr;
        nuevo->altura = 1;
        return nuevo;
    }
    if (p.id < nodo->dato.id) nodo->izquierda = insertarNodo(nodo->izquierda, p);
    else if (p.id > nodo->dato.id) nodo->derecha = insertarNodo(nodo->derecha, p);
    else return nodo;

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
    int balance = obtenerBalance(nodo);

    if (balance > 1 && p.id < nodo->izquierda->dato.id) return rotarDerecha(nodo);
    if (balance < -1 && p.id > nodo->derecha->dato.id) return rotarIzquierda(nodo);
    if (balance > 1 && p.id > nodo->izquierda->dato.id) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }
    if (balance < -1 && p.id < nodo->derecha->dato.id) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }
    return nodo;
}

void ArbolAVL::insertar(int id, string nombre, int cant) {
    Producto p = {id, nombre, cant};
    raiz = insertarNodo(raiz, p);
    // Feedback visual
    cout << VERDE << "  [OK] " << RESET << "Producto agregado: " << nombre << endl;
}

// --- ELIMINAR ---
Nodo* ArbolAVL::nodoValorMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual->izquierda != nullptr) actual = actual->izquierda;
    return actual;
}

Nodo* ArbolAVL::eliminarNodo(Nodo* raiz, int id) {
    if (raiz == nullptr) return raiz;
    if (id < raiz->dato.id) raiz->izquierda = eliminarNodo(raiz->izquierda, id);
    else if (id > raiz->dato.id) raiz->derecha = eliminarNodo(raiz->derecha, id);
    else {
        if ((raiz->izquierda == nullptr) || (raiz->derecha == nullptr)) {
            Nodo* temp = (raiz->izquierda) ? raiz->izquierda : raiz->derecha;
            if (temp == nullptr) { temp = raiz; raiz = nullptr; }
            else *raiz = *temp;
            delete temp;
        } else {
            Nodo* temp = nodoValorMinimo(raiz->derecha);
            raiz->dato = temp->dato;
            raiz->derecha = eliminarNodo(raiz->derecha, temp->dato.id);
        }
    }
    if (raiz == nullptr) return raiz;
    raiz->altura = 1 + max(obtenerAltura(raiz->izquierda), obtenerAltura(raiz->derecha));
    int balance = obtenerBalance(raiz);
    
    if (balance > 1 && obtenerBalance(raiz->izquierda) >= 0) return rotarDerecha(raiz);
    if (balance > 1 && obtenerBalance(raiz->izquierda) < 0) {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }
    if (balance < -1 && obtenerBalance(raiz->derecha) <= 0) return rotarIzquierda(raiz);
    if (balance < -1 && obtenerBalance(raiz->derecha) > 0) {
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }
    return raiz;
}

void ArbolAVL::eliminar(int id) {
    if (buscarNodo(raiz, id) == nullptr) {
        cout << ROJO << "  [ERROR] " << RESET << "ID " << id << " no encontrado." << endl;
        return;
    }
    raiz = eliminarNodo(raiz, id);
    cout << AMARILLO << "  [ALERTA] " << RESET << "Producto eliminado correctamente." << endl;
}

// --- BUSCAR Y MOSTRAR ---
Nodo* ArbolAVL::buscarNodo(Nodo* raiz, int id) {
    if (raiz == nullptr || raiz->dato.id == id) return raiz;
    if (raiz->dato.id < id) return buscarNodo(raiz->derecha, id);
    return buscarNodo(raiz->izquierda, id);
}

void ArbolAVL::buscar(int id) {
    Nodo* res = buscarNodo(raiz, id);
    if (res != nullptr) {
        cout << "\n" << CYAN << "=== PRODUCTO ENCONTRADO ===" << RESET << endl;
        cout << " ID       : " << BOLD << res->dato.id << RESET << endl;
        cout << " Nombre   : " << BOLD << res->dato.nombre << RESET << endl;
        cout << " Cantidad : " << BOLD << res->dato.cantidad << RESET << endl;
    } else {
        cout << ROJO << "  [ERROR] " << RESET << "Producto no encontrado." << endl;
    }
}

void ArbolAVL::inOrden(Nodo* raiz) {
    if (raiz != nullptr) {
        inOrden(raiz->izquierda);
        cout << " " << left << setw(8) << raiz->dato.id 
             << " | " << left << setw(18) << raiz->dato.nombre 
             << " | " << right << setw(5) << raiz->dato.cantidad << endl;
        inOrden(raiz->derecha);
    }
}

void ArbolAVL::mostrarInventario() {
    cout << "\n" << BOLD << "   ID     | NOMBRE             | STOCK " << RESET << endl;
    cout << "----------+--------------------+-------" << endl;
    inOrden(raiz);
    cout << "----------+--------------------+-------" << endl;
}

// --- VISUALIZACIÓN DE ÁRBOL (NUEVO) ---
void ArbolAVL::imprimirArbol(Nodo* raiz, int espacio) {
    // Distancia entre niveles
    int COUNT = 8;
    
    if (raiz == nullptr) return;

    // Aumentar distancia
    espacio += COUNT;

    // Procesar hijo derecho primero
    imprimirArbol(raiz->derecha, espacio);

    // Imprimir nodo actual
    cout << endl;
    for (int i = COUNT; i < espacio; i++) cout << " ";
    cout << AMARILLO << "[" << raiz->dato.id << "]" << RESET << "\n";

    // Procesar hijo izquierdo
    imprimirArbol(raiz->izquierda, espacio);
}

void ArbolAVL::verArbolGrafico() {
    cout << "\n" << CYAN << "=== ESTRUCTURA DEL ARBOL AVL (Gira la cabeza a la izquierda) ===" << RESET << endl;
    if (raiz == nullptr) cout << " (Arbol vacio) " << endl;
    else imprimirArbol(raiz, 0);
    cout << "\n================================================================" << endl;
}

// --- ARCHIVOS ---
void ArbolAVL::guardarAux(Nodo* nodo, ofstream& archivo) {
    if (nodo != nullptr) {
        archivo << nodo->dato.id << " " << nodo->dato.nombre << " " << nodo->dato.cantidad << endl;
        guardarAux(nodo->izquierda, archivo);
        guardarAux(nodo->derecha, archivo);
    }
}

void ArbolAVL::guardarEnArchivo() {
    ofstream archivo("inventario.txt");
    if (archivo.is_open()) {
        guardarAux(raiz, archivo);
        archivo.close();
    }
}

void ArbolAVL::cargarDesdeArchivo() {
    ifstream archivo("inventario.txt");
    if (!archivo.is_open()) return;
    int id, cant;
    string nom;
    while (archivo >> id >> nom >> cant) {
        insertar(id, nom, cant);
    }
    archivo.close();
}