#include "Entita.hpp"
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


class Stanza {
    public:
        Entita * nemici; 
            /*
                Questa in realtà è una struttura dati del tipo
                NemiciStanza * s_nemici
                    {
                        Nemico * nemico
                        Proiettile * proiettili
                    }

                I nemici si possono muovere e a intervalli regolari sparano
                Proiettili è una struttura dati che contiene proiettili

            */ 
        Entita * porte;

        Entita * artefatti; //pick me up soon

        //volendo potrei fare una struct            
        cchar_t ** matrice_stampabile; //matrice di widechar con attributi 
        int ** matrice_logica;         //matrice logica/numerica
        

        WINDOW * schermata_mappa;  //prima window da stampare
        
        int x, y, maxx, maxy;

    public:
        Stanza(Entita * nemici, Entita * porte, Entita * artefatti, WINDOW * schermata_mappa, cchar_t ** matrice_stampabile, int ** matrice_logica, int x, int y, int maxx, int maxy);
        
        cchar_t ** genera_stanza(int ** matrice_stanza);

        void stampa_stanza();

        void creazione_porte();

        bool accessibile(int ** mappa, int x, int y);
};

