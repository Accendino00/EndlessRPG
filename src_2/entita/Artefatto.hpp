#include "../generale/libs.hpp"

#define TIPOART_AUMENTA_HP                              1
#define TIPOART_AUMENTA_ATTACCO                         2
#define TIPOART_ATTACCO_DIETRO                          3
#define TIPOART_ATTACCO_DIAGONALE                       4
#define TIPOART_AUMENTA_DIFESA                          5
#define TIPOART_AUMENTA_SPRINT                          6
#define TIPOART_CHIAVE                                  7

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