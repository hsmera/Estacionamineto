#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>

using namespace std; 

class Menu {
public:
    /**
     * @brief 
     * @param titulo 
     * @param opciones 
     * @return 
     */
    int mostrarMenu(const string& titulo, const vector<string>& opciones);
};

#endif 
