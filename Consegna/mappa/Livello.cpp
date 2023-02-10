#include "../generale/libs.hpp"

// Chiamare il costruttore di default equivale a generare il Livello 0.
Livello::Livello() : Livello(0) {}

Livello::Livello(int numLivello) {
  this->numLivello = numLivello;

  //alloco lo spazio per la matrice del livello
  (this -> matrice_livello) = (Stanza ***) new Stanza ** [DIM_MATRICE_LIVELLO_Y];
  for(int i=0; i < DIM_MATRICE_LIVELLO_Y; i++){
    (this -> matrice_livello [i]) = (Stanza **) new Stanza * [DIM_MATRICE_LIVELLO_X];
    for(int j=0; j < DIM_MATRICE_LIVELLO_X; j++){
      this -> matrice_livello [i][j] = NULL;
    }
  }

  FILE * fin;
  char livello_da_scegliere [100];  // Stringa contenente il nome del file della mappa
  int idLivello = (rand() % NUMERO_LIVELLI) + 1; // Impostazione dell'id casuale del livello

  // Creazione della stringa che contiene il percorso al file del livello scelto
  sprintf(livello_da_scegliere, "./mappa/matrici_livello/livello%d.lvl", idLivello);
  fin = fopen( livello_da_scegliere , "r");
  
  //Leggo il file e mi trascrivo i numeri in una matrice di interi
  for(int i= 0; i < DIM_MATRICE_LIVELLO_Y; i++){
      for(int j = 0; j < DIM_MATRICE_LIVELLO_X; j++){
          matrice_numerica [i][j] = fgetc(fin) - (int)'0'; // Traduco i numeri ascii in interi
      }
      fgetc(fin);
  }
  fclose(fin);

  //Imposto l'id della stanza da creare
  for(int i = 0; i < DIM_MATRICE_LIVELLO_Y; i++){
    for(int j = 0; j < DIM_MATRICE_LIVELLO_X; j++){
      if((matrice_numerica[i] [j]) != 3){
        if((matrice_numerica[i] [j]) == 0){       //mi serve per capire da dove iniziare
          current_y = i;
          current_x = j;
        }
        matrice_livello [i] [j] = new Stanza(matrice_numerica[i] [j]); 
      }
    }
  }

  //alloco memoria per la matrice di livello

  this -> imposta_stanza();
}


Livello::~Livello(){
  for(int i=0; i<DIM_MATRICE_LIVELLO_Y; i++){
    for(int j=0; j<DIM_MATRICE_LIVELLO_X; j++) {
      if (this->matrice_livello[i][j] != NULL) {
        delete (this->matrice_livello[i][j]);
        this->matrice_livello[i][j] = NULL;
      }
    }
    delete [] (this->matrice_livello[i]);
  }
  delete [] (this-> matrice_livello);
}

void Livello::imposta_stanza(){
  bool nord, sud, est, ovest;
  int boss = 0;

  for(int i = 0; i < DIM_MATRICE_LIVELLO_Y; i++){
    for(int j = 0; j < DIM_MATRICE_LIVELLO_X; j++){
      if(this -> matrice_livello [i] [j] != NULL){
        boss = 0;
        nord = false;
        sud = false; 
        est = false; 
        ovest = false;
        if(i+1 < DIM_MATRICE_LIVELLO_Y){
          if(this -> matrice_livello [i + 1] [j] != NULL){
            sud = true;
            if(this -> matrice_livello [i + 1] [j]->getId() == ID_STANZA_BOSS){
              boss =  DIRECTION_SS;
            }
          }
        }
        if(i-1 >= 0){
          if (this -> matrice_livello [i - 1] [j] != NULL){
            nord = true;
            if(this -> matrice_livello [i - 1] [j]->getId() == ID_STANZA_BOSS){
              boss =  DIRECTION_NN;
            }
          }
        }
        if(j+1 < DIM_MATRICE_LIVELLO_X){
          if(this -> matrice_livello [i] [j + 1] != NULL){
            est = true;
            if(this -> matrice_livello [i] [j + 1]->getId() == ID_STANZA_BOSS){
              boss =  DIRECTION_EE;
            }
          }
        }
        if(j-1 >= 0){
          if (this -> matrice_livello [i] [j - 1] != NULL){
            ovest = true;
            if(this -> matrice_livello [i] [j - 1]->getId() == ID_STANZA_BOSS){
              boss =  DIRECTION_OO;
            }
          }
        }
        this -> matrice_livello [i] [j] -> imposta_porte(nord, sud, est, ovest, boss);
        this -> matrice_livello [i] [j] -> da_logica_a_stampabile(this->numLivello);
      }
    }
  }

  this->esploraStanza(current_y, current_x);
};

bool Livello::livello_successivo(){
  return false;
}

void Livello::stampa(){
  this->matrice_livello[this->current_y] [this->current_x]->stampa_stanza();
  this->stampaMinimappa();
};


bool Livello::cambia_stanza(int direzione){
  bool returnValue = false;
  switch(direzione){
    case DIRECTION_NN:
    if(current_y-1 >= 0){ //ricontrolla lo zero
      if(matrice_livello [current_y-1] [current_x] != NULL){
        (this->current_y)-=1;
        returnValue = true;
      }
    }
    break;
    case DIRECTION_OO:
    if(current_x-1 >= 0){ //ricontrolla lo zero
      if(matrice_livello [current_y] [current_x-1] != NULL){
        (this->current_x)-=1;
        returnValue = true;
      }
    }
    break;
    case DIRECTION_EE:
    if(current_x+1 < DIM_MATRICE_LIVELLO_X){ //ricontrolla lo zero
      if(matrice_livello [current_y] [current_x+1] != NULL){
        (this->current_x)+=1;
        returnValue = true;
      }
    }
    break;
    case DIRECTION_SS:
    if(current_y+1 < DIM_MATRICE_LIVELLO_Y){ //ricontrolla lo zero
      if(matrice_livello [current_y+1] [current_x] != NULL){
        (this->current_y)+=1;
        returnValue = true;
      }
    }
    break;
  }
  return returnValue;
}
// logica della morte (continee tutte le logiche , fare una funzione che vede se nella stanza corrente se si interagisce con la port andando ancor a destra per esempio cambia di stanza)

void Livello::calcolo_logica(Gioco * gioco){

  // Aggiornamento delle liste di entità che si trovano nella stanza
  (matrice_livello [current_y] [current_x]) -> calcolo_logica(gioco);

  // Cambiare stanza

  // Offset rispetto alla parte in alto a sinistra delle porte (orizzontali e verticali)
  int door_offset_x = gioco->getPlayer()->getX() - (((matrice_livello [current_y] [current_x]) -> getDimX() - DIMENSIONE_PORTA_ORIZZONTALE) / 2);
  int door_offset_y = gioco->getPlayer()->getY() - (((matrice_livello [current_y] [current_x]) -> getDimY() - DIMENSIONE_PORTA_VERTICALE) / 2);

  // 

  bool cambiatoStanza = false;
  if(matrice_livello [current_y] [current_x]->direzione_porta(gioco->getPlayer()->getY(), gioco->getPlayer()->getX()) == DIRECTION_NN){
    cambiatoStanza = cambia_stanza(DIRECTION_NN);
    if(cambiatoStanza) { 
      gioco->getPlayer()->modificaCoordinate( (matrice_livello [current_y] [current_x]->getDimY())-2, 
                                  (((matrice_livello [current_y] [current_x]) -> getDimX() - DIMENSIONE_PORTA_ORIZZONTALE) / 2) + door_offset_x);
    }
  }
  else if(matrice_livello [current_y] [current_x]->direzione_porta(gioco->getPlayer()->getY(), gioco->getPlayer()->getX()) == DIRECTION_OO){
    cambiatoStanza = cambia_stanza(DIRECTION_OO);
    if(cambiatoStanza) { 
      gioco->getPlayer()->modificaCoordinate( (((matrice_livello [current_y] [current_x]) -> getDimY() - DIMENSIONE_PORTA_VERTICALE) / 2) + door_offset_y, 
                                (matrice_livello [current_y] [current_x]->getDimX())-2);
    }
  }
  else if(matrice_livello [current_y] [current_x]->direzione_porta(gioco->getPlayer()->getY(), gioco->getPlayer()->getX()) == DIRECTION_EE){
    cambiatoStanza = cambia_stanza(DIRECTION_EE);
    if(cambiatoStanza) { 
      gioco->getPlayer()->modificaCoordinate( (((matrice_livello [current_y] [current_x]) -> getDimY() - DIMENSIONE_PORTA_VERTICALE) / 2) + door_offset_y, 
                                  1);
    }
  }
  else if(matrice_livello [current_y] [current_x]->direzione_porta(gioco->getPlayer()->getY(), gioco->getPlayer()->getX()) == DIRECTION_SS){
    cambiatoStanza = cambia_stanza(DIRECTION_SS);
    if(cambiatoStanza) { 
      gioco->getPlayer()->modificaCoordinate( 1, 
                                  (((matrice_livello [current_y] [current_x]) -> getDimX() - DIMENSIONE_PORTA_ORIZZONTALE) / 2) + door_offset_x);
    }
  }
  if (cambiatoStanza) {
    // Se ho cambiato stanza, aggiorno i tick a quelli di presenti, senza modificare le entità
    this->esploraStanza(current_y, current_x);
    //matrice_livello [current_y] [current_x] -> aggiornaTick();
    this->aggiornaTick();
    switch(matrice_livello[current_y] [current_x] -> getId()){
      case ID_STANZA_SPAWN:
        gioco->getPlayer()->setFrame(FRAME_OF_E);
        break;
      case ID_STANZA_NORMALE:
        gioco->getPlayer()->setFrame(FRAME_OF_N);
        break;
      case ID_STANZA_BOSS:
        gioco->getPlayer()->setFrame(FRAME_OF_B);
        break;
    }
  }
}

void Livello::aggiungiProiettile(Proiettile * proiettile) {
  this->matrice_livello[this->current_y][this->current_x]->aggiungiProiettile(proiettile);
}

void Livello::aggiornaTick() {
  this -> matrice_livello [current_y] [current_x] -> aggiornaTick();
}

Stanza * Livello::getStanza() {
  return this->matrice_livello[this->current_y][this->current_x];
}

int Livello::offsetY() {
  return this->matrice_livello[this->current_y][this->current_x]->zero_y();
}

int Livello::offsetX() {
  return this->matrice_livello[this->current_y][this->current_x]->zero_x();
}

bool Livello::Bossisdead(){
  if(this->getStanza()->getId() == ID_STANZA_BOSS && this->getStanza()->getNumNemici() == 0){
      return true;
  } else {
    return false;
  }
}

bool Livello::isBossstanza(){
  if(this->getStanza()->getId() == ID_STANZA_BOSS){
    return true;
  } else {
    return false;
  }
}


int Livello::getNumNemici() {
  // loop su tutte le stanze e conto i nemici
  int numNemici = 0;
  for(int i = 0; i < DIM_MATRICE_LIVELLO_Y; i++) {
    for(int j = 0; j < DIM_MATRICE_LIVELLO_X; j++) {
      if (matrice_livello[i][j] != NULL && matrice_livello[i][j]->getId() != ID_STANZA_BOSS) {
        numNemici += matrice_livello[i][j]->getNumNemici();
      }
    }
  }
  return numNemici;
}

void Livello::stampaMinimappa() {

  // Coordinate in alto a sinistra di dove stampare la minimappa
  int offsetx = gd->getTerminalX() - 30;
  int offsety = 5;

  mvprintw(offsety - 3, offsetx - 2,  "╔");
  mvprintw(offsety - 2, offsetx - 2,  "║");
  for(int i = -1; i < 1 + (DIM_MATRICE_LIVELLO_X * 4); i++) {
      mvprintw(offsety - 3, offsetx + i, "═");
      mvprintw(offsety - 1, offsetx + i, "═");    
  }
  mvprintw(offsety - 3, offsetx + 1 + (DIM_MATRICE_LIVELLO_X * 4), "╗");
  mvprintw(offsety - 2, offsetx + 1 + (DIM_MATRICE_LIVELLO_X * 4), "║");


  mvprintw(offsety - 2, offsetx, "Livello attuale : %d", this->numLivello+1);

  mvprintw(offsety - 1, offsetx - 2,  "╠");
  mvprintw(offsety + (DIM_MATRICE_LIVELLO_Y * 3), offsetx - 2,  "╚");
  mvprintw(offsety - 1, offsetx + 1 + (DIM_MATRICE_LIVELLO_X * 4), "╣");
  mvprintw(offsety + (DIM_MATRICE_LIVELLO_Y * 3), offsetx + 1 + (DIM_MATRICE_LIVELLO_X * 4), "╝");
  for(int i = 0; i < (DIM_MATRICE_LIVELLO_Y * 3); i++) {
    mvprintw(offsety + i, offsetx - 2, "║");
    mvprintw(offsety + i, offsetx + 1 + (DIM_MATRICE_LIVELLO_X * 4),  "║");
  }
  for(int i = -1; i < 1 + (DIM_MATRICE_LIVELLO_X * 4); i++) {
    mvprintw(offsety - 1, offsetx + i, "═");
    mvprintw(offsety + (DIM_MATRICE_LIVELLO_Y * 3), offsetx + i,  "═");
  }

  // Stampa tutte le stanze, in base al loro colore e se le ho esplorate
  for(int i = 0; i < DIM_MATRICE_LIVELLO_Y; i++) {
    for(int j = 0; j < DIM_MATRICE_LIVELLO_X; j++) {
      if (matrice_livello[i][j] != NULL && matrice_livello[i][j]->getTrovata()) {
        if(!matrice_livello[i][j]->getEsplorata() && matrice_livello[i][j]->getId() != ID_STANZA_BOSS) {
          attron(COLOR_PAIR(MINIMAP_UNKNOWN_PAIR));
        } else {
          switch(matrice_livello[i][j]->getId()){
            case ID_STANZA_SPAWN:
              attron(COLOR_PAIR(MINIMAP_SPAWN_PAIR));
            break;
            case ID_STANZA_BOSS:
              attron(COLOR_PAIR(MINIMAP_BOSS_PAIR));
            break;
            case ID_STANZA_NORMALE:
              attron(COLOR_PAIR(MINIMAP_NORMAL_PAIR));
            break;
          }
        }
        mvprintw(offsety + (3*i),     offsetx + (4*j), "▛▀▀▜");
        mvprintw(offsety + 1 + (3*i), offsetx + (4*j), "▌  ▐");
        mvprintw(offsety + 2 + (3*i), offsetx + (4*j), "▙▄▄▟");
        
        if (i+1 < DIM_MATRICE_LIVELLO_Y 
            && matrice_livello[i+1][j] != NULL
            && matrice_livello[i+1][j]->getTrovata()) {
          mvprintw(offsety + 2 + (3*i), offsetx + 1 + (4*j), "  ");
        } 
        if (i-1 >= 0 
            && matrice_livello[i-1][j] != NULL
            && matrice_livello[i-1][j]->getTrovata()) {
          mvprintw(offsety + (3*i),     offsetx + 1 + (4*j), "  ");
        }
        if (j+1 < DIM_MATRICE_LIVELLO_X 
            && matrice_livello[i][j+1] != NULL
            && matrice_livello[i][j+1]->getTrovata()) {
          mvprintw(offsety + 1 + (3*i), offsetx + 3 + (4*j), " ");
        } 
        if (j-1 >= 0 
            && matrice_livello[i][j-1] != NULL
            && matrice_livello[i][j-1]->getTrovata()) {
          mvprintw(offsety + 1 + (3*i), offsetx + (4*j), " ");
        }

        if(!matrice_livello[i][j]->getEsplorata() && matrice_livello[i][j]->getId() != ID_STANZA_BOSS) {
          attroff(COLOR_PAIR(MINIMAP_UNKNOWN_PAIR));
          attron(COLOR_PAIR(MINIMAP_UNKNOWN_PAIR_TEXT));
          mvprintw(offsety + 1 + (3*i), offsetx + 1 + (4  *j), "??");
          attroff(COLOR_PAIR(MINIMAP_UNKNOWN_PAIR_TEXT));
        } else {
          switch(matrice_livello[i][j]->getId()){
            case ID_STANZA_SPAWN:
              attroff(COLOR_PAIR(MINIMAP_SPAWN_PAIR));
            break;
            case ID_STANZA_BOSS:
              if (!this->Bossisdead()) 
                mvprintw(offsety + 1 + (3*i), offsetx + 1 + (4  *j), "👹");
              attroff(COLOR_PAIR(MINIMAP_BOSS_PAIR));
            break;
            case ID_STANZA_NORMALE:
              attroff(COLOR_PAIR(MINIMAP_NORMAL_PAIR));
            break;
          }
        }
        
        // Non finiro' mai in questo caso se non ho esplorato la stanza
        if (i == current_y && j == current_x) {
          attron(A_BOLD);
          switch(matrice_livello[i][j]->getId()){
            case ID_STANZA_SPAWN:
              attron(COLOR_PAIR(MAP_SPAWN_PAIR));
            break;
            case ID_STANZA_BOSS:
              attron(COLOR_PAIR(MAP_BOSS_PAIR));
            break;
            case ID_STANZA_NORMALE:
              attron(COLOR_PAIR(MAP_NORMAL_PAIR));
            break;
          }
          mvprintw(offsety + 1 + (3*i), offsetx + 1 + (4  *j), "TU");
          switch(matrice_livello[i][j]->getId()){
            case ID_STANZA_SPAWN:
              attroff(COLOR_PAIR(MAP_SPAWN_PAIR));
            break;
            case ID_STANZA_BOSS:
              attroff(COLOR_PAIR(MAP_BOSS_PAIR));
            break;
            case ID_STANZA_NORMALE:
              attroff(COLOR_PAIR(MAP_NORMAL_PAIR));
            break;
          }
          attroff(A_BOLD);
        }
      }
    }
  }
}


int Livello::getNumLivello() {
  return this->numLivello;
}

void Livello::setNumLivello(int numLivello) {
  this->numLivello = numLivello;
}

void Livello::esploraStanza(int y, int x) {
  if (matrice_livello[y][x] != NULL) {
    matrice_livello[y][x]->setTrovata(true);
    matrice_livello[y][x]->setEsplorata(true);
    // set trovata a true per tutti i vicini
    if (y+1 < DIM_MATRICE_LIVELLO_Y && matrice_livello[y+1][x] != NULL) {
      matrice_livello[y+1][x]->setTrovata(true);
    }
    if (y-1 >= 0 && matrice_livello[y-1][x] != NULL) {
      matrice_livello[y-1][x]->setTrovata(true);
    }
    if (x+1 < DIM_MATRICE_LIVELLO_X && matrice_livello[y][x+1] != NULL) {
      matrice_livello[y][x+1]->setTrovata(true);
    }
    if (x-1 >= 0 && matrice_livello[y][x-1] != NULL) {
      matrice_livello[y][x-1]->setTrovata(true);
    }
  }
}



bool Livello::haArtefatto(int type) {
  bool returnValue = false;
  // controllo in tutte le stanze se la lista degli artefatti contiene un artefatto di quel tipo
  for (int i = 0; i < DIM_MATRICE_LIVELLO_Y; i++) {
    for (int j = 0; j < DIM_MATRICE_LIVELLO_X; j++) {
      if (matrice_livello[i][j] != NULL) {
        if (matrice_livello[i][j]->haArtefatto(type)) {
          returnValue = true;
        }
      }
    }
  }
  return returnValue;
}