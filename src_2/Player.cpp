#pragma once
#include "libs.hpp"

Player::Player(int y, int x):Entita(y, x, 0, 0, NULL){

    // ricorda di chiudere queste cose dopo che le apri
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];

    srand(time(NULL));

    wchar_t dragonerosso [5] = L"\u2665";
   
    setcchar(&(this->stampabile[0][0]), dragonerosso, A_BOLD, 2, NULL);
    
    this->y = y;
    this->x = x;

};

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