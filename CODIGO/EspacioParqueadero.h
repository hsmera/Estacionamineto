#ifndef ESPACIO_PARQUEADERO_H
#define ESPACIO_PARQUEADERO_H

#include <string>
#include <memory>
#include "Auto.h"
#include "Propietario.h"

class EspacioParqueadero
{
private:
    int id;
    bool ocupado;
    std::unique_ptr<Auto> autoEstacionado;
    std::unique_ptr<Propietario> propietario;

public:
    explicit EspacioParqueadero(int id);
    ~EspacioParqueadero();

    void ocuparEspacio(Auto *autoEstacionado, Propietario *propietario);
    void liberarEspacio();
    std::string obtenerEstado() const;

    bool estaOcupado() const { return ocupado; }

    const Auto *getAuto() const; // Nuevo método para obtener un puntero al Auto
    int getId() const;
    const Propietario *getPropietario() const;
};

#endif // ESPACIO_PARQUEADERO_H
