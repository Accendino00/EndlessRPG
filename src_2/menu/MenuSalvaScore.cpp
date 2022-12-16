#include "../generale/libs.hpp"

MenuSalvaScore::MenuSalvaScore(int score):Menu(0,3,7) {
    this->score = score;
}



void MenuSalvaScore::loopMenu() {
    bool esciDaSalvaScore = false;

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
                        // Cambia lettera
                        break;
                    case 1:
                        // Salva ed esci
                        esciDaSalvaScore = true;
                        break;
                    case 2:
                        // Esci senza salvare
                        esciDaSalvaScore = true;
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
    } while (!esciDaSalvaScore);
}    


void MenuSalvaScore::printAll(){
    // Stampa gigantesca di GAME OVER in caratteri cubitali
    printLine("Seleziona lettera (invio per cambiare)", 0);
    printLine("Salva il tuo score ed esci",1);
    printLine("Esci senza salvare il tuo score", 2);    
}
