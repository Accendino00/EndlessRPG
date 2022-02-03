#include<ncurses.h>
#include <string>



int main(int argc, char ** argv)
{
    //Start NCURSES
    initscr();
    noecho();
    cbreak();

    //Grandezza Schermo
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //Creazione Schermo per un input
    WINDOW * menuwin = newwin(6,xMax=12, yMax=8,5);
    box(menuwin,0,0);
    refresh();
    wrefresh(menuwin);

    //Frecce della tastiera
    keypad(menuwin,true);
    std::string scelte[3]={"Scelta 1", "Scelta 2", "Scelta 3"};
    int scelta = 'a';
    int evidenziato = 0;

    while(scelta != 'q')
    {
        for(int i= 0; i<3; i++)
        {
            if (i == evidenziato)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, scelte[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        scelta = wgetch(menuwin);

        switch(scelta)
        {
            case KEY_UP:
                evidenziato--;
                break;
            case KEY_DOWN:
                evidenziato++;
                break;
            default:
                break;
        }
        if (scelta == 10){
            break;
        }
    }
    //Il wait
    getch();
    endwin();
    return 0;
}