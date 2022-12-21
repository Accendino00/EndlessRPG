#include "../generale/libs.hpp"

MenuSalvaScore::MenuSalvaScore(int score):Menu(0,3,7) {
    this->score = score;
    
    int i = 0;
    for( char l = 'a'; l<='z'; ++l) {
        i++;
        this->alphabet[i] = l;
    } 
    this->alphabet[27] = '\0';
    
}



void MenuSalvaScore::loopMenu() {
    bool esciDaSalvaScore = false;
    this->letter = 0;

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
                            // Conferma il carattere e vai al prossimo
                            this->letter = 0;
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
                case KEY_RIGHT:
                    switch(this->getSelezione()) {
                        case 0:
                            // Cambia carattere
                            if(this->letter < 26){
                                this->letter++;
                            }
                            else 
                                this->letter = 0;
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
    char daStampare[100];
    sprintf(daStampare, "%c", this->alphabet[this->letter]);
    printLine(daStampare,0);
    //printLine("Seleziona lettera (freccia a destra per cambiare)", 0);
    printLine("Salva il tuo score ed esci",1);
    printLine("Esci senza salvare il tuo score", 2);    
}
