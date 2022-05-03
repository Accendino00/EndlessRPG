#include <ncursesw/ncurses.h>
#include "Player.hpp"


void Player::movimento(int input, Stanza stanza){

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