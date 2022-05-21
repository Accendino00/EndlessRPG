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
*/


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

    this -> nord = false;
    this -> sud = false;
    this -> est = false;
    this -> ovest = false;


};

Stanza::Stanza(int a){
    FILE * fin;
    char mappa_da_scegliere [100];
    int idMappa = (rand() % 1 )+ 1;
    sprintf(mappa_da_scegliere, "./mappa/matrici_mappe/mappaBoss%d.map", idMappa);
    fin = fopen( mappa_da_scegliere , "r");
    
    
    //come aprire un file

    this -> matrice_logica = new int* [DIM_STANZA_BOSS_Y];
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

    this -> nord = false;
    this -> sud = false;
    this -> est = false;
    this -> ovest = false;



};

void Stanza::stampa_stanza(){
    int offsetx = ((gd -> getTerminalX()) - DIM_STANZA_X)/2;
    int offsety = ((gd -> getTerminalY()) - DIM_STANZA_Y)/2;
    for(int i = 0; i < this->dim_y; i++){
        for(int j = 0; j < this->dim_x; j++){
            mvprintw(offsety+i , offsetx+j , "%d", matrice_logica[i][j]);
        }
    }
    
}

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
};