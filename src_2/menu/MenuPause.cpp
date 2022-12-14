#include "../generale/libs.hpp"

MenuPause::MenuPause():Menu(0,3,1) {}



void MenuPause::loopPause() {
    bool esciDaPause = false;

    MenuOptions *m_options;
    MenuMain *m_main;

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
                            // Riprendi
                            esciDaPause = true;
                            break;
                        case 1:
                            // Opzioni
                            m_options = new MenuOptions();
                            m_options->loopMenu();
                            delete m_options;
                            break;
                        case 2:
                            // Torna al menù principale
                            m_main = new MenuMain;
                            m_main->loopMenu();
                            delete m_main;
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
    } while (!esciDaPause);
}    


void MenuPause::printAll(){
    printLine("Torna al gioco", 0);
    printLine("Opzioni",1);
    printLine("Menù principale", 2);    
}
