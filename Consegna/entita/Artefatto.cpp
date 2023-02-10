#include "../generale/libs.hpp"

/**
 * @brief Construct a new Artefatto:: Artefatto object
 * 
 * @param y Posizione Y dell'artefatto.
 * @param x Posizione X dell'artefatto.
 * @param type Tipo dell'artefatto
 * @param tipoStanza Cambia il colore degli artefatti a seconda della stanza
 */

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

    short color = 0;

    switch(tipoStanza){
        case ID_STANZA_SPAWN:
            switch (type) {
                case TIPOART_AUMENTA_HP:
                    color = ARTEFATTO_CUORE_PAIR_E;
                    break;
                case TIPOART_AUMENTA_ATTACCO:
                case TIPOART_AUMENTA_DIFESA:
                case TIPOART_AUMENTA_MAX_HP:
                    color = ARTEFATTO_STATISTICHE_PAIR_E;
                    break;
                case TIPOART_AUMENTA_SPRINT:
                case TIPOART_ATTACCO_DIETRO:
                case TIPOART_ATTACCO_DIAGONALE:
                case TIPOART_ATTACCO_SHOTGUN:
                case TIPOART_VEL_PROIETTILI:
                    color = ARTEFATTO_POTENZIAMENTO_PAIR_E;
                    break;
                case TIPOART_CHIAVE:
                    color = ARTEFATTO_CHIAVE_PAIR_E;
                    break;
            }
        break;
        case ID_STANZA_NORMALE:
            switch (type) {
                case TIPOART_AUMENTA_HP:
                    color = ARTEFATTO_CUORE_PAIR_N;
                    break;
                case TIPOART_AUMENTA_ATTACCO:
                case TIPOART_AUMENTA_DIFESA:
                case TIPOART_AUMENTA_MAX_HP:
                    color = ARTEFATTO_STATISTICHE_PAIR_N;
                    break;
                case TIPOART_AUMENTA_SPRINT:
                case TIPOART_ATTACCO_DIETRO:
                case TIPOART_ATTACCO_DIAGONALE:
                case TIPOART_ATTACCO_SHOTGUN:
                case TIPOART_VEL_PROIETTILI:
                    color = ARTEFATTO_POTENZIAMENTO_PAIR_N;
                    break;
                case TIPOART_CHIAVE:
                    color = ARTEFATTO_CHIAVE_PAIR_N;
                    break;
            }
        break;
        case ID_STANZA_BOSS:
            switch (type) {
                case TIPOART_AUMENTA_HP:
                    color = ARTEFATTO_CUORE_PAIR_B;
                    break;
                case TIPOART_AUMENTA_ATTACCO:
                case TIPOART_AUMENTA_DIFESA:
                case TIPOART_AUMENTA_MAX_HP:
                    color = ARTEFATTO_STATISTICHE_PAIR_B;
                    break;
                case TIPOART_AUMENTA_SPRINT:
                case TIPOART_ATTACCO_DIETRO:
                case TIPOART_ATTACCO_DIAGONALE:
                case TIPOART_ATTACCO_SHOTGUN:
                case TIPOART_VEL_PROIETTILI:
                    color = ARTEFATTO_POTENZIAMENTO_PAIR_B;
                    break;
                case TIPOART_CHIAVE:
                    color = ARTEFATTO_CHIAVE_PAIR_B;
                    break;
            }
        break;
    }


    if(type == TIPOART_AUMENTA_HP){
        setcchar(&(this->stampabile[0][0]), L"♥", A_NORMAL, color, NULL);
    }
    else if(type == TIPOART_AUMENTA_ATTACCO){
        setcchar(&(this->stampabile[0][0]), L"A", A_NORMAL, color, NULL);
    }
    else if(type == TIPOART_ATTACCO_DIETRO ){
        setcchar(&(this->stampabile[0][0]), L"⇄", A_NORMAL, color, NULL);
    }
    else if(type == TIPOART_ATTACCO_DIAGONALE ){
        setcchar(&(this->stampabile[0][0]), L"↗", A_NORMAL, color, NULL);
    }
    else if(type == TIPOART_AUMENTA_DIFESA){
        setcchar(&(this->stampabile[0][0]), L"D", A_NORMAL, color, NULL);
    }
    else if(type == TIPOART_AUMENTA_SPRINT){
        setcchar(&(this->stampabile[0][0]), L"⟫", A_NORMAL, color, NULL);
    }
    else if(type == TIPOART_CHIAVE){
        setcchar(&(this->stampabile[0][0]), L"C", A_NORMAL, color, NULL);
    }
    else if(type == TIPOART_ATTACCO_SHOTGUN){
        setcchar(&(this->stampabile[0][0]), L"⇶", A_NORMAL, color, NULL);
    }
    else if(type == TIPOART_VEL_PROIETTILI){
        setcchar(&(this->stampabile[0][0]), L"↯", A_NORMAL, color, NULL);
    }
    else if(type == TIPOART_AUMENTA_MAX_HP){
        setcchar(&(this->stampabile[0][0]), L"♥", A_NORMAL, color, NULL);
    }

}

int Artefatto::getIDArtefatto(){
    return this->idArtefatto;
}
/**
 * @brief Gestisce il contatto del Player con l'artefatto ( se esiste )
 * e applica l'effetto.
 * @param player 
 */
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