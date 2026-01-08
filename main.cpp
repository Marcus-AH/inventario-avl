#include <iostream>
#include <limits>
#include <string>
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
    // cin.ignore se maneja localmente en los casos que usan getline para evitar doble salto
    cin.get();
}

void mostrarBanner() {
    cout << CYAN << BOLD;
    cout << "  ____            _   _                 \n";
    cout << " |  _ \\ ___  __ _| |_(_) ___  _ __      \n";
    cout << " | |_) / _ \\/ _` | __| |/ _ \\| '_ \\     \n";
    cout << " |  _ <  __/ (_| | |_| | (_) | | | |    \n";
    cout << " |_| \\_\\___|\\__, |\\__|_|\\___/|_| |_|    \n";
    cout << "            |___/                       \n";
    cout << "  SISTEMA POS & INVENTARIO AVL          \n" << RESET;
    cout << "========================================\n";
}

int main() {
    ArbolAVL inventario;
    int opcion, id, cantidad;
    float precio;
    string nombre, cliente, dni;

    // Cargar historial
    inventario.cargarDesdeArchivo();
    inventario.cargarVentas();

    do {
        limpiarPantalla();
        mostrarBanner();
        
        cout << BOLD << " [1] " << RESET << "Agregar Producto" << endl;
        cout << BOLD << " [2] " << RESET << "Buscar Producto" << endl;
        cout << BOLD << " [3] " << RESET << "Eliminar Producto" << endl;
        cout << BOLD << " [4] " << RESET << "Ver Inventario + Ganancias" << endl;
        cout << BOLD << " [5] " << RESET << "Ver Arbol Grafico" << endl;
        cout << " ------------------------------" << endl;
        cout << AMARILLO << " [6] " << RESET << "NUEVA VENTA (Cliente)" << endl; 
        cout << " ------------------------------" << endl;
        cout << " [7] " << "Reporte Bajo Stock" << endl;
        cout << " [8] " << "Capital en Inventario" << endl;
        cout << VERDE    << " [9] " << RESET << "Exportar EXCEL (Completo)" << endl;
        cout << " [0] " << "Guardar y Salir" << endl;
        
        cout << "\n Seleccione: ";
        while(!(cin >> opcion)){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ROJO << " Ingrese numero: " << RESET;
        }

        switch(opcion) {
            case 1:
                cout << "\n--- ALTA DE PRODUCTO ---\n";
                cout << " ID: "; cin >> id;
                cout << " Nombre (Sin_Espacios): "; cin >> nombre;
                cout << " Cantidad: "; cin >> cantidad;
                cout << " Precio: $"; cin >> precio;
                inventario.insertar(id, nombre, cantidad, precio);
                inventario.guardarEnArchivo();
                cin.ignore(); cin.get(); // Pausa manual
                break;
            case 2:
                cout << " ID a buscar: "; cin >> id; inventario.buscar(id); 
                cin.ignore(); cin.get(); 
                break;
            case 3:
                cout << " ID a eliminar: "; cin >> id; inventario.eliminar(id); inventario.guardarEnArchivo(); 
                cin.ignore(); cin.get();
                break;
            case 4:
                limpiarPantalla(); inventario.mostrarInventario(); 
                cin.ignore(); cin.get();
                break;
            case 5:
                limpiarPantalla(); inventario.verArbolGrafico(); 
                cin.ignore(); cin.get();
                break;
            case 6: 
                // --- VENTA COMPLETA CON CLIENTE ---
                cout << "\n--- FACTURACION ---\n";
                cout << " ID Producto: "; cin >> id;
                cout << " Cantidad: "; cin >> cantidad;
                
                // Limpieza de buffer vital para leer strings con espacios
                cin.ignore(); 
                
                cout << " Nombre Cliente: "; 
                getline(cin, cliente); // Permite espacios (Ej: Juan Perez)
                
                cout << " DNI / RUC: "; 
                getline(cin, dni);
                
                inventario.registrarVenta(id, cantidad, cliente, dni);
                cin.get(); // Pausa
                break;
            case 7:
                inventario.reporteBajoStock(); cin.ignore(); cin.get(); break;
            case 8:
                inventario.mostrarValorTotal(); cin.ignore(); cin.get(); break;
            case 9:
                inventario.exportarExcel(); cin.ignore(); cin.get(); break;
            case 0:
                inventario.guardarEnArchivo(); inventario.guardarVentas();
                cout << "\n Cerrando sistema..." << endl;
                break;
            default:
                cout << " Opcion invalida." << endl; cin.ignore(); cin.get();
        }
    } while(opcion != 0);

    return 0;
}