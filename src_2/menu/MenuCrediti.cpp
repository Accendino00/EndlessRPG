#include "../generale/libs.hpp"

MenuCrediti::MenuCrediti() {}

void MenuCrediti::loopMenu() {
    bool esciDaCrediti = false;
    do {
        gd->frameStart();

        gd->getInput();

        erase();

        if(gd->checkInput(10)) {
            esciDaCrediti = true;
        }

        this->print();

        gd->frameFinish();
        refresh();
    } while (! (esciDaCrediti) );

}

void MenuCrediti::print() {
    int centerY = gd->getTerminalY()/2;
    int centerX = gd->getTerminalX()/2;

    attron(COLOR_PAIR(MENU_NORMAL));
    mvprintw(centerY+2,centerX-2,"Amoretti Jacopo Francesco");
    mvprintw(centerY+4,centerX-2,"Donati Davide");
    mvprintw(centerY+6,centerX-2,"Forciniti Giuseppe");
    mvprintw(centerY+8,centerX-2,"Marincas Petru Marcel");
    attroff(COLOR_PAIR(MENU_NORMAL));
        
        
    attron(COLOR_PAIR(MENU_HIGHLIGHT));
    mvprintw(centerY+10,centerX-2,"Esci");
    attroff(COLOR_PAIR(MENU_HIGHLIGHT));
}