/**
 * @file GameData.hpp
 * @date 2022
 * @authors Petru Marcel Marincas
 * 
 * @brief
 *      Classe che contiene tutti i dati di gioco globali.
 * 
 *      Questa classe viene istanziata una sola volta, e viene passata usata
 *      come variabile globale in tutti i file che includono "generale/libs.hpp".
 * 
 *      Ha diverse funzionalità, tra cui:
 *         - Gestione degli input
 *         - Gestione dei ticks
 *         - Gestione dei FPS
 *         - Gestione dei settings
 * 
 *      Contiene anche dei dati utili per il gioco, come:
 *        - La dimensione del terminale
 *        - I tasti che vengono premuti
 *        - Lo stato del gioco
 * 
 *      Per più dettagli, vedere la documentazione di ogni funzione.
 *      Le documentazioni sono scritte nel .cpp
 */

#pragma once
#include "../generale/libs.hpp"


// Massimo numero di tasti che posso premere in un frame
#define MAX_TASTI_INSIEME 32

/* 
 * N vuol dire Nord (in alto), S vuol dire Sud (in basso), 
 * E vuol dire Est (a destra), O vuol dire Ovest (a sinistra) 
 *
 * Vengono definite così in modo da poter essere usate come maschere
 * e poter usare un bitshift per cambiare direzione in modo veloce
 */
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

    // Settings
    int FPSCap;
    int difficulty;
    bool showPerformance; 
    bool impostazioniSalvate;

    // Per gli FPS
    std::chrono::_V2::system_clock::time_point start, end;

    // Per i tick
    std::chrono::duration<double> timeForTick;
    std::chrono::_V2::system_clock::time_point last_clock;
    long long int currentTick;

public:
    GameData ();
    ~GameData ();

    void startUp();

    // Per gli input
    void getInput ();
    bool checkInput (int inputToCheck);
    int getKey(int index);
    int getNumOfPressedKeys();

    // Per i FPS
    void frameStart();
    void frameFinish();

    // Per la dimensione del terminale
    int getTerminalX();
    int getTerminalY();

    // Per lo stato del gioco
    void setCloseGame(bool closeGame);
    bool getCloseGame();

    void setStatus(int status);
    int getStatus();

    // Per i ticks
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

