#include "../generale/libs.hpp"


Porta::Porta(int type, int direzione, bool portaConChiave, int dimstanzay, int dimstanzax) {
    // Impostazione della dimensione in base alla posizione della porta
    if(direzione == PORTA_EST || direzione == PORTA_OVEST) {
        (*this).h_dimy = DIMENSIONE_PORTA_VERTICALE;
        (*this).h_dimx = 1;
        (*this).s_dimy = DIMENSIONE_PORTA_VERTICALE;
        (*this).s_dimx = 1;
    } else if (direzione == PORTA_NORD || direzione == PORTA_SUD) {
        (*this).h_dimy = 1;
        (*this).h_dimx = DIMENSIONE_PORTA_ORIZZONTALE;
        (*this).s_dimy = 1;
        (*this).s_dimx = DIMENSIONE_PORTA_ORIZZONTALE;    
    }


    (*this).stampabile = new cchar_t * [s_dimy];
    for(int i = 0; i < s_dimy; i++) {
        (*this).stampabile[i] = new cchar_t [s_dimx];
    }


    if (portaConChiave)
        for(int i = 0; i < s_dimy; i++)
            for(int j = 0; j < s_dimx; j++) 
                setcchar(&(this->stampabile[i][j]), L"/", A_NORMAL, DOOR_KEY_PAIR, NULL);
    else
        for(int i = 0; i < s_dimy; i++)
            for(int j = 0; j < s_dimx; j++) 
                setcchar(&(this->stampabile[i][j]), L"/", A_NORMAL, DOOR_PAIR, NULL);

    // Impostazione della posizione della porta in base al tipo di porta e alla sua direzione
    switch(direzione) {
        case PORTA_EST:
            this->x = dimstanzax-1;
            this->y = (dimstanzay - DIMENSIONE_PORTA_VERTICALE)/2;
        break;
        case PORTA_OVEST:
            this->x = 0;
            this->y = (dimstanzay - DIMENSIONE_PORTA_VERTICALE)/2;
        break;
        case PORTA_SUD:
            this->x = (dimstanzax - DIMENSIONE_PORTA_ORIZZONTALE)/2;
            this->y = dimstanzay-1;
        break;
        case PORTA_NORD:
            this->x = (dimstanzax - DIMENSIONE_PORTA_ORIZZONTALE)/2;
            this->y = 0;
        break;
    }

        
    // Setting di base degli attributi di entita (NON USATI) 
    this->currentFrame = 0;
    this->maxLife = 1;
    this->currentLife = 1;
    this->passedActions = 0;
    this->lastTick = gd->getCurrentTick();
    this->ticksForAction = 2000;
}

void Porta::updateEntita() {
    /*
    ANCORA DA CAPIRE SE VOGLIAMO FARCI QUALCOSA (ANIMAZIONI O ALTRO)
    this->Entita::updateEntita();
    while(this->passedActions > 0) {
        // do nothing
        this->passedActions--;
    }
    */
}