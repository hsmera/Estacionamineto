#include "Menu.h"
#include <iostream>
#include <string>
#include "Parqueadero.h"
#include "Auto.h"
#include "Propietario.h"
#include <algorithm>
#include "Validaciones.h"
#include "RegistroHistorial.h"
#include <limits>
using namespace std;
int elegirEspacio()
{
    Validaciones<int> ingresar_entero;
    int espacioID;
    cout << "Ingrese el espacio: ";
    cin >> espacioID;
    // espacioID = ingresar_entero.ingresar("Ingrese el espacio: ", "entero");
    return espacioID;
}

// Función para registrar un auto y su propietario
void registrarAutoYPropietario(Auto *&nuevoAuto, Propietario *&nuevoPropietario)
{
    string placa, marca, color, estado;
    Validaciones<std::string> ingresar_string;

    cout << "\nIngrese los datos del auto:\n";
    placa = ingresar_string.ingresarPlaca("Ingrese la placa del auto (solo letras y numeros): ");
    cout << endl;
    marca = ingresar_string.ingresar("Marca: ", "string");
    cout << endl;
    color = ingresar_string.ingresar("Color: ", "string");

    // Crear el objeto Auto con la tarjeta generada
    nuevoAuto = new Auto(placa, marca, color, estado);

    string nombre, cedula, correo;
    bool esDiscapacitado;
    Validaciones<int> ingresar_entero;
    cout << "\nIngrese los datos del propietario:\n";
    nombre = ingresar_string.ingresar("Ingrese el nombre y apellido del propietario: ", "string");
    cout << endl;
    cout << "Cedula: ";
    cin >> cedula;
    cout << "Correo: ";
    cin >> correo;
    esDiscapacitado = ingresar_entero.ingresar("Tiene alguna discapacidad? (1: Si, 0: No): ", "entero");

    nuevoPropietario = new Propietario(nombre, cedula, correo, esDiscapacitado);
}

void pausar()
{
    cout << "Presione Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el buffer
    cin.get();                                                     // Espera a Enter
}

int main()
{
    const std::string rutaPropietarios = "propietarios.txt";
    const std::string rutaAutosPermitidos = "autos.txt";
    const std::string rutaHistorial = "historial.txt";
    Validaciones<std::string> validar;

    Menu menu;
    RegistroHistorial historial(rutaHistorial);

    Parqueadero parqueadero(20, rutaPropietarios, rutaAutosPermitidos);
    parqueadero.cargarPropietarios(rutaPropietarios);
    while (true)
    {
        vector<string> opciones = {
            "   Ingresar al parqueadero      ",
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
            "      Mostrar Historial          ",
            "Mostrar estado de forma circular ",
            "           Salir                 "};

        int opcion = menu.mostrarMenu("===== MENU PRINCIPAL =====", opciones);
        system("cls");
        switch (opcion + 1)
        {
        case 1: // Verificar si tiene tarjeta de parqueo
        {
            std::string placa, tarjeta;

            // Preguntar si el usuario tiene tarjeta de parqueo
            char respuesta;
            cout << "Tiene tarjeta de parqueo? (s/n): ";
            cin >> respuesta;

            if (respuesta == 's' || respuesta == 'S')
            {
                // Si tiene tarjeta, pedir la placa y la tarjeta
                placa = validar.ingresarPlaca("Ingrese la placa del auto: ");
                cout << endl;
                cout << "Ingrese la tarjeta de parqueo: ";
                cin >> tarjeta;

                // Limpiar espacios de la tarjeta ingresada
                tarjeta.erase(remove(tarjeta.begin(), tarjeta.end(), ' '), tarjeta.end());

                // Verificar si el auto tiene tarjeta registrada
                bool tarjetaValida = false;
                auto &autosPermitidos = parqueadero.getAutosPermitidos();

                for (const auto &autoPermitido : autosPermitidos)
                {
                    if (autoPermitido.getPlaca() == placa)
                    {
                        // Si el auto está permitido, verificar la tarjeta
                        auto it = parqueadero.getTarjetasParqueo().find(placa);
                        if (it != parqueadero.getTarjetasParqueo().end() && it->second == tarjeta)
                        {
                            tarjetaValida = true;
                            break;
                        }
                    }
                }

                // Si la tarjeta es válida, cambiar estado y permitir ingreso
                if (tarjetaValida)
                {
                    cout << "\nTarjeta de parqueo valida. Actualizando estado del auto...\n";

                    // Actualizar estado del auto en el parqueadero
                    parqueadero.actualizarEstadoAuto(placa, "Dentro del parqueadero");

                    cout << "Auto con placa " << placa << " ingreso correctamente al parqueadero.\n";
                }
                else
                {
                    cout << "\nTarjeta invalida o el auto no esta registrado. Primero debe registrarse en el parqueadero.\n";
                }
            }
            else
            {
                // Si no tiene tarjeta, mostrar mensaje de error
                cout << "\nDebe registrarse en el parqueadero primero.\n";
            }

            pausar();
            break;
        }
        case 2:
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
            pausar();
            break;
        }
        case 3:
        {
            // Retirar un auto por placa
            std::string placa;
            placa = validar.ingresarPlaca("\nIngrese la placa del auto a retirar: ");
            cout << endl;

            // Llamar a la función retirarAuto con la placa
            parqueadero.retirarAuto(placa);
            pausar();
            break;
        }

        case 4:
        { // Estacionar un auto
            string placa, tarjeta;
            placa = validar.ingresarPlaca("Ingrese la placa del auto a estacionar: ");
            cout << endl;
            cout << "\nIngrese la tarjeta de parqueo: ";
            cin >> tarjeta;
            cout << endl;
            parqueadero.estacionarAuto(new Auto(placa, "Desconocido", "Desconocido", tarjeta), nullptr, tarjeta, elegirEspacio());
            pausar();
            break;
        }
        case 5:
        { // Eliminar auto permitido
            std::string placa = validar.ingresarPlaca("Ingrese la placa a eliminar: ");
            cout << endl;
            parqueadero.eliminarAutoPermitido(placa);
            pausar();
            break;
        }
        case 6:
        { // Mostrar estado del parqueadero
            cout << "\n===== ESTADO DEL PARQUEADERO =====\n";
            parqueadero.mostrarEstado();
            pausar();
            break;
        }
        case 7:
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
                    // Obtener el número de la tarjeta desde el mapa de tarjetas
                    std::string tarjeta;
                    try
                    {
                        tarjeta = parqueadero.getTarjetasParqueo().at(autoPermitido.getPlaca());
                    }
                    catch (const std::out_of_range &)
                    {
                        tarjeta = "No asignada"; // Si no se encuentra la tarjeta, mostramos "No asignada"
                    }

                    // Imprimir los detalles del auto y la tarjeta
                    cout << "- Placa: " << autoPermitido.getPlaca()
                         << ", Marca: " << autoPermitido.getMarca()
                         << ", Color: " << autoPermitido.getColor()
                         << ", Estado: " << autoPermitido.getEstado()
                         << ", Tarjeta: " << tarjeta << '\n'; // Imprimir el número de la tarjeta
                }
            }
            pausar();
            break;
        }
        case 8:
        { // Guardar lista de autos permitidos a archivo
            parqueadero.guardarAutosPermitidos(rutaAutosPermitidos);
            cout << "\nLista de autos permitidos guardada.\n";
            pausar();
            break;
        }
        case 9:
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
                         << ", Cedula: " << propietario.getCedula()
                         << ", Correo: " << propietario.getCorreo()
                         << ", Es discapacitado: " << (propietario.getEsDiscapacitado() ? "Si" : "No") << '\n';

                    for (const auto &autoAsociado : propietario.getAutos())
                    {
                        std::string tarjeta;
                        try
                        {
                            tarjeta = parqueadero.getTarjetasParqueo().at(autoAsociado.getPlaca());
                        }
                        catch (const std::out_of_range &)
                        {
                            tarjeta = "No asignada"; // Si no se encuentra la tarjeta, mostramos "No asignada"
                        }

                        cout << "  - Auto: Placa: " << autoAsociado.getPlaca()
                             << ", Marca: " << autoAsociado.getMarca()
                             << ", Color: " << autoAsociado.getColor()
                             << ", Tarjeta: " << tarjeta << '\n';
                    }
                }
            }
            pausar();
            break;
        }
        case 10:
        {
            parqueadero.guardarPropietarios(rutaPropietarios);
            cout << "\nLista de propietarios guardada.\n";
            pausar();
            break;
        }
        case 11: // Eliminar propietario
        {
            string cedula;
            cout << "\nIngrese la cedula del propietario a eliminar: ";
            cin >> cedula;

            parqueadero.eliminarPropietario(cedula);
            pausar();
            break;
        }
        case 12:
        {
            bool salirHistorial = false; // Variable para controlar el ciclo del submenú
            while (!salirHistorial)
            {
                vector<string> opcionesHistorial = {
                    "Mostrar historial general por fecha",
                    "Mostrar historial de un auto por fecha",
                    "Regresar al menu principal"};
                int opcionHistorial = menu.mostrarMenu("===== MENU HISTORIAL =====", opcionesHistorial);
                system("cls");
                switch (opcionHistorial + 1)
                {
                case 1:
                {
                    std::string fecha = validar.ingresarFecha("Ingrese la fecha (YYYY-MM-DD): ");
                    cout << endl;
                    historial.mostrarHistorialPorFecha(fecha);
                    pausar();
                    break;
                }
                case 2:
                {
                    std::string fecha = validar.ingresarFecha("Ingrese la fecha (YYYY-MM-DD): ");
                    cout << endl;
                    std::string placa = validar.ingresarPlaca("Ingrese la placa del auto (solo letras y numeros): ");
                    cout << endl;
                    historial.mostrarHistorialPorPlacaYFecha(placa, fecha);
                    pausar();
                    break;
                }
                case 3:
                    salirHistorial = true; // Cambiar el valor para salir del ciclo
                    break;
                default:
                    cout << "\nOpción inválida.\n";
                    break;
                }
            }
            break;
        }
        case 13: // Mostrar estado en formato circular
        {
            std::cout << "\n===== ESTADO DEL PARQUEADERO (FORMATO CIRCULAR) =====\n";
            parqueadero.mostrarEstadoCircular();
            pausar(); // Método existente para pausar la ejecución
            break;
        }
        case 14:
        {
            cout << "\nSaliendo del programa...\n";
            return 0;
        }
        default:
            cout << "\nOpción inválida.\n";
            break;
        }
    }

    return 0;
}
