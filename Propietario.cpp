#include "Propietario.h"

Propietario::Propietario() : nombreCompleto(""), cedula(""), celular(""), esDiscapacitado(false) {}

Propietario::Propietario(const string& nombreCompleto, const string& cedula, const string& celular, bool esDiscapacitado)
    : nombreCompleto(nombreCompleto), cedula(cedula), celular(celular), esDiscapacitado(esDiscapacitado) {}

string Propietario::getNombreCompleto() const {
    return nombreCompleto;
}
string Propietario::getCedula() const {
    return cedula;
}
string Propietario::getCelular() const {
    return celular;
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
void Propietario::setCelular(const string& celular) {
    this->celular = celular;
}
void Propietario::setEsDiscapacitado(bool esDiscapacitado) {
    this->esDiscapacitado = esDiscapacitado;
}

// Destructor
Propietario::~Propietario() {}
