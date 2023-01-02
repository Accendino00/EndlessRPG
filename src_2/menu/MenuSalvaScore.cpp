#include "../generale/libs.hpp"

MenuSalvaScore::MenuSalvaScore(int score):Menu(0,3,7) {
    this->score = score;
}



void MenuSalvaScore::loopMenu() {
    bool esciDaSalvaScore = false;
    this->letter = 'a';
    this->x_offset = 34;
    int nome_utente[11];
    int j = 0;
    bool forgot_username = true;
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
                            if(this->letter <= 'z' && j <= 10){
                                this->x_offset++;
                                    nome_utente[j] = this->letter;
                                    j++; 
                                    forgot_username = false;

                            }  
                            else {
                                this->x_offset = 34;
                                this->letter = 'a';
                            }
                            break;
                        case 1:
                            // Salva nome e punteggio ed esci
                            {          
                            FILE *fin = fopen("score.csv", "a" );   
                            if(!feof(fin)){
                                // Se l'utente non ha inserito il nome
                                if(forgot_username == true){
                                    int random_number = rand()%400;
                                    fprintf(fin, "Player%d", random_number);
                                    fprintf(fin, "%s%d\n", ";",this->score);
                                }
                                else {
                                    // Aggiungo il carattere di fine stringa
                                    nome_utente[j+1] = '\0';
                                    int k = 0;
                                    char c;
                                    // Aggiungo il nome utente al file con ;score
                                    do {
                                        fprintf(fin, "%c",nome_utente[k]);                                    k++;
                                        c = fgetc(fin);
                                        } while(k < j && c != EOF);
                                    fprintf(fin, "%s%d\n", ";",this->score);
                                }
                            }    
                                fclose(fin);
                                esciDaSalvaScore = true;  
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
