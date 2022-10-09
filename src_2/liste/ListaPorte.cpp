#include "../generale/libs.hpp"

ListaPorte::ListaPorte(){
    this->head = NULL;
}

ListaPorte::~ListaPorte(){
    this->deletecList();
    this->deleteList();
}

bool ListaPorte::checkEntity_p(Porta *entity, bool b){

    // Controlla se l'entità è presente nella lista
    plistaP headTemp = head;
    bool returnvalue = false;
    plistaP cheadTemp = chead;

    if(!b){
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


void ListaPorte::addEntita_p(Porta *entity, bool b){

    // aggiunge entita controllando che non sia gia presente

    plistaP headTemp = head;
    plistaP cheadTemp = chead;

    if(!b && !(checkEntity_p(entity, false))){
        plistaP headTemp = head;

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
    addEntita_p(entity, false);
}

bool ListaPorte::removeEntita_p(Porta *entity,bool b, bool deleteEntita){
    bool returnValue = false;
    plistaP headTemp;
    if (b) {
        headTemp = chead;
    } else {
        headTemp = head;
    }

    if(checkEntity_p(entity, b)){
        returnValue = true;
        while(headTemp->e != entity){
            headTemp = headTemp->next;
        }
        // Caso in cui non è la testa della lista
        if(headTemp->prev != NULL){
            // Caso in cui è al centro della lista
            if(headTemp->next != NULL){
                headTemp->prev->next = headTemp->next;
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
                if (b) {
                    chead = headTemp->next;
                } else {
                    head = headTemp->next;
                }
                if(deleteEntita) delete headTemp->e;
                delete headTemp;
            }
            // Caso in cui la lista non ha altri elementi
            else{
                if (b) {
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

bool ListaPorte::removeEntita(Porta *entity, bool deleteEntita) {
    removeEntita_p(entity, false, deleteEntita);
}


bool ListaPorte::makecList(Porta *entity){
    // Controlla quali entità sono a contatto con l'entità di input e le aggiungo in chead. Ritorno true se ci sono entita a contatto.

    bool returnValue = false;
    plistaP headTemp = head;

    while(headTemp != NULL){
        while(!(entity->controllaContatto(headTemp->e))){
            headTemp = headTemp->next;
            returnValue = true;
        }
        addEntita_p(entity, true);
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
            removeEntita_p(temp->prev->e, true, false);
        } 
        removeEntita_p(temp->e, true, false);
    }
};

void ListaPorte::deleteList(){
    plistaP temp = getList();
    if(temp != NULL) {
        while(temp->next != NULL){
            temp = temp->next;
            removeEntita(temp->prev->e, true);
        } 
        removeEntita(temp->e, true);
    }
};


void ListaPorte::stampaTutte(int offsetY, int offsetX) {
    plistaP headTemp = head;
    while(headTemp != NULL) {
        headTemp->e->stampa(offsetY, offsetX);
        headTemp = headTemp->next; 
    }
}