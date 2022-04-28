/*

@Petru
	Questo è il file main temporaneo

	Ci implementerò un basilare loop perché il gioco funzioni
	Man mano aggiungerò le altre funzioni, come i menu e quant'altro

	Se volete aggiungerci roba, fatelo
	cercate però di evitare di committare qualcosa che non funziona	
	

*/

#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <chrono>

#include <locale.h>

#include "Entita.hpp"


int main() {

    //Start NCURSES
	setlocale(LC_ALL, "");
    initscr();
	curs_set(0);
    noecho();
    cbreak();
	nodelay(stdscr, true);

    //Grandezza Schermo
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
	

    //Frecce della tastiera
    keypad(stdscr,true);
	

	int pressedKeys[100];
	int i = 0;


	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_MAGENTA);

	int input = L'a';

	wchar_t ** example = (wchar_t **) calloc(1, sizeof(wchar_t *));
	for(int i = 0; i < 1; i++) {
		example[0] =(wchar_t *) calloc(1, sizeof(wchar_t));
	}
	for(int i = 0; i < 1; i++) {
		for(int j = 0; j < 1; j++) {
			example[i][j] = (wchar_t) L'🧙';
		}
	}
	
	Entita * player = new Entita(xMax/2,yMax/2,1,1,0,0,example);

	wchar_t ** example2 = (wchar_t **) calloc(2, sizeof(wchar_t *));
	example2[0] = (wchar_t *) calloc(2, sizeof(wchar_t));
	example2[1] = (wchar_t *) calloc(2, sizeof(wchar_t));
	example2[0][0] = (wchar_t) L'🔥';
	example2[1][0] = (wchar_t) L'🔥';
	example2[0][1] = (wchar_t) L'🔥';
	example2[1][1] = (wchar_t) L'🔥';
	
	Entita * item = new Entita(xMax/2-10,yMax/2-5,2,2,0,0,example2);


	int cordx=player->x,cordy=player->y;

	do {
		i = 0;
		do {
			input= getch();
			pressedKeys[i] = (input);
			i++;	
		} while(input != ERR);
		erase();
		move(yMax/2, (xMax/2));
		
		if (i>0) {
			for(int j = 0; j < i; j++) {
        		wprintw(stdscr, "%lc", pressedKeys[j]);
			}
		} else {
			waddch(stdscr,'e');
		}



		switch(pressedKeys[0]) {
			case (L'w'):
				cordy--;
				break;
			case (L's'):
				cordy++;
				break;
			case (L'd'):
				cordx++;
				break;
			case (L'a'):
				cordx--;
				break;
		}

		player->modificaCoordinate(cordx,cordy);
		item->stampa(stdscr,0,0);
		player->stampa(stdscr, 0, 0);
		move(0,0);
		if(player->controllaContattore(item)) {
			printw("True");
		} else {
			printw("False");
		}

		refresh();
		usleep(100000);

	} while (pressedKeys[0] != L'q');

	/*for(unsigned int xincin = 0u; xincin <= 1000000u; xincin++) {
		wchar_t ** example = (wchar_t **) calloc(1, sizeof(wchar_t *));
		example[0] = (wchar_t *) calloc(1, sizeof(wchar_t));
		example[0][0] = (wchar_t) L'🥸';

		Entita * player = new Entita(0,0,1,1,A_BOLD,1,example);

		//do {
			i = 0;
			//input = getch();
			int c;
			do {
				c = getch();
				pressedKeys[i] = (c);
				i++;	
			} while(c != ERR);

			clear();
			move(yMax/2, (xMax/2));
			if (i>0) {
				for(int j = 0; j < i; j++) {
            		wprintw(stdscr, "%lc", pressedKeys[j]);
				}
			} else {
				waddch(stdscr,'e');
			}
		//mvwprintw(stdscr,0,0,"┤東京 \u0061");
		//waddwstr(stdscr, xy);
		move(0,0);
		wchar_t * xy = (wchar_t*) L"🥸😋┤";
		waddwstr(stdscr,xy);
			(*player).stampa(stdscr,20,20);
			move(10,10);
			addch(example[0][0]);
			refresh();
			usleep(50000);
		//} while (pressedKeys[0] != 'q');

		delete player;		
		free(example[0]);
		free(example);

	}
	*/
	endwin();
	return 0;
}
