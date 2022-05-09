#include "../generale/libs.hpp"

MenuMain::MenuMain() {
    selezione = 0;
}

void MenuMain::loopMenu() {
    // Loop generale del gioco
    MenuOptions * m_options;
    Gioco * gioco;
    do {
        gd->frameStart();

        // SCHERMATA INIZIALE
        // Il menu principale
        gd->getInput();
        this->manageInput();

        erase();


        if(gd->checkInput(10)) {
            switch(this->getSelezione()) {
                case 0:
                    // Play
                    gioco = new Gioco();
                    gioco->gameLoop();
                    delete gioco;
                    break;
                case 1:
                    // Score
                    break;
                case 2:    
                    m_options = new MenuOptions();
                    m_options->loopMenu();
                    delete m_options;
                    break;
                case 3:
                    gd->setCloseGame(true);
                    break;
            }
        }

        this->print();

        gd->frameFinish();
        refresh();
    } while (! (gd->getCloseGame()) );

}

void MenuMain::manageInput() {
    int i = 0;
    int numOfOptions = 4;
    while(i < gd->getNumOfPressedKeys()) {
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

int MenuMain::getSelezione() {
    return this->selezione;
}

void MenuMain::print() {

    int centerY = gd->getTerminalY()/2;
    int centerX = gd->getTerminalX()/2;
    attron(COLOR_PAIR(MAIN_TITLE));
    mvprintw(centerY-13,centerX-15, "      ,╓▄▄▄▄▄▄▄▄#╗╗╤╤╗╗▄      ");
    mvprintw(centerY-12,centerX-15, "  .▄Φ╨╨╙p╤═╨╜*\"░7ñm╝bw  ▀▄    ");
    mvprintw(centerY-11,centerX-15, "  ▄⌐  `   ì   ╙,╓▄▄▄⌡┘─  ╙▄   ");
    mvprintw(centerY-10,centerX-15, "╓▓╫*^'▀▀▀▀▓#  ▓▄Φ▀▓▀▀Mñ▄▄▄╩▀▄ ");
    mvprintw(centerY-9, centerX-15, "▓HH╙║▀ΦM ▄▀   ,p, `╙╙╙║▄▌,║W∩▓");
    mvprintw(centerY-8, centerX-15, "\"▓╙╓█▄¿*╙▀▄╖'╨╩║▄▄▄Φ▀▌▐▄▓└╜╥▄▀");
    mvprintw(centerY-7, centerX-15, " ▐▌║█▓▐█▀▀▌▀╣▀╙▐▓▄▄▓▓▌▄▀  ╓▀└ ");
    mvprintw(centerY-6, centerX-15, " :▌╙██████████▀▀╙▓ ╓▄▀`  ╓▀   ");
    mvprintw(centerY-5, centerX-15, " ║M ╙▀▓▄█▄▓▄▄▓▄▄#▀▀Å╦Xφ▄▀└    ");
    mvprintw(centerY-4, centerX-15, " ╫ └,*═«-\"\"\"\"╓≤≡╧╨▄▄Φ▀`       ");
    mvprintw(centerY-3, centerX-15, " ╙▄,  `````╓▄▄▄#▀╙            ");
    mvprintw(centerY-2, centerX-15, "   `╙▀▀╙╙╙└`                  ");
    attroff(COLOR_PAIR(MAIN_TITLE));

    attron(COLOR_PAIR(MENU_NORMAL));

    // Stampa delle opzioni
    if (this->getSelezione() == 0) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+2,centerX-2,"Gioca");
    if (this->getSelezione() == 0) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }

    // Stampa delle opzioni
    if (this->getSelezione() == 1) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+4,centerX-2,"Punteggi");
    if (this->getSelezione() == 1) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }

    // Stampa delle opzioni
    if (this->getSelezione() == 2) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+6,centerX-2,"Opzioni");
    if (this->getSelezione() == 2) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }

    // Stampa delle opzioni
    if (this->getSelezione() == 3) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    mvprintw(centerY+8,centerX-2,"Esci");
    if (this->getSelezione() == 3) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
        attron(COLOR_PAIR(MENU_NORMAL));
    }

    attroff(COLOR_PAIR(MENU_NORMAL));
}