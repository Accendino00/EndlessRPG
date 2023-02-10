#include "../generale/libs.hpp"

MenuIstruzioni::MenuIstruzioni():Menu(0,1,6) {}

void MenuIstruzioni::loopMenu() {
    bool esciDaIstruzioni = false;

    do {
        gd->frameStart();
        gd->getInput();
        erase();
        this->manageInput();
        int i = 0;
        while(i < gd->getNumOfPressedKeys()) {
            switch(gd->getKey(i)) {
            case 10:
                switch(this->getSelezione()) {
                    case 0:
                        esciDaIstruzioni = true;
                        break;
                }
                    break;
            }
            i++;
    }   

        // Stampa, fine del frame e refresh dello schermo
        this->printAll();
        gd->frameFinish();
        refresh();
    } while (!esciDaIstruzioni);
}    


void MenuIstruzioni::printAll(){
    printIstruzioni();
    printLine("Indietro", 0);
}

void MenuIstruzioni::printIstruzioni() {

    int centerX = gd->getTerminalX()/2;
    int topOffset = (gd->getTerminalY()/2) - 15;

    int leftColumnX = centerX-44;
    int centerColumnX = centerX-14;
    int rightColumnX = centerX+18;

    attron(COLOR_PAIR(MENU_HIGHLIGHT));
    mvprintw(topOffset +  0, leftColumnX,  " > Comandi:               ");
    attroff(COLOR_PAIR(MENU_HIGHLIGHT));

    attron(COLOR_PAIR(MENU_NORMAL));
    mvprintw(topOffset +  1, leftColumnX,  "                          ");
    mvprintw(topOffset +  2, leftColumnX,  "    W    P      ↑         ");
    mvprintw(topOffset +  3, leftColumnX,  "  A S D       ← ↓ →       ");
    mvprintw(topOffset +  4, leftColumnX,  "                          ");
    mvprintw(topOffset +  5, leftColumnX,  "       SPACEBAR           ");
    mvprintw(topOffset +  6, leftColumnX,  "                          ");
    mvprintw(topOffset +  7, leftColumnX,  "                          ");
    mvprintw(topOffset +  8, leftColumnX,  " W : Muoviti in alto      ");
    mvprintw(topOffset +  9, leftColumnX,  " A : Muoviti a sinistra   ");
    mvprintw(topOffset + 10, leftColumnX,  " S : Muoviti in basso     ");
    mvprintw(topOffset + 11, leftColumnX,  " D : Muoviti a destra     ");
    mvprintw(topOffset + 12, leftColumnX,  " _ : Dash                 ");
    mvprintw(topOffset + 13, leftColumnX,  "                          ");
    mvprintw(topOffset + 14, leftColumnX,  " P : Pausa                ");
    mvprintw(topOffset + 15, leftColumnX,  "                          ");
    mvprintw(topOffset + 16, leftColumnX,  " ↑ : Spara in alto        ");
    mvprintw(topOffset + 17, leftColumnX,  " ← : Spara a sinistra     ");
    mvprintw(topOffset + 18, leftColumnX,  " ↓ : Spara in basso       ");
    mvprintw(topOffset + 19, leftColumnX,  " → : Spara a destra       ");
    attroff(COLOR_PAIR(MENU_NORMAL));



    attron(COLOR_PAIR(MENU_HIGHLIGHT));
    mvprintw(topOffset +  0, centerColumnX," > Obbiettivo:              ");
    attroff(COLOR_PAIR(MENU_HIGHLIGHT));

    attron(COLOR_PAIR(MENU_NORMAL));
    mvprintw(topOffset +  1, centerColumnX,"                            ");
    mvprintw(topOffset +  2, centerColumnX," Sconfiggi nemici, esplora  ");
    mvprintw(topOffset +  3, centerColumnX," tanti livelli e raccogli   ");
    mvprintw(topOffset +  4, centerColumnX," artefatti per battere      ");
    mvprintw(topOffset +  5, centerColumnX," l'high score!              ");
    mvprintw(topOffset +  6, centerColumnX,"                            ");
    mvprintw(topOffset +  7, centerColumnX," Schiva i proiettili rossi  ");
    mvprintw(topOffset +  8, centerColumnX," premendo spazio o stando   ");
    mvprintw(topOffset +  9, centerColumnX," dietro ad un muro oppure   ");
    mvprintw(topOffset + 10, centerColumnX," ancora colpendoli con i    ");
    mvprintw(topOffset + 11, centerColumnX," tuoi proiettili!           ");
    mvprintw(topOffset + 12, centerColumnX,"                            ");
    mvprintw(topOffset + 13, centerColumnX," Ogni volta che sconfiggi   ");
    mvprintw(topOffset + 14, centerColumnX," un nemico guadagnerai      ");
    mvprintw(topOffset + 15, centerColumnX," dello score!               ");
    attroff(COLOR_PAIR(MENU_NORMAL));
    

    attron(COLOR_PAIR(MENU_HIGHLIGHT));
    mvprintw(topOffset +  0, rightColumnX, " > Guida agli artefatti:  ");
    attroff(COLOR_PAIR(MENU_HIGHLIGHT));

    attron(COLOR_PAIR(MENU_NORMAL));
    mvprintw(topOffset +  1, rightColumnX, "                          ");
    mvprintw(topOffset +  2, rightColumnX, " Cuore:                   ");
    mvprintw(topOffset +  3, rightColumnX, "   : Ripristina vita      ");
    attroff(COLOR_PAIR(MENU_NORMAL));
    attron(COLOR_PAIR(ARTEFATTO_CUORE_PAIR_PAUSA));
    mvprintw(topOffset +  3, rightColumnX, " ♥ ");
    attroff(COLOR_PAIR(ARTEFATTO_CUORE_PAIR_PAUSA));

    attron(COLOR_PAIR(MENU_NORMAL));
    mvprintw(topOffset +  4, rightColumnX, "                          ");
    mvprintw(topOffset +  5, rightColumnX, " Statistiche:             ");
    mvprintw(topOffset +  6, rightColumnX, "   : Aumenta attacco      ");
    mvprintw(topOffset +  7, rightColumnX, "   : Aumenta difesa       ");
    mvprintw(topOffset +  8, rightColumnX, "   : Aumenta la vita      ");
    attroff(COLOR_PAIR(MENU_NORMAL));
    attron(COLOR_PAIR(ARTEFATTO_STATISTICHE_PAIR_PAUSA));
    mvprintw(topOffset +  6, rightColumnX, " A ");
    mvprintw(topOffset +  7, rightColumnX, " D ");
    mvprintw(topOffset +  8, rightColumnX, " ♥ ");
    attroff(COLOR_PAIR(ARTEFATTO_CUORE_PAIR_PAUSA));

    attron(COLOR_PAIR(MENU_NORMAL));
    mvprintw(topOffset +  9, rightColumnX, "                          ");
    mvprintw(topOffset + 10, rightColumnX, " Potenziamenti:           ");
    mvprintw(topOffset + 11, rightColumnX, "   : Aumenta sprint       ");
    mvprintw(topOffset + 12, rightColumnX, "   : Proiettili più veloci");
    mvprintw(topOffset + 13, rightColumnX, "   : Attacco dietro       ");
    mvprintw(topOffset + 14, rightColumnX, "   : Attacco in diagonale ");
    mvprintw(topOffset + 15, rightColumnX, "   : Attacco triplo       ");
    attroff(COLOR_PAIR(MENU_NORMAL));
    attron(COLOR_PAIR(ARTEFATTO_POTENZIAMENTO_PAIR_PAUSA));
    mvprintw(topOffset + 11, rightColumnX, " ⟫ ");
    mvprintw(topOffset + 12, rightColumnX, " ↯ ");
    mvprintw(topOffset + 13, rightColumnX, " ⇄ ");
    mvprintw(topOffset + 14, rightColumnX, " ↗ ");
    mvprintw(topOffset + 15, rightColumnX, " ⇶ ");
    attroff(COLOR_PAIR(ARTEFATTO_POTENZIAMENTO_PAIR_PAUSA));

    attron(COLOR_PAIR(MENU_NORMAL));
    mvprintw(topOffset + 16, rightColumnX, "                          ");
    mvprintw(topOffset + 17, rightColumnX, " Chiave:                  ");
    mvprintw(topOffset + 18, rightColumnX, "   : Chiave del boss      ");
    attroff(COLOR_PAIR(MENU_NORMAL));
    attron(COLOR_PAIR(ARTEFATTO_CHIAVE_PAIR_PAUSA));
    mvprintw(topOffset + 18, rightColumnX, " C ");
    attroff(COLOR_PAIR(ARTEFATTO_CHIAVE_PAIR_PAUSA));
}
