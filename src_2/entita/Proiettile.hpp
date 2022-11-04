#pragma once
#include "../generale/libs.hpp"

class Proiettile : public Entita {
private:
    bool playerProjectile;
    int direzione;
public:
    Proiettile(int y, int x, bool playerProjectile, int direzione, int danno);
    void updateEntita(Stanza * stanza, Player * player);
    bool isPlayerProjectile();
};