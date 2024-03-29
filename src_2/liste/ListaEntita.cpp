#include "../generale/libs.hpp"

ListaEntita::ListaEntita(){
    this->head = NULL;
    this->chead = NULL;
}

ListaEntita::~ListaEntita(){
    this->deletecList();
    this->deleteList();
}

bool ListaEntita::checkEntity_p(Entita *entity, bool contactList){

    // Controlla se l'entità è presente nella lista
    plistaE headTemp = head;
    bool returnvalue = false;
    plistaE cheadTemp = chead;

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


bool ListaEntita::checkEntity(Entita *entity){
    return checkEntity_p(entity, false);
}


void ListaEntita::addEntita_p(Entita *entity, bool contactList){

    // aggiunge entita controllando che non sia gia presente

    plistaE headTemp = head;
    plistaE cheadTemp = chead;

    if(!contactList && !(checkEntity_p(entity, false))){
        if(head == NULL){
            head = new listaE;
            head->prev = NULL;
            head->e = entity;
            head->next = NULL;
        }
        else{
            while(headTemp->next != NULL) headTemp = headTemp->next;
            headTemp->next = new listaE;
            headTemp->next->prev = headTemp;
            headTemp->next->next = NULL;
            headTemp->next->e = entity;
        }
    }
    else if(!(checkEntity_p(entity, true))){
        if(chead == NULL){
            chead = new listaE;
            chead->prev = NULL;
            chead->e = entity;
            chead->next = NULL;
        }
        else{
            while(cheadTemp->next!=NULL){
                cheadTemp = cheadTemp->next;
            }
            cheadTemp->next = new listaE;
            cheadTemp->next->next = NULL;
            cheadTemp->next->prev = cheadTemp;
            cheadTemp->next->e = entity;
        }
    }
}

void ListaEntita::addEntita(Entita *entity){
    addEntita_p(entity, false);
}

bool ListaEntita::removeEntita_p(Entita *entity,bool contactList, bool deleteEntita){
    bool returnValue = false;
    plistaE headTemp;
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

bool ListaEntita::removeEntita(Entita *entity, bool deleteEntita) {
    return removeEntita_p(entity, false, deleteEntita);
}


bool ListaEntita::makecList(Entita *entity){
    // Controlla quali entità sono a contatto con l'entità di input e le aggiungo in chead. Ritorno true se ci sono entita a contatto.

    deletecList();

    bool returnValue = false;
    plistaE headTemp = head;

    while(headTemp != NULL){
        if (headTemp->e != entity && (entity->controllaContatto(headTemp->e))) {
            addEntita_p(headTemp->e, true);
            returnValue = true;
        }
        headTemp = headTemp->next;
    }
    return returnValue;
};

plistaE ListaEntita::getList(){
    return head;
};

plistaE ListaEntita::getcList(){
    return chead;
};

void ListaEntita::deletecList(){
    plistaE temp = getcList();
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

void ListaEntita::deleteList(){
    plistaE temp = getList();
    if(temp != NULL) {
        while(temp->next != NULL){
            temp = temp->next;    
        }
        while(temp->prev != NULL) {
            temp = temp->prev;    
            removeEntita(temp->next->e, true);
        }
        if (temp->next != NULL) {
            removeEntita(temp->next->e, true);
        }
        removeEntita(temp->e, true);
    }
};

int ListaEntita::lengthList(){
    int returnvalue=0;
    listaE * tmp = this-> head;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

int ListaEntita::lengthcList(){
    int returnvalue=0;
    listaE * tmp = this-> chead;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

void ListaEntita::stampaTutte(int offsetY, int offsetX) {
    plistaE headTemp = head;
    while(headTemp != NULL) {
        headTemp->e->stampa(offsetY, offsetX);
        headTemp = headTemp->next; 
    }
}