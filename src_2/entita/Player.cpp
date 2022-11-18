#include "../generale/libs.hpp"

Player::Player(int y, int x, int life) {
    this->lastinput = L'd';
    // Impostazione dell'hitbox e della dimensione dello stampabile. 
    // Inoltre il giocatore ha 1 solo frame di stampa
    (*this).h_dimy = 1;
    (*this).h_dimx = 1;
    (*this).s_dimy = 1;
    (*this).s_dimx = 3;
    (*this).currentFrame = FRAME_OF_E;

    this->passedActions = 0;
    this->lastTick = gd->getCurrentTick();

    this->attacco_diagonale = false;
    this->attacco_dietro = false;

	this->dashDistanceY = 5;
	this->dashDistanceX = this->dashDistanceY*2;

    this->maxLife=life;
    this->currentLife = this->maxLife;

    this->damage = 100;
    this->difesa = 10;
	
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [3];
   
    setcchar(&(this->stampabile[0][0]), L"P", A_NORMAL, PLAYER_COLOR_PAIR_E, NULL);
    setcchar(&(this->stampabile[0][1]), L"P", A_NORMAL, PLAYER_COLOR_PAIR_N, NULL);
    setcchar(&(this->stampabile[0][2]), L"P", A_NORMAL, PLAYER_COLOR_PAIR_B, NULL);

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
                if(attacco_dietro){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_OO,this->damage,livello->getStanza()->getId()));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NE,this->damage,livello->getStanza()->getId()));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SE,this->damage,livello->getStanza()->getId()));
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_EE,this->damage,livello->getStanza()->getId()));
                break;
            case (KEY_DOWN):
                if(attacco_dietro){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NN,this->damage,livello->getStanza()->getId()));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SO,this->damage,livello->getStanza()->getId()));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SE,this->damage,livello->getStanza()->getId()));
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SS,this->damage,livello->getStanza()->getId()));
                break;
            case (KEY_LEFT):
                if(attacco_dietro){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_EE,this->damage,livello->getStanza()->getId()));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NO,this->damage,livello->getStanza()->getId()));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SO,this->damage,livello->getStanza()->getId()));
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_OO,this->damage,livello->getStanza()->getId()));
                break;
            case (KEY_UP):
                if(attacco_dietro){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SS,this->damage,livello->getStanza()->getId()));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NE,this->damage,livello->getStanza()->getId()));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NO,this->damage,livello->getStanza()->getId()));
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NN,this->damage,livello->getStanza()->getId()));
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
            muovi(direzione,val);
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
    switch(direzione){
        case DIRECTION_EE:
            this->attacco_dietro = true;
            break;
        case DIRECTION_SE:
            this->attacco_diagonale = true;
            break;
    }
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
        this->currentLife += quantita*(100/(100+(float)this->difesa));
    }
}

void Player::setChiave(bool val){
    this->chiave = val;
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
    int coordx = (gd->getTerminalX()/2) - 3;

    // Stampa dei cuori
    attron(COLOR_PAIR(0));
    mvprintw(coordy+2, coordx - (maxLife/20), "HP : ");
    attroff(COLOR_PAIR(0));
    attron(COLOR_PAIR(HEARTS_PAIR));
    for(int i = currentLife/10; i>0; i--){
        printw("\u2665");
    }
    for(int i = (maxLife-currentLife+5)/10; i>0; i--){
        printw("\u2661");
    }
    attroff(COLOR_PAIR(HEARTS_PAIR));

    // Stampa dell'attacco
    mvprintw(coordy+4, coordx, "🗡  : %d", this->damage);

    // Stampa della difesa
    mvprintw(coordy+5, coordx, "🛡  : %.0lf%%", 100 - (100*(100/(100+(double)this->difesa))));

    // Stampa della chiave
    mvprintw(coordy+6, coordx, "🔑 : %lc", (this->chiave)? L'✓' : L'❌');
}



