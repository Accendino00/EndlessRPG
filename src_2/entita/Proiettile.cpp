#include "../generale/libs.hpp"

Proiettile::Proiettile(int y, int x, bool playerProjectile, int direction) {
    this->lastTick = gd->getCurrentTick();
    this->x = x;
    this->y = y;
    this->dim_x = 1;
    this->dim_y = 1;
    this->direction = direction;
    this->moveInDirection();
    
    if(this->direction == DIRECTION_UP || this->direction == DIRECTION_DOWN) {
        this->ticksForAction = 6;  
    }
    else if(this->direction == DIRECTION_RIGHT || this->direction == DIRECTION_LEFT) {
        this->ticksForAction = 3;  
    }
    
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

void Proiettile::updateProjectile(/*dati sulla mappa e sui nemici da controllare*/) {
    this->updateTicks();
    while (this->passedActions > 0) {
        this->moveInDirection();
        this->passedActions--;
    }
}

void Proiettile::moveInDirection() {
    switch(this->direction) {
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
            this->incrementaX(-1);
            break;
    }
}