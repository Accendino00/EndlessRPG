#include <iostream>
#include <ncurses.h>

#include "Entita.hpp"

Entita::Entita(int x,int y, int dim_x, int dim_y, int attr, int color, char ** stampa) {
    (*this).x = x;
    (*this).y = y;
    (*this).dim_x = dim_x;
    (*this).dim_y = dim_y;
    (*this).attr = attr;
    (*this).color = color;

    (*this).stampabile = (char **) calloc(dim_y, sizeof(char*));
    for(int i = 0; i < dim_y; i++) {
        (*this).stampabile[i] = (char *) calloc(dim_x, sizeof(char));
    }
    for(int i = 0; i < dim_y; i++) {
        for(int j = 0; j < dim_x; j++) {
            (*this).stampabile[i][j] = stampa[i][j]; 
        }
    }
}

void Entita::stampa(WINDOW * window, int offsetX, int offsetY) {
    printf("dioporco");
    wattron(window, (*this).color);
    for(int i = 0; i < (*this).dim_y; i++) {
        for(int j = 0; j < (*this).dim_x; j++) {
            printf("%c\n", (*this).stampabile[i][j]);
            mvwaddchstr(window, (*this).y+i+offsetY, (*this).x+j+offsetX,(chtype *)"X");
        }
    } 
    wattroff(window, (*this).color);
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
