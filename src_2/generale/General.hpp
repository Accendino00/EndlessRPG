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
    short FPSCap;
    short difficulty;
    bool showPerformance; 
    bool impostazioniSalvate;

    // for fps
    std::chrono::_V2::system_clock::time_point start, end;


public:
    GameData ();
    ~GameData ();

    void startUp();
    void getInput ();
    bool checkInput (int inputToCheck);

    void frameStart();
    void frameFinish();

    int getKey(int index);
    int getNumOfPressedKeys();

    int getTerminalX();
    int getTerminalY();

    void setCloseGame(bool closeGame);
    bool getCloseGame();

    void setStatus(int status);
    int getStatus();

    // Per i settings
    void salvaImpostazioni();
    void caricaImpostazioni();

    int getFPSCap();
    void cycleFPSCap(bool direction);

    const char * getShowPerformance();
    void cycleShowPerformance(bool direction);

    const char * getDifficulty();
    void cycleDifficulty(bool direction);

    const char * getImpostazioniSalvate();
};

