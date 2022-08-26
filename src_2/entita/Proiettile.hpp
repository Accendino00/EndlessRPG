#pragma once
#include "../generale/libs.hpp"

class Proiettile : public Entita {
private:
    bool playerProjectile;
    int direzione;
public:
    Proiettile(int y, int x, bool playerProjectile, int direzione);
    void updateEntita(/*dati sulla mappa e sui nemici da controllare*/);
};