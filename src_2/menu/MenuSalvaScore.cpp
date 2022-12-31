#include "../generale/libs.hpp"

MenuSalvaScore::MenuSalvaScore(int score):Menu(0,3,7) {
    this->score = score;
}



void MenuSalvaScore::loopMenu() {
    bool esciDaSalvaScore = false;
    this->letter = 'a';
    this->x_offset = 34;
    int nome_utente[100];

    do {
        gd->frameStart();
        gd->getInput();
        erase();
        this->manageInput();
        int i = 0;
        int j = 0;
        while(i < gd->getNumOfPressedKeys()) {
            switch(gd->getKey(i)) {
                case 10:
                    switch(this->getSelezione()) {
                        case 0:
                            // Conferma il carattere e vai al prossimo
                            if(this->letter <= 'z'){
                                this->x_offset++;
                                //if(nome_utente[j] < 100){
                                    nome_utente[j] = this->letter;
                                    j++;   
                                    
                            }
                            else {
                                this->x_offset = 34;
                                this->letter = 'a';
                            }
                            break;
                        case 1:
                            // Salva nome e punteggio ed esci
                            {
                            esciDaSalvaScore = true;            
                            FILE *fin = fopen("score.csv", "w");
                            int k = 0;
                            char c;
                            //finché non arrivi in fondo al file
                            c = fgetc(fin);
                            do {
                               if(c != EOF){
                                fprintf(fin, "%c",nome_utente[k]);
                                k++;
                                c = fgetc(fin);
                                }
                            } while(k <= j && k != EOF);
                            fclose(fin);
                            break;
                            }
                        case 2:
                            // Esci senza salvare
                            esciDaSalvaScore = true;
                            break;
                    }
                    break;
                case KEY_RIGHT:
                    switch(this->getSelezione()) {
                        case 0:
                            // Cambia carattere in avanti
                            if(this->letter < 'z'){
                                this->letter++;
                            }
                            else 
                                this->letter = 'a';
                            break;
                    }
                    break;
                case KEY_LEFT:
                    switch(this->getSelezione()){
                        case 0:
                            // Cambia carattere indietro
                            if(this->letter > 'a'){
                                this->letter--;
                            }
                            else
                                this->letter = 'z';
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
    printGameOver();
    
    if(this->letter >= 'a' && x_offset >= 0){
        attron(COLOR_PAIR(MENU_NORMAL));
        int centerY = gd->getTerminalY()/2;
        int centerX = gd->getTerminalX()/2;
            mvprintw(centerY+3,-14+centerX,"Usa la freccia per cambiare lettera:");
            mvprintw(centerY+5,-32+centerX+(this->x_offset),"<%c>",this->letter);
        attroff(COLOR_PAIR(MENU_NORMAL));
    }

    printLine("Salva il tuo score ed esci",1);
    printLine("Esci senza salvare il tuo score", 2);    
}

void MenuSalvaScore::printGameOver(){
        int centerY = gd->getTerminalY()/2;
        int centerX = gd->getTerminalX()/2;
        attron(COLOR_PAIR(GAME_OVER));
        mvprintw(centerY-13,centerX-15, "███▀▀▀██ ███▀▀▀███ ███▀█▄█▀███ ██▀▀▀");
        mvprintw(centerY-12,centerX-15, "██    ██ ██     ██ ██   █   ██ ██   ");
        mvprintw(centerY-11,centerX-15, "██   ▄▄▄ ██▄▄▄▄▄██ ██   ▀   ██ ██▀▀▀");
        mvprintw(centerY-10,centerX-15, "██    ██ ██     ██ ██       ██ ██   ");
        mvprintw(centerY-9, centerX-15, "███▄▄▄██ ██     ██ ██       ██ ██▄▄▄");
        mvprintw(centerY-8, centerX-15, "                                    ");
        mvprintw(centerY-7, centerX-15, "███▀▀▀███ ▀███  ██▀ ██▀▀▀ ██▀▀▀▀██▄ ");
        mvprintw(centerY-6, centerX-15, "██     ██   ██  ██  ██    ██     ██ ");
        mvprintw(centerY-5, centerX-15, "██     ██   ██  ██  ██▀▀▀ ██▄▄▄▄▄▀▀ ");
        mvprintw(centerY-4, centerX-15, "██     ██   ██  █▀  ██    ██     ██ ");
        mvprintw(centerY-3, centerX-15, "███▄▄▄███    ▀█▀    ██▄▄▄ ██     ██▄");
        attroff(COLOR_PAIR(GAME_OVER));
    };
