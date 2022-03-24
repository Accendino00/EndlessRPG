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

#include "Entita.hpp"


int main() {
	setlocale(LC_ALL, "");

    //Start NCURSES
    initscr();
    noecho();
    cbreak();
	nodelay(stdscr, true);

    //Grandezza Schermo
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //Frecce della tastiera
    keypad(stdscr,true);
	

	int input;
	int pressedKeys[100];
	int i = 0;


	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	attron(COLOR_PAIR(1));

	for(char xincin = 'a'; xincin < 'z'; xincin++) {
		chtype ** example = (chtype **) calloc(1, sizeof(chtype *));
		example[0] = (chtype *) calloc(1, sizeof(chtype));
		example[0][0] = (chtype) (unsigned char) xincin;

		Entita * player = new Entita(0,0,1,1,0,1,example);
		std::cout << example[0][0];

		do {
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
			if (i>0)
				for(int j = 0; j < i; j++) {
					waddch(stdscr, pressedKeys[j]);
				}
			else
				waddch(stdscr,'e');

			(*player).stampa(stdscr,20,20);
			refresh();
			usleep(100000);
		} while (pressedKeys[0] != 'q');

		attroff(COLOR_PAIR(1));
		
		free(example[0]);
		free(example);

	}

	endwin();
	return 0;
}
