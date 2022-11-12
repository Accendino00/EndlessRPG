#include "../generale/libs.hpp"

Player::Player(int y, int x, int life) {
    this->lastinput = L'd';
    // Impostazione dell'hitbox e della dimensione dello stampabile. 
    // Inoltre il giocatore ha 1 solo frame di stampa
    (*this).h_dimy = 1;
    (*this).h_dimx = 1;
    (*this).s_dimy = 1;
    (*this).s_dimx = 1;
    (*this).currentFrame = 0;

    this->passedActions = 0;
    this->lastTick = gd->getCurrentTick();

	this->dashDistanceY = 5;
	this->dashDistanceX = this->dashDistanceY*2;

    this->maxLife=life;
    this->currentLife = this->maxLife;

    this->damage = 10;
	
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];
   
    setcchar(&(this->stampabile[0][0]), L"P", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    
    this->y = y;
    this->x = x;
};

void Player::manageInput(Livello * livello) {
	int i = 0;
    while(i < gd->getNumOfPressedKeys()) {
        this->gestione_player(gd->getKey(i), livello);
        i++;
    }
}

void Player::gestione_player(int input, Livello * livello){
    switch(input) {
            // Movimento basilare
			case (L'w'):
			    muoviPlayer(DIRECTION_NN, 1, livello);
                this->lastinput = (L'w');
			    break;
			case (L's'):
			    muoviPlayer(DIRECTION_SS, 1, livello);
                this->lastinput = (L's');
				break;
			case (L'd'):
			    muoviPlayer(DIRECTION_EE, 1, livello);
                this->lastinput = (L'd');
				break;
			case (L'a'):
			    muoviPlayer(DIRECTION_OO, 1, livello);
                this->lastinput = (L'a');
				break;
            // Dash
            case (L' '):
                for (int i = 0; i < this->dashDistanceX; i++) {
                    if(this->lastinput == L'd') muoviPlayer(DIRECTION_EE,1,livello);
                    if(this->lastinput == L'a') muoviPlayer(DIRECTION_OO,1,livello);
                }
                for (int i = 0; i < this->dashDistanceY; i++) {
                    if(this->lastinput == L'w') muoviPlayer(DIRECTION_NN,1,livello);
                    if(this->lastinput == L's') muoviPlayer(DIRECTION_SS,1,livello);
                }
                break;
            // Proiettili
            case (KEY_RIGHT):
                if(attacco){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_OO,this->damage));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NE,this->damage));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SE,this->damage));
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_EE,this->damage));
                break;
            case (KEY_DOWN):
                if(attacco){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NN,this->damage));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SO,this->damage));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SE,this->damage));
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SS,this->damage));
                break;
            case (KEY_LEFT):
                if(attacco){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_EE,this->damage));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NO,this->damage));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SO,this->damage));
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_OO,this->damage));
                break;
            case (KEY_UP):
                if(attacco){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SS,this->damage));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NE,this->damage));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NO,this->damage));
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NN,this->damage));
                break;
		}

};

void Player::muoviPlayer(int direzione, int val, Livello * livello) {
    switch (movimentoValido(direzione, val, livello->getStanza(), true) ) {
        case STANZA_ACC_LIBERO:
            muovi(direzione, val);
            break;
        case STANZA_ACC_PROIETTILE_NEMICO:
            this->modificaVita(- ((livello->getStanza())->dmgDaProiettiliContactList(false)) );
            
            break;
        case STANZA_ACC_ARTEFATTO:
            // Faccio cose con l'artefatto nella contact list
            livello->getStanza()->effettiArtefatti(this);
            break;
        break;
        case STANZA_ACC_PORTA:
        case STANZA_ACC_MURO:
            // non si può muovere in quella direzione
            break;
        default:
            
        break;
    }
}

void Player::modificaDanno(int danno){
    this->damage += danno;
}

void Player::aggiungiDirezioneAttacco(int direzione){
    case DIRECTION_EE:
        this->attacco_dietro = true;
        break;
    case DIRECTION_SE:
        this->attaco_diagonale = true;
        break;
}

void Player::modificaDifesa(int val){
    this->difesa += val;
}


void Player::modificaVita(int quantita){
    if(quantita>0){
        if(quantita + this->getVita() > this->maxLife) {
            this->currentLife = this->maxLife;
        } else {
            this->currentLife += quantita;
        }
    }
    else{
            this->currentLife += quantita*(100/(100+this->difesa));
    }
}

void Player::setChiave(bool val){
    if(val) this->chiave = true;
};

bool Player::getChiave(){
    return this->chiave;
}

void Player::modificaSprint(int val){
    this->dashDistanceX += val*2;
    this->dashDistanceY += val;
}


void Player::stampaHUDplayer(){
    int coordy = 0;
    int coordx = 0;
    attron(COLOR_PAIR(0));
    mvprintw(coordy+2, coordx, "HP : ");
    attroff(COLOR_PAIR(0));
    attron(COLOR_PAIR(HEARTS_PAIR));
    for(int i = currentLife/10; i>0; i--){
        printw("\u2665");
    }
    for(int i = (maxLife-currentLife)/10; i>0; i--){
        printw("\u2661");
    }
    attroff(COLOR_PAIR(HEARTS_PAIR));

}



