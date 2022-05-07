#include "../generale/libs.hpp"


MenuOptions::MenuOptions() {
    selezione = 0;
}

void MenuOptions::loopMenu() {
    // Loop generale del gioco
    bool LeaveMenu = false;
    do {

        // SCHERMATA INIZIALE
        // Il menu principale
        gd->getInput();
        this->manageInput();

        erase();

        if(gd->checkInput(10)) {
            switch(this->getSelezione()) {
                case 0:                    
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    LeaveMenu = true;
                    break;
            }
        }

        this->print();

        refresh();
    } while (! LeaveMenu);

}

void MenuOptions::manageInput() {
    int i = 0;
    int numOfOptions = 5;
    while(i < gd->getNumOfPressedKeys() && gd->getKey(i) != ERR) {
        switch(gd->getKey(i)) {
            case KEY_UP:
            case L'w':
            case L'W':
                selezione = (selezione -1 +numOfOptions) % numOfOptions;
                break;
            case KEY_DOWN:
            case L's':
            case L'S':
                selezione = (selezione + 1) % numOfOptions;
                break;
        }
        i++;
    }
}

int MenuOptions::getSelezione() {
    return this->selezione;
}

void MenuOptions::print() {


    // Stampa delle opzioni
    if (this->getSelezione() == 0) {
        attron(A_BOLD | A_REVERSE);
    }
    mvprintw(5,5,"Show FPS");
    if (this->getSelezione() == 0) {
        attroff(A_BOLD | A_REVERSE);
    }
    // Stampa delle opzioni
    if (this->getSelezione() == 1) {
        attron(A_BOLD | A_REVERSE);
    }
    mvprintw(7,5,"Qualcosa 1");
    if (this->getSelezione() == 1) {
        attroff(A_BOLD | A_REVERSE);
    }
    // Stampa delle opzioni
    if (this->getSelezione() == 2) {
        attron(A_BOLD | A_REVERSE);
    }
    mvprintw(9,5,"Qualcosa 2");
    if (this->getSelezione() == 2) {
        attroff(A_BOLD | A_REVERSE);
    }
    // Stampa delle opzioni
    if (this->getSelezione() == 3) {
        attron(A_BOLD | A_REVERSE);
    }
    mvprintw(11,5,"Qualcosa 3");
    if (this->getSelezione() == 3) {
        attroff(A_BOLD | A_REVERSE);
    }
    // Stampa delle opzioni
    if (this->getSelezione() == 4) {
        attron(A_BOLD | A_REVERSE);
    }
    mvprintw(13,5,"Indietro");
    if (this->getSelezione() == 4) {
        attroff(A_BOLD | A_REVERSE);
    }
}