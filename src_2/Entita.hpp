#pragma once
#include "libs.hpp"

class Entita {
public:
    // Coordinate
    int x, y;
    // Dimensioni hitbox
    int dim_x, dim_y;
    // Matrice che contiene il contenuto da stampare per rappresentare l'entità
    cchar_t ** stampabile;

public:
    Entita(int y,int x, int dim_y, int dim_x, cchar_t ** stampa);
    ~Entita();

    void stampa(WINDOW * window, int offsetY, int offsetX);
    
    bool controllaContatto(Entita * entita);

    void modificaCoordinate(int new_y, int new_x);
    void incrementaX(int amount);
    void incrementaY(int amount);
};