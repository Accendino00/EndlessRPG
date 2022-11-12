#include "../generale/libs.hpp"

Artefatto::Artefatto(int type){
    (*this).h_dimy = 1;
    (*this).h_dimx = 1;
    (*this).s_dimy = 1;
    (*this).s_dimx = 1;
    (*this).currentFrame = 0;
    
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];
    this->lastTick = gd->getCurrentTick();
    setcchar(&(this->stampabile[0][0]), L"N", A_NORMAL, PLAYER_COLOR_PAIR, NULL);

    this->ticksForAction = 250;

    this->currentLife = 1;
    this->maxLife = 1;


    if(type == AUMENTA_HP){
        setcchar(&(this->stampabile[0][0]), L"1", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    }
    else if(type == AUMENTA_ATTACCO){
        setcchar(&(this->stampabile[0][0]), L"2", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    }
    else if(type == ATTACCO_DIETRO ){
        setcchar(&(this->stampabile[0][0]), L"3", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    }
    else if(type == ATTACCO_DIAGONALE ){
        setcchar(&(this->stampabile[0][0]), L"4", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    }
    else if(type == AUMENTA_DIFESA){
        setcchar(&(this->stampabile[0][0]), L"5", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    }
    else if(type == AUMENTA_SPRINT){
        setcchar(&(this->stampabile[0][0]), L"6", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    }
    else if(type == CHIAVE){
        setcchar(&(this->stampabile[0][0]), L"7", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    }

}

int Artefatto::getIDArtefatto(){
    return this->idArtefatto;
}

void Artefatto::updateEntita(Player * player){
    this->Entita::updateEntita();

    
    };