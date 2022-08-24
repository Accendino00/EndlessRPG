#include "../generale/libs.hpp"

Entita::Entita(){
    this->y = 0;
    this->x = 0;
    this->h_dimy = 0;
    this->h_dimx = 0;
    this->stampabile = NULL;
    this->currentLife = 1;
    this->maxLife = 1;

    this->passedActions = 0;
    this->ticksForAction = 0;
    this->lastTick = gd->getCurrentTick();
}

Entita::Entita(int life, int y,int x, int h_dimy, int h_dimx, cchar_t ** stampa) {
    // Impostazione delle coordinate
    (*this).y = y;
    (*this).x = x;

    // Impostazione dell'hitbox
    (*this).h_dimy = h_dimy;
    (*this).h_dimx = h_dimx;
    // Se non specificato, la dimensione del hitbox coincide con quella dello 
    // stampabile, e pertanto ve ne esiste solo 1.
    (*this).s_dimy = h_dimy;
    (*this).s_dimx = h_dimx;
    (*this).currentFrame = 0;

    this->currentLife = life;
    this->maxLife = life;

    // Alloco lo "stampabile" dell'entità
    (*this).stampabile = new cchar_t * [s_dimy];
    for(int i = 0; i < s_dimy; i++) {
        (*this).stampabile[i] =  new cchar_t [s_dimx];
    }
    // Uso delle variabili temporanee dove salvare i dati provenienti dai cchar_t in input
    // Per impostarli nel cchar_t dell'entità
    wchar_t temp_c [CCHARW_MAX];
    attr_t temp_a;
    short temp_s;

    // Imposto il cchar_t dell'entità
    for(int i = 0; i < s_dimy; i++) {
        for(int j = 0; j < s_dimx; j++) {
            getcchar(&(stampa[i][j]), temp_c, &temp_a, &temp_s, NULL);
            setcchar(&((*this).stampabile[i][j]), temp_c, temp_a, temp_s, NULL);
        }
    }
}

Entita::~Entita() {
    // Dealloco tutto lo stampabile
    for(int i = 0; i < (*this).s_dimy; i++) {
        delete[] this->stampabile[i];
    }
    delete[] this->stampabile;
}

void Entita::stampa(int offsetY, int offsetX) {
    int offsetDisplay = (*this).h_dimx * currentFrame;
    for(int i = 0; i < (*this).h_dimy; i++) {
        for(int j = offsetDisplay; j < ((*this).h_dimx + (offsetDisplay)); j++) {
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
            (this->x >= entita->x && this->x < (entita->x + entita->h_dimx)) 
                && 
            (this->y >= entita->y && this->y < (entita->y + entita->h_dimy))
        )
            ||
        (
            ((this->x + this->h_dimx) > entita->x && (this->x + this->h_dimx) < (entita->x + entita->h_dimx)) 
                && 
            ((this->y + this->h_dimy) > entita->y && (this->y + this->h_dimy) < (entita->y + entita->h_dimy))
        )
            ||
        (
            ((this->x + this->h_dimx) > entita->x && (this->x + this->h_dimx) < (entita->x + entita->h_dimx)) 
                && 
            (this->y >= entita->y && this->y < (entita->y + entita->h_dimy))
        )
            ||
        (
            ((*this).x >= entita->x && (*this).x < (entita->x + entita->h_dimx)) 
                && 
            ((this->y + this->h_dimy) > entita->y && (this->y + this->h_dimy) < (entita->y + entita->h_dimy))
        )
            ||
        // Secondo nel primo        
        (
            (entita->x >= this->x && entita->x < (this->x + this->h_dimx)) 
                && 
            (entita->y >= this->y && entita->y < (this->y + this->h_dimy))
        )
            ||
        (
            ((entita->x + entita->h_dimx) > this->x && (entita->x + entita->h_dimx) < (this->x + this->h_dimx)) 
                && 
            ((entita->y + entita->h_dimy) > this->y && (entita->y + entita->h_dimy) < (this->y + this->h_dimy))
        )
            ||
        (
            ((entita->x + entita->h_dimx) > this->x && (entita->x + entita->h_dimx) < (this->x + this->h_dimx)) 
                && 
            (entita->y >= this->y && entita->y < (this->y + this->h_dimy))
        )
            ||
        (
            (entita->x >= this->x && entita->x < (this->x + this->h_dimx))
                && 
            ((entita->y + entita->h_dimy) > this->y && (entita->y + entita->h_dimy) < (this->y + this->h_dimy))
        )
    );
}

void Entita::updateTicks() {
    if((gd->getCurrentTick() - this->lastTick) >= this->ticksForAction) {
        this->passedActions += (gd->getCurrentTick() - this->lastTick) / this->ticksForAction;
        this->lastTick = gd->getCurrentTick();
    }
}

void Entita::nextFrame() {
    int maxFrames = getMaxFrames();
    if(this->currentFrame < (maxFrames - 1)) {
        this->currentFrame++; 
    } else {
        this->currentFrame = 0;
    }
}

void Entita::setFrame(int frame) { 
    int maxFrames = getMaxFrames();
    if(frame < (maxFrames)) {
        this->currentFrame = frame; 
    } 
}

int Entita::getMaxFrames() {
    return (this->s_dimx / this->h_dimx);
}

void Entita::modificaVita(int quantita) {
    if(quantita + this->getVita() > this->maxLife) {
        this->currentLife = this->maxLife;
    } else {
        this->currentLife += quantita;
    }
}

int Entita::getVita() {
    return this->currentLife;
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