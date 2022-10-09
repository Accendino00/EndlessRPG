#pragma once
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


    if(type == AUMENTA_HP){
        
    }
    else if(type == AUMENTA_ATTACCO){

    }
    else if(type == ATTACCO_DIETRO ){
        
    }
    else if(type == ATTACCO_DIAGONALE ){
        
    }
    else if(type == AUMENTA_DIFESA){
        
    }
    else if(type == AUMENTA_SPRINT){
        
    }
    else if(type == CHIAVE){

    }

}