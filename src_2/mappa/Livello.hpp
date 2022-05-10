#pragma once
#include "../generale/libs.hpp"

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

    public:
    void genera_livello();
    
    void scegli_lato(Stanza *** matrice_livello , int * x, int *y);

    void stampa_livello();
};