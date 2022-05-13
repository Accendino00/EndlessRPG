#pragma once
#include "../generale/libs.hpp"

class Proiettile : public Entita {
private:
    bool playerProjectile;
    int direction;

public:

    Proiettile(int y, int x, bool playerProjectile, int direction);

    void updateProjectile(/*dati sulla mappa e sui nemici da controllare*/);

    void moveInDirection() ;
};