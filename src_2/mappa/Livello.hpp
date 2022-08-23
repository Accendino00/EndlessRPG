#pragma once
#include "../generale/libs.hpp"

#define DIM_MATRICE_LIVELLO_Y 5
#define DIM_MATRICE_LIVELLO_X 5

class Livello {
    public:
    
    /*
    struct Stanza_boss{
        Entita * boss;
        Stanza battaglia_boss;
        Livello * livello_successivo;
    };
    
    */
    Stanza *** matrice_livello;
    // Dovrebbe anche esserci "stanza attuale", che dovrebbero essere delle cooridnate x e y che indicano il punto della matrice dove si trovano
    Livello();
    void scegli_lato(Stanza *** matrice_livello , int * x, int *y);
    void crea_porte();
    void stanza_corrente();
    /*
    public:
    Livello();

    void genera_livello();
    
    void scegli_lato(Stanza *** matrice_livello , int * x, int *y);

    void stampa_livello();
    */
};