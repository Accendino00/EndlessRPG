#include <ncurses.h>
#include <iostream>


const char *menuprincipale;
const char *menusecondario;

class MainMenu{
protected:
int yMax, xMax;

public:
    MainMenu(){
        this->yMax=8;
        this->xMax=11;
    }
    void destroy_win(WINDOW *menuwin){
        wborder(menuwin, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        wrefresh(menuwin);
        delwin(menuwin);
    }
    void crediti(){
        //Grandezza Schermo
        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);

        //Creazione Schermo per un input
        WINDOW * menuwin = newwin(this->yMax,this->xMax, 15,70); //rettanngolo alto 8 e largo 11, 70 e 15 sono da dove parte la finestra
        wrefresh(menuwin);

        //Frecce della tastiera
        keypad(menuwin,true);

        mvprintw(15, 60, "Il progetto è stato realizzato da:");
        refresh();
        mvprintw(17, 70, "Davide Donati");
        refresh();
        mvprintw(18, 70, "Jacopo Amoretti");
        refresh();
        mvprintw(19, 70, "Giuseppe Forciniti");
        refresh();
        mvprintw(20, 70, "Petru Marincas");
        refresh();
        char scelte[1][20]={"Indietro"};
        int scelta;
        int evidenziato = 0;
        bool uscire = false;
        while(scelta != 'q' && uscire == false)
        {
            for(int i=0; i!='q'; i++) {
                wattron(menuwin, A_REVERSE | A_BLINK);
                mvwprintw(menuwin, 7, 3, scelte[0]);
                wattroff(menuwin, A_REVERSE | A_BLINK);
            }
            scelta = wgetch(menuwin);
            switch(scelta)
            {
                case 10:
                    if(evidenziato==0){
                        destroy_win(menuwin);
                        scr_restore(menusecondario);
                    }
                default:
                    break;
            }
        }
        getch();
    }
    void opzioni(){
        //Grandezza Schermo
        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);

        //Creazione Schermo per un input
        WINDOW * menuwin = newwin(yMax=5,xMax=11,15,70);
        box(menuwin,0,0);
        refresh();
        wrefresh(menuwin);

        //Frecce della tastiera
        keypad(menuwin,true);

        char scelte[3][20]={"Difficolta", "Crediti", "Indietro"};
        int scelta;
        int evidenziato = 0;
        bool uscire = false;
        while(scelta != 'q' && uscire == false)
        {
            for(int i= 0; i<3; i++)
            {
                if (i == evidenziato)
                    wattron(menuwin, A_REVERSE | A_BLINK);
                mvwprintw(menuwin, i+1, 1, scelte[i]);
                wattroff(menuwin, A_REVERSE | A_BLINK);
            }
            scelta = wgetch(menuwin);

            switch(scelta)
            {
                case KEY_UP:
                    evidenziato--;
                    if(evidenziato==-1){
                        evidenziato=0;
                    }
                    break;
                case KEY_DOWN:
                    evidenziato++;
                    if(evidenziato==3){
                        evidenziato=2;
                    }
                    break;
                case 10:
                    if(evidenziato==0){
                        //scorrimento difficoltà
                    }
                    if(evidenziato==1){
                        scr_dump(menusecondario);
                        destroy_win(menuwin);
                        crediti();
                    }
                    if(evidenziato==2){
                        destroy_win(menuwin);
                        scr_restore(menuprincipale);
                        wrefresh(menuwin);
                    }
                    uscire = true;
                    break;
                default:
                    break;
            }
        }
        getch();
    }
    void menu()
        {
            //Start NCURSES
            initscr();
            noecho();
            cbreak();

            //Grandezza Schermo
            int yMax, xMax;
            getmaxyx(stdscr, yMax, xMax);

            //Creazione Schermo per un input
            WINDOW * menuwin = newwin(yMax=5,xMax=11, 15,70);
            box(menuwin,0,0);
            refresh();
            wrefresh(menuwin);

            //Frecce della tastiera
            keypad(menuwin,true);

            mvprintw(11, 50, "Usa le frecce per spostarti nel menù Principale");
            refresh();
            mvprintw(12, 50,"Premi 'Q' per uscire");
            refresh();
            char scelte[3][20]={"Gioca", "Opzioni", "Esci"};
            int scelta;
            int evidenziato = 0;
            bool uscire = false;
            while(scelta != 'q' && uscire == false)
            {
                for(int i= 0; i<3; i++)
                {
                    if (i == evidenziato)
                        wattron(menuwin, A_REVERSE | A_BLINK);
                    mvwprintw(menuwin, i+1, 1, scelte[i]);
                    wattroff(menuwin, A_REVERSE | A_BLINK);
                }
                scelta = wgetch(menuwin);

                switch(scelta)
                {
                    case KEY_UP:
                        evidenziato--;
                        if(evidenziato==-1){
                            evidenziato=0;
                        }
                        break;
                    case KEY_DOWN:
                        evidenziato++;
                        if(evidenziato==3){
                            evidenziato=2;
                        }
                        break;
                    case 10: //convenzione e inutilizzabilità
                        if(evidenziato == 2) {
                            uscire = true;
                            break;
                        }
                        else if (evidenziato == 1) {
                            scr_dump(menuprincipale);
                            destroy_win(menuwin);
                            opzioni();
                            break;
                        }
                    default:
                        break;
                }
            }
            getch();
            endwin();
}
};



int main(int argc, char ** argv)
{
MainMenu menu1;
menu1.menu();
    return 0;
}

