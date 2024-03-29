#include "../generale/libs.hpp"
//#include "Stanzaprova.cpp"


/**
 * @brief Costruttore di Stanza. Usando l'id capisce che tipo di stanza creare. 
 * Viene scelta una stanza casuale tra quelle presenti nei file, viene letta
 * e viene impostata.
 * 
 * La parte logica non viene interpretata, viene solo letta e salvata.
 * La parte stampabile delle stanza invece viene solo allocata.
 * 
 * @param id Può essere "ID_STANZA_SPAWN", "ID_STANZA_NORMALE" oppure "ID_STANZA_BOSS" 
 */
Stanza::Stanza(int id){
    this->dim_x=0;    
    this->dim_y=0;

    this->listaPorte = new ListaPorte();
    this->listaProiettili = new ListaProiettili();
    this->listaNemici = new ListaNemici();
    this->listaArtefatti = new ListaArtefatti();
    

    this->esplorata = false;
    this->trovata = false;

    this->idStanza = id;

    FILE * fin;
    char mappa_da_scegliere [100];  // Stringa contenente il nome del file della mappa
    int idMappa = 0;
    
    // Scelta del tipo di mappa usando il parametro "id"
    if (id == ID_STANZA_SPAWN) {
        idMappa = 0;
    } else if (id == ID_STANZA_NORMALE){
        idMappa = (rand() % NUMERO_STANZE_NORMALI) + 1; // Impostazione dell'id casuale della mappa
    } else if(id == ID_STANZA_BOSS){
        idMappa = (rand() % NUMERO_STANZE_BOSS) + 1; // Impostazione dell'id casuale della mappa
    }
    
    // Creazione della stringa che contiene il percorso al file della mappa scelta
    sprintf(mappa_da_scegliere, "./mappa/matrici_mappe/mappa%s%d.map", (id == ID_STANZA_BOSS)?("Boss"):(""), idMappa);
    fin = fopen( mappa_da_scegliere , "r");
    
    //controllo fino a fine riga per trovare le x
    while(fgetc(fin)!='\n'){
        this->dim_x+=1;
    }
    rewind(fin);

    //controllo fino a fine file per trovare le y
    while(!feof(fin)){
        if(fgetc(fin)=='\n'){
            this->dim_y+=1;
        }
    }
    rewind(fin);
    
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

int Stanza::getId(){
    return this->idStanza;
}

Stanza::~Stanza(){
    // Dealloco tutto
    delete (this->listaPorte);
    delete (this->listaNemici);
    delete (this->listaProiettili);
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
    (*this).listaArtefatti->stampaTutte(this->zero_y(), this->zero_x());   
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
void Stanza::imposta_porte(bool nord, bool sud, bool est, bool ovest, int boss){
    // Imposto le porte della matrice logica e poi creo le entità
    if(nord){
        for(int i = 0; i < DIMENSIONE_PORTA_ORIZZONTALE; i++){
            matrice_logica [0] [i + (int)((this->dim_x - DIMENSIONE_PORTA_ORIZZONTALE)/2)] = 0;
        }
        if(boss == DIRECTION_NN){
            this->listaPorte->addEntita(new Porta(PORTA_NORD, true, this->dim_y, this->dim_x));
        } else {
            this->listaPorte->addEntita(new Porta(PORTA_NORD, false, this->dim_y, this->dim_x));
        }    
    }
    if(sud){
        for(int i = 0; i < DIMENSIONE_PORTA_ORIZZONTALE; i++){
            matrice_logica [this->dim_y-1] [i + (int)((this->dim_x - DIMENSIONE_PORTA_ORIZZONTALE)/2)] = 0;
        }
        if(boss == DIRECTION_SS){
            this->listaPorte->addEntita(new Porta(PORTA_SUD, true, this->dim_y, this->dim_x));
        } else{
            this->listaPorte->addEntita(new Porta(PORTA_SUD, false, this->dim_y, this->dim_x));
        } 
    }
    if(est){
        for(int i = 0; i < DIMENSIONE_PORTA_VERTICALE; i++){
            matrice_logica [i + (int)((this->dim_y - DIMENSIONE_PORTA_VERTICALE)/2)] [this->dim_x-1] = 0;
        }
        if(boss == DIRECTION_EE){
            this->listaPorte->addEntita(new Porta(PORTA_EST, true, this->dim_y, this->dim_x));
        } else{
            this->listaPorte->addEntita(new Porta(PORTA_EST, false, this->dim_y, this->dim_x));
        }
    }
    if(ovest){
        for(int i = 0; i < DIMENSIONE_PORTA_VERTICALE; i++){
            matrice_logica [i + (int)((this->dim_y - DIMENSIONE_PORTA_VERTICALE)/2)] [0] = 0;
        }
        if(boss == DIRECTION_OO){
            this->listaPorte->addEntita(new Porta(PORTA_OVEST, true, this->dim_y, this->dim_x));
        } else{
            this->listaPorte->addEntita(new Porta(PORTA_OVEST, false, this->dim_y, this->dim_x));
        }    
    }
}

/**
 * @brief Trasforma la matrice logica in matrice stampabile. 
 * Dopo di questo, la stanza può essere stampata, ovvero il metodo "stampa_stanza" funziona come previsto.
 * 
 * Il numero del livello viene usato per generare i nemici
 * 
 * @param numLivello Il livello attuale. Più è alto, più i nemici sono forti.
 */
void Stanza::da_logica_a_stampabile(int numLivello) {
    for(int i = 0; i < dim_y; i++){
        for(int j = 0; j < dim_x; j++){
            switch(matrice_logica [i] [j]){
                Nemico * nemicoGenerato;
                case STANZA_SPAZIOLIBERO:
                    switch(this -> getId()){
                        case ID_STANZA_SPAWN:
                            setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, MAP_SPAWN_PAIR, NULL);
                            break;
                        case ID_STANZA_NORMALE:
                            setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, MAP_NORMAL_PAIR, NULL);
                            break;
                        case ID_STANZA_BOSS:
                            setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, MAP_BOSS_PAIR, NULL);
                            break;
                    }
                break;
                case STANZA_MURO:
                    switch(this -> getId()){
                        case ID_STANZA_SPAWN:
                            setcchar(&(matrice_stampabile [i] [j]), L"█", A_NORMAL, MAP_SPAWN_PAIR, NULL);
                            break;
                        case ID_STANZA_NORMALE:
                            setcchar(&(matrice_stampabile [i] [j]), L"█", A_NORMAL, MAP_NORMAL_PAIR, NULL);
                            break;
                        case ID_STANZA_BOSS:
                            setcchar(&(matrice_stampabile [i] [j]), L"█", A_NORMAL, MAP_BOSS_PAIR, NULL);
                            break;
                    }
                break;
                case STANZA_NEMICONORMALE:
                    nemicoGenerato = new Nemico(NORMAL_ENEMY, i, j, this->getId(), numLivello);
                    listaNemici->addEntita(nemicoGenerato);
                    // Libero lo spazio dalla matrice logica e dalla matrice stampabile dove è stato generato il nemico
                    for (int i_1 = i; i_1 < i + nemicoGenerato->getDimY(); i_1++){
                        for (int j_1 = j; j_1 < j + nemicoGenerato->getDimX(); j_1++){
                            matrice_logica[i_1][j_1] = STANZA_SPAZIOLIBERO;
                            switch(this -> getId()){
                                case ID_STANZA_SPAWN:
                                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, MAP_SPAWN_PAIR, NULL);
                                    break;
                                case ID_STANZA_NORMALE:
                                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, MAP_NORMAL_PAIR, NULL);
                                    break;
                                case ID_STANZA_BOSS:
                                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, MAP_BOSS_PAIR, NULL);
                                    break;
                            }
                        }
                    }
                break;
                case STANZA_NEMICOBOSS:
                    nemicoGenerato = new Nemico(BOSS_ENEMY, i, j, this->getId(), numLivello);
                    listaNemici->addEntita(nemicoGenerato);
                    // Libero lo spazio dalla matrice logica e dalla matrice stampabile dove è stato generato il nemico
                    for (int i_1 = i; i_1 < i + nemicoGenerato->getDimY(); i_1++){
                        for (int j_1 = j; j_1 < j + nemicoGenerato->getDimX(); j_1++){
                            matrice_logica[i_1][j_1] = STANZA_SPAZIOLIBERO;
                            switch(this -> getId()){
                                case ID_STANZA_SPAWN:
                                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, MAP_SPAWN_PAIR, NULL);
                                    break;
                                case ID_STANZA_NORMALE:
                                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, MAP_NORMAL_PAIR, NULL);
                                    break;
                                case ID_STANZA_BOSS:
                                    setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, MAP_BOSS_PAIR, NULL);
                                    break;
                            }
                        }
                    }
                break;
            }
        }
    }
}

int Stanza::accessibile(Entita * entita, bool giocatore){
    int returnvalue = STANZA_ACC_LIBERO;
    
    // Controllo contatto con entita
    this->listaPorte-> makecList(entita);
    this->listaNemici-> makecList(entita);
    this->listaProiettili-> makecList(entita);
    this->listaArtefatti-> makecList(entita);

    if(this->listaNemici->lengthcList() >= 1){
        returnvalue = STANZA_ACC_NEMICO;
    } else if(this->listaPorte->lengthcList() >= 1){
        returnvalue = STANZA_ACC_PORTA;
    }

    // Controllo accessibilità della cella se sono dentro le mura
    else if(
        entita->getX() >= 0 && 
        (entita->getX() + entita->getDimX() - 1) < (this->dim_x) && 
        entita->getY() >= 0 && 
        (entita->getY() + entita->getDimY() - 1) < (this->dim_y)
    ) {
        // Se sono dentro le mura, allora controllo se la cella è libera
        // Se lo è, allora finirò gli else if e ritornerò STANZA_ACC_LIBERO
        for(int x = 0; x < entita->getDimX(); x++) {
            for(int y = 0; y < entita->getDimY(); y++) {
                if(this -> matrice_logica [entita->getY() + y] [entita->getX() + x] != 0){
                    returnvalue = STANZA_ACC_MURO;
                }
            }
        }

        if (returnvalue == STANZA_ACC_LIBERO){
            if(this->listaProiettili->lengthcList(false) >= 1){
                returnvalue = STANZA_ACC_PROIETTILE_NEMICO;
            } else if(this->listaProiettili->lengthcList(true) >= 1){
                returnvalue = STANZA_ACC_PROIETTILE_GIOCATORE;
            } else if(this->listaArtefatti->lengthcList() >= 1){
                returnvalue = STANZA_ACC_ARTEFATTO;
            }
        }
    }

    // Se sono un giocatore, cerco di uscire fuori dalle mura: mi trovo in una porta? Se falso, allora STANZA_ACC_MURO
    else if(giocatore && direzione_porta(entita->getY(), entita->getX()) == 0){
        returnvalue = STANZA_ACC_MURO;
    } else if (!giocatore) { 
        // Infine, se non sono un giocatore e sono fuori dalle mura e non ho trovato nient'altro, allora STANZA_ACC_MURO
        returnvalue = STANZA_ACC_MURO;
    }
    
    
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

void Stanza::aggiungiArtefatto (Artefatto * artefatto) {
    this->listaArtefatti->addEntita(artefatto);
}


void Stanza::calcolo_logica(Gioco * gioco){
    this->listaProiettili->aggiornaEntita(gioco);
    this->listaNemici->aggiornaEntita(gioco);
    this->listaArtefatti->aggiornaEntita(gioco);
    
    // Se ho battuto tutti i nemici, allora tolgo le porte. Se ho anche la chiave, allora tolgo anche la porta con chiave
    if(this->listaNemici->lengthList() == 0 && this->listaPorte->lengthList(gioco->getPlayer()->getChiave()) > 0){
        this->listaPorte->deleteList(gioco->getPlayer()->getChiave());
        this->listaPorte->deleteList(false);
    } else if (this->listaNemici->lengthList() == 0 && this->listaPorte->lengthList(false) > 0) {
        this->listaPorte->deleteList(false);
    }
}

void Stanza::aggiornaTick() {
    this->listaProiettili->aggiornaTick();
    this->listaNemici->aggiornaTick();
}

/**
 * @brief Danneggia tutti i nemici nella contact list
 * dei nemici con la quantità inserita come parametro.
 * 
 * @param quantita Danno da infliggere a tutti i nemici 
 *                 nella contact list
 */
void Stanza::dmgNemiciContactList(Gioco * gioco, int quantita) {
    this->listaNemici->dmgNemiciContactList(gioco, quantita);
}

/**
 * @brief Ritorna il danno totale che infliggono tutti i proiettili
 * della contact list dei proiettili della stanza. 
 * 
 * In particolare, somma insieme soltanto proiettili dello stesso tipo: 
 * se type è vero, allora somma i proiettili del giocatore, altrimenti 
 * somma i proiettili dei nemici.
 * 
 * @param type      Se vero, somma i proiettili del giocatore. Se falso, 
 *                  somma i proiettili dei nemici.
 * @return int      Il totale dei danni dei proiettili sommati
 */
int Stanza::dmgDaProiettiliContactList(bool type) {
    return this->listaProiettili->dmgDaProiettiliContactList(type); 
}

/**
 * @brief Cancella i proiettili sovrapposti con l'entità inserita.
 * Se giocatore è vero, allora bisogna cancellare tutti i proiettili nemici,
 * se bool è falso, allora bisogna cancellare tutti i proiettili alleati.
 * 
 * @param entita    L'entità con cui si deve creare la contact list
 * @param giocatore Se vero cancella proiettili nemici, se falso cancella proiettili alleati 
 */
void Stanza::cancellaProiettiliSovrapposti(Entita * entita, bool giocatore) {
    this->listaProiettili->makecList(entita);
    this->listaProiettili->deletecList_fromList(!giocatore); // Cancello il contrario del tipo di nemici
}


void Stanza::effettiArtefatti(Player * player){
    this->listaArtefatti->effettiArtefatti(player);
}

bool Stanza::haArtefatto(int type) {
    // ritorna vero se la lista artefatti contiene l'artefatto di tipo type
    return this->listaArtefatti->checkEntity(type);
}


int Stanza::getNumNemici() { 
    return this->listaNemici->lengthList();
}

// getter e setter di trovata ed esplorata
bool Stanza::getTrovata() {
    return this->trovata;
}

void Stanza::setTrovata(bool trovata) {
    this->trovata = trovata;
}

bool Stanza::getEsplorata() {
    return this->esplorata;
}

void Stanza::setEsplorata(bool esplorata) {
    this->esplorata = esplorata;
}