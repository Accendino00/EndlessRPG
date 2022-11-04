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
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_EE));
                break;
            case (KEY_DOWN):
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_SS));
                break;
            case (KEY_LEFT):
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_OO));
                break;
            case (KEY_UP):
                livello->aggiungiProiettile(new Proiettile(this->y, this->x,true,DIRECTION_NN));
                break;
		}

};

void Player::muoviPlayer(int direzione, int val, Livello * livello) {
    switch (movimentoValido(direzione, val, livello->getStanza(), true) ) {
        case STANZA_ACC_LIBERO:
            muovi(direzione, val);
            break;
        default:
            erase();
            mvprintw(42,5,"Contatto giocatore!");
            refresh();
        break;
    }
}

void Player::inventario(){
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



