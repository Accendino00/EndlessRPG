#pragma once
#include "libs.hpp"

Player::Player(int y, int x):Entita(y, x, 0, 0, NULL){

    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];

    wchar_t dragonerosso [5] = L"\u2665";
   
    setcchar(&(this->stampabile[0][0]), dragonerosso, A_BOLD, 2, NULL);

    this->y = y;
    this->x = x;

};

void Player::movimento(int input, Stanza stanza)
{
	int lastinput = NULL;

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