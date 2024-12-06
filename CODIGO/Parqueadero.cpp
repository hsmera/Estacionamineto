#include "Parqueadero.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>  // Asegúrate de incluir esta cabecera
#include <limits>

using namespace std;

// Constructor
Parqueadero::Parqueadero(int totalEspacios, const std::string &rutaPropietarios, const std::string &rutaAutosPermitidos)
{
    for (int i = 1; i <= totalEspacios; ++i)
    {
        espacios.push_back(std::make_unique<EspacioParqueadero>(i));
    }

    cargarPropietarios(rutaPropietarios);
    cargarAutosPermitidos(rutaAutosPermitidos);
}

// Método para estacionar un auto
void Parqueadero::estacionarAuto(Auto *autoEstacionado, Propietario *propietario, int espacioID)
{
    if (espacioID < 1 || espacioID > static_cast<int>(espacios.size()))
    {
        cerr << "Espacio invalido.\n";
        return;
    }

    auto &espacio = espacios[espacioID - 1];
    if (espacio->estaOcupado())
    {
        cerr << "El espacio ya está ocupado.\n";
        return;
    }

    if (find(autosPermitidos.begin(), autosPermitidos.end(), autoEstacionado->getPlaca()) == autosPermitidos.end())
    {
        cerr << "Auto no permitido.\n";
        return;
    }

    espacio->ocuparEspacio(autoEstacionado, propietario);
    cout << "Auto estacionado en espacio " << espacioID << ".\n";
}

// Método para retirar un auto
void Parqueadero::retirarAuto(int espacioID)
{
    if (espacioID < 1 || espacioID > static_cast<int>(espacios.size()))
    {
        cerr << "Espacio invalido.\n";
        return;
    }

    auto &espacio = espacios[espacioID - 1];
    if (!espacio->estaOcupado())
    {
        cerr << "El espacio ya esta vacio.\n";
        return;
    }

    espacio->liberarEspacio();
    cout << "Auto retirado del espacio " << espacioID << ".\n";
}

// Mostrar el estado de los espacios del parqueadero
void Parqueadero::mostrarEstado() const
{
    for (const auto &espacio : espacios)
    {
        cout << espacio->obtenerEstado() << '\n';
    }
}

// Registrar un auto permitido
void Parqueadero::registrarAutoPermitido(const Auto &autoPermitido)
{
    // Verificar si el auto ya está registrado por su placa
    auto it = std::find_if(autosPermitidos.begin(), autosPermitidos.end(),
                           [&autoPermitido](const Auto &a) { return a.getPlaca() == autoPermitido.getPlaca(); });

    if (it == autosPermitidos.end())
    {
        autosPermitidos.push_back(autoPermitido);
        cout << "Auto con placa " << autoPermitido.getPlaca() << " registrado.\n";
    }
    else
    {
        cerr << "El auto con placa " << autoPermitido.getPlaca() << " ya esta registrado.\n";
    }
}


// Eliminar un auto permitido
void Parqueadero::eliminarAutoPermitido(const std::string &placa)
{
    auto it = std::find_if(autosPermitidos.begin(), autosPermitidos.end(),
                           [&placa](const Auto &a) { return a.getPlaca() == placa; });

    if (it != autosPermitidos.end())
    {
        autosPermitidos.erase(it);
        cout << "Auto con placa " << placa << " eliminado correctamente.\n";
    }
    else
    {
        cerr << "El auto con placa " << placa << " no esta en la lista de permitidos.\n";
    }
}


// Guardar lista de autos permitidos en archivo
void Parqueadero::guardarAutosPermitidos(const std::string &rutaArchivo)
{
    try
    {
        std::ofstream archivo(rutaArchivo);
        if (!archivo)
            throw std::runtime_error("No se pudo abrir el archivo para escritura.");

        for (const auto &autoPermitido : autosPermitidos)
        {
            archivo << autoPermitido.getPlaca() << " "
                    << autoPermitido.getMarca() << " "
                    << autoPermitido.getColor() << '\n';
        }

        cout << "Autos permitidos guardados correctamente en " << rutaArchivo << ".\n";
    }
    catch (const std::exception &e)
    {
        cerr << "Error al guardar autos permitidos: " << e.what() << '\n';
    }
}

// Guardar información de propietarios en archivo
void Parqueadero::guardarPropietarios(const std::string& rutaArchivo) {
    std::ofstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para guardar propietarios: " << rutaArchivo << std::endl;
        return;
    }

    for (const auto& propietario : propietarios) {
        // Escribir datos básicos del propietario
        archivo << propietario.getNombreCompleto() << ","
                << propietario.getCedula() << ","
                << propietario.getCorreo() << ","
                << (propietario.getEsDiscapacitado() ? "1" : "0") << '\n';

        // Escribir autos asociados
        for (const auto& autoAsociado : propietario.getAutos()) {
            archivo << "  - " << autoAsociado.getPlaca() << " "
                    << autoAsociado.getMarca() << " "
                    << autoAsociado.getColor() << '\n';
        }
    }

    archivo.close();
    std::cout << "Propietarios guardados correctamente en " << rutaArchivo << "." << std::endl;
}


void Parqueadero::eliminarPropietario(const std::string &cedula)
{
    // Buscar al propietario en la lista
    auto it = std::find_if(propietarios.begin(), propietarios.end(),
                           [&cedula](const Propietario &p) { return p.getCedula() == cedula; });

    if (it != propietarios.end())
    {
        // Obtener los autos asociados al propietario
        const auto &autosAsociados = it->getAutos();

        // Eliminar los autos asociados del archivo y la lista de autos permitidos
        for (const auto &autoAsociado : autosAsociados)
        {
            auto itAuto = std::find_if(autosPermitidos.begin(), autosPermitidos.end(),
                                       [&autoAsociado](const Auto &a) { return a.getPlaca() == autoAsociado.getPlaca(); });

            if (itAuto != autosPermitidos.end())
            {
                autosPermitidos.erase(itAuto);
            }
        }

        // Eliminar el propietario de la lista
        propietarios.erase(it);
        cout << "Propietario con cedula " << cedula << " eliminado correctamente.\n";

        // Guardar los cambios en los archivos
        guardarPropietarios("propietarios.txt");
        guardarAutosPermitidos("autos.txt");
    }
    else
    {
        cerr << "No se encontro un propietario con la cedula " << cedula << ".\n";
    }
}



// Cargar lista de autos permitidos desde archivo
void Parqueadero::cargarAutosPermitidos(const std::string &rutaArchivo)
{
    try
    {
        std::ifstream archivo(rutaArchivo);
        if (!archivo)
            throw std::runtime_error("No se pudo abrir el archivo de autos permitidos.");

        std::string placa, marca, color;
        while (archivo >> placa >> marca >> color)
        {
            autosPermitidos.emplace_back(placa, marca, color);
        }

        cout << "Autos permitidos cargados correctamente desde " << rutaArchivo << ".\n";
    }
    catch (const std::exception &e)
    {
        cerr << "Error al cargar autos permitidos: " << e.what() << '\n';
    }
}


// Cargar información de propietarios desde archivo
void Parqueadero::cargarPropietarios(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo de propietarios: " << rutaArchivo << std::endl;
        return;
    }

    propietarios.clear();
    std::string linea;

    while (getline(archivo, linea)) {
        // Separar la primera línea del propietario
        std::istringstream streamPropietario(linea);
        std::string nombreCompleto, cedula, correo;
        bool esDiscapacitado;

        getline(streamPropietario, nombreCompleto, ',');
        getline(streamPropietario, cedula, ',');
        getline(streamPropietario, correo, ',');
        streamPropietario >> esDiscapacitado;

        Propietario propietario(nombreCompleto, cedula, correo, esDiscapacitado);

        // Leer autos asociados hasta encontrar la siguiente línea vacía o un nuevo propietario
        while (getline(archivo, linea) && !linea.empty()) {
            if (linea[0] == ' ') { // Línea de auto (inicia con espacio para diferenciarla)
                std::istringstream streamAuto(linea.substr(2)); // Saltar el espacio inicial y guion
                std::string placa, marca, color;
                streamAuto >> placa >> marca >> color;

                // Validar y corregir si el guion está incluido en la placa
                if (placa == "-") {
                    placa = marca;
                    marca = color;
                    color = "";
                    streamAuto >> color;
                }

                Auto autoAsociado(placa, marca, color);
                propietario.agregarAuto(autoAsociado);
            } else {
                // Si es otra línea de propietario, volver al inicio del loop principal
                archivo.seekg(-static_cast<int>(linea.size()) - 1, std::ios::cur); // Retrocede la línea
                break;
            }
        }

        // Agregar propietario a la lista
        propietarios.push_back(propietario);
    }

    archivo.close();
    std::cout << "Propietarios cargados correctamente desde " << rutaArchivo << "." << std::endl;
}


const std::vector<Auto>& Parqueadero::getAutosPermitidos() const
{
    return autosPermitidos;
}

const std::vector<Propietario>& Parqueadero::getPropietarios() const {
    return propietarios;
}

void Parqueadero::agregarPropietario(const Propietario &nuevoPropietario) {
    propietarios.push_back(nuevoPropietario);
}

// g++ main.cpp EspacioParqueadero.cpp Parqueadero.cpp Propietario.cpp Auto.cpp Menu.cpp -o main.exe