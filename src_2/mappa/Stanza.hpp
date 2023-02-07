#pragma once
#include "../generale/libs.hpp"

#define NUMERO_STANZE_NORMALI 5
#define NUMERO_STANZE_BOSS 1

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
private:
    int ** matrice_logica;
    cchar_t ** matrice_stampabile;
    ListaPorte * listaPorte;
    ListaProiettili * listaProiettili;
    ListaNemici * listaNemici;
    ListaArtefatti * listaArtefatti;

    int idStanza;

    int dim_y;
    int dim_x;

    bool esplorata;
    bool trovata;

public:
    Stanza(int id);
    ~Stanza();

    void stampa_stanza();
    void imposta_porte(bool nord, bool sud, bool est, bool ovest, int boss);
    void da_logica_a_stampabile(int numLivello);
    int accessibile(Entita * entita, bool giocatore);
    int direzione_porta(int y_entity, int x_entity);

    int zero_x();
    int zero_y();

    int getDimX();
    int getDimY();

    ListaProiettili * getListaProiettili();
    void aggiungiProiettile(Proiettile * proiettile);
    void aggiungiNemico (Nemico * nemico);
    void aggiungiArtefatto (Artefatto * artefatto);

    void calcolo_logica(Gioco * gioco);
    void aggiornaTick();

    void dmgNemiciContactList(Gioco * gioco, int quantita);
    int dmgDaProiettiliContactList(bool type);
    void cancellaProiettiliSovrapposti(Entita * entita, bool giocatore);

    void effettiArtefatti(Player * player);
    bool haArtefatto(int type);

    int getId();

    int getNumNemici();


    //getter e setter di esplorata e trovata
    bool getEsplorata();
    void setEsplorata(bool esplorata);
    bool getTrovata();
    void setTrovata(bool trovata);
    
};



