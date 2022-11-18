#pragma once
#include "../generale/libs.hpp"

class Gioco {
private:
    Player * player;
    Livello * livello_corrente;
    int livello_counter;

    bool gameOver;

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

    void gameLoop();
};