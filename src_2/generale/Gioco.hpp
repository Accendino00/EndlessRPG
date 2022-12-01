#pragma once
#include "../generale/libs.hpp"

class Gioco {
private:
    Player * player;
    Livello * livello_corrente;
    int livello_counter;
    bool gameOver;

    cchar_t consoleEventi [10][64];

public:
    Gioco();
    ~Gioco();

    Player * getPlayer();
    Livello * getLivello();
    int getLivelloCounter();

    void setPlayer(Player * player);
    void setLivello(Livello * livello);
    void setLivelloCounter(int livello_counter);

    void spawnArtefatto(int y, int x);

    void cambialivello();
    void gameLoop();

    void printConsoleEventi();
    void addConsoleEventi(const char * text, int id);
};