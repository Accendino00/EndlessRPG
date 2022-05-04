#include "libs.hpp"

/*

    Comandi per compilazione con debug:
        g++ -g -o Gioco Entita.cpp Compatibility.cpp main.cpp -lncursesw
        valgrind --leak-check=full          --show-leak-kinds=all          --track-origins=yes          --verbose          --log-file=valgrind-out.txt          ./Gioco
*/

#define MAX_TASTI_INSIEME 32

struct GameData {
    int terminalY, terminalX;   // La dimensione del terminale

    int num_PressedKeys;        // Il numero di input premuti in un determinato frame dall'utente
    int pressedKeys [MAX_TASTI_INSIEME]; // L'elenco degli input premuti nel frame dall'utente

    int status;                 // Assume i valori ERR o OK. Se ERR, il programma dovrebbe venire terminato.
    bool closeGame;             // Se true, allora il gioco deve venire chiuso

    // short max_colorId;       // L'id del colore massimo che ho creato
                                // Il massimo è la define: UINT_LEAST16_MAX


};

/*
 Inizializzazione delle impostazioni di ncurses e di alcuni dati iniziali
 Chiude il programma con codice ERR se c'è stato un errore da uno dei metodi di ncurses
*/
void startUp (GameData * gd) {
    gd->num_PressedKeys = 0;
    gd->status = OK;
    gd->closeGame = false;

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
        gd->status = ERR;
        exit(gd->status);
    }
    
    // Grandezza del terminale, cioè il numero di righe e colonne
    getmaxyx(stdscr, gd->terminalY, gd->terminalX);
	
    // Inizializzazione dei colori
    if (has_colors() == false)
    {
        endwin();
        printf("I colori non sono supportati da questo terminale!\n");
        gd->status = ERR;
        exit(gd->status);
    }
	start_color(); 

    // Inizializzazione del random
    srand(time(NULL));


    /////////////////////////////////////
    // LETTURA DEI DATI DI SALVATAGGIO //
    /////////////////////////////////////
}

void getInput (GameData * gd) {
    gd->num_PressedKeys = 0;
	do {
		gd->pressedKeys[gd->num_PressedKeys] = getch();
        gd->num_PressedKeys++;
	} while(gd->pressedKeys[gd->num_PressedKeys-1] != ERR);
}

bool checkInput (const GameData gd, int inputToCheck) {
    int i = 0;
    while (i < gd.num_PressedKeys && gd.pressedKeys[i] != inputToCheck) { i++; }
    return (i < gd.num_PressedKeys && gd.pressedKeys[i] == inputToCheck);
}

int main () {

    // Inizializzazione
    GameData gd;
    startUp(&gd);
    //Menu m_main, m_pause, m_options, m_credits, m_insertName;
    //HighscoreMenu m_score;
    //ConfirmMenu m_confirmExit, m_confirmExitPause;

    WINDOW *win = newwin(15,17,2,10);
    refresh();
        box(win,0,0);
        mvwprintw(win,0,1,"AAAAAA");
        mvwprintw(win,1,2,"prova");
        wrefresh(win);

            WINDOW *win2 = newwin(20,18,6,17);
    refresh();
        box(win2,0,0);
        mvwprintw(win2,0,1,"AAAAAA");
        mvwprintw(win2,1,2,"prova");
        wrefresh(win2);

    // Loop generale del gioco
    do {
        
        // SCHERMATA INIZIALE
        // Il menu principale
        getInput(&gd);
        //m_main.manageInput(gd);
//
        //if(checkInput(gd, KEY_ENTER)) {
        //    switch(m_main.getSelezione()) {
        //        case 1:
        //            // Play
        //        case 2:
        //            // Highscores
        //        case 3:
        //            // Options
        //        case 4:
        //            // Exit
        //    }
        //}
//
        //m_main.print();

    refresh();
    werase(win);
        wrefresh(win);
        wrefresh(win2);
        if (checkInput(gd, L'q'))
            gd.closeGame = true;
    } while (!gd.closeGame);

    endwin();
    return gd.status;
}