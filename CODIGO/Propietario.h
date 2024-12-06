#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include <string>
#include "Auto.h"
#include <vector>

class Propietario {
private:
    std::string nombreCompleto;
    std::string cedula;
    std::string correo;
    bool esDiscapacitado;
    std::vector<Auto> autos;

public:
    Propietario();
    Propietario(const std::string& nombreCompleto, const std::string& cedula, const std::string& correo, bool esDiscapacitado);

    // Métodos para gestionar los autos
    void agregarAuto(const Auto &autoNuevo);
    const std::vector<Auto>& getAutos() const;

    std::string getNombreCompleto() const;
    std::string getCedula() const;
    std::string getCorreo() const;
    bool getEsDiscapacitado() const;

    void setNombreCompleto(const std::string& nombreCompleto);
    void setCedula(const std::string& cedula);
    void setCorreo(const std::string& correo);
    void setEsDiscapacitado(bool esDiscapacitado);

    ~Propietario();
};

#endif // PROPIETARIO_H
