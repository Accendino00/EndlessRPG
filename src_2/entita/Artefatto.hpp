#include "../generale/libs.hpp"

#define AUMENTA_HP                              1
#define AUMENTA_ATTACCO                         2
#define ATTACCO_DIETRO                          3
#define ATTACCO_DIAGONALE                       4
#define AUMENTA_DIFESA                          5
#define AUMENTA_SPRINT                          6
#define CHIAVE                                  7


class Artefatto : public Entita {
    private:
        int idArtefatto;
    public:
        Artefatto(int type);
        int getIDArtefatto();
        void updateEntita(Player * player);
};