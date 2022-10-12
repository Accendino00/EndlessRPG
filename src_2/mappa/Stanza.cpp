#include "../generale/libs.hpp"
//#include "Stanzaprova.cpp"
/*

Stanza::Stanza(int tipoStanza) {
    // Implementare
}


int ** Stanza::scegli_stanza(){
    switch(rand() % 0){
        case 0:
        int ** mappa = Stanzaprova;
        if(Stanza::lettura_matrice(mappa) == true){
            Stanza::matrice_logica = mappa;
        }
        break;
    }
    return mappa;
}

bool Stanza::lettura_matrice(int ** mappa){
    bool returnvalue = true;
    for(int i = 0; i < maxy; i++){
        for(int j = 0; j < maxx; j++){
            if(mappa [i] [j] != 0 || mappa [i] [j] != 1){
                returnvalue = false;
            }
        }
    }
    return returnvalue;
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
    sprintf

    char ciao [20];
    sprintf(ciao, "mappa%d.map", idMappa1)  


    //EOF endodfile



Stanza::Stanza(int a){
    FILE * fin;
    char mappa_da_scegliere [100];
    int idMappa = (rand() % 1 )+ 1;
    sprintf(mappa_da_scegliere, "./mappa/matrici_mappe/mappa%d.map", idMappa);
    fin = fopen( mappa_da_scegliere , "r");
    
    
    //come aprire un file

    this -> matrice_logica = new int* [DIM_STANZA_Y];
    for(int i=0; i < DIM_STANZA_Y; i++ ){
        this -> matrice_logica [i] = new int [DIM_STANZA_X];
    }
        
    
    //alloco memoria per la matrice

    for(int i= 0; i < DIM_STANZA_Y; i++){
        for(int j = 0; j < DIM_STANZA_X; j++){
            matrice_logica [i][j] = fgetc(fin) -48 ;
        }
        fgetc(fin);
    }
    fclose(fin);
    
    //leggo il file


};

Stanza::Stanza(int a){
    FILE * fin;
    char mappa_da_scegliere [100];
    int idMappa = (rand() % 1 )+ 1;
    sprintf(mappa_da_scegliere, "./mappa/matrici_mappe/mappaBoss%d.map", idMappa);
    fin = fopen( mappa_da_scegliere , "r");
    
    
    //come aprire un file

    this -> matrice_logica = new int * [DIM_STANZA_BOSS_Y];
    for(int i=0; i < DIM_STANZA_BOSS_Y; i++ ){
        this -> matrice_logica [i] = new int [DIM_STANZA_BOSS_X];
    }
        
    
    //alloco memoria per la matrice

    for(int i= 0; i < DIM_STANZA_Y; i++){
        for(int j = 0; j < DIM_STANZA_X; j++){
            matrice_logica [i][j] = fgetc(fin) -48 ;
        }
        fgetc(fin);
    }
    fclose(fin);
    
    //leggo il file

    



};
*/

/**
 * @brief Costruttore di Stanza. Usando l'id capisce che tipo di stanza creare. 
 * Viene scelta una stanza casuale tra quelle presenti nei file, viene letta
 * e viene impostata.
 * 
 * @param id Può essere "ID_STANZA_SPAWN", "ID_STANZA_NORMALE" oppure "ID_STANZA_BOSS" 
 */
Stanza::Stanza(int id){
    
    this->listaPorte = new ListaPorte();
    this->listaProiettili = new ListaProiettili();
    this->listaNemici = new ListaNemici();
    
    this->idStanza = id;

    FILE * fin;
    char mappa_da_scegliere [100];  // Stringa contenente il nome del file della mappa
    int idMappa = 0;

    // Scelta del tipo di mappa usando il parametro "id"
    if (id == ID_STANZA_SPAWN) {
        idMappa = 0;
        this->dim_y = DIM_STANZA_SPAWN_Y;
        this->dim_x = DIM_STANZA_SPAWN_X;
    } else if (id == ID_STANZA_NORMALE){
        idMappa = (rand() % NUMERO_STANZE_NORMALI) + 1; // Impostazione dell'id casuale della mappa
        this->dim_y = DIM_STANZA_Y;
        this->dim_x = DIM_STANZA_X;
    } else if(id == ID_STANZA_BOSS){
        idMappa = (rand() % NUMERO_STANZE_BOSS) + 1; // Impostazione dell'id casuale della mappa
        this->dim_y = DIM_STANZA_BOSS_Y;
        this->dim_x = DIM_STANZA_BOSS_X;
    }

    // Creazione della stringa che contiene il percorso al file della mappa scelta
    sprintf(mappa_da_scegliere, "./mappa/matrici_mappe/mappa%s%d.map", (id == ID_STANZA_BOSS)?("Boss"):(""), idMappa);
    fin = fopen( mappa_da_scegliere , "r");
    
    
    // Allocazione della matrice logica della mappa
    this -> matrice_logica = new int* [this->dim_y];
    for(int i=0; i < this->dim_y; i++ ){
        this -> matrice_logica [i] = new int [this->dim_x];
    }
        
    // Impostazione della matrice logica
    for(int i= 0; i < this->dim_y; i++){
        for(int j = 0; j < this->dim_x; j++){
            matrice_logica [i][j] = fgetc(fin) - (int)'0'; // Traduco i numeri ascii in interi
        }
        fgetc(fin);
    }
    fclose(fin);


    // Allocazione della matrice stampabile
    this -> matrice_stampabile = new cchar_t * [dim_y];
    for(int i = 0; i < dim_y; i++){
        this -> matrice_stampabile [i] = new cchar_t [dim_x];
    }

};

Stanza::~Stanza(){
    // Dealloco tutto
    delete (this->listaPorte);
    delete (this->listaNemici);
    for(int i = 0; i < (*this).dim_y; i++) {
        delete[] this->matrice_stampabile[i];
        delete[] this->matrice_logica[i];
    }
    delete[] this->matrice_stampabile;
    delete[] this->matrice_logica;
}

/**
 * @brief Stampa la stanza. Deve essere chiamato dopo il metodo "da_logica_a_stampabile"
 * 
 * Utilizzando la matrice "matrice_stampabile", ne stampa i vari caratteri usando
 * il metodo specifico "mvadd_wch".
 */
void Stanza::stampa_stanza(){ 
    int offsetx = this->zero_x();
    int offsety = this->zero_y();
    for(int i = 0; i < this->dim_y; i++){
        for(int j = 0; j < this->dim_x; j++){
            mvadd_wch(offsety+i , offsetx+j, &(matrice_stampabile[i][j]));
        }
    }

    (*this).listaPorte->stampaTutte(this->zero_y(), this->zero_x());   
    (*this).listaProiettili->stampaTutte(this->zero_y(), this->zero_x());   
    (*this).listaNemici->stampaTutte(this->zero_y(), this->zero_x());   
}

int Stanza::zero_x(){
    return ((gd -> getTerminalX()) - this -> dim_x)/2;
}

int Stanza::zero_y(){
    return ((gd -> getTerminalY()) - this -> dim_y)/2;
}


/**
 * @brief Imposta la presenza di porte nella matrice logica della stanza.
 * 
 * Se il booleano della porta corrispondente è vero, allora la porta che si trova
 * in quella direzione nella stanza viene impostata come esistente. 
 * Ovvero i valori della matrice logica che si trovano nelle posizioni corrette vengono
 * sostituiti da caselle vuote.
 * 
 * Vengono anche impostate le entità "porta" della stanza. 
 * 
 * @param nord 
 * @param sud 
 * @param est 
 * @param ovest 
 */
void Stanza::imposta_porte(bool nord, bool sud, bool est, bool ovest){

    // Imposto le porte della matrice logica e poi creo le entità
    if(nord){
        for(int i = 0; i < DIMENSIONE_PORTA_ORIZZONTALE; i++){
            matrice_logica [0] [i + (int)((this->dim_x - DIMENSIONE_PORTA_ORIZZONTALE)/2)] = 0;
        }
        this->listaPorte->addEntita(new Porta(this->idStanza, PORTA_NORD, false));
    }
    if(sud){
        for(int i = 0; i < DIMENSIONE_PORTA_ORIZZONTALE; i++){
            matrice_logica [this->dim_y-1] [i + (int)((this->dim_x - DIMENSIONE_PORTA_ORIZZONTALE)/2)] = 0;
        }
        this->listaPorte->addEntita(new Porta(this->idStanza, PORTA_SUD, false));
    }
    if(est){
        for(int i = 0; i < DIMENSIONE_PORTA_VERTICALE; i++){
            matrice_logica [i + (int)((this->dim_y - DIMENSIONE_PORTA_VERTICALE)/2)] [this->dim_x-1] = 0;
        }
        this->listaPorte->addEntita(new Porta(this->idStanza, PORTA_EST, false));
    }
    if(ovest){
        for(int i = 0; i < DIMENSIONE_PORTA_VERTICALE; i++){
            matrice_logica [i + (int)((this->dim_y - DIMENSIONE_PORTA_VERTICALE)/2)] [0] = 0;
        }
        this->listaPorte->addEntita(new Porta(this->idStanza, PORTA_OVEST, false));
    }
}

/**
 * @brief Trasforma la matrice logica in matrice stampabile. 
 * Dopo di questo, la stanza può essere stampata, ovvero il metodo "stampa_stanza" funziona come previsto.
 */
void Stanza::da_logica_a_stampabile(){
    for(int i = 0; i < dim_y; i++){
        for(int j = 0; j < dim_x; j++){
            switch(matrice_logica [i] [j]){
                case STANZA_SPAZIOLIBERO:
                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, FLOOR_PAIR, NULL);
                break;
                case STANZA_MURO:
                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, WALL_PAIR, NULL);
                break;
                case STANZA_NEMICONORMALE:
                    listaNemici->addEntita(new Nemico(NORMAL_ENEMY, i, j));
                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, FLOOR_PAIR, NULL);
                break;
                case STANZA_NEMICOBOSS:
                    listaNemici->addEntita(new Nemico(BOSS_ENEMY, i, j));
                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, FLOOR_PAIR, NULL);
                break;
            }
        }
    }
}

/*
// Da rivedere
bool Stanza::accessibile(int y_entity, int x_entity){
    //int offsetx = ((gd -> getTerminalX()) - this -> dim_x)/2;
    //int offsety = ((gd -> getTerminalY()) - this -> dim_y)/2;
    //int halfx = dim_x/2;
    //int halfy = dim_y/2;
    int returnbool = false;
    if(
        x_entity >= 0 && 
        x_entity < this -> dim_x && 
        y_entity > 0 && 
        y_entity < this -> dim_y && 
        this -> matrice_logica [y_entity] [x_entity] != 1
    ){
        returnbool = true;
    } return returnbool;
}
*/

/* ANCORA DA FARE::

    Pulire il codice
    Impostare lo spawn dei nemici 
        (in attesa di petru, ma puoi già pensare a come 
        fare impostanto di punti di spawn e usando entità 
        placeholder)

    Fare un metodo che ha come parametri "x" e "y" 
    e ritorna true se è una casella della mappa libera
    o false se vi è un muro, interno o esterno, 
    oppure se è fuori dai bounds della mappa.
        -(Sostituto di accessibile)

*/

//  Solo per il giocatore serve fare il controllo della direzione porta
bool Stanza::accessibile(int y_entity, int x_entity, bool giocatore){
    bool returnvalue = false;
    // Prima controllo se c'è la porta, poi controllo se mi sto muovendo fuori da quella porta
    if(giocatore && direzione_porta(y_entity, x_entity)!=0){
        returnvalue = true;
    }
    else if(
        x_entity >= 0 && 
        x_entity < (this -> dim_x) && 
        y_entity >= 0 && 
        y_entity < (this -> dim_y) && 
        this -> matrice_logica [y_entity] [x_entity] != 1
    ){
        returnvalue = true;
    }
    
    // Da controllare anche il contatto con entita

    return returnvalue;
}

/**
 * @brief Cerco se dove sono c'è una porta ed in che direzione si trova quella porta, resituendo la direzione se giusta
 * 
 * @param y_entity coordinata y dell'entità
 * @param x_entity coordinata x dell'entità
 * @return int attribuito alla direzione
 */
int Stanza::direzione_porta(int y_entity, int x_entity){
    int returnvalue = 0;
        // Porta NN
    if(     matrice_logica [0] [(int)(dim_x/2)] == 0 
        &&  y_entity <= -1 
        &&  x_entity >= ((this->dim_x - DIMENSIONE_PORTA_ORIZZONTALE)/2) 
        &&  x_entity <= ((this->dim_x - DIMENSIONE_PORTA_ORIZZONTALE)/2) + DIMENSIONE_PORTA_ORIZZONTALE)
    {
        returnvalue = DIRECTION_NN;
    }
        // Porta SS
    else if(     matrice_logica [dim_y-1] [(int)(dim_x/2)] == 0 
        &&  y_entity >= dim_y  
        &&  x_entity >= ((this->dim_x - DIMENSIONE_PORTA_ORIZZONTALE)/2) 
        &&  x_entity <= ((this->dim_x - DIMENSIONE_PORTA_ORIZZONTALE)/2) + DIMENSIONE_PORTA_ORIZZONTALE)
    {
        returnvalue = DIRECTION_SS;
    }
        // Porta EE
    else if(     matrice_logica [(int)(dim_y/2)] [dim_x-1] == 0
        &&  x_entity >= dim_x 
        &&  y_entity >= ((this->dim_y - DIMENSIONE_PORTA_VERTICALE)/2) 
        &&  y_entity <= ((this->dim_y - DIMENSIONE_PORTA_VERTICALE)/2) + DIMENSIONE_PORTA_VERTICALE)
    {
        returnvalue = DIRECTION_EE;
    }
        // Porta OO
    else if(     matrice_logica [(int)(dim_y/2)] [0] == 0 
        &&  x_entity <= -1
        &&  y_entity >= ((this->dim_y - DIMENSIONE_PORTA_VERTICALE)/2) 
        &&  y_entity <= ((this->dim_y - DIMENSIONE_PORTA_VERTICALE)/2) + DIMENSIONE_PORTA_VERTICALE)
    {
        returnvalue = DIRECTION_OO;
    }
    return returnvalue;
};

int Stanza::getDimX() {
    return this->dim_x;
}

int Stanza::getDimY() {
    return this->dim_y;
}

ListaProiettili * Stanza::getListaProiettili() {
    return this->listaProiettili;
}

void Stanza::aggiungiProiettile(Proiettile * proiettile) {
    this->listaProiettili->addEntita(proiettile);
}


void Stanza::calcolo_logica(Player * player){
    this->listaProiettili->aggiornaEntita(this, player);
    this->listaNemici->aggiornaEntita(this, player);
}

void Stanza::aggiornaTick() {
    this->listaProiettili->aggiornaTick();
    this->listaNemici->aggiornaTick();
}