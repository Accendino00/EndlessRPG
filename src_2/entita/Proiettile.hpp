#pragma once
#include "../generale/libs.hpp"

class Proiettile : public Entita {
private:
    bool playerProjectile;
    int direction;

    long int lastTick;
    long int ticksBeforeAction;

public:

    Proiettile(int x, int y, bool playerProjectile, int direction) {
        this->lastTick = gd->currentTick;
        this->x = x;
        this->y = y;
        this->direction = direction;
        this->moveInDirection();

        this->stampabile = new cchar_t * [1];
        this->stampabile[0] = new cchar_t [1];
    
        short color = (playerProjectile) ? (PLAYER_BULLET_PAIR) : (ENEMY_BULLET_PAIR);
        switch(direction) {
            case DIRECTION_UP:
                setcchar(&(this->stampabile[0][0]), L"\u25B2", A_NORMAL, color, NULL);
                break;
            case DIRECTION_DOWN:
                setcchar(&(this->stampabile[0][0]), L"\u25BC", A_NORMAL, color, NULL);
                break;
            case DIRECTION_RIGHT:
                setcchar(&(this->stampabile[0][0]), L"\u25B6", A_NORMAL, color, NULL);
                break;
            case DIRECTION_LEFT:
                setcchar(&(this->stampabile[0][0]), L"\u25C0", A_NORMAL, color, NULL);
                break;
        }
    }

    void updateProjectile(/*dati sulla mappa e sui nemici da controllare*/) {
        if((gd->currentTick - this->lastTick) >= ticksBeforeAction) {
            this->lastTick = gd->currentTick;
            moveInDirection();
        }
    }

    void moveInDirection(int direction) {
        switch(direction) {
            case DIRECTION_UP:
                this->incrementaY(1);
                break;
            case DIRECTION_DOWN:
                this->incrementaY(-1);
                break;
            case DIRECTION_RIGHT:
                this->incrementaX(1);
                break;
            case DIRECTION_LEFT:
                this->incrementaX(1);
                break;
        }
    }
};