#pragma once
#include "../generale/libs.hpp"

class Livello {
    public:
    
    struct Stanza_boss{
        Entita * boss;
        Stanza battaglia_boss;
        Livello * livello_successivo;
    };

    struct Struttura_stanza{
        Stanza stanza_corrente;
        Stanza * nord;
        Stanza * sud;
        Stanza * est;
        Stanza * ovest;
    };

    Stanza *** stanze;

    public:
    void genera_livello();

    void stampa_livello();
};