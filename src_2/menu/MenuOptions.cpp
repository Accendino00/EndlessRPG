#include "../generale/libs.hpp"


MenuOptions::MenuOptions() {
    selezione = 0;
}

void MenuOptions::loopMenu() {
    // Loop generale del gioco
    bool LeaveMenu = false;
    MenuCrediti * m_crediti;
    do {
        gd->frameStart();

        // SCHERMATA INIZIALE
        // Il menu principale
        gd->getInput();
        this->manageInput();

        erase();

        if(gd->checkInput(10)) {
            switch(this->getSelezione()) {
                case 3:
                    gd->salvaImpostazioni();
                    break;
                case 4:
                    m_crediti = new MenuCrediti();
                    m_crediti->loopMenu();
                    delete m_crediti;
                    break;
                case 5:
                    LeaveMenu = true;
                    break;
            }
        }

        this->print();

        gd->frameFinish();
        refresh();
    } while (! LeaveMenu);

}

void MenuOptions::manageInput() {
    int i = 0;
    int numOfOptions = 6;
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
            case KEY_LEFT:
            case L'A':
            case L'a':
                switch(selezione) {
                    case 0:
                        gd->cycleDifficulty(false);
                        break;
                    case 1:
                        gd->cycleFPSCap(false);
                        break;
                    case 2:
                        gd->cycleShowPerformance(false);
                        break;
                }
                break;
            case 10:
            case KEY_RIGHT:
            case L'D':
            case L'd':
                switch(selezione) {
                    case 0:
                        gd->cycleDifficulty(true);
                        break;
                    case 1:
                        gd->cycleFPSCap(true);
                        break;
                    case 2:
                        gd->cycleShowPerformance(true);
                        break;
                }
                break;
        }
        i++;
    }
}

int MenuOptions::getSelezione() {
    return this->selezione;
}

void MenuOptions::print() {

    int centerY = gd->getTerminalY()/2;
    int centerX = gd->getTerminalX()/2;

    attron(COLOR_PAIR(MENU_NORMAL));

    // Stampa delle opzioni
    if (this->getSelezione() == 0) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+2,centerX-2,"Difficoltà:\t< %s \t>",gd->getDifficulty());
    if (this->getSelezione() == 0) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }

    // Stampa delle opzioni
    if (this->getSelezione() == 1) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+4,centerX-2,"FPS cap:\t\t< %d \t>", gd->getFPSCap());
    if (this->getSelezione() == 1) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }

    // Stampa delle opzioni
    if (this->getSelezione() == 2) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+6,centerX-2,"Mostra FPS:\t< %s\t>", gd->getShowPerformance());
    if (this->getSelezione() == 2) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }

    // Stampa delle opzioni
    if (this->getSelezione() == 3) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+8,centerX-2,"%s", gd->getImpostazioniSalvate());
    if (this->getSelezione() == 3) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }

    // Stampa delle opzioni
    if (this->getSelezione() == 4) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+10,centerX-2,"Crediti");
    if (this->getSelezione() == 4) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }    
    
    // Stampa delle opzioni
    if (this->getSelezione() == 5) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+12,centerX-2,"Indietro");
    if (this->getSelezione() == 5) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }

    attroff(COLOR_PAIR(MENU_NORMAL));
}