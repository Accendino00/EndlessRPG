#pragma once
#include "../generale/libs.hpp"

#define MAX_TASTI_INSIEME 32


class GameData {
private:
    int terminalY, terminalX;   // La dimensione del terminale

    int num_PressedKeys;        // Il numero di input premuti in un determinato frame dall'utente
    int pressedKeys [MAX_TASTI_INSIEME]; // L'elenco degli input premuti nel frame dall'utente

    int status;                 // Assume i valori ERR o OK. Se ERR, il programma dovrebbe venire terminato.
    bool closeGame;             // Se true, allora il gioco deve venire chiuso

    // short max_colorId;       // L'id del colore massimo che ho creato
                                // Il massimo è la define: UINT_LEAST16_MAX

    // Settings
    short maxFPS;
    short difficulty;
    bool showPerformance; 


public:
    GameData ();
    ~GameData ();

    void startUp();
    void getInput ();
    bool checkInput (int inputToCheck);

    int getKey(int index);
    int getNumOfPressedKeys();

    int getTerminalX();
    int getTerminalY();

    void setCloseGame(bool closeGame);
    bool getCloseGame();

    void setStatus(int status);
    int getStatus();
};

