#include "../generale/libs.hpp"

/*
 Inizializzazione delle impostazioni di ncurses e di alcuni dati iniziali
 Chiude il programma con codice ERR se c'è stato un errore da uno dei metodi di ncurses
*/
GameData::GameData () {
    this->num_PressedKeys = 0;
    this->status = OK;
    this->closeGame = false;
    this->maxFPS = 60;
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

    initializeColors();
    bkgd(COLOR_PAIR(MAIN_TITLE));
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
	} while(this->pressedKeys[this->num_PressedKeys-1] != ERR);
}

bool GameData::checkInput (int inputToCheck) {
    int i = 0;
    while (i < this->num_PressedKeys && this->pressedKeys[i] != inputToCheck) { i++; }
    return (i < this->num_PressedKeys && this->pressedKeys[i] == inputToCheck);
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