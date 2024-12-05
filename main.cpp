#include <iostream>
#include <string>
#include "Parqueadero.h"
#include "Auto.h"
#include "Propietario.h"

using namespace std;

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    cout << "\n===== MENU PRINCIPAL =====\n";
    cout << "1. Estacionar un auto\n";
    cout << "2. Retirar un auto\n";
    cout << "3. Registrar auto permitido\n";
    cout << "4. Eliminar auto permitido\n";
    cout << "5. Mostrar estado del parqueadero\n";
    cout << "6. Mostrar lista de autos permitidos\n";
    cout << "0. Salir\n";
    cout << "Ingrese una opción: ";
}

// Función para registrar un auto y su propietario
void registrarAutoYPropietario(Auto*& nuevoAuto, Propietario*& nuevoPropietario) {
    string placa, marca, color;
    cout << "\nIngrese los datos del auto:\n";
    cout << "Placa: ";
    cin >> placa;
    cout << "Marca: ";
    cin >> marca;
    cout << "Color: ";
    cin >> color;
    nuevoAuto = new Auto(placa, marca, color);

    string nombre, cedula, celular;
    bool esDiscapacitado;
    cout << "\nIngrese los datos del propietario:\n";
    cout << "Nombre completo: ";
    cin.ignore(); // Limpiar el buffer
    getline(cin, nombre);
    cout << "Cédula: ";
    cin >> cedula;
    cout << "Celular: ";
    cin >> celular;
    cout << "¿Es discapacitado? (1: Sí, 0: No): ";
    cin >> esDiscapacitado;
    nuevoPropietario = new Propietario(nombre, cedula, celular, esDiscapacitado);
}

// Función para elegir un espacio del parqueadero
int elegirEspacio() {
    int espacioID;
    cout << "\nIngrese el número del espacio (1-12): ";
    cin >> espacioID;
    return espacioID;
}

// Menú principal del programa
int main() {
    const int TOTAL_ESPACIOS = 12;
    Parqueadero parqueadero(TOTAL_ESPACIOS);

    int opcion = -1;
    while (opcion != 0) {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
            case 1: { // Estacionar un auto
                Auto* nuevoAuto = nullptr;
                Propietario* nuevoPropietario = nullptr;
                registrarAutoYPropietario(nuevoAuto, nuevoPropietario);

                int espacioID = elegirEspacio();
                parqueadero.estacionarAuto(nuevoAuto, nuevoPropietario, espacioID);
                break;
            }
            case 2: { // Retirar un auto
                int espacioID = elegirEspacio();
                parqueadero.retirarAuto(espacioID);
                break;
            }
            case 3: { // Registrar auto permitido
                string placa;
                cout << "\nIngrese la placa del auto permitido: ";
                cin >> placa;
                parqueadero.registrarAutoPermitido(placa);
                break;
            }
            case 4: { // Eliminar auto permitido
                string placa;
                cout << "\nIngrese la placa del auto a eliminar: ";
                cin >> placa;
                parqueadero.eliminarAutoPermitido(placa);
                break;
            }
            case 5: { // Mostrar estado del parqueadero
                cout << "\n===== ESTADO DEL PARQUEADERO =====\n";
                parqueadero.mostrarEstado();
                break;
            }
            case 6: { // Mostrar lista de autos permitidos
                cout << "\n===== AUTOS PERMITIDOS =====\n";
                // Recorremos y mostramos los autos permitidos
                for (const auto& placa : parqueadero.getAutosPermitidos()) {
                    cout << "- " << placa << '\n';
                }
                break;
            }
            case 0: // Salir
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }
    }

    return 0;
}
