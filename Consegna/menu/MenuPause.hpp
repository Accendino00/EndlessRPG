/**
 * @file MenuPause.hpp
 * @author Jacopo Francesco Amoretti
 * @date 2022
 * 
 * @brief 
 *  Classe di MenuPause. Gestisce il menu di pausa.
 *  Da questo menu si può:
 *   - Continuare il gioco
 *   - Modificare la difficoltà
 *   - Vedere le istruzioni
 *   - Uscire dal gioco
 */
#pragma once
#include "../generale/libs.hpp"

class MenuPause : public Menu {
public:
    MenuPause();
    bool loopMenu();
    void printAll();
};