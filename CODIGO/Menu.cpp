#include "Menu.h"
#include <conio.h> 
#include <cstdlib> 

using namespace std;

int Menu::mostrarMenu(const string& titulo, const vector<string>& opciones) {
    int opcionSeleccionada = 0;
    const int numOpciones = opciones.size();

    while (true) {
        system("cls");
        cout << titulo << "\n\n";

        for (int i = 0; i < numOpciones; i++) {
            if (i == opcionSeleccionada) {
                cout << " > " << opciones[i] << " <\n"; 
            } else {
                cout << "   " << opciones[i] << '\n';
            }
        }

        int tecla = getch();

        if (tecla == 224) { 
            tecla = getch();
            if (tecla == 72) {
                opcionSeleccionada = (opcionSeleccionada - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) { 
                opcionSeleccionada = (opcionSeleccionada + 1) % numOpciones;
            }
        } else if (tecla == 13) { 
            return opcionSeleccionada; 
        }
    }
}
