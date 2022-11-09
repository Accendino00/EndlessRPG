#pragma once
#include "../generale/libs.hpp"

#define NUMERO_LIVELLI          2

#define DIM_MATRICE_LIVELLO_Y   5
#define DIM_MATRICE_LIVELLO_X   5

class Livello {
private:
    int matrice_numerica [DIM_MATRICE_LIVELLO_Y][DIM_MATRICE_LIVELLO_X];
    Stanza *** matrice_livello;
    int current_y;
    int current_x;

public:
    Livello();
    ~Livello();

    void scegli_lato(Stanza *** matrice_livello , int * x, int *y);
    void imposta_stanza();
    void stanza_corrente();
    void stampa(Player * player);
    bool cambia_stanza(int direzione);
    void calcolo_logica(Player * player);
    bool livello_successivo();
    bool Bossisdead();
    bool isBossstanza();

    int accessibile(int y_entity, int x_entity, bool giocatore);
    
    void aggiungiProiettile(Proiettile * proiettile);

    Stanza * getStanza();

    int offsetY();
    int offsetX();
};