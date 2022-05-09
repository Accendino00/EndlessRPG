#pragma once
#include "../generale/libs.hpp"

class Gioco {
private:
    Player * player;

    Livello * livello;
    // Potrei avere come dato la posizione attuale qua dentro
    // Potrei averlo dentro a Livello

    //Entita * proiettili;

public:
    Gioco();
    
    void gameLoop();
};