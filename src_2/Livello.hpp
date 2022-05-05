#ifdef __linux__ 
    #include <ncurses.h>
#elif _WIN32
    #include <ncursesw/ncurses.h>
#else
    #error Errore di compilazione, sistema operativo non supportato
#endif

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include "libs.hpp"

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

    public:
    void genera_livello();

    void stampa_livello();
};