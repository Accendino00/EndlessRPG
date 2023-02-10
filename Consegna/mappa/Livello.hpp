/**
 * @file Livello.hpp
 * @author Davide Donati
 * @date 2022
 * 
 * @brief 
 *  Classe del livello, ovvero di un insieme di 5x5 stanze.
 *  Per richiedere informazioni delle stanze, bisogna passare
 *  attraverso questa classe.
 * 
 *  La matrice_numerica è quella letta dal file di testo, mentre
 *  La matrice matrice_livello è quella contente tutte le varie stanze.
 * 
 *  La current_y e current_x indicano in quale stanza ci si trova.
 */

#pragma once
#include "../generale/libs.hpp"

// Define del numero di livelli che possiamo scegliere casualmente
#define NUMERO_LIVELLI          7

#define DIM_MATRICE_LIVELLO_Y   5
#define DIM_MATRICE_LIVELLO_X   5

class Livello {
private:
    int matrice_numerica [DIM_MATRICE_LIVELLO_Y][DIM_MATRICE_LIVELLO_X];
    Stanza *** matrice_livello;
    int current_y;
    int current_x;

    int numLivello;

public:
    Livello();
    Livello(int numLivello);
    ~Livello();

    void scegli_lato(Stanza *** matrice_livello , int * x, int *y);
    void imposta_stanza();
    void stanza_corrente();
    void stampa();
    bool cambia_stanza(int direzione);
    void calcolo_logica(Gioco * player);
    
    bool livello_successivo();

    bool Bossisdead();
    bool isBossstanza();
    
    void aggiungiProiettile(Proiettile * proiettile);

    Stanza * getStanza();

    int offsetY();
    int offsetX();

    int getNumNemici();

    void stampaMinimappa();

    bool haArtefatto(int type);

    // Getter e setter di numLivello
    int getNumLivello();
    void setNumLivello(int numLivello);

    void esploraStanza(int y, int x);

    void aggiornaTick();
};