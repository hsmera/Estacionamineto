#ifndef ESPACIO_PARQUEADERO_H
#define ESPACIO_PARQUEADERO_H

#include "Auto.h"
#include "Propietario.h"
#include <string>

using namespace std;

class EspacioParqueadero {
private:
    int id;                      // Identificador del espacio
    bool ocupado;                // Estado del espacio
    Auto* autoEstacionado;       // Puntero al auto estacionado
    Propietario* propietario;    // Puntero al propietario del auto

public:
    EspacioParqueadero(int id);
    ~EspacioParqueadero();

    void ocuparEspacio(Auto* autoEstacionado, Propietario* propietario);
    void liberarEspacio();
    string obtenerEstado() const;

    int getId() const { return id; }
    bool estaOcupado() const { return ocupado; }
};

#endif // ESPACIO_PARQUEADERO_H
