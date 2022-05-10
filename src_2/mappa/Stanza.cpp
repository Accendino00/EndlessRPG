#include "../generale/libs.hpp"

Stanza::Stanza(int tipoStanza) {
    // Implementare
}

Stanza::Stanza(Entita * nemici, Entita * porte, Entita * artefatti, WINDOW * schermata_mappa, cchar_t ** matrice_stampabile, int ** matrice_logica, int x, int y, int maxx, int maxy){
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


bool Stanza::accessibile(int ** mappa, int x, int y){
    int returnbool = false;
    if(x >= 0 && x < 80 && y >= 0 && y < 20 && mappa[x][y] != 1){
        returnbool = true;
    } return returnbool;
}


cchar_t ** Stanza::da_logica_a_stampabile(int ** matrice_stanza){
    cchar_t ** matrice_da_stampare;
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
    return matrice_da_stampare;
}
//la funzione ch estampa effetivamente la faccio a parte, qui passo semplicemente da matric elogica a matrice grafica

void Stanza::stampa_stanza(WINDOW * window_one, cchar_t ** mappa_stampabile, int offset_y, int offset_x){
    for(int i = 0; i < (*this).y; i++){
        for(int j = 0; j < (*this).x; j++){
            mvwadd_wch( (window_one), (this->y)+i+offset_y, (this->x)+j+offset_y,  & (mappa_stampabile)[i][j]);
        }
    }
}

