#ifndef PARQUEADERO_H
#define PARQUEADERO_H

#include "EspacioParqueadero.h"
#include <vector>
#include <string>
#include <memory> // Para std::unique_ptr

using namespace std;

class Parqueadero {
private:
    vector<unique_ptr<EspacioParqueadero>> espacios; // Espacios del parqueadero
    vector<string> autosPermitidos;                  // Placas de autos permitidos

public:
    Parqueadero(int totalEspacios);
    ~Parqueadero() = default;

    void estacionarAuto(Auto* autoEstacionado, Propietario* propietario, int espacioID);
    void retirarAuto(int espacioID);
    void mostrarEstado() const;

    void registrarAutoPermitido(const string& placa);
    void eliminarAutoPermitido(const string& placa);
    void cargarAutosPermitidos(const string& rutaArchivo);
    void guardarAutosPermitidos(const string& rutaArchivo);
};

#endif // PARQUEADERO_H
