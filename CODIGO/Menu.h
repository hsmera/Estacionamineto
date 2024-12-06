#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>

class Menu {
public:
    /**
     * @brief 
     * @param titulo 
     * @param opciones 
     * @return 
     */
    int mostrarMenu(const std::string& titulo, const std::vector<std::string>& opciones);
};

#endif 
