#include <iostream>
#include <ncurses.h>

#include "Entita.hpp"

Entita::Entita(int x,int y, int dim_x, int dim_y, int attr, int color, wchar_t ** stampa) {
    (*this).x = x;
    (*this).y = y;
    (*this).dim_x = dim_x;
    (*this).dim_y = dim_y;
    (*this).attr = attr;
    (*this).color = color;


    (*this).stampabile = (wchar_t **) calloc(dim_y, sizeof(wchar_t*));
    for(int i = 0; i < dim_y; i++) {
        (*this).stampabile[i] = (wchar_t *) calloc(dim_x, sizeof(wchar_t));
    }
    for(int i = 0; i < dim_y; i++) {
        for(int j = 0; j < dim_x; j++) {
            (*this).stampabile[i][j] = stampa[i][j];
        }
    }
}

Entita::~Entita() {
    for(int i = 0; i < (*this).dim_y; i++) {
        free((*this).stampabile[i]);
    }
    free((*this).stampabile);
}

void Entita::stampa(WINDOW * window, int offsetX, int offsetY) {
    wattron(window, COLOR_PAIR((*this).color));
    wattron(window, (*this).attr);
    for(int i = 0; i < (*this).dim_y; i++) {
        for(int j = 0; j < (*this).dim_x; j++) {
            move((*this).y+i+offsetY, (*this).x+j+offsetX);
            wprintw(window, "%lc", (*this).stampabile[i][j]);
        }
    } 
    wattroff(window, (*this).attr);
    wattroff(window, COLOR_PAIR((*this).color));
}
    
bool Entita::controllaContatto(Entita entita) {
    return false;
}

bool controllaContattore(/*Mappa*/);

void Entita::modificaCoordinate(int new_x, int new_y) {
    (*this).x = new_x;
    (*this).y = new_y;
}


void Entita::incrementaX(int amount) {
    (*this).x += amount;
}
void Entita::incrementaY(int amount) {
    (*this).y += amount;
}

void incrementaX_CC(Entita * arrayEntita, /*Mappa*/ int amount);
void incrementaY_CC(Entita * arrayEntita, /*Mappa*/ int amount);