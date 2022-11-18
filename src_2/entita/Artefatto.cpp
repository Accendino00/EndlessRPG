#include "../generale/libs.hpp"

Artefatto::Artefatto(int y, int x, int type) {
    (*this).h_dimy = 1;
    (*this).h_dimx = 1;
    (*this).s_dimy = 1;
    (*this).s_dimx = 1;
    (*this).currentFrame = 0;
    
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];
    this->lastTick = gd->getCurrentTick();

    setcchar(&(this->stampabile[0][0]), L"N", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);

    this->ticksForAction = 250;

    this->currentLife = 1;
    this->maxLife = 1;

    this->x = x;
    this->y = y;

    this->idArtefatto = type;


    if(type == TIPOART_AUMENTA_HP){
        setcchar(&(this->stampabile[0][0]), L"1", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }
    else if(type == TIPOART_AUMENTA_ATTACCO){
        setcchar(&(this->stampabile[0][0]), L"2", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }
    else if(type == TIPOART_ATTACCO_DIETRO ){
        setcchar(&(this->stampabile[0][0]), L"3", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }
    else if(type == TIPOART_ATTACCO_DIAGONALE ){
        setcchar(&(this->stampabile[0][0]), L"4", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }
    else if(type == TIPOART_AUMENTA_DIFESA){
        setcchar(&(this->stampabile[0][0]), L"5", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }
    else if(type == TIPOART_AUMENTA_SPRINT){
        setcchar(&(this->stampabile[0][0]), L"6", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }
    else if(type == TIPOART_CHIAVE){
        setcchar(&(this->stampabile[0][0]), L"7", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }

}

Artefatto::Artefatto(int type) : Artefatto(0,0,type) {}

int Artefatto::getIDArtefatto(){
    return this->idArtefatto;
}

void Artefatto::updateEntita(Player * player){
    this->Entita::updateEntita();
    if(this->passedActions >= 1 && this->currentLife > 0){
        // Fare cose, come cambiare il frame attuale
        this->nextFrame();
        if (player->controllaContatto(this)) {
            this->applicaEffetto(player);
        }
        this->passedActions--;
    }
};


void Artefatto::applicaEffetto(Player * player) {
    switch(this->idArtefatto) {
        case TIPOART_AUMENTA_HP:
            player->modificaVita((rand() % (player->getVita()-10))+10);
        break;
        case TIPOART_AUMENTA_ATTACCO:
            player->modificaDanno((rand() % (8))+3);
        break;               
        case TIPOART_ATTACCO_DIETRO:
            player->aggiungiDirezioneAttacco(DIRECTION_EE);
        break;
        case TIPOART_ATTACCO_DIAGONALE:
            player->aggiungiDirezioneAttacco(DIRECTION_SE);
        break;
        case TIPOART_AUMENTA_DIFESA:
            player->modificaDifesa((rand() % (10)+5));
        break;
        case TIPOART_AUMENTA_SPRINT:
            player->modificaSprint(2);
        break;
        case TIPOART_CHIAVE:
            player->setChiave(true);
        break;
    }
    this->currentLife = 0;
}