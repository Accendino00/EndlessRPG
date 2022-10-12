#pragma once
#include "../generale/libs.hpp"

class Gioco {
private:
    Player * player;
    Livello * livello;
    
    bool gameOver;

public:
    Gioco();
    ~Gioco();

    void gameLoop();
};