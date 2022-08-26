#include "../generale/libs.hpp"


MenuOptions::MenuOptions() : Menu(0, 6, 0)  {}

void MenuOptions::loopMenu() {
    bool LeaveMenu = false;
    MenuCrediti * m_crediti;
    do {
        // Inizio del frame, lettura input e erase dello schermo
        gd->frameStart();
        gd->getInput();
        erase();


        /*** Gestione degli input ***/

        // Per cambiare l'impostazione selezionata 
        this->manageInput();

        // Gestione della modifica delle impostazioni o selezione di menu
        int i = 0;
        while(i < gd->getNumOfPressedKeys()) {
            switch(gd->getKey(i)) {
                case KEY_LEFT:
                case L'A':
                case L'a':
                    switch(this->getSelezione()) {
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
                case KEY_RIGHT:
                case L'D':
                case L'd':
                    switch(this->getSelezione()) {
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
                case 10:
                    switch(this->getSelezione()) {
                        case 3:
                            // Save
                            gd->salvaImpostazioni();
                            break;
                        case 4:
                            // Credits
                            m_crediti = new MenuCrediti();
                            m_crediti->loopMenu();
                            delete m_crediti;
                            break;
                        case 5:
                            // Exit
                            LeaveMenu = true;
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
    } while (! LeaveMenu);
}

void MenuOptions::printAll() {
    char daStampare[100];
    sprintf(daStampare, "Difficoltà: < %s \t>",gd->getDifficulty());
    printLine(daStampare, 0);
    
    sprintf(daStampare, "FPS cap:    < %d \t>", gd->getFPSCap());
    printLine(daStampare, 1);    
    
    sprintf(daStampare, "Mostra FPS: < %s \t>", gd->getShowPerformance());
    printLine(daStampare, 2);    
    
    printLine(gd->getImpostazioniSalvate(), 3);
    printLine("Crediti", 4);
    printLine("Indietro", 5);    
}