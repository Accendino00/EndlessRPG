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

        struct topologia{
            wchar_t ** stampabile; //matrice di widechar con attributi cchar_t
            int ** logica;         //matrice logica/numerica
        };

        WINDOW * schermata_mappa;  //prima window da stampare


    public:
        bool genera_stanza();

        void stampa_stanza();

        void creazione_porte();

        void coordinate();

        bool accessibile();
};

