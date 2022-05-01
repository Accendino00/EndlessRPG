#include "Entita.hpp"
#include "General.hpp"

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

    // Queste possono anche diventare un'unica struttura dati
    cchar_t ** mappa_stampa;
    int ** mappa_logica;


public:
    bool generaStanza();

};