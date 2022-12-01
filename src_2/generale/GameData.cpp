#include "../generale/libs.hpp"

/*
 Inizializzazione delle impostazioni di ncurses e di alcuni dati iniziali
 Chiude il programma con codice ERR se c'è stato un errore da uno dei metodi di ncurses
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
    this->timeForTick = std::chrono::duration<double>(0.001);
    this->last_clock = std::chrono::system_clock::now();
}

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

bool GameData::checkInput (int inputToCheck) {
    int i = 0;
    while (i < this->num_PressedKeys && this->pressedKeys[i] != inputToCheck) { i++; }
    return (i < this->num_PressedKeys && this->pressedKeys[i] == inputToCheck);
}

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

int GameData::getKey(int index) {
    int returnValue = ERR;
    if(index >= 0 && index < this->num_PressedKeys) {
        returnValue = this->pressedKeys[index];
    }
    return returnValue;
}


int GameData::getTerminalX() {
    return this->terminalX;
}

int GameData::getTerminalY() {
    return this->terminalY;
}

int GameData::getNumOfPressedKeys() {
    return this->num_PressedKeys;
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

void GameData::salvaImpostazioni() {
    FILE * fout;
    fout = fopen("settings.csv","w");
    fprintf(fout,"fpscap;%d\ndifficulty;%d\nshowperformance;%d", this->FPSCap, this->difficulty, this->showPerformance);
    fclose(fout);
    this->impostazioniSalvate = true;
}

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
// True = destra , False = sinistra
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