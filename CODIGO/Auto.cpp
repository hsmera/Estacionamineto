#include "Auto.h"

// Constructor por defecto
Auto::Auto() : placa(""), marca(""), color(""),estado(""){}

// Constructor parametrizado
Auto::Auto(const string& placa, const string& marca, const string& color, const string& estado)
    : placa(placa), marca(marca), color(color) ,estado("No se encuentra en el parqueadero"){}

// Getters
string Auto::getPlaca() const {
    return placa;
}

string Auto::getMarca() const {
    return marca;
}

string Auto::getColor() const {
    return color;
}

string Auto::getEstado() const { 
    return estado; 
}

// Setters
void Auto::setPlaca(const string& placa) {
    this->placa = placa;
}

void Auto::setMarca(const string& marca) {
    this->marca = marca;
}

void Auto::setColor(const string& color) {
    this->color = color;
}

void Auto::setEstado(const std::string &nuevoEstado) {
    estado = nuevoEstado; 
}

// Destructor
Auto::~Auto() {}
