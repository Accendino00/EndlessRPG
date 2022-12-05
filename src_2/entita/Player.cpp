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

    this->velocitaProiettile = 1.0;

    this->passedActions = 0;
    this->lastTick = gd->getCurrentTick();

    this->attacco_diagonale = false;
    this->attacco_dietro = false;
    this->attacco_shotgun = false;

	this->sprintDistance = 3;

    this->maxVita=life;
    this->vita = this->maxVita;

    this->damage = 30;
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
                for (int i = 0; i < this->sprintDistance*2; i++) {
                    if(this->lastinput == L'd') muoviPlayer(DIRECTION_EE,1,livello);
                    if(this->lastinput == L'a') muoviPlayer(DIRECTION_OO,1,livello);
                }
                for (int i = 0; i < this->sprintDistance; i++) {
                    if(this->lastinput == L'w') muoviPlayer(DIRECTION_NN,1,livello);
                    if(this->lastinput == L's') muoviPlayer(DIRECTION_SS,1,livello);
                }
                break;
            // Proiettili
            case (KEY_RIGHT):
                if(attacco_dietro){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_OO,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NE,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SE,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                }
                if(attacco_shotgun){
                    this->sparaProiettile(DIRECTION_EE, 1, livello->getStanza());
                    this->sparaProiettile(DIRECTION_EE, -1, livello->getStanza());
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_EE,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                break;
            case (KEY_DOWN):
                if(attacco_dietro){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NN,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SO,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SE,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                }
                if(attacco_shotgun){
                    this->sparaProiettile(DIRECTION_SS, 1, livello->getStanza());
                    this->sparaProiettile(DIRECTION_SS, -1, livello->getStanza());
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SS,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                break;
            case (KEY_LEFT):
                if(attacco_dietro){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_EE,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NO,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SO,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                }
                if(attacco_shotgun){
                    this->sparaProiettile(DIRECTION_OO, 1, livello->getStanza());
                    this->sparaProiettile(DIRECTION_OO, -1, livello->getStanza());
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_OO,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                break;
            case (KEY_UP):
                if(attacco_dietro){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SS,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                }
                if(attacco_diagonale){
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NE,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                    livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NO,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
                }
                if(attacco_shotgun){
                    this->sparaProiettile(DIRECTION_NN, 1, livello->getStanza());
                    this->sparaProiettile(DIRECTION_NN, -1, livello->getStanza());
                }
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NN,this->damage,livello->getStanza()->getId(), this->velocitaProiettile));
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
        case TIPOART_ATTACCO_DIETRO:
            this->attacco_dietro = true;
            break;
        case TIPOART_ATTACCO_DIAGONALE:
            this->attacco_diagonale = true;
            break;
        case TIPOART_ATTACCO_SHOTGUN:
            this->attacco_shotgun = true;
            break;
    }
}

void Player::sparaProiettile(int dir, int offset, Stanza * stanza) {
    int osX, osY;
    if( dir == DIRECTION_NN ) { osX =  offset; osY =  0;}
    if( dir == DIRECTION_SS ) { osX = -offset; osY =  0;}
    if( dir == DIRECTION_EE ) { osX =  0;      osY = -offset;}
    if( dir == DIRECTION_OO ) { osX =  0;      osY =  offset;}
    if( dir == DIRECTION_NE ) { osX =  offset; osY =  offset;}
    if( dir == DIRECTION_SE ) { osX =  offset; osY = -offset;}
    if( dir == DIRECTION_SO ) { osX = -offset; osY = -offset;}
    if( dir == DIRECTION_NO ) { osX = -offset; osY =  offset;}

    stanza->aggiungiProiettile(new Proiettile((this->y)+osY,(this->x)+osX,true,dir,this->damage,stanza->getId(), this->velocitaProiettile));

}

void Player::modificaDifesa(int val){
    this->difesa += val;
}


void Player::modificaVita(int quantita){
    // Se cura, allora non può curare di più di quanto ha perso
    if(quantita>0){
        if(quantita + this->getVita() > this->maxVita) {
            this->vita = this->maxVita;
        } else {
            this->vita += quantita;
        }
    }
    // Se danno, allora la quantità dipende dalla difesa
    // Viene usata la formula che si legge sotto in modo da dare più importanza 
    // alla difesa presa inizalmente e non arrivare mai a 100% di danno negato
    else{
        this->vita += quantita*(100/(100+(float)this->difesa));
    }
}

void Player::modificaMaxVita(int quantita){
    this->maxVita += quantita;
    this->modificaVita(quantita);
}

void Player::setChiave(bool val){
    this->chiave = val;
};

bool Player::getChiave(){
    return this->chiave;
}

void Player::modificaSprint(int val){
    this->sprintDistance += val;
}

void Player::modificaVelProiettile(double val){
    this->velocitaProiettile += val;
}

int Player::getSprint(){
    return this->sprintDistance;
}

double Player::getVelProiettile(){
    return this->velocitaProiettile;
}

bool Player::getAttacks(int attack){
    switch(attack){
        case 1:
            return this->attacco_dietro;
        break;
        case 2:
            return this->attacco_diagonale;
        break;
        case 3:
            return this->attacco_shotgun;
        break;
    }
    return false;
}

void Player::stampaHUDplayer(){
    // Stampa la vita

    // Modo per arrotondare per eccesso
    int numeroCuori = (this->vita + (10 - 1))/10;
    int numeroCuoriMax = (this->maxVita + (10 - 1))/10;
    int insideWidth = numeroCuoriMax > 25 ? numeroCuoriMax : 25;

    // Calcolo coordinate offset
    int coordy = 3;
    int coordx = gd->getTerminalX()/2 - insideWidth/2;

    attron(COLOR_PAIR(0));

    mvprintw(coordy - 1, coordx - 1,  "╔");
    mvprintw(coordy,     coordx - 1,  "║");
    mvprintw(coordy + 1, coordx - 1,  "╚");
    for(int i = 0; i < insideWidth; i++) {
        mvprintw(coordy - 1, coordx + i, "═");
        mvprintw(coordy + 1, coordx + i, "═");    
    }
    mvprintw(coordy - 1, coordx + insideWidth, "╗");
    mvprintw(coordy,     coordx + insideWidth, "║");
    mvprintw(coordy + 1, coordx + insideWidth, "╝");
    mvprintw(coordy - 1, coordx, "[P]ersonaggio");

    attroff(COLOR_PAIR(0));


    attron(COLOR_PAIR(HEARTS_PAIR));
    for(int i=0; i<insideWidth; i++){
        if(i<numeroCuori){
            mvprintw(coordy, coordx+i, "\u2665");
        } else if (i<numeroCuoriMax){
            mvprintw(coordy, coordx+i, "\u2661");
        }
    }
    attroff(COLOR_PAIR(HEARTS_PAIR));


    attron(COLOR_PAIR(0));

    mvprintw(coordy + 1, coordx + insideWidth - 11, "╦══════════╣");
    mvprintw(coordy + 2, coordx + insideWidth - 11, "║ Chiave:%lc ║", (this->chiave)? L'✓' : L'x');
    mvprintw(coordy + 3, coordx + insideWidth - 11, "║          ║");
    if(damage < 999) mvprintw(coordy + 3, coordx + insideWidth - 10 , " ATK:%d", this->damage);
                else mvprintw(coordy + 3, coordx + insideWidth - 10 , " ATK:999+");
    mvprintw(coordy + 4, coordx + insideWidth - 11, "║          ║");
    mvprintw(coordy + 4, coordx + insideWidth - 10 , " DEF:%.0lf%%", 100 - (100*(100/(100+(double)this->difesa))));
    mvprintw(coordy + 5, coordx + insideWidth - 11, "╚══════════╝");


    mvprintw(coordy + 2, coordx - 1, "╔Inventario:═╗");
    mvprintw(coordy + 3, coordx - 1, "║%lc           ║", (this->attacco_diagonale)? L'\u2197' : L' ');
    mvprintw(coordy + 4, coordx - 1, "║%lc           ║", (this->attacco_dietro)? L'\u21C4' : L' ');
    mvprintw(coordy + 5, coordx - 1, "║%lc           ║", (this->attacco_shotgun)? L'\u21F6' : L' ');
    mvprintw(coordy + 6, coordx - 1, "║            ║");

    // si bugga quando prendi il primo sprint e poi aggiunge solo 1 icona al posto di 2 ogni powerup
    for(int i=0; i<this->getSprint(); i++){
        mvprintw(coordy+6, coordx+i, "s");
    };
    mvprintw(coordy + 7, coordx - 1, "║            ║");
    // non si aggiorna non si sa perche
    for(float i=1.0; i<=this->getVelProiettile(); i+=0.5){
        mvprintw(coordy+7, (coordx)+((i-1)*2), "v");
    };
    
    mvprintw(coordy + 8, coordx - 1, "╚════════════╝");

    attroff(COLOR_PAIR(0));
}



