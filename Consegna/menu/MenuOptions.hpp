/**
 * @file MenuOptions.hpp
 * @author Jacopo Francesco Amoretti
 * @date 2022
 * 
 * @brief 
 *  Classe di MenuOptions. Gestisce il menu delle opzioni.
 * 
 *  Si possono cambiare:
 *   - La difficoltà
 *   - L'FPS cap (ovvero il massimo numero di FPS)
 *   - Se mostrare gli FPS o no
 * 
 *  Posso decidere di salvare le impostazioni, che farà 
 *  salvare le impostazioni su file.
 * 
 *  Infine, posso uscire da questo menu.
 */

#pragma once
#include "../generale/libs.hpp"

class MenuOptions : public Menu {
public:
    MenuOptions();
    void loopMenu();
    void printAll();
};