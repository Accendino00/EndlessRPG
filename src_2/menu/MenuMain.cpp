#include "../generale/libs.hpp"

MenuMain::MenuMain() : Menu(0, 4, 0) {}

void MenuMain::loopMenu() {

    MenuOptions * m_options;
    Gioco * gioco;

    // Loop del menu principale del gioco
    do {
        // Inizio del frame, lettura input e erase dello schermo
        gd->frameStart();
        gd->getInput();
        erase();


        /*** Gestione degli input ***/
        
        // Per cambiare la selezione
        this->manageInput();

        // Se viene fatta una selezione
        // 10 è il codice dell'ENTER, KEY_ENTER non funziona correttamente
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
                    // Options
                    m_options = new MenuOptions();
                    m_options->loopMenu();
                    delete m_options;
                    break;
                case 3:
                    // Exit
                    gd->setCloseGame(true);
                    break;
            }
        }

        // Stampa, fine del frame e refresh dello schermo
        this->printAll();
        gd->frameFinish();
        refresh();
    } while (! (gd->getCloseGame()) );
}

void MenuMain::printAll() {
    printTitle();

    printLine("Gioca", 0);
    printLine("Punteggi", 1);
    printLine("Opzioni", 2);
    printLine("Esci", 3);
}

void MenuMain::printTitle() {
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
};