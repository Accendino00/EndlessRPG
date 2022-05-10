#include "../generale/libs.hpp"

Player::Player(int y, int x) {

	this->dim_x=1;
	this->dim_y=1;

    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];
   
    setcchar(&(this->stampabile[0][0]), L"P", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    
    this->y = y;
    this->x = x;
};

void Player::manageInput() {
	int i = 0;
    while(i < gd->getNumOfPressedKeys()) {
        this->movimento(gd->getKey(i));
        i++;
    }
}

void Player::movimento(int input){
    switch(input) {
			case (L'w'):
			    y--;
                lastinput = (L'w');
			    break;
			case (L's'):
				y++;
                lastinput = (L's');
				break;
			case (L'd'):
				x++;
                lastinput = (L'd');
				break;
			case (L'a'):
				x--;
                lastinput = (L'a');
				break;
            case (L' '):
                if(lastinput == NULL) y=y-2;
                if(lastinput == L'w') y=y-2;
                if(lastinput == L's') y=y+2;
                if(lastinput == L'd') y=x-2;
                if(lastinput == L'a') y=x+2;
                break;

		}

};

void Player::inventario(){
    getmaxyx(stdscr, yMax, xMax);

};