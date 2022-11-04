#include "../generale/libs.hpp"

Proiettile::Proiettile(int y, int x, bool playerProjectile, int direzione, int danno) {
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
    //this->muovi(this->direzione, 1);
    
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

    this->currentLife = 1;
    this->maxLife = 1;

    this->damage = danno;

    this->playerProjectile = playerProjectile;
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
    while (this->getVita() != 0 && this->passedActions > 0) {
        // Interazione con il giocatore
        this->muovi(this->direzione,1);
        if (!this->isPlayerProjectile()  && player->controllaContatto(this->getX(), this->getY(), this->getDimX(), this->getDimY())) {
            // Per danneggiare il giocatore, modifico la sua vita con il negativo del danno che fa il proiettile
            player->modificaVita(- (this->getDamage())); 
            this->setVita(0);
        } else {
            this->muovi(this->direzione,-1);
        }

        // Interazione con tutte le altre entità / la stanza
        switch(movimentoValido(this->direzione, 1, stanza, false)) {
            case STANZA_ACC_LIBERO:
                this->muovi(this->direzione,1);
                break;
            case STANZA_ACC_NEMICO:
                if (this->isPlayerProjectile()) {
                    stanza->dmgNemiciContactList(this->getDamage());
                }
                this->setVita(0);
                break;
            case STANZA_ACC_PORTA:
            case STANZA_ACC_MURO:
                this->setVita(0);
                break;
            default:
                this->setVita(0);
                break;
        }
        this->passedActions--;
    }
}

/**
 * @brief Ritorna vero se è un proiettile del giocatore
 * 
 * @return true     E' un proiettile del giocatore
 * @return false    E' un proiettile dei nemici
 */
bool Proiettile::isPlayerProjectile(){
    return this->playerProjectile;
}