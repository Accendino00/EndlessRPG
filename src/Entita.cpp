#pragma once

#include <iostream>

#ifdef __linux__ 
    #include <ncurses.h>
#elif _WIN32
    #include <ncursesw/ncurses.h>
#else
    #error Errore di compilazione, sistema operativo non supportato
#endif

#include "Entita.hpp"

Entita::Entita(int x,int y, int dim_x, int dim_y, int attr, wchar_t ** stampa) {
    (*this).x = x;
    (*this).y = y;
    (*this).dim_x = dim_x;
    (*this).dim_y = dim_y;
    (*this).attr = attr;


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
    wattron(window, (*this).attr);
    for(int i = 0; i < (*this).dim_y; i++) {
        for(int j = 0; j < (*this).dim_x; j++) {
            move((*this).y+i+offsetY, (*this).x+j+offsetX);
            wprintw(window, "%lc", (*this).stampabile[i][j]);
        }
    } 
    wattroff(window, (*this).attr);
}

bool Entita::controllaContatto(Entita * entita) {
        // Controllo se ciascuno dei 4 vertici di una entità è contenuto tra x e x+dimx e y e y+dimy dell'altra entità

    return (
        // Primo nel secondo
        (
            (this->x >= entita->x && this->x < (entita->x + entita->dim_x)) 
                && 
            (this->y >= entita->y && this->y < (entita->y + entita->dim_y))
        )
            ||
        (
            ((this->x + this->dim_x) > entita->x && (this->x + this->dim_x) < (entita->x + entita->dim_x)) 
                && 
            ((this->y + this->dim_y) > entita->y && (this->y + this->dim_y) < (entita->y + entita->dim_y))
        )
            ||
        (
            ((this->x + this->dim_x) > entita->x && (this->x + this->dim_x) < (entita->x + entita->dim_x)) 
                && 
            (this->y >= entita->y && this->y < (entita->y + entita->dim_y))
        )
            ||
        (
            ((*this).x >= entita->x && (*this).x < (entita->x + entita->dim_x)) 
                && 
            ((this->y + this->dim_y) > entita->y && (this->y + this->dim_y) < (entita->y + entita->dim_y))
        )
            ||
        // Secondo nel primo        
        (
            (entita->x >= this->x && entita->x < (this->x + this->dim_x)) 
                && 
            (entita->y >= this->y && entita->y < (this->y + this->dim_y))
        )
            ||
        (
            ((entita->x + entita->dim_x) > this->x && (entita->x + entita->dim_x) < (this->x + this->dim_x)) 
                && 
            ((entita->y + entita->dim_y) > this->y && (entita->y + entita->dim_y) < (this->y + this->dim_y))
        )
            ||
        (
            ((entita->x + entita->dim_x) > this->x && (entita->x + entita->dim_x) < (this->x + this->dim_x)) 
                && 
            (entita->y >= this->y && entita->y < (this->y + this->dim_y))
        )
            ||
        (
            (entita->x >= this->x && entita->x < (this->x + this->dim_x))
                && 
            ((entita->y + entita->dim_y) > this->y && (entita->y + entita->dim_y) < (this->y + this->dim_y))
        )
    );
}

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