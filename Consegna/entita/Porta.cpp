#include "../generale/libs.hpp"

/**
 * @brief Costruttore della classe Porta.
 * 
 * @param direzione         La direzione della stanza dove costruirla.
 *                          Può essere PORTA_NORD, PORTA_SUD, PORTA_EST, PORTA_OVEST.
 * @param portaConChiave    Se la porta è con chiave o meno. Cambia il suo colore e il suo funzionamento.
 * @param dimstanzay        La dimensione della stanza in cui si trova la porta.
 * @param dimstanzax        La dimensione della stanza in cui si trova la porta.
 */
Porta::Porta(int direzione, bool portaConChiave, int dimstanzay, int dimstanzax) {
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

    // Se la porta è con chiave, allora ha un colore diverso
    this->portaConChiave = portaConChiave;
    if (portaConChiave)
        for(int i = 0; i < s_dimy; i++)
            for(int j = 0; j < s_dimx; j++) 
                setcchar(&(this->stampabile[i][j]), L"X", A_NORMAL, DOOR_KEY_PAIR, NULL);
    else
        for(int i = 0; i < s_dimy; i++)
            for(int j = 0; j < s_dimx; j++) 
                setcchar(&(this->stampabile[i][j]), L"X", A_NORMAL, DOOR_PAIR, NULL);


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
    this->maxVita = 1;
    this->vita = 1;
    this->passedActions = 0;
    this->lastTick = gd->getCurrentTick();
    this->ticksForAction = 2000; 
}

void Porta::updateEntita() {
    // Ovverride vuoto, in quanto non dovrei aggiornare i suoi tick, come invece
    // le entità normali fanno.
}

bool Porta::isPortaConChiave() {
    return this->portaConChiave;
}