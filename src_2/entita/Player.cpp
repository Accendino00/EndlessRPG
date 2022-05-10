#include "../generale/libs.hpp"

Player::Player(int y, int x, int life) {
    int lastinput = NULL;
	this->dim_x=1;
	this->dim_y=1;
    this->life=life;
    this->current_life = this->life;
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];
   
    setcchar(&(this->stampabile[0][0]), L"P", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    
    this->y = y;
    this->x = x;
};

void Player::manageInput() {
	int i = 0;
    while(i < gd->getNumOfPressedKeys()) {
        this->gestione_player(gd->getKey(i));
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
    for(int i = current_life/10; i>0; i--){
        printw("\u2665");
    }
    for(int i = (life-current_life)/10; i>0; i--){
        printw("\u2661");
    }
    attroff(COLOR_PAIR(HEARTS_PAIR));

}

void Player::gestione_player(int input){
    switch(input) {
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
            case (L' '):
                if(this->lastinput == NULL) y=y-2;
                if(this->lastinput == L'w') y=y-2;
                if(this->lastinput == L's') y=y+2;
                if(this->lastinput == L'd') y=x-2;
                if(this->lastinput == L'a') y=x+2;
                break;

		}

};

void Player::inventario(){
    getmaxyx(stdscr, yMax, xMax);

}