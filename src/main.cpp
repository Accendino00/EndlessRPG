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
	

	chtype pressedKeys[100];
	int i = 0;


	start_color();
	init_pair(1, COLOR_WHITE, COLOR_MAGENTA);

	for(unsigned int xincin = 0u; xincin <= 1000000u; xincin++) {
		wchar_t ** example = (wchar_t **) calloc(1, sizeof(wchar_t *));
		example[0] = (wchar_t *) calloc(1, sizeof(wchar_t));
		example[0][0] = (wchar_t) L'┤';

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
		wchar_t * xy = L"🥸😋┤";
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

	endwin();
	return 0;
}
