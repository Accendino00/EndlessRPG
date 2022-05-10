#include "../generale/libs.hpp"

Entita::Entita(){
    this->y = 0;
    this->x = 0;
    this->dim_y = 0;
    this->dim_x = 0;
    this->stampabile = NULL;
}

Entita::Entita(int life, int y,int x, int dim_y, int dim_x, cchar_t ** stampa) {
    (*this).y = y;
    (*this).x = x;
    (*this).dim_y = dim_y;
    (*this).dim_x = dim_x;


    (*this).stampabile = new cchar_t * [dim_y];
    for(int i = 0; i < dim_y; i++) {
        (*this).stampabile[i] =  new cchar_t [dim_x];
    }
    wchar_t temp_c [CCHARW_MAX];
    attr_t temp_a;
    short temp_s;
    for(int i = 0; i < dim_y; i++) {
        for(int j = 0; j < dim_x; j++) {
            getcchar(&(stampa[i][j]), temp_c, &temp_a, &temp_s, NULL);
            setcchar(&((*this).stampabile[i][j]), temp_c, temp_a, temp_s, NULL);
        }
    }
}

Entita::~Entita() {
    for(int i = 0; i < (*this).dim_y; i++) {
        free((*this).stampabile[i]);
    }
    free((*this).stampabile);
}

void Entita::stampa(int offsetY, int offsetX) {
    for(int i = 0; i < (*this).dim_y; i++) {
        for(int j = 0; j < (*this).dim_x; j++) {
            mvadd_wch(  (this->y)+i+offsetY, 
                        (this->x)+j+offsetX, 
                        & (this->stampabile)[i][j]);
        }
    } 
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

void Entita::modificaCoordinate(int new_y, int new_x) {
    (*this).y = new_y;
    (*this).x = new_x;
}

void Entita::incrementaX(int amount) {
    (*this).x += amount;
}
void Entita::incrementaY(int amount) {
    (*this).y -= amount;
}