#include "../generale/libs.hpp"

/**
 * @file Artefatto.hpp
 * @author Giuseppe Forciniti
 * @date 2022
 * 
 * @brief Classe Artefatto che gestisce gli Artefatti.
 * Gli Artefatti sono Entità che possono essere prese dal giocatore che
 * riceve dei potenziamenti.
 * 
 * Ci sono vari tipi di Artefatto e vengono generati in modo casuale alla
 * morte di un Nemico. Ogni Artefatto è riconoscibile per la diversa icona,
 * e il suo effetto è mostrato nella HUD stampata nella classe Player.
 *
 * I potenziamenti degli Artefatti influiscono direttamente sui parametri
 * del Player.
 *
 *
 * 
 */

#define TIPOART_AUMENTA_HP                              1
#define TIPOART_AUMENTA_ATTACCO                         2
#define TIPOART_ATTACCO_DIETRO                          3
#define TIPOART_ATTACCO_DIAGONALE                       4
#define TIPOART_AUMENTA_DIFESA                          5
#define TIPOART_AUMENTA_SPRINT                          6
#define TIPOART_CHIAVE                                  7
#define TIPOART_VEL_PROIETTILI                          8
#define TIPOART_ATTACCO_SHOTGUN                         9
#define TIPOART_AUMENTA_MAX_HP                          10

#define TIPOART_MAX                                     7


class Artefatto : public Entita {
    private:
        int idArtefatto;
    public:
        Artefatto(int y, int x, int type, int tipoStanza);
        int getIDArtefatto();
        void updateEntita(Player * player);
        void applicaEffetto(Player * player);
};