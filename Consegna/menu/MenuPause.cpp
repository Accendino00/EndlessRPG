#include "../generale/libs.hpp"

MenuPause::MenuPause():Menu(0,4,1) {}


/**
 * @brief Loop del menu della pausa.
 * 
 * Può venire aperto durante la partita per modificare
 * le impostazioni, per vedere le istruzioni e per tornare
 * al menu principale.
 * 
 * @return true     Se si vuole tornare al menu principale
 * @return false    Se non si vuole tornare al menu principale
 */
bool MenuPause::loopMenu() {
    bool esciDaPause = false;
    bool returnValue = false;

    MenuOptions *m_options;
    MenuIstruzioni * m_istruzioni;

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
                            // Istruzioni
                            m_istruzioni = new MenuIstruzioni();
                            m_istruzioni->loopMenu();
                            delete m_istruzioni;
                            break;
                        case 3:
                            // Torna al menù principale
                            esciDaPause = true;
                            returnValue = true;
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

    return returnValue;
}    


void MenuPause::printAll(){
    printLine("Torna al gioco", 0);
    printLine("Opzioni",1);
    printLine("Istruzioni",2);
    printLine("Menù principale", 3);    
}
