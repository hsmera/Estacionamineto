#ifndef AUTO_H
#define AUTO_H

#include <string>

using namespace std;

class Auto
{
private:
    string placa;
    string marca;
    string color;

public:
    // Constructor por defecto
    Auto();

    // Constructor parametrizado
    Auto(const string &placa, const string &marca, const string &color);

    // Sobrecargar el operador == para comparar Autos por placa
    bool operator==(const string &otherPlaca) const
    {
        return placa == otherPlaca;
    }

    // Métodos getters
    string getPlaca() const;
    string getMarca() const;
    string getColor() const;

    // Métodos setters
    void setPlaca(const string &placa);
    void setMarca(const string &marca);
    void setColor(const string &color);

    // Destructor
    ~Auto();
};

#endif
