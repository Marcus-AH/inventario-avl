#include "ArbolAVL.h"

// ==========================================
// === LÓGICA BÁSICA AVL ===
// ==========================================

ArbolAVL::ArbolAVL() { raiz = nullptr; }

int ArbolAVL::obtenerAltura(Nodo* n) { if (n == nullptr) return 0; return n->altura; }

int ArbolAVL::obtenerBalance(Nodo* n) { if (n == nullptr) return 0; return obtenerAltura(n->izquierda) - obtenerAltura(n->derecha); }

Nodo* ArbolAVL::rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierda; Nodo* T2 = x->derecha;
    x->derecha = y; y->izquierda = T2;
    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    return x;
}

Nodo* ArbolAVL::rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecha; Nodo* T2 = y->izquierda;
    y->izquierda = x; x->derecha = T2;
    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    return y;
}

Nodo* ArbolAVL::insertarNodo(Nodo* nodo, Producto p) {
    if (nodo == nullptr) {
        Nodo* nuevo = new Nodo();
        nuevo->dato = p; nuevo->izquierda = nullptr; nuevo->derecha = nullptr; nuevo->altura = 1;
        return nuevo;
    }
    if (p.id < nodo->dato.id) nodo->izquierda = insertarNodo(nodo->izquierda, p);
    else if (p.id > nodo->dato.id) nodo->derecha = insertarNodo(nodo->derecha, p);
    else { 
        // Si ya existe, actualizamos datos pero MANTENEMOS la ganancia acumulada previa si no se especifica
        float gananciaPrev = nodo->dato.gananciasAcumuladas;
        nodo->dato = p; 
        if (p.gananciasAcumuladas == 0) nodo->dato.gananciasAcumuladas = gananciaPrev; 
        return nodo; 
    }

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
    int balance = obtenerBalance(nodo);

    if (balance > 1 && p.id < nodo->izquierda->dato.id) return rotarDerecha(nodo);
    if (balance < -1 && p.id > nodo->derecha->dato.id) return rotarIzquierda(nodo);
    if (balance > 1 && p.id > nodo->izquierda->dato.id) { nodo->izquierda = rotarIzquierda(nodo->izquierda); return rotarDerecha(nodo); }
    if (balance < -1 && p.id < nodo->derecha->dato.id) { nodo->derecha = rotarDerecha(nodo->derecha); return rotarIzquierda(nodo); }
    return nodo;
}

void ArbolAVL::insertar(int id, string nombre, int cant, float precio, float ganancia) {
    Producto p = {id, nombre, cant, precio, ganancia};
    raiz = insertarNodo(raiz, p);
    cout << VERDE << "  [OK] " << RESET << "Producto procesado." << endl;
}

Nodo* ArbolAVL::nodoValorMinimo(Nodo* nodo) {
    Nodo* actual = nodo; while (actual->izquierda != nullptr) actual = actual->izquierda; return actual;
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
    if (balance > 1 && obtenerBalance(raiz->izquierda) < 0) { raiz->izquierda = rotarIzquierda(raiz->izquierda); return rotarDerecha(raiz); }
    if (balance < -1 && obtenerBalance(raiz->derecha) <= 0) return rotarIzquierda(raiz);
    if (balance < -1 && obtenerBalance(raiz->derecha) > 0) { raiz->derecha = rotarDerecha(raiz->derecha); return rotarIzquierda(raiz); }
    return raiz;
}

void ArbolAVL::eliminar(int id) {
    if (buscarNodo(raiz, id) == nullptr) { cout << ROJO << "  [ERROR] " << RESET << "ID no encontrado." << endl; return; }
    raiz = eliminarNodo(raiz, id);
    cout << AMARILLO << "  [ALERTA] " << RESET << "Producto eliminado." << endl;
}

// ==========================================
// === NUEVA LÓGICA DE VENTAS CON CLIENTE ===
// ==========================================

void ArbolAVL::registrarVenta(int id, int cantidad, string cliente, string dni) {
    Nodo* nodo = buscarNodo(raiz, id);
    
    if (nodo == nullptr) {
        cout << ROJO << "  [ERROR] " << RESET << "Producto no encontrado." << endl;
        return;
    }
    
    if (nodo->dato.cantidad < cantidad) {
        cout << ROJO << "  [ERROR] " << RESET << "Stock insuficiente. Solo hay " << BOLD << nodo->dato.cantidad << RESET << " unidades." << endl;
        return;
    }
    
    // Procesar venta
    nodo->dato.cantidad -= cantidad;
    float total = cantidad * nodo->dato.precio;
    
    // ACUMULAR GANANCIA AL PRODUCTO (NUEVO)
    nodo->dato.gananciasAcumuladas += total; 

    // Guardar en historial
    Venta v = {id, nodo->dato.nombre, cantidad, total, cliente, dni};
    historialVentas.push_back(v);
    
    cout << VERDE << "  [VENTA EXITOSA] " << RESET << endl;
    cout << "  Cliente  : " << cliente << " (DNI: " << dni << ")" << endl;
    cout << "  Total    : $" << fixed << setprecision(2) << total << endl;
    
    guardarEnArchivo(); 
    guardarVentas();   
}

void ArbolAVL::guardarVentas() {
    ofstream archivo("ventas.txt");
    if (archivo.is_open()) {
        for (const auto& v : historialVentas) {
            // Reemplazar espacios en nombre cliente por guiones bajos para evitar error de lectura simple
            string clienteSeguro = v.nombreCliente;
            replace(clienteSeguro.begin(), clienteSeguro.end(), ' ', '_');
            
            archivo << v.idProducto << " " << v.nombreProducto << " " << v.cantidadVendida << " " 
                    << v.totalVenta << " " << clienteSeguro << " " << v.dniCliente << endl;
        }
        archivo.close();
    }
}

void ArbolAVL::cargarVentas() {
    ifstream archivo("ventas.txt");
    if (!archivo.is_open()) return;
    
    Venta v;
    while (archivo >> v.idProducto >> v.nombreProducto >> v.cantidadVendida >> v.totalVenta >> v.nombreCliente >> v.dniCliente) {
        // Restaurar espacios en nombre cliente
        replace(v.nombreCliente.begin(), v.nombreCliente.end(), '_', ' ');
        historialVentas.push_back(v);
    }
    archivo.close();
}

// ==========================================
// === BÚSQUEDA Y VISUALIZACIÓN ===
// ==========================================

Nodo* ArbolAVL::buscarNodo(Nodo* raiz, int id) {
    if (raiz == nullptr || raiz->dato.id == id) return raiz;
    if (raiz->dato.id < id) return buscarNodo(raiz->derecha, id);
    return buscarNodo(raiz->izquierda, id);
}

void ArbolAVL::buscar(int id) {
    Nodo* res = buscarNodo(raiz, id);
    if (res != nullptr) {
        cout << "\n" << CYAN << "=== DETALLES DEL PRODUCTO ===" << RESET << endl;
        cout << " ID       : " << res->dato.id << endl;
        cout << " Nombre   : " << res->dato.nombre << endl;
        cout << " Precio   : $" << res->dato.precio << endl;
        cout << " Stock    : " << res->dato.cantidad << endl;
        cout << " Ganancias Generadas: " << VERDE << "$" << res->dato.gananciasAcumuladas << RESET << endl;
    } else { cout << ROJO << "  [ERROR] " << RESET << "No encontrado." << endl; }
}

void ArbolAVL::inOrden(Nodo* raiz) {
    if (raiz != nullptr) {
        inOrden(raiz->izquierda);
        cout << " " << left << setw(6) << raiz->dato.id << " | " << left << setw(15) << raiz->dato.nombre 
             << " | " << right << setw(5) << raiz->dato.cantidad << " | $" << right << setw(7) << fixed << setprecision(2) << raiz->dato.precio 
             << " | " << VERDE << "$" << setw(8) << raiz->dato.gananciasAcumuladas << RESET << endl;
        inOrden(raiz->derecha);
    }
}

void ArbolAVL::mostrarInventario() {
    cout << "\n" << BOLD << "   ID   | NOMBRE          | STOCK |  PRECIO  | GANANCIA ACUM." << RESET << endl;
    cout << "--------+-----------------+-------+----------+---------------" << endl;
    inOrden(raiz);
    cout << "--------+-----------------+-------+----------+---------------" << endl;
}

void ArbolAVL::imprimirArbol(Nodo* raiz, int espacio) {
    int COUNT = 8;
    if (raiz == nullptr) return;
    espacio += COUNT;
    imprimirArbol(raiz->derecha, espacio);
    cout << endl;
    for (int i = COUNT; i < espacio; i++) cout << " ";
    cout << AMARILLO << "[" << raiz->dato.id << "]" << RESET << "\n";
    imprimirArbol(raiz->izquierda, espacio);
}

void ArbolAVL::verArbolGrafico() {
    cout << "\n" << CYAN << "=== ESTRUCTURA AVL ===" << RESET << endl;
    if (raiz == nullptr) cout << " (Vacio) " << endl; else imprimirArbol(raiz, 0);
    cout << "\n======================" << endl;
}

bool ArbolAVL::estaVacio() { return raiz == nullptr; }

// ==========================================
// === PERSISTENCIA Y REPORTES ACTUALIZADOS ===
// ==========================================

void ArbolAVL::guardarAux(Nodo* nodo, ofstream& archivo) {
    if (nodo != nullptr) {
        // ID Nombre Cantidad Precio GananciaAcumulada
        archivo << nodo->dato.id << " " << nodo->dato.nombre << " " 
                << nodo->dato.cantidad << " " << nodo->dato.precio << " " << nodo->dato.gananciasAcumuladas << endl;
        guardarAux(nodo->izquierda, archivo);
        guardarAux(nodo->derecha, archivo);
    }
}

void ArbolAVL::guardarEnArchivo() {
    ofstream archivo("inventario.txt");
    if (archivo.is_open()) { guardarAux(raiz, archivo); archivo.close(); }
}

void ArbolAVL::cargarDesdeArchivo() {
    ifstream archivo("inventario.txt");
    if (!archivo.is_open()) return;
    int id, cant; float precio, ganancia; string nom;
    // Ahora lee 5 campos
    while (archivo >> id >> nom >> cant >> precio >> ganancia) { insertar(id, nom, cant, precio, ganancia); }
    archivo.close();
}

// --- EXPORTAR EXCEL ACTUALIZADO ---
void ArbolAVL::exportarCSVInventario(Nodo* nodo, ofstream& archivo) {
    if (nodo != nullptr) {
        // ID, Nombre, Stock, Precio, GananciaTotalDeEsteProducto
        archivo << nodo->dato.id << "," << nodo->dato.nombre << "," << nodo->dato.cantidad << "," 
                << nodo->dato.precio << "," << nodo->dato.gananciasAcumuladas << endl;
        exportarCSVInventario(nodo->izquierda, archivo);
        exportarCSVInventario(nodo->derecha, archivo);
    }
}

void ArbolAVL::exportarExcel() {
    ofstream archivo("ReporteCompleto.csv");
    if (archivo.is_open()) {
        // TABLA 1: INVENTARIO Y RENDIMIENTO POR PRODUCTO
        archivo << "REPORTE DE RENDIMIENTO E INVENTARIO,,,," << endl;
        archivo << ",,,," << endl;
        archivo << "--- TABLA 1: ESTADO DEL PRODUCTO ---,,,," << endl;
        archivo << "ID,Producto,Stock Actual,Precio Unitario,GANANCIA HISTORICA GENERADA ($)" << endl;
        exportarCSVInventario(raiz, archivo);
        
        archivo << ",,,," << endl;
        archivo << ",,,," << endl;
        
        // TABLA 2: DETALLE DE VENTAS CON CLIENTE
        archivo << "--- TABLA 2: BITACORA DE VENTAS ---,,,," << endl;
        archivo << "ID Prod,Producto,Cliente,DNI,Cant. Vendida,Monto Venta ($)" << endl;
        
        float gananciaTotal = 0;
        for (const auto& v : historialVentas) {
            archivo << v.idProducto << "," << v.nombreProducto << "," << v.nombreCliente << "," 
                    << v.dniCliente << "," << v.cantidadVendida << "," << v.totalVenta << endl;
            gananciaTotal += v.totalVenta;
        }
        
        archivo << ",,,,," << endl;
        archivo << ",,,,TOTAL CAJA:," << gananciaTotal << endl;

        archivo.close();
        cout << VERDE << "  [EXITO] " << RESET << "Reporte generado con Datos de Cliente y Rendimiento." << endl;
    } else { cout << ROJO << "  [ERROR] " << RESET << "Error creando CSV." << endl; }
}

void ArbolAVL::reporteBajoStockAux(Nodo* nodo, bool& hayAlertas) {
    if (nodo != nullptr) {
        reporteBajoStockAux(nodo->izquierda, hayAlertas);
        if (nodo->dato.cantidad < 5) {
            cout << ROJO << "  [ALERTA] " << RESET << nodo->dato.nombre << " (ID: " << nodo->dato.id << ") Stock: " << nodo->dato.cantidad << endl;
            hayAlertas = true;
        }
        reporteBajoStockAux(nodo->derecha, hayAlertas);
    }
}

void ArbolAVL::reporteBajoStock() {
    bool hayAlertas = false; cout << "\n=== STOCK CRITICO ===" << endl;
    reporteBajoStockAux(raiz, hayAlertas);
    if (!hayAlertas) cout << VERDE << "  Todo saludable." << RESET << endl;
}

void ArbolAVL::calcularValorTotalAux(Nodo* nodo, float& total) {
    if (nodo != nullptr) {
        total += (nodo->dato.cantidad * nodo->dato.precio);
        calcularValorTotalAux(nodo->izquierda, total);
        calcularValorTotalAux(nodo->derecha, total);
    }
}

void ArbolAVL::mostrarValorTotal() {
    float total = 0; calcularValorTotalAux(raiz, total);
    cout << "\n=== VALOR INVENTARIO (CAPITAL INVERTIDO) ===" << endl;
    cout << "  Total: $" << fixed << setprecision(2) << total << endl;
}