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

void Player::manageInput(ListaEntita * proiettili) {
	int i = 0;
    while(i < gd->getNumOfPressedKeys()) {
        this->gestione_player(gd->getKey(i), proiettili);
        i++;
    }
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

void Player::gestione_player(int input, ListaEntita * proiettili){
    switch(input) {
            // Movimento basilare
			case (L'w'):
			    y--;
                this->lastinput = (L'w');
			    break;
			case (L's'):
				y++;
                this->lastinput = (L's');
				break;
			case (L'd'):
				x++;
                this->lastinput = (L'd');
				break;
			case (L'a'):
				x--;
                this->lastinput = (L'a');
				break;
            // Dash
            case (L' '):
                if(this->lastinput == L'w') y-=this->dashDistanceY;
                if(this->lastinput == L's') y+=this->dashDistanceY;
                if(this->lastinput == L'd') x+=this->dashDistanceX;
                if(this->lastinput == L'a') x-=this->dashDistanceX;
                break;
            // Proiettili
            case (KEY_RIGHT):
                proiettili->addEntita(new Proiettile(this->y, this->x,true,DIRECTION_EE));
                break;
            case (KEY_DOWN):
                proiettili->addEntita(new Proiettile(this->y, this->x,true,DIRECTION_SS));
                break;
            case (KEY_LEFT):
                proiettili->addEntita(new Proiettile(this->y, this->x,true,DIRECTION_OO));
                break;
            case (KEY_UP):
                proiettili->addEntita(new Proiettile(this->y, this->x,true,DIRECTION_NN));
                break;
		}

};

void Player::inventario(){
}










