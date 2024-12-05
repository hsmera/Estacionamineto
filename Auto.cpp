#include "Auto.h"

// Constructor por defecto
Auto::Auto() : placa(""), marca(""), color("") {}

// Constructor parametrizado
Auto::Auto(const string& placa, const string& marca, const string& color)
    : placa(placa), marca(marca), color(color) {}

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

// Destructor
Auto::~Auto() {}
