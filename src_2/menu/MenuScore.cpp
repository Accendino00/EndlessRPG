#include "../generale/libs.hpp"

MenuScore::MenuScore() : Menu(0,1,8) {}

void MenuScore::caricaScore() {
    pUserData tmp = this->head; // Salvo la testa
    FILE *fin;
    fin = fopen("score.csv", "r");
    // Booleano per uscire dalla lettura
    bool exit = false;
    // Temp per la lettura
    char c;

    if (fin != NULL) { // Leggo gli score solo se ve ne sono effettivamente
        while(!exit) { // Lettura degli score fino a quando gli ho letti tutti e devo uscire 
            pUserData curr = new UserData;
            for (int i = 0; i < 3; i++) { // Carico il nome
                c = fgetc(fin);
                curr->nome[i] = c;
            }
            curr->nome[3] = '\0';
            curr->score = 0;     //Carico il punteggio
            int i = 10000000;
            while (c != '\n') {
                c = fgetc(fin);
                if (feof(fin) && c != '\n') {
                    curr->score += (c - '0') * i;
                    i /= 10;
                }
            }
            while (i >= 1) {
                curr->score = curr->score / 10;
                i /= 10;
            }
            curr->next = tmp;
        }
        //Controllo per fine del file
        if (feof(fin)) {
            exit = true;
        }
    }
}

void MenuScore::loopScore() {
    bool esciDaScore = false;
    do {
        gd->frameStart();
        gd->getInput();
        erase();
        this->manageInput();
        int i = 0;
        while(i < gd->getNumOfPressedKeys()) {
            switch(gd->getKey(i)) {
                case KEY_LEFT: //Mi muovo a sinistra nella pagina
                case L'A':
                case L'a':
                    break;
                case KEY_RIGHT: //Mi muovo a destra nella pagina
                case L'D':
                case L'd':
                    break;
            }
            i++;
        }


        // Stampa, fine del frame e refresh dello schermo
        //this->printAll();
        gd->frameFinish();
        refresh();
        //switch();

        //while (!esciDaScore)
    } while (!esciDaScore);
}


