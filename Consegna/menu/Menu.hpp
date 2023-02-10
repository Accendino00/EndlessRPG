/**
 * @file Menu.hpp
 * @author Jacopo Francesco Amoretti
 * @date 2022
 * 
 * @brief 
 *  Classe di Menu. Tutti gli altri menu ereditano da questa.
 *  Gestisce le cose comuni a tutti i menu, ovvero come stampare
 *  le linee, come gestire l'input e come gestire la selezione.
 */

#pragma once
#include "../generale/libs.hpp"

class Menu {
private:
    short selezione;
    int numOfOptions;
    int lineOffset;

public:
    Menu(int selezione, int numOfOptions, int lineOffset);

    void manageInput();
    int getSelezione();

    void printLine(const char * text, int id);
};