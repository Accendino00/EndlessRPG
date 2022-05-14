#include "../generale/libs.hpp"

Proiettile::Proiettile(int y, int x, bool playerProjectile, int direction) {
    this->lastTick = gd->getCurrentTick();
    this->x = x;
    this->y = y;
    this->dim_x = 1;
    this->dim_y = 1;
    this->direction = direction;
    this->moveInDirection();
    
    if(this->direction == DIRECTION_NN || this->direction == DIRECTION_SS) {
        this->ticksForAction = 40;  
    }
    else if(this->direction == DIRECTION_EE || this->direction == DIRECTION_OO) {
        this->ticksForAction = 20;  
    } else {
        this->ticksForAction = 50;
    }
    
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];

    short color = (playerProjectile) ? (PLAYER_BULLET_PAIR) : (ENEMY_BULLET_PAIR);
    switch(direction) {
        case DIRECTION_NN:
            setcchar(&(this->stampabile[0][0]), L"\u21D1", A_NORMAL, color, NULL);
            break;
        case DIRECTION_SS:
            setcchar(&(this->stampabile[0][0]), L"\u21D3", A_NORMAL, color, NULL);
            break;
        case DIRECTION_EE:
            setcchar(&(this->stampabile[0][0]), L"\u21D2", A_NORMAL, color, NULL);
            break;
        case DIRECTION_OO:
            setcchar(&(this->stampabile[0][0]), L"\u21D0", A_NORMAL, color, NULL);
            break;
        case DIRECTION_NE:
            setcchar(&(this->stampabile[0][0]), L"\u21D7", A_NORMAL, color, NULL);
            break;
        case DIRECTION_SE:
            setcchar(&(this->stampabile[0][0]), L"\u21D8", A_NORMAL, color, NULL);
            break;
        case DIRECTION_SO:
            setcchar(&(this->stampabile[0][0]), L"\u21D9", A_NORMAL, color, NULL);
            break;
        case DIRECTION_NO:
            setcchar(&(this->stampabile[0][0]), L"\u21D6", A_NORMAL, color, NULL);
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
        case DIRECTION_NN:
            this->incrementaY(1);
            break;
        case DIRECTION_SS:
            this->incrementaY(-1);
            break;
        case DIRECTION_EE:
            this->incrementaX(1);
            break;
        case DIRECTION_OO:
            this->incrementaX(-1);
            break;
        case DIRECTION_NE:
            this->incrementaY(1);
            this->incrementaX(1);
            break;
        case DIRECTION_SE:
            this->incrementaY(-1);
            this->incrementaX(1);
            break;
        case DIRECTION_SO:
            this->incrementaY(-1);
            this->incrementaX(-1);
            break;
        case DIRECTION_NO:
            this->incrementaY(1);
            this->incrementaX(-1);
            break;
    }
}