#include "Propietario.h"
#include <vector>

using namespace std;
Propietario::Propietario() : nombreCompleto(""), cedula(""), correo(""), esDiscapacitado(false) {}

Propietario::Propietario(const string& nombreCompleto, const string& cedula, const string& correo, bool esDiscapacitado)
    : nombreCompleto(nombreCompleto), cedula(cedula), correo(correo), esDiscapacitado(esDiscapacitado) {}

string Propietario::getNombreCompleto() const {
    return nombreCompleto;
}
string Propietario::getCedula() const {
    return cedula;
}
string Propietario::getCorreo() const {
    return correo;
}
bool Propietario::getEsDiscapacitado() const {
    return esDiscapacitado;
}

void Propietario::setNombreCompleto(const string& nombreCompleto) {
    this->nombreCompleto = nombreCompleto;
}
void Propietario::setCedula(const string& cedula) {
    this->cedula = cedula;
}
void Propietario::setCorreo(const string& correo) {
    this->correo = correo;
}
void Propietario::setEsDiscapacitado(bool esDiscapacitado) {
    this->esDiscapacitado = esDiscapacitado;
}

void Propietario::agregarAuto(const Auto &autoNuevo) {
    autos.push_back(autoNuevo);
}

const vector<Auto>& Propietario::getAutos() const {
    return autos;
}

// Destructor
Propietario::~Propietario() {}
