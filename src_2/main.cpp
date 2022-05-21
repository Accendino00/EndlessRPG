#pragma once
#include "libs.hpp"

/*

    Comandi per compilazione con debug:
        g++ -g -o Gioco Entita.cpp Compatibility.cpp main.cpp -lncursesw
        valgrind --leak-check=full          --show-leak-kinds=all          --track-origins=yes          --verbose          --log-file=valgrind-out.txt          ./Gioco
*/

int main () {

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
	init_pair(1, COLOR_BLUE, COLOR_RED);
    // I colori sono occupati da 0 a 7, tutti gli altri numeri short (max 65535) sono occupabili da numeri personalizzati
    init_color(25,500,500,500);
    init_color(26,1000 * 78 / 255,1000 * 65 / 255,1000 * 135 / 255);
    init_color(27,1000 * 248 / 255,1000 * 255 / 255,1000 * 229 / 255);
    init_pair(2,COLOR_BLUE,COLOR_RED);

    int dimy = 100, dimx = 100;
    // ricorda di chiudere queste cose dopo che le apri
    cchar_t ** player_graphical = (cchar_t **) calloc(dimy, sizeof(cchar_t*));
    for(int i = 0; i < dimy; i++) {
        player_graphical[i] = (cchar_t *) calloc(dimx, sizeof(cchar_t));
    }

    srand(time(NULL));

    wchar_t prova1 [5] = L"c";
    wchar_t prova2 [5] = L"a";
    wchar_t prova3 [5] = L"u";
    for(int i = 0; i < dimy; i++) {
        for(int j = 0; j < dimx; j++) {
            int r = rand() % 3;
            setcchar(&(player_graphical[i][j]), (r==0)?(prova1):((r==1)?(prova2):(prova3)) , A_BOLD, 1, NULL);
        }
    }
    Entita * player = new Entita(10, yMax/2, xMax/2, dimy, dimx, player_graphical); 
	int cordx=player->x,cordy=player->y;

	int input = L'a';

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

        // QUA POSSO FARE COSE //

        wattron(stdscr, A_BOLD | COLOR_PAIR(2));
        wprintw(stdscr, "Ciao");
        wattroff(stdscr, A_BOLD | COLOR_PAIR(2));

		cchar_t prova;
		prova.chars[0] = L'a';
		prova.chars[1] = L'\0';
		prova.attr = A_NORMAL;
		prova.ext_color = 2;
		mvwadd_wch(stdscr, 50,20,(const cchar_t *) &prova);

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
        player->modificaCoordinate(cordy,cordx);
        player->stampa( 0, 0);


		move(10,2);
		for(int k = 0; k < i; k++) {
			printw("%d ", pressedKeys[k]);
		}
		usleep(100000);

        if(pressedKeys[0] == KEY_RESIZE) {
            getmaxyx(stdscr, yMax, xMax);
        }

        /////////////////////////

		//usleep(16000);
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

        // PER AVERE UN CAP DI FPS
        double fps_cap = 1000;
        if(elapsed_seconds.count() <= (1/fps_cap)) {
            usleep(((1/fps_cap) - elapsed_seconds.count())*1000000);
        }
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;

		move(0,0);
		printw("FPS: %f", (1/elapsed_seconds.count()));
		move(1,0);
		printw("ms: %f",elapsed_seconds.count()*1000);
		
		refresh();
	} while (pressedKeys[0] != L'q');

/*
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
	double numStampeADDCH = 0, numStampeWPRINTW=0;

	Entita * item = new Entita(xMax/2-10,yMax/2-5,2,2,A_BOLD | COLOR_PAIR(1),example2, example3);

	cchar_t * x = new cchar_t; 
	x[0] = {COLOR_PAIR(1) | A_BOLD, L"\u3444\u3761"};

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

		
		switch(pressedKeys[0]) {
			case (L'1'):
				numStampeADDCH-=10000;
				break;
			case (L'2'):
				numStampeADDCH-=1000;
				break;
			case (L'3'):
				numStampeADDCH+=1000;
				break;
			case (L'4'):
				numStampeADDCH+=10000;
				break;
		}

		switch(pressedKeys[0]) {
			case (L'5'):
				numStampeWPRINTW-=10000;
				break;
			case (L'6'):
				numStampeWPRINTW-=1000;
				break;
			case (L'7'):
				numStampeWPRINTW+=1000;
				break;
			case (L'8'):
				numStampeWPRINTW+=10000;
				break;
		}

		for(int i=0; i < numStampeADDCH; i++) {
			move(15,15);
			wadd_wch(stdscr, x);
		}
		for(int i=0; i < numStampeWPRINTW; i++) {
			move(16,16);
			wattron(stdscr, COLOR_PAIR(1)|A_BOLD);
			waddwstr(stdscr, L"\u3761");
			wattroff(stdscr, COLOR_PAIR(1)|A_BOLD);
		}

		player->modificaCoordinate(cordx,cordy);
		item->stampa(stdscr,0,0);
		player->stampa(stdscr, 0, 0);
		move(3,0);
		printw("numcontrolli grande -> piccolo: %f",numcontrolliGTP);
		move(4,0);
		printw("numcontrolli piccolor -> grande: %f",numcontrolliPTG);
		move(5,0);
		printw("num ADDCH: %f",numStampeADDCH);
		move(6,0);
		printw("num PRINTW: %f",numStampeWPRINTW);
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
    */

    delete(player);

	endwin();
	return 0;
}