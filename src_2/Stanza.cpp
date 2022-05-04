#include "Entita.hpp"
#include <ncursesw/ncurses.h>


Stanza::Stanza(Entita * nemici, Entita * porte, Entita * artefatti, WINDOW * schermata_mappa, wchar_t ** matrice_stampabile, int ** matrice_logica, int x, int y, int maxx, int maxy){
    (*this).nemici = nemici;
    (*this).porte = porte;
    (*this).artefatti = artefatti;
    (*this).schermata_mappa = schermata_mappa;
    (*this).matrice_stampabile = matrice_stampabile;
    (*this).matrice_logica = matrice_logica;
    (*this).x = x;
    (*this).y = y;
    (*this).maxx = getmaxx(stdscr); //sus
    (*this).maxy = getmaxy(stdscr);
}

/*
    bool Stanza::accessibile(int ** mappa, int x, int y){
        int returnbool = false;
        if(x >= 0 && x < 80 && y >= 0 && y < 20 && mappa[x][y] != 1){
            returnbool = true;
        } return returnbool;
    }
*/

wchar_t ** Stanza::genera_stanza(int ** matrice_stanza){
    wchar_t ** matrice_da_stampare;
    for(int i = 0; i < maxy; i++){
        for(int j = 0; j < maxx; j++){
            switch(matrice_stanza [i] [j]){
                case(0):
                break;
                case(1):
                break;
                case(2):
                break;
                case(3):
                break;
                case(4):
                break;
                case(5):
                //if l'entià è spawnata
                //matrice_da_stampare [i] [j] = "";
                break;
            }
        }
    }
}
//la funzione ch estampa effetivamente la faccio a parte, qui passo semplicemente da matric elogica a matrice grafica

