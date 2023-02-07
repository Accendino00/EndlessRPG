#include "../generale/libs.hpp"

MenuSalvaScore::MenuSalvaScore(int score):Menu(0,3,7) {
    this->score = score;
    for (int i = 0; i < 10; i++) {
        nome_utente[i] = '\0';
    }
}


/*

    Il tuo nome:

        a b [c] -


    Lettera da inserire: < a > 
    Conferma e salva
    Esci senza salvare
*/


void MenuSalvaScore::loopMenu() {
    bool esciDaSalvaScore = false;
    this->letter = 'a';
    int j = 0; // Contatore per il nome utente 
    bool forgot_username = true;
    FILE *fin = NULL;

    do {
        // Inizio del frame, lettura input e erase dello schermo
        gd->frameStart();
        gd->getInput();
        erase();

        this->manageInput();
        int i = 0;
        while(i < gd->getNumOfPressedKeys()) {
            switch(gd->getKey(i)) {
                case 10: // Enter
                    switch(this->getSelezione()) {
                        case 0:
                            // Conferma il carattere e vai al prossimo
                            if(j < 10){ // Nome utente massimo di 10 caratteri
                                if(this->letter <= 'z'){
                                    nome_utente[j] = this->letter;
                                    j++; 
                                    forgot_username = false;
                                }  
                                else {
                                    this->letter = 'a';
                                }
                            }
                            break;
                        case 1:
                            // Salva nome e punteggio ed esci       
                            fin = fopen("score.csv", "a" );   
                            if(!feof(fin)){
                                // Se l'utente non ha inserito il nome
                                if(forgot_username == true){
                                    int random_number = rand()%400;
                                    fprintf(fin, "Player%d", random_number);
                                    fprintf(fin, ";%d\n",this->score);
                                }
                                else {
                                    // Aggiungo il carattere di fine stringa
                                    nome_utente[j+1] = '\0';
                                    int k = 0;
                                    char c;
                                    // Aggiungo il nome utente al file con ;score
                                    do {
                                        fprintf(fin, "%c",nome_utente[k]);                                    
                                        k++;
                                        c = fgetc(fin);
                                        } while(k < j && c != EOF);
                                    fprintf(fin, ";%d\n",this->score);
                                }
                            }    
                            fclose(fin);
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


    attron(COLOR_PAIR(MENU_NORMAL));
    int centerY = gd->getTerminalY()/2;
    int centerX = gd->getTerminalX()/2;
    mvprintw(centerY+3,centerX-10,"Il tuo nome:");
    if (strlen(nome_utente) < 10) {
        mvprintw(centerY+5,centerX-8,"%s  ← <%c>", this->nome_utente, this->letter);
        attron(A_BLINK);
        mvprintw(centerY+5,centerX-8 + strlen(nome_utente),"_");
        attroff(A_BLINK);
    } else {
        mvprintw(centerY+5,centerX-8,"%s", this->nome_utente);    
    }
    attroff(COLOR_PAIR(MENU_NORMAL));

    char stringa[100];

    if (strlen(nome_utente) < 10) {
        sprintf(stringa, "Seleziona lettera e premi invio: <%c>", this->letter);
    } else {
        sprintf(stringa, "Il nome ha lunghezza massima!");
    }
    printLine(stringa, 0);
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
