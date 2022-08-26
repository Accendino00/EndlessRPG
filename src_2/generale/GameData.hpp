#pragma once
#include "../generale/libs.hpp"

// Tasti che possono premere insieme 
#define MAX_TASTI_INSIEME 32

// N vuol dire Nord (in alto), S vuol dire Sud (in basso), 
// E vuol dire Est (a destra), O vuol dire Ovest (a sinistra) 
#define DIRECTION_NN    0b00000001
#define DIRECTION_NE    0b00000010
#define DIRECTION_EE    0b00000100
#define DIRECTION_SE    0b00001000
#define DIRECTION_SS    0b00010000
#define DIRECTION_SO    0b00100000
#define DIRECTION_OO    0b01000000
#define DIRECTION_NO    0b10000000


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

    // Livello attuale
    int numLivello;

    // Score attuale
    int score;

    // for fps
    std::chrono::_V2::system_clock::time_point start, end;

    // for logic ticks
    std::chrono::duration<double> timeForTick;
    std::chrono::_V2::system_clock::time_point last_clock;
    long long int currentTick;

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

    void incNumLivello();
    int getNumLivello();

    void changeScore(int amount);
    int getScore();

    void manageTicks();
    long long int getCurrentTick();
    void resetTicks();

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

