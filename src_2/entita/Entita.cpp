#include "../generale/libs.hpp"

Entita::Entita(){
    this->y = 0;
    this->x = 0;
    this->h_dimy = 0;
    this->h_dimx = 0;
    this->stampabile = NULL;
    this->vita = 1;
    this->maxVita = 1;

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

    this->vita = life;
    this->maxVita = life;

    this->passedActions = 0;
    this->ticksForAction = 1000; // Placeholder
    this->lastTick = gd->getCurrentTick();

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
        for(int j = 0; j < ((*this).h_dimx); j++) {
            mvadd_wch(  (this->y)+i+offsetY, 
                        (this->x)+j+offsetX, 
                        & (this->stampabile)[i][j+offsetDisplay]);
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

//overloading del metodo controllaContatto
bool Entita::controllaContatto(int posx, int posy, int h_dimx, int h_dimy) {
    
    // Controllo se ciascuno dei 4 vertici di una entità è contenuto tra x e x+dimx e y e y+dimy dell'altra entità
    return (
        // Primo nel secondo
        (
            (this->x >= posx && this->x < (posx + h_dimx)) 
                && 
            (this->y >= posy && this->y < (posy + h_dimy))
        )
            ||
        (
            ((this->x + this->h_dimx) > posx && (this->x + this->h_dimx) < (posx + h_dimx)) 
                && 
            ((this->y + this->h_dimy) > posy && (this->y + this->h_dimy) < (posy + h_dimy))
        )
            ||
        (
            ((this->x + this->h_dimx) > posx && (this->x + this->h_dimx) < (posx + h_dimx)) 
                && 
            (this->y >= posy && this->y < (posy + h_dimy))
        )
            ||
        (
            ((*this).x >= posx && (*this).x < (posx + h_dimx)) 
                && 
            ((this->y + this->h_dimy) > posy && (this->y + this->h_dimy) < (posy + h_dimy))
        )
            ||
        // Secondo nel primo        
        (
            (posx >= this->x && posx < (this->x + this->h_dimx)) 
                && 
            (posy >= this->y && posy < (this->y + this->h_dimy))
        )
            ||
        (
            ((posx + h_dimx) > this->x && (posx + h_dimx) < (this->x + this->h_dimx)) 
                && 
            ((posy + h_dimy) > this->y && (posy + h_dimy) < (this->y + this->h_dimy))
        )
            ||
        (
            ((posx + h_dimx) > this->x && (posx + h_dimx) < (this->x + this->h_dimx)) 
                && 
            (posy >= this->y && posy < (this->y + this->h_dimy))
        )
            ||
        (
            (posx >= this->x && posx < (this->x + this->h_dimx))
                && 
            ((posy + h_dimy) > this->y && (posy + h_dimy) < (this->y + this->h_dimy))
        )
    );
}


void Entita::updateEntita() {
    // Aggiornamento dei tick e conto delle azioni che deve eseguire l'entità dall'ultima volta che è stata aggiornata
    if((gd->getCurrentTick() - this->lastTick) >= this->ticksForAction) {
        this->passedActions += (gd->getCurrentTick() - this->lastTick) / this->ticksForAction;
        this->lastTick = gd->getCurrentTick();
    }
}

void Entita::toCurrentTick() {
    this->lastTick = gd->getCurrentTick();
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



// Getter e setter di vita
int Entita::getVita() {
    return this->vita;
}

void Entita::setVita(int quantita) {
    this->vita = quantita;
}

void Entita::modificaVita(int quantita) {
    if(quantita + this->getVita() > this->vita) {
        this->vita = this->vita;
    } else {
        this->vita += quantita;
    }
}


// Getter e setter di MaxVita
int Entita::getMaxVita() {
    return this->maxVita;
}

void Entita::setMaxVita(int quantita) {
    this->maxVita = quantita;
}



int Entita::getDamage() {
    return this->damage;
}


void Entita::modificaCoordinate(int new_y, int new_x) {
    (*this).y = new_y;
    (*this).x = new_x;
}

void Entita::incrementaX(int val) {
    (*this).x += val;
}
void Entita::incrementaY(int val) {
    (*this).y -= val;
}
int Entita::getX() {
    return this->x;
}

int Entita::getY() {
    return this->y;
}


int Entita::getDimX() {
    return this->h_dimx;
}

int Entita::getDimY() {
    return this->h_dimy;
}

void Entita::muovi(int direzione, int val) {
    switch(direzione) {
        case DIRECTION_NN:
            this->incrementaY(val);
            break;
        case DIRECTION_SS:
            this->incrementaY(-val);
            break;
        case DIRECTION_EE:
            this->incrementaX(val);
            break;
        case DIRECTION_OO:
            this->incrementaX(-val);
            break;
        case DIRECTION_NE:
            this->incrementaY(val);
            this->incrementaX(val);
            break;
        case DIRECTION_SE:
            this->incrementaY(-val);
            this->incrementaX(val);
            break;
        case DIRECTION_SO:
            this->incrementaY(-val);
            this->incrementaX(-val);
            break;
        case DIRECTION_NO:
            this->incrementaY(val);
            this->incrementaX(-val);
            break;
    }
}

/**
 * @brief Funzione che controlla se l'entità si può muovere in una certa
 * direzione, ad un certo numero di x e y, in una specifica stanza.
 * 
 * 
 * @param direzione Direzione del moviemnto, vedere le costanti DIRECTION_* in GameData.hpp
 * @param val       Numero di "spazi" di cui si vuole muovere l'entità
 * @param stanza    Stanza in cui si vuole muovere l'entità
 * @param giocatore Se l'entità che si vuole muovere è il giocatore o no
 *                  Ci sono delle differenze fondamentali, in quanto il giocatore può 
 *                  "uscire" dalle stanze, a differenza delle altre entità.
 * 
 * @return int      Ritorna un valore particolare che indica in cosa si è imbattuta l'entità.
 *                  Vedere le costanti STANZA_ACC_* in Stanza.hpp
 */
int Entita::movimentoValido(int direzione, int val, Stanza * stanza, bool giocatore) {    
    int returnValue = STANZA_ACC_LIBERO;
    muovi(direzione, val);
    returnValue = stanza -> accessibile(this, giocatore);
    muovi(direzione, -val);
    return returnValue;
}