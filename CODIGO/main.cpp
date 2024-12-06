#include "Menu.h"
#include <iostream>
#include <string>
#include "Parqueadero.h"
#include "Auto.h"
#include "Propietario.h"
#include <algorithm>
#include "Validaciones.h"

using namespace std;
int elegirEspacio()
{
    Validaciones<int> ingresar_entero;
    int espacioID;
    espacioID = ingresar_entero.ingresar("Ingrese el espacio para estacionarse: \n", "entero");
    return espacioID;
}

// Función para registrar un auto y su propietario
void registrarAutoYPropietario(Auto *&nuevoAuto, Propietario *&nuevoPropietario)
{
    string placa, marca, color;
    Validaciones<std::string> ingresar_string;
    cout << "\nIngrese los datos del auto:\n";
    cout << "Placa: ";
    cin >> placa;
    marca = ingresar_string.ingresar("Marca: ", "string");
    cout << "\n";
    color = ingresar_string.ingresar("Color: ", "string");
    nuevoAuto = new Auto(placa, marca, color);

    string nombre, cedula, correo;
    bool esDiscapacitado;
    Validaciones<int> ingresar_entero;
    cout << "\nIngrese los datos del propietario:\n";
    cout << "Nombre y Apellido: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Cedula: ";
    cin >> cedula;
    cout << "Correo: ";
    cin >> correo;
    esDiscapacitado = ingresar_entero.ingresar("Tiene alguna discapacidad? (1: Si, 0: No): ", "entero");
    nuevoPropietario = new Propietario(nombre, cedula, correo, esDiscapacitado);
}
int main()
{
    const std::string rutaPropietarios = "propietarios.txt";
    const std::string rutaAutosPermitidos = "autos.txt";
    Menu menu;

    Parqueadero parqueadero(20, rutaPropietarios, rutaAutosPermitidos);
    parqueadero.cargarPropietarios(rutaPropietarios);
    while (true)
    {
        vector<string> opciones = {
            "   Registrar datos del auto     ",
            "       Retirar un auto          ",
            "      Estacionar un auto        ",
            "    Eliminar auto registrado    ",
            "  Mostrar estado del parqueadero",
            "Mostrar lista de autos registrados",
            "    Guardar lista de autos       ",
            "   Mostrar lista de propietarios ",
            "  Guardar lista de propietarios  ",
            "     Eliminar propietario        ",
            "           Salir                 "};

        int opcion = menu.mostrarMenu("===== MENU PRINCIPAL =====", opciones);
        system("cls");
        switch (opcion+1)
        {
        case 0:
        { // Registrar un auto permitido y su propietario
            Auto *nuevoAuto = nullptr;
            Propietario *nuevoPropietario = nullptr;

            registrarAutoYPropietario(nuevoAuto, nuevoPropietario);

            nuevoPropietario->agregarAuto(*nuevoAuto);
            parqueadero.registrarAutoPermitido(*nuevoAuto);
            parqueadero.agregarPropietario(*nuevoPropietario);

            parqueadero.guardarPropietarios(rutaPropietarios);
            parqueadero.guardarAutosPermitidos(rutaAutosPermitidos);

            cout << "Registro completo.\n";
            delete nuevoAuto;
            delete nuevoPropietario;
            break;
        }
        case 1:
        { // Registrar un auto permitido y su propietario
            Auto *nuevoAuto = nullptr;
            Propietario *nuevoPropietario = nullptr;

            registrarAutoYPropietario(nuevoAuto, nuevoPropietario);

            // Asociar el auto con el propietario
            nuevoPropietario->agregarAuto(*nuevoAuto);

            // Registrar el auto permitido
            parqueadero.registrarAutoPermitido(*nuevoAuto);

            // Agregar el propietario a la lista de propietarios
            parqueadero.agregarPropietario(*nuevoPropietario);

            // Guardar propietario y autos en archivos
            parqueadero.guardarPropietarios(rutaPropietarios);
            parqueadero.guardarAutosPermitidos(rutaAutosPermitidos);

            cout << "Registro completo.\n";
            delete nuevoAuto;
            delete nuevoPropietario;
            break;
        }
        case 2:
        { // Retirar un auto
            int espacioID = elegirEspacio();
            parqueadero.retirarAuto(espacioID);
            break;
        }
        case 3:
        { // Estacionar un auto
            string placa;
            cout << "\nIngrese la placa del auto a estacionar: ";
            cin >> placa;

            int espacioID = elegirEspacio();
            parqueadero.estacionarAuto(new Auto(placa, "Desconocido", "Desconocido"), nullptr, espacioID);
            break;
        }
        case 4:
        { // Eliminar auto permitido
            string placa;
            cout << "\nIngrese la placa del auto a eliminar: ";
            cin >> placa;
            parqueadero.eliminarAutoPermitido(placa);
            break;
        }
        case 5:
        { // Mostrar estado del parqueadero
            cout << "\n===== ESTADO DEL PARQUEADERO =====\n";
            parqueadero.mostrarEstado();
            break;
        }
        case 6:
        { // Mostrar lista de autos permitidos
            cout << "\n===== AUTOS PERMITIDOS =====\n";
            if (parqueadero.getAutosPermitidos().empty())
            {
                cout << "No hay autos registrados.\n";
            }
            else
            {
                for (const auto &autoPermitido : parqueadero.getAutosPermitidos())
                {
                    cout << "- Placa: " << autoPermitido.getPlaca()
                         << ", Marca: " << autoPermitido.getMarca()
                         << ", Color: " << autoPermitido.getColor() << '\n';
                }
            }
            break;
        }
        case 7:
        { // Guardar lista de autos permitidos a archivo
            parqueadero.guardarAutosPermitidos(rutaAutosPermitidos);
            cout << "Lista de autos permitidos guardada.\n";
            break;
        }
        case 8:
        { // Mostrar lista de propietarios y sus autos
            cout << "\n===== PROPIETARIOS REGISTRADOS =====\n";
            if (parqueadero.getPropietarios().empty())
            {
                cout << "No hay propietarios registrados.\n";
            }
            else
            {
                for (const auto &propietario : parqueadero.getPropietarios())
                {
                    cout << "Nombre: " << propietario.getNombreCompleto()
                         << ", Cédula: " << propietario.getCedula()
                         << ", Correo: " << propietario.getCorreo()
                         << ", Es discapacitado: " << (propietario.getEsDiscapacitado() ? "Sí" : "No") << '\n';

                    for (const auto &autoAsociado : propietario.getAutos())
                    {
                        cout << "  - Auto: Placa: " << autoAsociado.getPlaca()
                             << ", Marca: " << autoAsociado.getMarca()
                             << ", Color: " << autoAsociado.getColor() << '\n';
                    }
                }
            }
            break;
        }
        case 9:
        {
            parqueadero.guardarPropietarios(rutaPropietarios);
            cout << "Lista de propietarios guardada.\n";
            break;
        }
        case 10: // Eliminar propietario
        {
            string cedula;
            cout << "\nIngrese la cedula del propietario a eliminar: ";
            cin >> cedula;

            parqueadero.eliminarPropietario(cedula);
            break;
        }
        case 11:
            cout << "\nSaliendo del programa...\n";
            return 0;
        default:
            cout << "\nOpción inválida.\n";
            break;
        }
        cout << "Presione Enter para continuar...";
        cin.get();
    }

    return 0;
}
