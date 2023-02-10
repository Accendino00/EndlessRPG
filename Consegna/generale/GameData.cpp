/**
 * @file GameData.cpp
 * @date 2022
 * @authors Petru Marcel Marincas
 * 
 * @brief
 *      Per più dettagli, vedere la documentazione di ogni funzione
 *      o il @brief di GameData.hpp.
 */

#include "../generale/libs.hpp"


/**
 * Inizializzazione delle impostazioni di ncurses e di alcuni dati iniziali
 * Chiude il programma con codice ERR se c'è stato un errore da uno dei metodi di ncurses
 */
GameData::GameData () {
    this->num_PressedKeys = 0;
    this->status = OK;
    this->closeGame = false;
    this->FPSCap = 60;
    this->difficulty = 1;
    this->showPerformance = true;
    this->impostazioniSalvate = true;

    this->currentTick = 0;

    // Devo usare chrono per avere meno cast. Ha il suo particolare 
    // tipo di dato per misurare la durata del tempo
    this->timeForTick = std::chrono::duration<double>(0.001); // Ovvero 1 tick ogni 1ms
    this->last_clock = std::chrono::system_clock::now();
}

/**
 * @brief Inizializza ncurses e le impostazioni di gioco.
 * 
 * In caso di errore, termina l'esecuzione del programma 
 * restituendo il codice di errore, ovvero -1.
 */
void GameData::startUp() {
    // Per avere accesso ad un numero maggiore di caratteri
	setlocale(LC_ALL, "");

    // Inizializzazione di ncurses
    initscr();
	
    // Se una opzione di queste non venisse abilitata correttamente, ritorna ERR, quindi, se questo succede
    // Interrompo l'esecuzione del gioco e ritorno un errore, in quanto il gioco si basa sul funzionamento di queste
    bool er = FALSE;
    er = er || (ERR == curs_set(0)           );    // Togliere il puntatore dal terminale
	er = er || (ERR == noecho()              );    // Non scrivere su schermo i tasti premuti
    er = er || (ERR == cbreak()              );    // Lasciare le combinazioni di tasti del terminale standard
	er = er || (ERR == nodelay(stdscr, true) );    // Evitare che l'input fermi il gioco
    er = er || (ERR == keypad(stdscr,true)   );    // Frecce della tastiera e altri tasti particolari abilitati

    if (er) {
        endwin();
        printf("Delle opzioni di ncurses non sono abilitate!\n");
        this->status = ERR;
        exit(this->status);
    }
    
    // Grandezza del terminale, cioè il numero di righe e colonne
    getmaxyx(stdscr, this->terminalY, this->terminalX);
	
    // Inizializzazione dei colori
    if (has_colors() == false)
    {
        endwin();
        printf("I colori non sono supportati da questo terminale!\n");
        this->status = ERR;
        exit(this->status);
    }
	start_color(); 

    // Inizializzazione del random
    srand(time(NULL));

    // Carica le impostazioni da file
    this->caricaImpostazioni();

    initializeColors();
    bkgd(COLOR_PAIR(MENU_NORMAL));
}





/**
 * @brief Prende in input i tasti premuti e li salva in un array.
 * 
 * Aggiorna quindi gli attributi "num_PressedKeys" e "pressedKeys".
 *    - Il primo è il numero di tasti premuti insieme salvati nell'array.
 *    - Il secondo è l'array di tasti premuti insieme.
 * 
 * Gestisce inoltre la richiesta di ridimensionamento del terminale:
 *    - Quando in input vi è KEY_RESIZE, allora si sta ridimensionando il terminale.
 *    - Pertanto cambio gli attributi this->terminalX e this->terminalY.
 */
void GameData::getInput () {
    this->num_PressedKeys = 0;
	do {
		this->pressedKeys[this->num_PressedKeys] = getch();
        // Cambio i dati delle dimensioni del terminale se KEY_RESIZE è uno degli input
        if(this->pressedKeys[this->num_PressedKeys] == KEY_RESIZE) {
            getmaxyx(stdscr, this->terminalY, this->terminalX);  
        }
        this->num_PressedKeys++;
	} while(    this->num_PressedKeys < (MAX_TASTI_INSIEME-1) 
            &&  this->pressedKeys[this->num_PressedKeys-1] != ERR);
}

/**
 * @brief Controlla se un tasto è stato premuto.
 * 
 * @param inputToCheck Il tasto da controllare
 * @return true Se il tasto è stato premuto
 * @return false Se il tasto non è stato premuto
 */
bool GameData::checkInput (int inputToCheck) {
    int i = 0;
    while (i < this->num_PressedKeys && this->pressedKeys[i] != inputToCheck) { i++; }
    return (i < this->num_PressedKeys && this->pressedKeys[i] == inputToCheck);
}

/**
 * @brief Ritorna il tasto premuto all'indice index in pressedKeys.
 * 
 * @param index L'indice del tasto da ritornare
 * @return int Il tasto premuto all'indice index in pressedKeys
 */
int GameData::getKey(int index) {
    int returnValue = ERR;
    if(index >= 0 && index < this->num_PressedKeys) {
        returnValue = this->pressedKeys[index];
    }
    return returnValue;
}

/**
 * @brief Ritorna il numero di tasti premuti insieme.
 * 
 * @return int Il numero di tasti premuti insieme
 */
int GameData::getNumOfPressedKeys() {
    return this->num_PressedKeys;
}

/** 
 * frameStart() e frameFinish() sono due funzioni che servono per controllare il framerate.
 * 
 * frameStart() deve essere chiamata all'inizio del ciclo di gioco, mentre frameFinish() 
 * deve essere chiamata alla fine.
 * 
 * frameFinish() controlla se il tempo trascorso dall'inizio del ciclo di gioco è inferiore
 * al tempo necessario per avere un framerate pari a FPSCap. Se questo è vero, allora
 * il programma si ferma per il tempo necessario per arrivare al framerate desiderato.
 * 
 * Inoltre se showPerformance è true, allora viene stampato a schermo il framerate e il tempo.
 */

void GameData::frameStart() {
    this->start = std::chrono::system_clock::now();
}

void GameData::frameFinish() {
    this->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = (this->end) - (this->start);

    // PER AVERE UN CAP DI FPS
    if(elapsed_seconds.count() <= (1/((double)this->FPSCap))) {
        usleep(((1/((double)this->FPSCap)) - elapsed_seconds.count())*1000000);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;

    if (this->showPerformance) {
        mvprintw(0,0,"FPS: %.0f", (1/elapsed_seconds.count()));
        mvprintw(1,0,"ms: %.1f",elapsed_seconds.count()*1000);
    }
}



int GameData::getTerminalX() {
    return this->terminalX;
}

int GameData::getTerminalY() {
    return this->terminalY;
}

void GameData::setStatus(int status) {
    this->status = status;
}

int GameData::getStatus() {
    return this->status;
}

void GameData::setCloseGame(bool closeGame) {
    this->closeGame = closeGame;
}

bool GameData::getCloseGame() {
    return this->closeGame;
}



// Gestione tick

/**
 * @brief Gestisce i tick del gioco.
 * Dovrebbe venire chiamato ad ogni ciclo di gioco.
 * 
 * Se il tempo trascorso dall'ultima volta dove è stato chiamato manageTicks() è maggiore
 * di timeForTick, allora aggiunge la qunatità di tick che sono passati a currentTick.
 */
void GameData::manageTicks() {
    std::chrono::_V2::system_clock::time_point nowTime = std::chrono::system_clock::now();
    std::chrono::duration<double> passedTime = (nowTime - this->last_clock);
    if(passedTime >= this->timeForTick) {
        this->currentTick += (long int) (passedTime.count() / (this->timeForTick.count()));
        this->last_clock = nowTime;
    }
}

long long int GameData::getCurrentTick() {
    return this->currentTick;
}

void GameData::resetTicks() {
    this->currentTick = 0;
    this->last_clock = std::chrono::system_clock::now();
}



/**
 * @brief Salva le impostazioni sul file "settigs.csv".
 */
void GameData::salvaImpostazioni() {
    FILE * fout;
    fout = fopen("settings.csv","w");
    fprintf(fout,"fpscap;%d\ndifficulty;%d\nshowperformance;%d", this->FPSCap, this->difficulty, this->showPerformance);
    fclose(fout);
    this->impostazioniSalvate = true;
}

/**
 * @brief Carica le impostazioni dal file "settigs.csv".
 * Se il file non esiste, allora lo crea e salva le impostazioni di default.
 * 
 * Le impostazioni vengono caricate seguendo una struttura del tipo:
 *  fpscap;60
 *  difficulty;1
 *  showperformance;1
 * 
 * Nel caso in cui il file non rispetti questa struttura, il comportamento del
 * programma è indefinito in quanto non vengono eseguiti controlli. 
 * (Mi aspetto che il file dei settings lo scriva e lo legga solo il programma). 
 */
void GameData::caricaImpostazioni() {
    FILE * fin;
    fin = fopen("settings.csv", "r");
    if(fin == NULL) {  
        FILE * fout;
        fout = fopen("settings.csv","w");
        fprintf(fout,"fpscap;%d\ndifficulty;%d\nshowperformance;%d", this->FPSCap, this->difficulty, this->showPerformance);
        fclose(fout);
    } else {
        // Temp per la lettura
        char c;
        // Lettura del FPSCAP
        while(c != ';') {
            c = fgetc(fin);
        }
        this->FPSCap = 0;
        while(c != '\n') {
            c = fgetc(fin);
            if (c != '\n') {
                this->FPSCap *= 10;
                this->FPSCap += (c - '0');
            }
        }
        while(c!=';'){
            c = fgetc(fin);
        }
        c = fgetc(fin);
        this->difficulty = c - '0';
        while(c!=';') {
            c = fgetc(fin);
        }
        c = fgetc(fin);
        this->showPerformance = c - '0'; 
        fclose(fin);
    }
}

// Settings
// Per le direzioni nei cycle: True == destra , False == sinistra.
// In generale: la funzione "get" ti ritorna l'impostazione, mentre
// la funzione "cycle" cambia l'impostazione in base alla direzione.

int GameData::getFPSCap() {
    return this->FPSCap;
}

void GameData::cycleFPSCap(bool direction) {
    if(direction) {
        this->FPSCap = (this->FPSCap + 30) % 330;
        if(this->FPSCap < 60) {
            this->FPSCap = 60;
        }
    } else {
        this->FPSCap = (this->FPSCap - 30 + 330) % 330;
        if(this->FPSCap < 60) {
            this->FPSCap = 300;
        }
    }
    this->impostazioniSalvate = false;
}

const char * GameData::getShowPerformance() {
    if(this->showPerformance) {
        return "Vero";
    } else {
        return "Falso";
    }
}
void GameData::cycleShowPerformance(bool direction) {
    this->showPerformance = !this->showPerformance;
    this->impostazioniSalvate = false;
}

/**
 * @brief Ritorna la difficoltà come stringa.
 * Corrisponde con i valori da 0 a 3 della difficoltà.
 * 
 * @return const char*  "Facile"
 *                      "Normale"
 *                      "Difficile"
 *                      "Impossibile" 
 */
const char * GameData::getDifficulty() {
    if(this->difficulty==0) {
        return "Facile";
    } else if(this->difficulty==1) {
        return "Normale";
    } else if(this->difficulty==2) {
        return "Difficile";
    } else {
        return "Impossibile";
    }
}

void GameData::cycleDifficulty(bool direction) {
    if(direction) {
        this->difficulty = (this->difficulty + 1) % 4;
    } else {
        this->difficulty = (this->difficulty - 1 + 4) % 4;
    }
    this->impostazioniSalvate = false;
}

const char * GameData::getImpostazioniSalvate() {
    if (this->impostazioniSalvate) {
        return "Impostazioni salvate!";
    } else {
        return "Salva impostazioni";
    }
}