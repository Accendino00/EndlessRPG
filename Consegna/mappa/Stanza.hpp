/**
 * @file Stanza.hpp
 * @author Davide Donati
 * @date 2022
 * 
 * @brief 
 *  Classe della stanza.
 * 
 *  Una stanza ha un insieme di attributi che sono:
 *  - matrice_logica: matrice che rappresenta la stanza in termini di logica.
 *                    Ovvero è una matrice di interi dove ogni intero rappresenta 
 *                    un elemento specifico in un posto specifico nella stanza.
 *  - matrice_stampabile: matrice che rappresenta la stanza dal punto di vista grafico
 *  - listaPorte: lista delle porte che si trovano nella stanza
 *  - listaProiettili: lista dei proiettili che si trovano nella stanza
 *  - listaNemici: lista dei nemici che si trovano nella stanza
 *  - listaArtefatti: lista degli artefatti che si trovano nella stanza
 *  
 *  - idStanza: id della stanza (ovvero ID_STANZA_SPAWN, ID_STANZA_NORMALE, ID_STANZA_BOSS)
 *  - dim_x, dim_y: dimensioni della stanza
 *  - esplorata e trovata: indicano se la stanza è stata esplorata (ovvero ci sono entrato)
 *                         e/o se è stata trovata (è adiacente ad una stanza che ho esplorato)
 * 
 * 
 *  Il suo funzionamento per l'inizializzazione è il seguente:
 *   1. Leggo la stanza in modo casuale da un file, e la imposto in base ai numeri che sto leggendo.
 *   2. Interpreto la matrice logica e creo gli oggetti che ci sono dentro (aggiungo i nemici).
 *      Alla fine di questo passaggio, la mia matrice logica sarà formata solo da 0 (libero) e 1 (muro).
 *   3. Creo la matrice stampabile, in base alla matrice logica.
 *   
 *  Dal livello, mi scelgo le porte che voglio generare, e le imposto nella stanza.
 *  Alla fine, la stanza è pronta per essere esplorata.
 * 
 *  Durante il loop di gioco, nella stanza nella quale mi trovo devo chiamare il metodo
 *  calcolo_logica() per far si che gli elementi all'interno della stanza (nemici, proiettili
 *  sparati, etc.) vengano aggiornati correttamente.
 */

#pragma once
#include "../generale/libs.hpp"

// Numero di stanze normali e di stanze boss che posso scegliere casualmente
#define NUMERO_STANZE_NORMALI 10
#define NUMERO_STANZE_BOSS 3

// Dimensioni della stanza di spawn, utili allo spawn del giocatore
#define DIM_STANZA_SPAWN_X 50
#define DIM_STANZA_SPAWN_Y 30

// Id delle varie tipologie di stanze
#define ID_STANZA_SPAWN 0
#define ID_STANZA_NORMALE 1
#define ID_STANZA_BOSS 2

// Id di quello che posso trovare nel file della stanza e che devo interpretare 
#define STANZA_SPAZIOLIBERO 0
#define STANZA_MURO 1
#define STANZA_NEMICONORMALE 4
#define STANZA_NEMICOBOSS 5

// Valori di ritorno per la funzione di accesso
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



