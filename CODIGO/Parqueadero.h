#ifndef PARQUEADERO_H
#define PARQUEADERO_H

#include <vector>
#include <string>
#include <memory>
#include "EspacioParqueadero.h"
#include "Auto.h"
#include "Propietario.h"

class Parqueadero {
private:
    // Espacios del parqueadero
    std::vector<std::unique_ptr<EspacioParqueadero>> espacios;

    // Lista de autos permitidos (ahora contiene objetos Auto)
    std::vector<Auto> autosPermitidos;


    // Lista de propietarios
    std::vector<Propietario> propietarios;
    

public:
    // Constructor
    explicit Parqueadero(int totalEspacios, const std::string& rutaPropietarios, const std::string& rutaAutosPermitidos);

    // Métodos principales
    void estacionarAuto(Auto* autoEstacionado, Propietario* propietario, int espacioID);
    void retirarAuto(int espacioID);

    // Mostrar estado del parqueadero
    void mostrarEstado() const;

    // Gestión de autos permitidos
    void registrarAutoPermitido(const Auto &autoPermitido);
    void eliminarAutoPermitido(const std::string& placa);

    // Carga y guardado de datos
    void cargarAutosPermitidos(const std::string& rutaArchivo);
    void guardarAutosPermitidos(const std::string& rutaArchivo);
    void guardarPropietarios(const std::string& rutaArchivo);
    void cargarPropietarios(const std::string& rutaArchivo);

    // Métodos adicionales
    void guardarAutos(const std::string& rutaArchivo); // Guardar autos estacionados
    const std::vector<Auto>& getAutosPermitidos() const;
    const std::vector<Propietario>& getPropietarios() const;
    void agregarPropietario(const Propietario &nuevoPropietario);
    void eliminarPropietario(const std::string &cedula);


};

#endif // PARQUEADERO_H
