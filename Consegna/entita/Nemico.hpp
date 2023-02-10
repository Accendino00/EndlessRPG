/**
 * @file Nemico.hpp
 * @author Petru Marcel Marincas
 * @date 2022
 * 
 * @brief 
 *    Contiene la classe Nemico, che estende la classe Entita.
 *    Un nemico è un'entità che si muove e spara, e che può essere
 *    sconfitto dal giocatore.
 * 
 *    Ci sono diversi tipi di nemici. 
 *    In particolare sono distinti in due macro categorie:
 *     - Nemici normali
 *     - Boss
 * 
 *    I primi sono più facili da battere, mentre i secondi sono
 *    più forti e, se sconfitti, si ottengono più punti e si batte
 *    il livello attuale.
 * 
 *    Le azioni dei nemici sono determinati da un array di azioni.
 *    Ogni azione è un numero intero, che viene generato facendo OR
 *    tra le varie definizioni di azioni, e che viene poi interpretato
 *    facendo AND. (OR e AND bit a bit)
 * 
 *    Per esempio, se un nemico ha l'azione "AZIONE_SPARA_GIOCATORE | AZIONE_SPARA_PRINCIPALE",
 *    allora il nemico spara al giocatore e usa il suo proiettile principale.
 * 
 * 
 *    Dopo che viene compiuta un azione, si passa alla prossima, fino a quando si sono
 *    fatte tutte le azioni e, a questo punto, si ricomincia dall'inizio.
 */
#pragma once
#include "../generale/libs.hpp"

#define NORMAL_ENEMY 4
#define BOSS_ENEMY 5

// Vedere in GameData i define delle direzioni

// Queste sono le definizioni per le varie azioni che i nemici possono compiere.
// Sono scritti sottoforma di bit, in modo da poter essere combinati tra loro
// usando delle OR bit a bit, in modo da poter compiere più azioni contemporaneamente.

#define AZIONE_PAUSA    0b10000000000000000000000000000000

#define AZIONE_SPARA_DIREZIONE                0b0100000000    
#define AZIONE_SPARA_GIOCATORE                0b1000000000
#define AZIONE_SPARA_SPUTAFUOCO               0b1100000000

#define AZIONE_SPARA_PRINCIPALE            0b0010000000000
#define AZIONE_SPARA_SECONDARIO            0b0100000000000
#define AZIONE_SPARA_TERZIARIO             0b1000000000000

#define MUOVI_DIREZIONE                  0b010000000000000
#define MUOVI_PATTERN                    0b100000000000000

#define FRAME_PROSSIMO                 0b01000000000000000
#define FRAME_ORIENTAZIONE             0b10000000000000000
#define FRAME_NEUTRO                   0b11000000000000000

class Nemico : public Entita {
private:
    // Contiene le azioni del nemico
    int numActions;
    int currentAction;
    int * actions;

    int patternDirezione; // Usata per nemici che si muovono in maniera ripetitiva

    int type; // BOSS_ENEMY o NORMAL_ENEMY
    char nome [30];

    int punti; // I punti che da al giocatore quando viene sconfitto

    // Diventa vero dopo che viene colpito una volta;
    bool mostraVita;
    // Serve per capire se è stato l'ultimo ad essere colpito
    int tickOfLastHit;

    double velocitaProiettile;

public:
    Nemico(int type, int posy, int posx, int tipoStanza, int numLivello);
    ~Nemico();

    void updateEntita(Stanza * stanza, Player * player);
    bool muoviNemico(int direzione, int val, Stanza * stanza, Player * player);
    void stampa(int offsetY, int offsetX);
    void stampaVita(int blocchi);

    int getType();
    bool isMostrabile();

    void sparaProiettile(int dir, int offset, Stanza * stanza);

    int getPunti();

    void modificaVita(int quantita);
    int getTickOfLastHit();
};