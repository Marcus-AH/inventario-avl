#include <iostream>
#include <limits>
#include <stdlib.h> // Para system("pause") o cin.get()
#include "ArbolAVL.h"

using namespace std;

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    cout << "\n" << BOLD << "Presione Enter para continuar..." << RESET;
    cin.ignore();
    cin.get();
}

void mostrarBanner() {
    cout << CYAN << BOLD;
    cout << "  ____           _   _              \n";
    cout << " |  _ \\ ___  ___| |_(_) ___  _ __   \n";
    cout << " | |_) / _ \\/ __| __| |/ _ \\| '_ \\  \n";
    cout << " |  _ <  __/ (__| |_| | (_) | | | | \n";
    cout << " |_| \\_\\___|\\___|\\__|_|\\___/|_| |_| \n";
    cout << "     SISTEMA DE INVENTARIO AVL      \n" << RESET;
    cout << "====================================\n";
}

int main() {
    ArbolAVL inventario;
    int opcion, id, cantidad;
    string nombre;

    // Cargar datos silenciosamente
    inventario.cargarDesdeArchivo();

    do {
        limpiarPantalla();
        mostrarBanner();
        
        cout << BOLD << " [1] " << RESET << "Agregar Producto" << endl;
        cout << BOLD << " [2] " << RESET << "Buscar Producto" << endl;
        cout << BOLD << " [3] " << RESET << "Eliminar Producto" << endl;
        cout << BOLD << " [4] " << RESET << "Ver Lista (Tabla)" << endl;
        cout << BOLD << " [5] " << RESET << "Ver Estructura Arbol (Grafico)" << endl; // NUEVO
        cout << BOLD << " [6] " << RESET << "Guardar y Salir" << endl;
        cout << "\n Seleccione una opcion: ";
        
        while(!(cin >> opcion)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ROJO << " Opcion invalida. Intente de nuevo: " << RESET;
        }

        switch(opcion) {
            case 1:
                cout << "\n--- NUEVO REGISTRO ---\n";
                cout << " ID: "; cin >> id;
                cout << " Nombre (sin espacios): "; cin >> nombre;
                cout << " Cantidad: "; cin >> cantidad;
                inventario.insertar(id, nombre, cantidad);
                inventario.guardarEnArchivo();
                pausar();
                break;
            case 2:
                cout << "\n--- BUSQUEDA ---\n";
                cout << " ID a buscar: "; cin >> id;
                inventario.buscar(id);
                pausar();
                break;
            case 3:
                cout << "\n--- ELIMINAR ---\n";
                cout << " ID a eliminar: "; cin >> id;
                inventario.eliminar(id);
                inventario.guardarEnArchivo();
                pausar();
                break;
            case 4:
                limpiarPantalla();
                mostrarBanner();
                inventario.mostrarInventario();
                pausar();
                break;
            case 5:
                limpiarPantalla();
                mostrarBanner();
                inventario.verArbolGrafico();
                pausar();
                break;
            case 6:
                inventario.guardarEnArchivo();
                cout << "\n" << VERDE << " Guardando cambios..." << RESET << endl;
                cout << " ¡Hasta luego!" << endl;
                break;
            default:
                cout << ROJO << " Opcion no reconocida." << RESET << endl;
                pausar();
        }
    } while(opcion != 6);

    return 0;
}