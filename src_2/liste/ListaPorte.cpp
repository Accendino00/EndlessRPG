#include "../generale/libs.hpp"

ListaPorte::ListaPorte(){
    this->head = NULL;
    this->chead = NULL;
}

ListaPorte::~ListaPorte(){
    this->deletecList();
    this->deleteList();
}

bool ListaPorte::checkEntity_p(Porta *entity, bool contactList){

    // Controlla se l'entità è presente nella lista
    plistaP headTemp = head;
    bool returnvalue = false;
    plistaP cheadTemp = chead;

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


bool ListaPorte::checkEntity(Porta *entity){
    return checkEntity_p(entity, false);
}


void ListaPorte::addEntita_p(Porta *entity, bool contactList){

    // aggiunge entita controllando che non sia gia presente

    plistaP headTemp = head;
    plistaP cheadTemp = chead;

    if(!contactList && !(checkEntity_p(entity, false))){
        if(head == NULL){
            head = new listaP;
            head->prev = NULL;
            head->e = entity;
            head->next = NULL;
        }
        else{
            while(headTemp->next != NULL) headTemp = headTemp->next;
            headTemp->next = new listaP;
            headTemp->next->prev = headTemp;
            headTemp->next->next = NULL;
            headTemp->next->e = entity;
        }
    }
    else if(!(checkEntity_p(entity, true))){
        if(chead == NULL){
            chead = new listaP;
            chead->prev = NULL;
            chead->e = entity;
            chead->next = NULL;
        }
        else{
            while(cheadTemp->next!=NULL){
                cheadTemp = cheadTemp->next;
            }
            cheadTemp->next = new listaP;
            cheadTemp->next->next = NULL;
            cheadTemp->next->prev = cheadTemp;
            cheadTemp->next->e = entity;
        }
    }
}

void ListaPorte::addEntita(Porta *entity){
    return addEntita_p(entity, false);
}

bool ListaPorte::removeEntita_p(Porta *entity,bool contactList, bool deleteEntita){
    bool returnValue = false;
    plistaP headTemp;
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

bool ListaPorte::removeEntita(Porta *entity) {
    removeEntita_p(entity, true, false); // La cancello dalla contactlist senza cancellare l'entita
    return removeEntita_p(entity, false, true); // La cancello dalla lista normale cancellando l'entita
}


bool ListaPorte::makecList(Entita *entity){
    // Controlla quali entità sono a contatto con l'entità di input e le aggiungo in chead. Ritorno true se ci sono entita a contatto.

    deletecList();
    
    bool returnValue = false;
    plistaP headTemp = head;

    while(headTemp != NULL){
        if (headTemp->e != entity && (entity->controllaContatto(headTemp->e))) {
            addEntita_p(headTemp->e, true);
            returnValue = true;
        }
        headTemp = headTemp->next;
    }
    return returnValue;
};

plistaP ListaPorte::getList(){
    return head;
};

plistaP ListaPorte::getcList(){
    return chead;
};

void ListaPorte::deletecList(){
    plistaP temp = getcList();
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

void ListaPorte::deleteList(){
    plistaP temp = getList();
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


void ListaPorte::deleteList(bool conChiave) {
    plistaP temp = getList();
    while(temp != NULL) {
        if (temp->e->isPortaConChiave() == conChiave) {
            removeEntita(temp->e);
            temp = getList();
        } else {
            temp = temp->next;
        }
    }
}


void ListaPorte::stampaTutte(int offsetY, int offsetX) {
    plistaP headTemp = head;
    while(headTemp != NULL) {
        headTemp->e->stampa(offsetY, offsetX);
        headTemp = headTemp->next; 
    }
}


int ListaPorte::lengthList(bool conChiave) {
    int returnvalue=0;
    listaP * tmp = this-> head;
    while(tmp!=NULL){
        if (tmp->e->isPortaConChiave() == conChiave)
            returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

int ListaPorte::lengthList(){
    int returnvalue=0;
    listaP * tmp = this-> head;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

int ListaPorte::lengthcList(){
    int returnvalue=0;
    listaP * tmp = this-> chead;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

