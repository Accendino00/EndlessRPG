#include "../generale/libs.hpp"

Nemico::Nemico (int type) {

    // Impostazione dell'hitbox e della dimensione dello stampabile. 
    // Inoltre il giocatore ha 1 solo frame di stampa
    (*this).h_dimy = 1;
    (*this).h_dimx = 1;
    (*this).s_dimy = 1;
    (*this).s_dimx = 1;
    (*this).currentFrame = 0;

    this->maxLife=100;
    this->currentLife = this->maxLife;
	
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];
   
    setcchar(&(this->stampabile[0][0]), L"N", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    
    this->y = 20;
    this->x = 20;

    this->ticksForAction = 500;
    this->currentAction = 0;
    this->numActions = 4;
    this->actions = new int[4];
    actions[0] = MUOVI_DIREZIONE | DIRECTION_EE;
    actions[1] = MUOVI_DIREZIONE | DIRECTION_NN;
    actions[2] = MUOVI_DIREZIONE | DIRECTION_OO;
    actions[3] = MUOVI_DIREZIONE | DIRECTION_SS;


    /*if(type == NORMAL_ENEMY) {
        int idNemico = ( rand() % 5 );
        switch(idNemico) {
            case 0:

            break;
            case 1:

            break;
            case 2:

            break;
            case 3:

            break;
            case 4:

            break;
        }
    } else if (type == BOSS_ENEMY) {
        int idNemico = ( rand() % 3 );
        switch(idNemico) {
            case 0:

            break;
            case 1:

            break;
            case 2:

            break;
        }
    }*/
}

void Nemico::updateNemico(Player * player /*e altri dati sulla mappa e sui nemici da controllare*/) {
    this->updateTicks();
    while (this->passedActions > 0) {
        int azione = this->actions[this->currentAction];
        // Gestione del movimento con direzione
        if( (azione & MUOVI_DIREZIONE) == MUOVI_DIREZIONE ) {
            switch(azione & DIRECTION_MASK) {
                case DIRECTION_EE:
                    this->incrementaX(1);
                break;
                case DIRECTION_OO:
                    this->incrementaX(-1);
                break;
                case DIRECTION_NN:
                    this->incrementaY(-1);
                break;
                case DIRECTION_SS:
                    this->incrementaY(1);
                break;
            }
        }

        // Gestione del movimento pattern 
        else if( (azione & MUOVI_PATTERN) == MUOVI_PATTERN ) {
            switch(patternDirezione) {
                case DIRECTION_EE:
                    // if can't move, change direction
                    this->incrementaX(1);
                break;
                case DIRECTION_OO:
                    this->incrementaX(-1);
                break;
                case DIRECTION_NN:
                    this->incrementaY(-1);
                break;
                case DIRECTION_SS:
                    this->incrementaY(1);
                break;
            }
        }
        this->currentAction = (this->currentAction + 1) % this->numActions;
        this->passedActions--;
    }
}
