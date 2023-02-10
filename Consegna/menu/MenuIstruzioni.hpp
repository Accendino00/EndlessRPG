/**
 * @file MenuIstruzioni.hpp
 * @author Jacopo Francesco Amoretti
 *         Petru Marcel Marincas
 * @date 2022
 * 
 * @brief 
 *  Classe di MenuIstruzioni. Gestisce il menu delle istruzioni.
 *  Mostra le istruzioni del gioco, attraverso 3 colonne.
 *  Descrive i comandi, l'obbiettivo e cosa fanno gli artefatti.
 *  Si può tornare al menu principale.
 */

#pragma once
#include "../generale/libs.hpp"

class MenuIstruzioni : public Menu {
public:
    MenuIstruzioni();
    void loopMenu();
    void printAll();
    void printIstruzioni();
};