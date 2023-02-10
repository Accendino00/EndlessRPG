#include "../generale/libs.hpp"

Entita::Entita(){
    this->vita = 1;
    this->maxVita = 1;
    this->damage = 0;
    this->y = 0;
    this->x = 0;
    this->h_dimy = 0;
    this->h_dimx = 0;
    this->s_dimy = 0;
    this->s_dimx = 0;
    this->stampabile = NULL;

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
    // La dimensione dello stampabile coincide con quella dell'hitbox
    // in questo caso, quindi l'entità fatta con questo costruttore
    // ha 1 solo frame.
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

/**
 * @brief Stampa l'entità.
 * Essa viene stampata in base alle sue coordinate x e y, però
 * viene offsettata di offsetY e offsetX. Questo permette di stamparla
 * nel suo posto giusto all'interno della mappa, ma anche di mantere la
 * logica delle x e delle y coerente.
 * 
 * @param offsetY La distanza in y da aggiungere alle coordinate dell'entità
 * @param offsetX La distanza in x da aggiungere alle coordinate dell'entità
 */
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

// Overloading del metodo controllaContatto, in modo che lo possa usare direttamente con un'altra entita'
bool Entita::controllaContatto(Entita * entita) {
    // Controllo se ciascuno dei 4 vertici di una entità è contenuto tra x e x+dimx e y e y+dimy dell'altra entità
    return controllaContatto(entita->x, entita->y, entita->h_dimx, entita->h_dimy);
}

/**
 * @brief Controllo il contatto dell'entità con un altro oggetto.
 * L'oggetto ha posizione (posx, posy) e dimensioni (h_dimx, h_dimy).
 * In particolare, la posizione fa riferimento alla posizione del vertice
 * in alto a sinistra dell'oggetto, mentre le dimensioni fanno riferimento
 * alla dimensione dell'oggetto in termini di hitbox.
 * 
 * Funziona controllando una serie di casi, in particolare:
 * 1) Se il vertice in alto a sinistra dell'entità è contenuto nell'oggetto
 * 2) Se il vertice in basso a destra dell'entità è contenuto nell'oggetto
 * ...
 * 5) Se il vertice in alto a sinistra dell'oggetto è contenuto nell'entità
 * 6) Se il vertice in basso a destra dell'oggetto è contenuto nell'entità
 * ...
 * 
 * Facendo questi 8 controlli, se uno di essi mi ritorna true, allora so che
 * c'è una sovrapposizione tra le entità. Questo controllo è comodo in quanto
 * risulta di costo costante.
 * 
 * @param posx 
 * @param posy 
 * @param h_dimx 
 * @param h_dimy 
 * @return true 
 * @return false 
 */
bool Entita::controllaContatto(int posx, int posy, int h_dimx, int h_dimy) {
    
    return (
        // Primo nel secondo
        (
            (this->x >= posx && this->x <= (posx + h_dimx - 1)) 
                && 
            (this->y >= posy && this->y <= (posy + h_dimy - 1))
        )
            ||
        (
            ((this->x + this->h_dimx - 1) >= posx && (this->x + this->h_dimx - 1) <= (posx + h_dimx - 1)) 
                && 
            ((this->y + this->h_dimy - 1) >= posy && (this->y + this->h_dimy - 1) <= (posy + h_dimy - 1))
        )
            ||
        (
            ((this->x + this->h_dimx - 1) >= posx && (this->x + this->h_dimx - 1) <= (posx + h_dimx - 1)) 
                && 
            (this->y >= posy && this->y <= (posy + h_dimy - 1))
        )
            ||
        (
            ((*this).x >= posx && (*this).x <= (posx + h_dimx - 1)) 
                && 
            ((this->y + this->h_dimy - 1) >= posy && (this->y + this->h_dimy - 1) <= (posy + h_dimy - 1))
        )
            ||
        // Secondo nel primo        
        (
            (posx >= this->x && posx <= (this->x + this->h_dimx - 1)) 
                && 
            (posy >= this->y && posy <= (this->y + this->h_dimy - 1))
        )
            ||
        (
            ((posx + h_dimx - 1) >= this->x && (posx + h_dimx - 1) <= (this->x + this->h_dimx - 1)) 
                && 
            ((posy + h_dimy - 1) >= this->y && (posy + h_dimy - 1) <= (this->y + this->h_dimy - 1))
        )
            ||
        (
            ((posx + h_dimx - 1) >= this->x && (posx + h_dimx - 1) <= (this->x + this->h_dimx - 1)) 
                && 
            (posy >= this->y && posy <= (this->y + this->h_dimy - 1))
        )
            ||
        (
            (posx >= this->x && posx <= (this->x + this->h_dimx - 1))
                && 
            ((posy + h_dimy - 1) >= this->y && (posy + h_dimy - 1) <= (this->y + this->h_dimy - 1))
        )
    );
}

/**
 * @brief In baes a ticksForAction, capisco quante azioni devo fare
 * (e che quindi aggiungo a passedActions) in base al numero di tick
 * passati dall'ultima volta che ho aggiornato l'entità. 
 */
void Entita::updateEntita() {
    // Aggiornamento dei tick e conto delle azioni che deve eseguire l'entità dall'ultima volta che è stata aggiornata
    if((gd->getCurrentTick() - this->lastTick) >= this->ticksForAction) {
        this->passedActions += (gd->getCurrentTick() - this->lastTick) / this->ticksForAction;
        this->lastTick = gd->getCurrentTick(); // Aggiorno il tick dell'ultima azione
    }
}

/**
 * @brief Per riportare i tick dell'entità a quelli correnti, senza fare aggiornamenti
 */
void Entita::toCurrentTick() {
    this->lastTick = gd->getCurrentTick();
}

/**
 * @brief Cambia il frame che viene mostrato dell'entità nella funzione stampa,
 * ciclando sui vari frame dell'entità.)
 */
void Entita::nextFrame() {
    int maxFrames = getMaxFrames();
    if(this->currentFrame < (maxFrames - 1)) {
        this->currentFrame++; 
    } else {
        this->currentFrame = 0;
    }
}

/**
 * @brief Imposta il frame dell'entità.
 * Se il frame inserito in input è più grande del numero di frame dell'entità,
 * allora il frame non viene modificato.
 * 
 * @param frame Il frame dell'entità che si vuole impostare (da 0 a maxFrames-1, inclusi)
 */
void Entita::setFrame(int frame) { 
    int maxFrames = getMaxFrames();
    if(frame < (maxFrames)) {
        this->currentFrame = frame; 
    } 
}

int Entita::getMaxFrames() {
    return (this->s_dimx / this->h_dimx);
}



// Getter e setter vari
int Entita::getDamage() {
    return this->damage;
}


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


int Entita::getMaxVita() {
    return this->maxVita;
}

void Entita::setMaxVita(int quantita) {
    this->maxVita = quantita;
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

/**
 * @brief Muove l'entità in base alla direzione e alla quantità che si passa
 * per parametro.
 * 
 * Per la definizione delle direzioni, vedere GameData.hpp
 * 
 * @param direzione Direzione in cui si vuole muovere l'entità
 *                  Usare le costanti definite in GameData.hpp
 * @param val       Quantità di cui si vuole muovere l'entità
 */
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