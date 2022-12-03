#include "../generale/libs.hpp"

Artefatto::Artefatto(int y, int x, int type, int tipoStanza) {
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

    this->vita = 1;
    this->maxVita = 1;

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
    else if(type == TIPOART_ATTACCO_SHOTGUN){
        setcchar(&(this->stampabile[0][0]), L"9", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }
    else if(type == TIPOART_VEL_PROIETTILI){
        setcchar(&(this->stampabile[0][0]), L"8", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }
    else if(type == TIPOART_AUMENTA_MAX_HP){
        setcchar(&(this->stampabile[0][0]), L"A", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    }

}

int Artefatto::getIDArtefatto(){
    return this->idArtefatto;
}

void Artefatto::updateEntita(Player * player){
    this->Entita::updateEntita();
    if(this->passedActions >= 1 && this->vita > 0){
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
            player->modificaVita((rand() % (player->getMaxVita()-10))+10); // La cura avviene tra 10 e maxVita
        break;
        case TIPOART_AUMENTA_ATTACCO:
            player->modificaDanno((rand() % (5))+5); // Il danno aumenta da 5 a 10
        break;               
        case TIPOART_ATTACCO_DIETRO:
            player->aggiungiDirezioneAttacco(TIPOART_ATTACCO_DIETRO);
        break;
        case TIPOART_ATTACCO_DIAGONALE:
            player->aggiungiDirezioneAttacco(TIPOART_ATTACCO_DIAGONALE);
        break;
        case TIPOART_AUMENTA_DIFESA:
            player->modificaDifesa((rand() % (10)+5)); // La difesa aumenta da 5 a 15
        break;
        case TIPOART_AUMENTA_SPRINT:
            player->modificaSprint(2);
        break;
        case TIPOART_CHIAVE:
            player->setChiave(true);
        break;
        case TIPOART_VEL_PROIETTILI:
            player->modificaVelProiettile(0.5);
        break;
        case TIPOART_ATTACCO_SHOTGUN:
            player->aggiungiDirezioneAttacco(TIPOART_ATTACCO_SHOTGUN);
        break;
        case TIPOART_AUMENTA_MAX_HP:
            player->modificaMaxVita(10);
        break;
    }
    this->vita = 0;
}