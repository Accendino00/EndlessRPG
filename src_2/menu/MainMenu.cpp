#include "libs.hpp"
#include "MainMenu.hpp"

MainMenu::MainMenu() {
    selezione = 0;
}

void MainMenu::manageInput(int * inputs, int num_inputs) {
    int i = 0;
    while(i < num_inputs && inputs[i] != ERR) {
        switch(inputs[i]) {
            case KEY_UP:
            case L'w':
            case L'W':
                selezione = (selezione -1 +3) % 3;
                break;
            case KEY_DOWN:
            case L's':
            case L'S':
                selezione = (selezione + 1) % 3;
                break;
        }
    }
}

int MainMenu::getSelezione() {
    return this->selezione;
}

void MainMenu::print() {


    // Stampa delle opzioni
    if (this->getSelezione() == 0) {
        attron(A_BOLD | A_REVERSE);
    }
}