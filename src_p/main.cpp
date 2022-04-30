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
#ifdef __linux__ 
    #include <ncurses.h>
#elif _WIN32
    #include <ncursesw/ncurses.h>
#else
    #error Errore di compilazione, sistema operativo non supportato
#endif
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
	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	int input = L'a';

	wchar_t ** example = (wchar_t **) calloc(4, sizeof(wchar_t *));
	for(int i = 0; i < 4; i++) {
		example[i] =(wchar_t *) calloc(4, sizeof(wchar_t));
	}
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			example[i][j] = (wchar_t) L'🧙';
		}
	}
	
	Entita * player = new Entita(xMax/2,yMax/2,4,4, A_BOLD | COLOR_PAIR(0),example,NULL);

	wchar_t ** example2 = (wchar_t **) calloc(2, sizeof(wchar_t *));
	example2[0] = (wchar_t *) calloc(2, sizeof(wchar_t));
	example2[1] = (wchar_t *) calloc(2, sizeof(wchar_t));
	example2[0][0] = (wchar_t) L'I';
	example2[1][0] = (wchar_t) L'T';
	example2[0][1] = (wchar_t) L'E';
	example2[1][1] = (wchar_t) L'M';
	int ** example3 = (int **) calloc(2, sizeof(int *));
	example3[0] = (int *) calloc(2, sizeof(int));
	example3[1] = (int *) calloc(2, sizeof(int));
	example3[0][0] = A_BOLD;
	example3[1][0] = A_BLINK;
	example3[0][1] = A_REVERSE;
	example3[1][1] = A_TOP;

	double numcontrolliGTP = 0, numcontrolliPTG=0;
	
	Entita * item = new Entita(xMax/2-10,yMax/2-5,2,2,A_BOLD | COLOR_PAIR(1),example2, example3);


	int cordx=player->x,cordy=player->y;

	do {
		auto start = std::chrono::system_clock::now();
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

		switch(pressedKeys[0]) {
			case (L'h'):
				numcontrolliGTP-=10000;
				break;
			case (L'j'):
				numcontrolliGTP-=1000;
				break;
			case (L'k'):
				numcontrolliGTP+=1000;
				break;
			case (L'l'):
				numcontrolliGTP+=10000;
				break;
		}

		switch(pressedKeys[0]) {
			case (L'y'):
				numcontrolliPTG-=10000;
				break;
			case (L'u'):
				numcontrolliPTG-=1000;
				break;
			case (L'i'):
				numcontrolliPTG+=1000;
				break;
			case (L'o'):
				numcontrolliPTG+=10000;
				break;
		}

		player->modificaCoordinate(cordx,cordy);
		item->stampa(stdscr,0,0);
		player->stampa(stdscr, 0, 0);
		move(3,0);
		printw("numcontrolli grande -> piccolo: %f",numcontrolliGTP);
		move(4,0);
		printw("numcontrolli piccolor -> grande: %f",numcontrolliPTG);
		for(int i=0; i < numcontrolliGTP; i++) {
			player->controllaContatto(item);
		}
		for(int i=0; i < numcontrolliPTG; i++) {
			item->controllaContatto(player);
		}
		move(2,0);
		if(player->controllaContatto(item)) {
			printw("True");
		} else {
			printw("False");
		}

		
		//usleep(16000);
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		move(0,0);
		printw("FPS: %f", (1/elapsed_seconds.count()));
		move(1,0);
		printw("ms: %f",elapsed_seconds.count()*1000);
		
		refresh();
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
