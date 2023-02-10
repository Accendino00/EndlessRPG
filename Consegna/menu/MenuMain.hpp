/**
 * @file MenuMain.hpp
 * @author Jacopo Francesco Amoretti
 * @date 2022
 * 
 * @brief 
 *  Classe di MenuMain. Gestisce il menu principale.
 *  Da questo menu si può:
 *   - Iniziare una nuova partita
 *   - Visualizzare i punteggi migliori
 *   - Modificare le impostazioni
 *   - Uscire dal gioco
 *  
 *  In alto è mostrato il nome del gioco.
 */

#pragma once
#include "../generale/libs.hpp"

class MenuMain : public Menu {
public:
    MenuMain();

    void loopMenu();
    void printAll();
    void printTitle();
};