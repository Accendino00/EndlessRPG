#include "../generale/libs.hpp"

ListaNemici::ListaNemici(){
    this->head = NULL;
    this->chead = NULL;
}

ListaNemici::~ListaNemici(){
    this->deletecList();
    this->deleteList();
}

bool ListaNemici::checkEntity_p(Nemico *entity, bool contactList){

    // Controlla se l'entità è presente nella lista
    plistaN headTemp = head;
    bool returnvalue = false;
    plistaN cheadTemp = chead;

    if(!contactList){
        while(headTemp != NULL && !returnvalue){
                if(headTemp->e == entity)returnvalue = true;
                else headTemp = headTemp->next;
        }
    }
    else{
        while(cheadTemp != NULL && !returnvalue){
                if(cheadTemp->e == entity)returnvalue = true;
                else cheadTemp = cheadTemp->next;
        }
    }

    return returnvalue;
}


bool ListaNemici::checkEntity(Nemico *entity){
    return checkEntity_p(entity, false);
}


void ListaNemici::addEntita_p(Nemico *entity, bool contactList){

    // aggiunge entita controllando che non sia gia presente

    plistaN headTemp = head;
    plistaN cheadTemp = chead;

    if(!contactList && !(checkEntity_p(entity, false))){
        if(head == NULL){
            head = new listaN;
            head->prev = NULL;
            head->e = entity;
            head->next = NULL;
        }
        else{
            while(headTemp->next != NULL) headTemp = headTemp->next;
            headTemp->next = new listaN;
            headTemp->next->prev = headTemp;
            headTemp->next->next = NULL;
            headTemp->next->e = entity;
        }
    }
    else if(!(checkEntity_p(entity, true))){
        if(chead == NULL){
            chead = new listaN;
            chead->prev = NULL;
            chead->e = entity;
            chead->next = NULL;
        }
        else{
            while(cheadTemp->next!=NULL){
                cheadTemp = cheadTemp->next;
            }
            cheadTemp->next = new listaN;
            cheadTemp->next->next = NULL;
            cheadTemp->next->prev = cheadTemp;
            cheadTemp->next->e = entity;
        }
    }
}

void ListaNemici::addEntita(Nemico *entity){
    addEntita_p(entity, false);
}

bool ListaNemici::removeEntita_p(Nemico *entity,bool contactList, bool deleteEntita){
    bool returnValue = false;
    plistaN headTemp;
    if (contactList) {
        headTemp = chead;
    } else {
        headTemp = head;
    }


    if(checkEntity_p(entity, contactList)){    
        returnValue = true;
        while(headTemp->e != entity){
            headTemp = headTemp->next;
        }
        // Caso in cui non è la testa della lista
        if(headTemp->prev != NULL){
            // Caso in cui è al centro della lista
            if(headTemp->next != NULL){
                headTemp->prev->next = headTemp->next;
                headTemp->next->prev = headTemp->prev;
                if(deleteEntita) delete headTemp->e;
                delete headTemp;
            }
            // Caso in cui è l'ultimo elemento della lista
            else{
                headTemp->prev->next = NULL;
                if(deleteEntita) delete headTemp->e;
                delete headTemp;
            }
        }
        // Caso in cui è la testa della lista
        else{
            // Caso in cui la lista ha altri elementi
            if(headTemp->next != NULL){
                headTemp->next->prev = NULL;
                if (contactList) {
                    chead = headTemp->next;
                } else {
                    head = headTemp->next;
                }
                if(deleteEntita) delete headTemp->e;
                delete headTemp;
            }
            // Caso in cui la lista non ha altri elementi
            else{
                if (contactList) {
                    chead = NULL;
                } else {
                    head = NULL;
                }
                if(deleteEntita) delete headTemp->e;
                delete headTemp;
            }
        }
    }
    return returnValue;
};

/**
 * @brief Cancella un nemico. C'e' una possibilita' che venga generato un artefatto. 
 * 
 * In particolare, cancella l'entita dalla clist e poi dalla lista normale.
 * Se viene cancellata con successo dalla lista, ritorna true.
 * 
 * Quando viene cancellato un nemico, puo' venire aggiunto un nuovo
 * artefatto. Questo viene fatto in base a determinate possibilita'
 * calcolate da GameData. Vedere GameData per chiarimenti.
 * 
 * @param stanza    Stanza dove aggiungere l'artefatto 
 * @param entity    Il nemico da cancellare
 * @return true     Se viene cancellata
 * @return false    Se non viene cancellata
 */
bool ListaNemici::removeEntita(Gioco * gioco, Nemico *entity) {
    gioco->getPlayer()->modificaScore(entity->getPunti());
    int x_artefatto = entity->getX() + (int) ((float)entity->getDimX()/2); 
    int y_artefatto = entity->getY() + (int) ((float)entity->getDimY()/2);
    bool returnValue = removeEntita(entity);
    
    if (returnValue)
        gioco->spawnArtefatto(y_artefatto, x_artefatto);


    return returnValue; 
}

/**
 * @brief Cancella un nemico.
 * 
 * Viene cancellato sia dalla clist che dalla lista dei nemici
 * normale. Se viene cancellato con successo, ritorna true.
 * 
 * @param entity    Il nemico da cancellare
 * @return true     Se viene cancellata
 * @return false    Se non viene cancellata
 */
bool ListaNemici::removeEntita(Nemico *entity) {
    removeEntita_p(entity, true, false); // La cancello dalla contactlist senza cancellare l'entita
    return removeEntita_p(entity, false, true); // La cancello dalla lista normale cancellando l'entita
}


bool ListaNemici::makecList(Entita *entity){
    // Controlla quali entità sono a contatto con l'entità di input e le aggiungo in chead. Ritorno true se ci sono entita a contatto.

    // Cancello la clist che c'era prima
    deletecList();

    bool returnValue = false;
    plistaN headTemp = head;
    while(headTemp != NULL){
        if (headTemp->e != entity && (entity->controllaContatto(headTemp->e))) {
            addEntita_p(headTemp->e, true);
            returnValue = true;
        }
        headTemp = headTemp->next;
    }
    return returnValue;
};

plistaN ListaNemici::getList(){
    return head;
};

plistaN ListaNemici::getcList(){
    return chead;
};

void ListaNemici::deletecList(){
    plistaN temp = getcList();
    if(temp != NULL) {
        while(temp->next != NULL){
            temp = temp->next;    
        }
        while(temp->prev != NULL) {
            temp = temp->prev;    
            removeEntita_p(temp->next->e, true, false);
        }
        if (temp->next != NULL) {
            removeEntita_p(temp->next->e, true, false);
        }
        removeEntita_p(temp->e, true, false);
    }
};

void ListaNemici::deleteList(){
    plistaN temp = getList();
    if(temp != NULL) {
        while(temp->next != NULL){
            temp = temp->next;    
        }
        while(temp->prev != NULL) {
            temp = temp->prev;    
            removeEntita(temp->next->e);
        }
        if (temp->next != NULL) {
            removeEntita(temp->next->e);
        }
        removeEntita(temp->e);
    }
};


/**
 * @brief Stampo tutti i nemici della lista, con un offset particolare.
 * 
 * Inoltre, stampo anche la barra della salute dell'ultimo nemico colpito.
 * Se vi è un boss, questa operazione viene fatta automaticamente.
 * 
 * @param offsetY 
 * @param offsetX 
 */
void ListaNemici::stampaTutte(int offsetY, int offsetX) {
    plistaN headTemp = head;
    if (head != NULL) {
        Nemico * ultimoColpito = head->e; 

        while(headTemp != NULL) {
            if (ultimoColpito != NULL && headTemp->e->getTickOfLastHit() > ultimoColpito->getTickOfLastHit()) {
                ultimoColpito = headTemp->e;
            }
            headTemp->e->stampa(offsetY, offsetX);
            headTemp = headTemp->next; 
        }

        if(ultimoColpito != NULL && ultimoColpito->getType() != BOSS_ENEMY && ultimoColpito->isMostrabile()) 
            ultimoColpito->stampaVita(40);
    }
}

void ListaNemici::aggiornaEntita(Gioco * gioco) {
    plistaN headTemp = head;
    while(headTemp != NULL) {
        if (headTemp->e->getVita() <= 0) {
            removeEntita(gioco, headTemp->e);
            headTemp = head;
        } else {
            headTemp->e->updateEntita(gioco->getLivello()->getStanza(), gioco->getPlayer());
            headTemp = headTemp->next; 
        }
    }
}

void ListaNemici::aggiornaTick() {
    plistaN headTemp = head;
    while(headTemp != NULL) {
        headTemp->e->toCurrentTick();
        headTemp = headTemp->next; 
    }
}

int ListaNemici::lengthList(){
    int returnvalue=0;
    listaN * tmp = this-> head;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

int ListaNemici::lengthcList(){
    int returnvalue=0;
    listaN * tmp = this-> chead;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

void ListaNemici::dmgNemiciContactList(Gioco * gioco, int quantita) {
    plistaN headTemp = chead;
    while(headTemp != NULL) {
        headTemp->e->modificaVita(-quantita);
        if (headTemp->e->getVita() <= 0) {
            removeEntita(gioco, headTemp->e);
            headTemp = chead;
        } else {
            headTemp = headTemp->next; 
        }
    }
}