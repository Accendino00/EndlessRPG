#include "../generale/libs.hpp"

MenuScore::MenuScore() : Menu(0,1,8) {}
void heapify(int arr[], int n, int i)
{
    int min = i; // Il valore più grande inizialmente è la radice
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // Se il figlio sinistro è più piccolo della radice
    if (l < n && arr[l] < arr[min])
        min = l;
 
    // Se il figlio destro è più piccolo della radice
    if (r < n && arr[r] < arr[min])
        min = r;
 
    // Se il valore più piccolo non è la radice
    if (min != i) {
        //Scambio la radice con il max
        int tmp = arr[i];  
        arr[i] = arr[min];
        arr[min] = tmp;
        heapify(arr, n, min);
    }
}
void heapSort(int arr[], int n)
{
    // Costruisco l'heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // Estraggo gli elementi dall'heap
    for (int i = n - 1; i >= 0; i--) {
        // Sposto la radice attuale alla fine
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
 
        // Ricostrusico l'heap con l'array meno un elemento
        heapify(arr, i, 0);
    }
}

void MenuScore::CaricaOrdinaScore() {
    pUserData tmp = this->head; // Salvo la testa
    FILE *fin;
    fin = fopen("score.csv", "r");
    // Booleano per uscire dalla lettura
    bool exit = false;
    // Temp per la lettura
    char c;
    this->scoreCounter = 0; //Contatore per dimensione array di ordinamento

    if (fin != NULL) { // Leggo gli score solo se ve ne sono effettivamente
    pUserData curr = new UserData;
        while(!exit) { // Lettura degli score fino a quando li ho letti tutti e devo uscire 
        
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
            this->scoreCounter++;
            curr->next = tmp;
        }
        //Controllo per fine del file
        if (feof(fin)) {
            exit = true;
        }
        //Dealloco curr
        curr->next = NULL;
        delete curr;
    }
    for(int i = 0; i <= scoreCounter; i++){
        this->arrayScore[i] = tmp->score;
        tmp = tmp->next;
    }
    heapSort(this->arrayScore,scoreCounter);
    //Dealloco tmp
    tmp->next=NULL;
    delete tmp;
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
                    if(this->pagina >= 0){
                        //stampa la pagina precedente    
                          pagina--;

                    }
                    break;
                case KEY_RIGHT: //Mi muovo a destra nella pagina
                case L'D':
                case L'd':
                    if(this->pagina <= this->scoreCounter){
                        //stampa la pagina successiva
                    }
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

void MenuScore::printAll(){
    pUserData tmp = this->head;
    char daStampare[100];
    int line = 0;
    for(int i = (this->pagina-1)*10; i++; i < this->pagina*10){
        sprintf(daStampare,tmp->nome,this->arrayScore[i]);
        printLine(daStampare, line);
        line++;
    }
}

