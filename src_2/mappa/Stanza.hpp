#pragma once
#include "../generale/libs.hpp"

#define NUMERO_STANZE_NORMALI 2
#define NUMERO_STANZE_BOSS 1


#define DIM_STANZA_X 50
#define DIM_STANZA_Y 30
#define DIM_STANZA_BOSS_X 50
#define DIM_STANZA_BOSS_Y 30
#define DIM_STANZA_SPAWN_X 50
#define DIM_STANZA_SPAWN_Y 30

#define ID_STANZA_SPAWN 0
#define ID_STANZA_NORMALE 1
#define ID_STANZA_BOSS 2

#define STANZA_SPAZIOLIBERO 0
#define STANZA_MURO 1
#define STANZA_NEMICONORMALE 4
#define STANZA_NEMICOBOSS 5

#define STANZA_ACC_LIBERO 0
#define STANZA_ACC_MURO 1 // si intende muro, fuori bound, direzione porta valido se si e' un giocatore
#define STANZA_ACC_NEMICO 2
#define STANZA_ACC_PORTA 3
#define STANZA_ACC_ARTEFATTO 4
#define STANZA_ACC_PROIETTILE_GIOCATORE 5
#define STANZA_ACC_PROIETTILE_NEMICO 6

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
        ListaPorte * listaPorte;
        ListaProiettili * listaProiettili;
        ListaNemici * listaNemici;

        int idStanza;

        int dim_y;
        int dim_x;

        Stanza(int id);
        ~Stanza();

        void stampa_stanza();
        void imposta_porte(bool nord, bool sud, bool est, bool ovest);
        void da_logica_a_stampabile();
        int accessibile(int y_entity, int x_entity, bool giocatore);
        int direzione_porta(int y_entity, int x_entity);

        int zero_x();
        int zero_y();

        int getDimX();
        int getDimY();

        ListaProiettili * getListaProiettili();
        void aggiungiProiettile(Proiettile * proiettile);
        void aggiungiNemico (Nemico * nemico);

        void calcolo_logica(Player * player);
        void aggiornaTick();
};



