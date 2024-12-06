#ifndef REGISTRO_HISTORIAL_H
#define REGISTRO_HISTORIAL_H

#include <string>
#include <vector>

class RegistroHistorial {
private:
    std::string rutaArchivo;

    std::string obtenerFechaHoraActual() const; // Método para obtener la fecha y hora actual

public:
    RegistroHistorial(const std::string& rutaArchivo);

    void registrarEvento(const std::string& placa, const std::string& accion);
    void mostrarHistorial() const;
};

#endif // REGISTRO_HISTORIAL_H
