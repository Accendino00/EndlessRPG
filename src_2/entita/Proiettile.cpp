#include "../generale/libs.hpp"

Proiettile::Proiettile(int y, int x, bool playerProjectile, int direzione) {
    this->lastTick = gd->getCurrentTick();
    this->x = x;
    this->y = y;
    // Impostazione dell'hitbox e della dimensione dello stampabile. 
    // Inoltre i proiettili hanno 1 solo frame di stampa
    (*this).h_dimy = 1;
    (*this).h_dimx = 1;
    (*this).s_dimy = 1;
    (*this).s_dimx = 1;
    (*this).currentFrame = 0;

    this->direzione = direzione;
    this->passedActions = 0;
    this->muovi(this->direzione, 1);
    
    this->passedActions = 0;
    this->lastTick = gd->getCurrentTick();

    // Velocità diverse in base alla direzione nella quale viaggiano
    if(this->direzione == DIRECTION_NN || this->direzione == DIRECTION_SS) {
        this->ticksForAction = 50;  
    }
    else if(this->direzione == DIRECTION_EE || this->direzione == DIRECTION_OO) {
        this->ticksForAction = 20;  
    } else {
        this->ticksForAction = 60;
    }
    
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];

    short color = (playerProjectile) ? (PLAYER_BULLET_PAIR) : (ENEMY_BULLET_PAIR);
    switch(direzione) {
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

void Proiettile::updateEntita(Stanza * stanza, Player * player) {
    this->Entita::updateEntita();
    while (this->passedActions > 0) {
        if (movimentoValido(this->direzione, 1, stanza, false)) {
            this->muovi(this->direzione,1);
        }
        this->passedActions--;
    }
}