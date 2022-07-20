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

Stanza::Stanza(int id){
    FILE * fin;
    char mappa_da_scegliere [100];
    int idMappa = (rand() % 1 )+ 1;

    if(id == ID_STANZA_SPAWN || id == ID_STANZA_NORMALE){
        this->dim_y = DIM_STANZA_Y;
        this->dim_x = DIM_STANZA_X;
        if (id == ID_STANZA_SPAWN) {
            idMappa = 0;
        }
    } else if(id == ID_STANZA_BOSS){
        this->dim_y = DIM_STANZA_BOSS_Y;
        this->dim_x = DIM_STANZA_BOSS_X;
    }

    sprintf(mappa_da_scegliere, "./mappa/matrici_mappe/mappa%s%d.map", (id == ID_STANZA_BOSS)?("boss"):(""), idMappa);
    fin = fopen( mappa_da_scegliere , "r");
    
    
    //come aprire un file

    this -> matrice_logica = new int* [this->dim_y];
    for(int i=0; i < this->dim_y; i++ ){
        this -> matrice_logica [i] = new int [this->dim_x];
    }
        
    
    //alloco memoria per la matrice

    for(int i= 0; i < this->dim_y; i++){
        for(int j = 0; j < this->dim_x; j++){
            matrice_logica [i][j] = fgetc(fin) -48 ;
        }
        fgetc(fin);
    }
    fclose(fin);

    this -> matrice_stampabile = new cchar_t * [dim_y];
    for(int i = 0; i < dim_y; i++){
        this -> matrice_stampabile [i] = new cchar_t [dim_x];
    }

};

 //Generalizzazione

void Stanza::stampa_stanza(){ 
    int offsetx = ((gd -> getTerminalX()) - this -> dim_x)/2;
    int offsety = ((gd -> getTerminalY()) - this -> dim_y)/2;
    for(int i = 0; i < this->dim_y; i++){
        for(int j = 0; j < this->dim_x; j++){
            mvadd_wch(offsety+i , offsetx+j, &(matrice_stampabile[i][j]));
        }
    }
    
}




void Stanza::imposta_porte(bool nord, bool sud, bool est, bool ovest){
    cchar_t ** portaOrizzontale = new cchar_t * [1];
    portaOrizzontale[0] = new cchar_t [DIMENSIONE_PORTA_ORIZZONTALE];
    for(int i = 0; i < DIMENSIONE_PORTA_ORIZZONTALE; i ++) {
        setcchar(&(portaOrizzontale[0][i]), L" ", A_NORMAL, DOOR_BACKGROUND, NULL);
    }
    cchar_t ** portaVerticale = new cchar_t * [DIMENSIONE_PORTA];
    for(int i = 0; i < DIMENSIONE_PORTA ; i ++) {
        portaVerticale[i]  = new cchar_t [1];
        setcchar(&(portaVerticale[i][0]), L" ", A_NORMAL, DOOR_BACKGROUND, NULL);
    }
    if(nord == true){
        for(int i = 0; i < DIMENSIONE_PORTA_ORIZZONTALE; i++){
            matrice_logica [0] [i + (int)((LARGHEZZA_STANZA - DIMENSIONE_PORTA_ORIZZONTALE)/2)] = 0;
        }
        
        this -> porte[PORTA_NORD] = new Entita(1, 0,(int)((LARGHEZZA_STANZA - DIMENSIONE_PORTA_ORIZZONTALE)/2), 1 , DIMENSIONE_PORTA_ORIZZONTALE, portaOrizzontale); 
    }
    if(sud == true){
        for(int i = 0; i < DIMENSIONE_PORTA_ORIZZONTALE; i++){
            matrice_logica [ALTEZZA_STANZA] [i + (int)((LARGHEZZA_STANZA - DIMENSIONE_PORTA_ORIZZONTALE)/2)] = 0;
        }
        this -> porte[PORTA_SUD] = new Entita(1, ALTEZZA_STANZA,(int)((LARGHEZZA_STANZA - DIMENSIONE_PORTA_ORIZZONTALE)/2), 1 , DIMENSIONE_PORTA * 2, portaOrizzontale); 
    }
    if(est == true){
        for(int i = 0; i < DIMENSIONE_PORTA; i++){
            matrice_logica [i + (int)((ALTEZZA_STANZA - DIMENSIONE_PORTA)/2)] [LARGHEZZA_STANZA] = 0;
        }
        this -> porte[PORTA_EST] = new Entita(1, LARGHEZZA_STANZA,(int)((ALTEZZA_STANZA - DIMENSIONE_PORTA)/2), DIMENSIONE_PORTA , 1 , portaVerticale);
    }
    if(ovest == true){
        for(int i = 0; i < DIMENSIONE_PORTA; i++){
            matrice_logica [i + (int)((ALTEZZA_STANZA - DIMENSIONE_PORTA)/2)] [0] = 0;
        }
        this -> porte[PORTA_OVEST] = new Entita(1, 0,(int)((ALTEZZA_STANZA - DIMENSIONE_PORTA)/2), DIMENSIONE_PORTA , 1, portaVerticale);
    }
}


void Stanza::da_logica_a_stampabile(){
    for(int i = 0; i < dim_y; i++){
        for(int j = 0; j < dim_x; j++){
            switch(matrice_logica [i] [j]){
                case 0:
                setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, FLOOR_PAIR, NULL);
                break;
                case 1:
                setcchar(&(matrice_stampabile [i] [j]), L" ", A_NORMAL, WALL_PAIR, NULL);
                break;
            }
        }
    }
}

bool Stanza::accessibile(int y_entity, int x_entity){
    //int offsetx = ((gd -> getTerminalX()) - this -> dim_x)/2;
    //int offsety = ((gd -> getTerminalY()) - this -> dim_y)/2;
    //int halfx = dim_x/2;
    //int halfy = dim_y/2;
    int returnbool = false;
    if(x_entity >= 0 && x_entity < this -> dim_x && y_entity > 0 && y_entity < this -> dim_y && this -> matrice_logica [y_entity] [x_entity] != 1){
        returnbool = true;
    } return returnbool;
}







