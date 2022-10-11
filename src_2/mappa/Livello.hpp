#pragma once
#include "../generale/libs.hpp"

#define DIM_MATRICE_LIVELLO_Y 5
#define DIM_MATRICE_LIVELLO_X 5

class Livello {
public:
    Stanza *** matrice_livello;
    int current_y;
    int current_x;
    int matrice_numerica [DIM_MATRICE_LIVELLO_Y][DIM_MATRICE_LIVELLO_X];
    
    Livello();
    ~Livello();

    void scegli_lato(Stanza *** matrice_livello , int * x, int *y);
    void imposta_stanza();
    void stanza_corrente();
    void stampa(Player * player);
    bool cambia_stanza(int direzione);
    void calcolo_logica(Player * player);
    bool livello_successivo();

    int offsetY();
    int offsetX();
};