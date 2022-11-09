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

    void gameLoop();
};