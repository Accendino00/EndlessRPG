#include "../generale/libs.hpp"

Player::Player(int y, int x) {

	this->dim_x=1;
	this->dim_y=1;

    // ricorda di chiudere queste cose dopo che le apri
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
				break;
			case (L's'):
				y++;
				break;
			case (L'd'):
				x++;
				break;
			case (L'a'):
				x--;
				break;
		}

};

void inventario(){

};