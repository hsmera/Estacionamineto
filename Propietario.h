#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include <string>

using namespace std;

class Propietario {
private:
    string nombreCompleto;
    string cedula;
    string celular;
    bool esDiscapacitado;

public:
    // Constructor por defecto
    Propietario();

    // Constructor parametrizado
    Propietario(const string& nombreCompleto, const string& cedula, const string& celular, bool esDiscapacitado);

    // Métodos getters
    string getNombreCompleto() const;
    string getCedula() const;
    string getCelular() const;
    bool getEsDiscapacitado() const;

    // Métodos setters
    void setNombreCompleto(const string& nombreCompleto);
    void setCedula(const string& cedula);
    void setCelular(const string& celular);
    void setEsDiscapacitado(bool esDiscapacitado);

    // Destructor
    ~Propietario();
};

#endif
