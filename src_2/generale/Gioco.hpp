#pragma once
#include "../generale/libs.hpp"

class Gioco {
private:
    Player * player;

    Livello * livello;

    ListaEntita proiettili;
    ListaEntita nemici;
    ListaEntita porte;
    ListaEntita artefatti;
    
    bool gameOver;
public:
    Gioco();
    ~Gioco();

    void gameLoop();
};