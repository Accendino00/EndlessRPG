/*

    Nemici:
        - Si muovono
            - In modo diverso da tipo a tipo
        - Sparano
            - Più o meno, in base al tipo
        - Possono cambiare forma
            - Per indicare che stanno per sparare
        - Hanno dimensione e immagini diverse




        - Per evitare di implementare nuove strutture dati, lo stampabile
        sarà contenuto nello stampabile, ma offsettato di una certa dimensione

        - La dimensione del nemico non cambierà dinamicamente, ma la sua forma sì,
        in quanto si potrà scegliere che parte stampare in base al tempo.

            - L'idea è un dato tipo:
                short FrameAttuale
            e nel for di stampabile, al x è j + (FrameAttuale*dim_x)

            Per implementare delle routine
            dovrei fare che ci sono delle cose che fa ogni n tick
            tipo 
            {spara, spara, spara, fermo, fermo, muovi, fermo, muovi, fermo} e poi quando 
            arriva alla fine ripete la routine
            quindi una serie di switch in base all'indice della cosa da fare adesso
            in base al nemico ogni cosa ha una cosa diversa

            ognuna di quelle cose è definita da dei define, tipo NEMICO_SPARA, NEMICO_FERMO, NEMICO_MUOVI, etc.

            Potrei far sì che ognuna di quelle cose sia una lista di cose che deve fare, tipo
            CAMBIA_ANIMAZIONE -> MUOVITI



            PER CAPIRE DOVE SPARARE:
                - Tra i due punti si forma un angolo, dove la distanza x è il
                raggio dell'angolo, l'altezza y è il valore della tangente dell'angolo
                
                - Per trovare l'angolo bisogna quindi fare arctan(y/x)

                In base all'angolo (se si trova in una di 3 sezioni per capire se in alto, diagonale, o di lato),
                e se la x di uno è maggiore dell'altro
                e se la y di uno è maggiore dell'altro
                si spara il proiettile
*/

#pragma once
#include "../generale/libs.hpp"

#define NORMAL_ENEMY 4
#define BOSS_ENEMY 5

// Vedere in GameData i define delle direzioni

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