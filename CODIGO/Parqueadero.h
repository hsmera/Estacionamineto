#ifndef PARQUEADERO_H
#define PARQUEADERO_H

#include <vector>
#include <string>
#include <memory>
#include "EspacioParqueadero.h"
#include "Auto.h"
#include "Propietario.h"
#include <unordered_map>

class Parqueadero
{
private:
    // Espacios del parqueadero
    std::vector<std::unique_ptr<EspacioParqueadero>> espacios;
    // Lista de autos permitidos (ahora contiene objetos Auto)
    std::vector<Auto> autosPermitidos;
    // Lista de propietarios
    std::vector<Propietario> propietarios;
    std::unordered_map<std::string, std::string> tarjetasParqueo;
    //vector<string> cargarAutosDesdeArchivo();

public:
    // Constructor
    explicit Parqueadero(int totalEspacios, const std::string &rutaPropietarios, const std::string &rutaAutosPermitidos);

    // Métodos principales
    void estacionarAuto(Auto *autoEstacionado, Propietario *propietario, const std::string &tarjeta, int espacioID);
    void retirarAuto(const std::string &placa);

    // Mostrar estado del parqueadero
    void mostrarEstado() const;

    // Gestión de autos permitidos
    void registrarAutoPermitido(const Auto &autoPermitido);
    void eliminarAutoPermitido(const std::string &placa);

    // Carga y guardado de datos
    void cargarAutosPermitidos(const std::string &rutaArchivo);
    void guardarAutosPermitidos(const std::string &rutaArchivo);
    void guardarPropietarios(const std::string &rutaArchivo);
    void cargarPropietarios(const std::string &rutaArchivo);

    // Métodos adicionales
    void guardarAutos(const std::string &rutaArchivo); // Guardar autos estacionados
    const std::vector<Auto> &getAutosPermitidos() const;
    const std::vector<Propietario> &getPropietarios() const;
    void agregarPropietario(const Propietario &nuevoPropietario);
    void eliminarPropietario(const std::string &cedula);
    void cargarTarjetas(const std::string &rutaArchivo);
    void guardarTarjetas(const std::string &rutaArchivo);
    std::string generarTarjetaParqueo();
    std::unordered_map<std::string, std::string>& getTarjetasParqueo();
    void actualizarEstadoAuto(const std::string &placa, const std::string &estado);
    void mostrarEstadoCircular() const;

};

#endif // PARQUEADERO_H
