#pragma once
#include "../generale/libs.hpp"

#define DIM_STANZA_X 50
#define DIM_STANZA_Y 30
#define DIM_STANZA_BOSS_X 50
#define DIM_STANZA_BOSS_Y 30
#define DIMENSIONE_PORTA 5
#define DIMENSIONE_PORTA_ORIZZONTALE 10
#define ALTEZZA_STANZA 30
#define LARGHEZZA_STANZA 50
#define PORTA_NORD  0
#define PORTA_SUD   1
#define PORTA_EST   2
#define PORTA_OVEST 3

#define ID_STANZA_SPAWN 0
#define ID_STANZA_NORMALE 1
#define ID_STANZA_BOSS 2

class Stanza {
    /*
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

            
        Entita * porte;

        Entita * artefatti; //pick me up soon

        //volendo potrei fare una struct            
        cchar_t ** matrice_stampabile; //matrice di widechar con attributi 
        int ** matrice_logica;         //matrice logica/numerica
        

        WINDOW * schermata_mappa;  //prima window da stampare
        
        int x, y, maxx, maxy;

    public:
        Stanza(int tipoStanza);
        Stanza(Entita * nemici, Entita * porte, Entita * artefatti, WINDOW * schermata_mappa, cchar_t ** matrice_stampabile, int ** matrice_logica, int x, int y, int maxx, int maxy);
        
        cchar_t ** da_logica_a_stampabile(int ** matrice_stanza);

        void stampa_stanza(WINDOW * window_one, cchar_t ** mappa_stampabile, int offset_y, int offset_x);

        void creazione_porte();

        bool accessibile(int ** mappa, int x, int y);
        
        int ** Stanza::scegli_stanza();
        
        bool Stanza::lettura_matrice(int ** mappa);
        */
       public:
        int ** matrice_logica;
        cchar_t ** matrice_stampabile;
        Entita * porte [4];
        void stampa_stanza();
        Stanza(int id);
        void imposta_porte(bool nord, bool sud, bool est, bool ovest);
        void da_logica_a_stampabile();
        int dim_y;
        int dim_x;
        bool accessibile(int y_entity, int x_entity);
        int zero_x();
        int zero_y();
        int direzione_porta(int y_entity, int x_entity);
       };



