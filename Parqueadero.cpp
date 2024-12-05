#include "Parqueadero.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <nlohmann/json.hpp> // Biblioteca JSON externa, instalar con: `nlohmann/json`

using namespace std;
using json = nlohmann::json;

Parqueadero::Parqueadero(int totalEspacios) {
    for (int i = 1; i <= totalEspacios; ++i) {
        espacios.push_back(make_unique<EspacioParqueadero>(i));
    }
}

void Parqueadero::estacionarAuto(Auto* autoEstacionado, Propietario* propietario, int espacioID) {
    if (espacioID < 1 || espacioID > espacios.size()) {
        cerr << "Espacio inválido.\n";
        return;
    }

    auto& espacio = espacios[espacioID - 1];
    if (espacio->estaOcupado()) {
        cerr << "El espacio ya está ocupado.\n";
        return;
    }

    if (find(autosPermitidos.begin(), autosPermitidos.end(), autoEstacionado->getPlaca()) == autosPermitidos.end()) {
        cerr << "Auto no permitido\n";
        return;
    }

    espacio->ocuparEspacio(autoEstacionado, propietario);
    cout << "Auto estacionado en espacio " << espacioID << ".\n";
}

void Parqueadero::retirarAuto(int espacioID) {
    if (espacioID < 1 || espacioID > espacios.size()) {
        cerr << "Espacio inválido.\n";
        return;
    }

    auto& espacio = espacios[espacioID - 1];
    if (!espacio->estaOcupado()) {
        cerr << "El espacio ya está vacío.\n";
        return;
    }

    espacio->liberarEspacio();
    cout << "Auto retirado del espacio " << espacioID << ".\n";
}

void Parqueadero::mostrarEstado() const {
    for (const auto& espacio : espacios) {
        cout << espacio->obtenerEstado() << '\n';
    }
}

void Parqueadero::registrarAutoPermitido(const string& placa) {
    autosPermitidos.push_back(placa);
    cout << "Auto con placa " << placa << " registrado.\n";
}

void Parqueadero::eliminarAutoPermitido(const string& placa) {
    autosPermitidos.erase(remove(autosPermitidos.begin(), autosPermitidos.end(), placa), autosPermitidos.end());
    cout << "Auto con placa " << placa << " eliminado.\n";
}

void Parqueadero::cargarAutosPermitidos(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo.\n";
        return;
    }

    json datos;
    archivo >> datos;
    autosPermitidos = datos.get<vector<string>>();
    cout << "Autos permitidos cargados correctamente.\n";
}

void Parqueadero::guardarAutosPermitidos(const string& rutaArchivo) {
    ofstream archivo(rutaArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo para escritura.\n";
        return;
    }

    json datos = autosPermitidos;
    archivo << datos.dump(4); // Guardar con formato legible
    cout << "Autos permitidos guardados correctamente.\n";
}
