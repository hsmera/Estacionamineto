#include "EspacioParqueadero.h"
#include <sstream>

EspacioParqueadero::EspacioParqueadero(int id) 
    : id(id), ocupado(false), autoEstacionado(nullptr), propietario(nullptr) {}

EspacioParqueadero::~EspacioParqueadero() = default;

void EspacioParqueadero::ocuparEspacio(Auto* autoEstacionado, Propietario* propietario) {
    this->autoEstacionado = std::unique_ptr<Auto>(autoEstacionado);
    this->propietario = std::unique_ptr<Propietario>(propietario);
    ocupado = true;
}

void EspacioParqueadero::liberarEspacio() {
    autoEstacionado.reset();
    propietario.reset();
    ocupado = false;
}

std::string EspacioParqueadero::obtenerEstado() const {
    std::ostringstream estado;
    if (ocupado) {
        estado << "Espacio " << id << ": Ocupado por auto con placa " << autoEstacionado->getPlaca();
    } else {
        estado << "Espacio " << id << ": Vacio";
    }
    return estado.str();
}

const Auto* EspacioParqueadero::getAuto() const {
    return autoEstacionado.get(); // Retorna un puntero al auto estacionado
}
