#include "../generale/libs.hpp"

MenuScore::MenuScore() : Menu(0,1,8) {}

void GameData::caricaScore() {
    ptrlist tmp = this->head; //Salvo la testa
    FILE *fin;
    fin = fopen("score.csv", "r");
    //booleano per uscire dalla lettura
    bool exit=true;
    // Temp per la lettura
    char c;
    while(exit) {
        if (fin == NULL) {
            char str[50] = "Il file score è inesistente"
            printf("%s",str);
        } else {
            ptrlist curr = new dati;
            while (c != ';') {   //Carico il nome
                c = fgetc(fin);
                strcpy(curr->nome[i], c);
                i++;
            }
            curr->score = 0;     //Carico il punteggio
            int i = 10000000;
            while (c != '\n') {
                c = fgetc(fin);
                if (c != '\n') {
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
            exit = false;
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


                    }
                    break;
                case KEY_RIGHT: //Mi muovo a destra nella pagina
                case L'D':
                case L'd':

                    }
                    break;
            }
            i++;
        // Stampa, fine del frame e refresh dello schermo
        this->printAll();
        gd->frameFinish();
        refresh();
        switch()

        while (!esciDaScore)
    }
}


