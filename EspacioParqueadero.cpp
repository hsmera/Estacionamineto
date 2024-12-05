#include "EspacioParqueadero.h"

using namespace std;

EspacioParqueadero::EspacioParqueadero(int id)
    : id(id), ocupado(false), autoEstacionado(nullptr), propietario(nullptr) {}

EspacioParqueadero::~EspacioParqueadero() {
    liberarEspacio(); // Liberar memoria si hay un auto y propietario asignados
}

void EspacioParqueadero::ocuparEspacio(Auto* autoEstacionado, Propietario* propietario) {
    this->autoEstacionado = autoEstacionado;
    this->propietario = propietario;
    ocupado = true;
}

void EspacioParqueadero::liberarEspacio() {
    delete autoEstacionado; // Eliminar el auto asignado
    delete propietario;     // Eliminar el propietario asignado
    autoEstacionado = nullptr;
    propietario = nullptr;
    ocupado = false;
}

std::string EspacioParqueadero::obtenerEstado() const {
    if (ocupado) {
        return "Espacio " + to_string(id) + " ocupado por auto con placa " + 
               autoEstacionado->getPlaca();
    } else {
        return "Espacio " + to_string(id) + " está libre.";
    }
}
