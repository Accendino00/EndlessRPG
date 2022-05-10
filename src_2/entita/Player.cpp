#include "../generale/libs.hpp"

Player::Player(int y, int x, int life) {
    int lastinput = NULL;
	this->dim_x=1;
	this->dim_y=1;
    this->life=10;

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

void Player::stampaHUDplayer(int danno){
    int coordy = 0;
    int coordx = 0;
    int life_now;
    for(int i = life; i>0; i--){
        
    }
    attron(COLOR_PAIR(HEARTS_PAIR));
    mvprintw(coordy+1, coordx, "        ┌─────────────┐");
    mvprintw(coordy+2, coordx, "HP : ");
    mvprintw(coordy+2, coordx+6, HP);
    mvprintw(coordy+3, coordx, "        └─────────────┘");
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