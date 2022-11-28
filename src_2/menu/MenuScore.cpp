#include "../generale/libs.hpp"

void heapify(UserData arr[], int n, int i)
{
    int min = i; // Il valore più grande inizialmente è la radice
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // Se il figlio sinistro è più piccolo della radice
    if (l < n && arr[l].score < arr[min].score)
        min = l;
 
    // Se il figlio destro è più piccolo della radice
    if (r < n && arr[r].score < arr[min].score)
        min = r;
 
    // Se il valore più piccolo non è la radice
    if (min != i) {
        //Scambio la radice con il max
        UserData tmp = arr[i];  
        arr[i] = arr[min];
        arr[min] = tmp;
        heapify(arr, n, min);
    }
}
void heapSort(UserData arr[], int n)
{
    // Costruisco l'heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // Estraggo gli elementi dall'heap
    for (int i = n - 1; i >= 0; i--) {
        // Sposto la radice attuale alla fine
        UserData tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
 
        // Ricostrusico l'heap con l'array meno un elemento
        heapify(arr, i, 0);
    }
}

MenuScore::MenuScore() : Menu(0,2,6) {
    // Inizializziamo gli attributi
    this->scoreCounter = 0;
    this->pagina = 0;

    // Leggiamo dal file gli score e li assegniamo alla lista di UserDataList
    pUserData tmp = NULL;

    FILE *fin = fopen("score.csv", "r");

    // Booleano per capire se c'è un errore nel file
    bool error = false;
    // Temp per la lettura
    char c;

    // Se esiste il file di input allora leggo
    if (fin != NULL && !feof(fin)) { 

        do { // Lettura degli score fino a quando li ho letti tutti e devo uscire 
            pUserData curr = new UserDataList;

            // Lettura del nome
            int j = 0;
            do {
                c = fgetc(fin); 

                if (c != ';' && c != EOF) {
                    curr->data.nome[j] = c;
                    j++;
                }
            } while (c != ';' && c != EOF && j < 10); // Leggo fino a quando non trovo il carattere ';' o arrivo al massimo
            curr->data.nome[j] = '\0'; // Aggiungo il carattere di fine stringa

            if (j == 10 && c != EOF && c != ';') { 
                // Se ho letto 10 caratteri e non ho trovato il carattere ';' allora leggo anche il prossimo
                c = fgetc(fin);
            }

            // Solo se ho letto l'intero numero ed ho un punto e virgola continuo
            if (c == ';') {
                // Lettura del punteggio
                curr->data.score = 0;     
                do {
                    c = fgetc(fin);
                    if (c != '\n' && c != EOF) {
                        curr->data.score *= 10;
                        curr->data.score += (c - '0');
                    }
                } while(c != '\n' && c != EOF);


                this->scoreCounter++;

                if (tmp == NULL) {
                    tmp = curr;
                    curr->next = NULL;
                } else {
                    pUserData tmp2 = tmp;
                    while (tmp2->next != NULL) {
                        tmp2 = tmp2->next;
                    }
                    if (tmp2->next == NULL) {
                        tmp2->next = curr;
                        curr->next = NULL;
                    }
                }
            } else {
                error = true;
            }
        
            // Controllo se c'è stato un errore
            if (error) {
                delete curr;
                curr = NULL;
            }

        } while(!error);
    }

    if(this->scoreCounter > 0){
        this->arrayScore = new UserData[this->scoreCounter]; //Puntatore ad array di strutture
        int i = 0;
        while (tmp != NULL) {
            this->arrayScore[i] = tmp->data;
            pUserData tmp2 = tmp;
            tmp = tmp->next;
            delete tmp2;
            tmp2 = NULL;
            i++;
        } 

        heapSort(this->arrayScore, this->scoreCounter);

    } else this->arrayScore = NULL;
}

MenuScore::~MenuScore(){
  delete [] (this->arrayScore);
}

void MenuScore::loopScore() {
    bool esciDaScore = false;
    this->pagina = 0; //Inizializzo le pagine 
    do {
        gd->frameStart();
        gd->getInput();
        erase();
        this->manageInput();
        int i = 0;
        while(i < gd->getNumOfPressedKeys()) {
            switch(this->getSelezione()) {
                // Se sono sul cambia pagina
                case 0:
                    switch(gd->getKey(i)) {
                        case KEY_LEFT: //Mi muovo a sinistra nella pagina
                        case L'A':
                        case L'a':
                            // loop around delle pagine quando diminuisco
                            if (this->pagina == 0) {
                                this->pagina = this->scoreCounter / 10;
                            } else {
                                this->pagina--;
                            }
                            break;
                        case KEY_RIGHT: //Mi muovo a destra nella pagina
                        case L'D':
                        case L'd':
                        case 10:
                            // loop around delle pagine quando aumento
                            if (this->pagina == this->scoreCounter / 10) {
                                this->pagina = 0;
                            } else {
                                this->pagina++;
                            }
                            break;
                    }
                break;

                // Se sono sull'uscita    
                case 1:
                    switch(gd->getKey(i)) {
                        case 10:
                            esciDaScore = true;
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
    } while (!esciDaScore);
}    

void MenuScore::printAll(){
    char daStampare[100];
    int line = 0;
    
    mvprintw((gd->getTerminalY()/2) - 20,gd->getTerminalX()/2-8,"POSIZIONE : NOME - PUNTEGGIO");
    for(int i = ((this->pagina)*10); i < ((this->pagina+1)*10) ; i++){ //Seleziono la porzione di array che voglio mostrare
        if(i < scoreCounter){
            sprintf(daStampare, "< %d° \t:\t %s - %d >", i + 1, arrayScore[i].nome, this->arrayScore[i].score);
            attron(COLOR_PAIR(MENU_NORMAL));
            int centerY = (gd->getTerminalY()/2) - 20;
            int centerX = gd->getTerminalX()/2;
            mvprintw(centerY+(2*(line+1)),centerX-8,"%s",daStampare);
            attroff(COLOR_PAIR(MENU_NORMAL));
            line ++;
        }
    }
    
    sprintf(daStampare, "Cambia pagina < %d >",this->pagina + 1);
    printLine(daStampare,0);
    printLine("Indietro",1);
}