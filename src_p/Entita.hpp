/**
 * @file Entita.hpp
 * @author Petru Marcel Marincas
 * @brief Super-classe per il presonaggio, i nemici, i proiettili e le altre entità del gioco
 * @version 0.1
 * @date 2022-02-07
 */


#pragma once

#ifdef __linux__ 
    #include <ncurses.h>
#elif _WIN32
    #include <ncursesw/ncurses.h>
#else
    #error Errore di compilazione, sistema operativo non supportato
#endif

#include <iostream>
#include "General.hpp"

class Entita {
public:
    // Coordinate
    int x, y;
    // Dimensioni hitbox
    int dim_x, dim_y;
    // Matrice che contiene il contenuto da stampare per rappresentare l'entità
    cchar_t ** entita_stampabile;

    int attr;   // Posso fare | tra gli attributi che voglio e salvarli come int
    int ** attr_arr;

public:
    Entita(int x,int y, int dim_x, int dim_y, int attr, cchar_t ** stampa, int ** attr_arr);
    ~Entita();

    void stampa(WINDOW * window, int offsetX, int offsetY);
    
    bool controllaContatto(Entita * entita);

    void modificaCoordinate(int new_x, int new_y);
    void incrementaX(int amount);
    void incrementaY(int amount);

    void incrementaX_CC(Entita * arrayEntita, /*Mappa, */ int amount);
    void incrementaY_CC(Entita * arrayEntita, /*Mappa, */ int amount);
};