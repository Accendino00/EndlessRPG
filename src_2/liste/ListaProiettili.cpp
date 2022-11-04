#include "../generale/libs.hpp"

ListaProiettili::ListaProiettili(){
    this->head = NULL;
    this->chead = NULL;
}

ListaProiettili::~ListaProiettili(){
    this->deletecList();
    this->deleteList();
}

bool ListaProiettili::checkEntity_p(Proiettile *entity, bool b){

    // Controlla se l'entità è presente nella lista
    plistaPro headTemp = head;
    bool returnvalue = false;
    plistaPro cheadTemp = chead;

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


bool ListaProiettili::checkEntity(Proiettile *entity){
    return checkEntity_p(entity, false);
}


void ListaProiettili::addEntita_p(Proiettile *entity, bool b){

    // aggiunge entita controllando che non sia gia presente

    plistaPro headTemp = head;
    plistaPro cheadTemp = chead;

    if(!b && !(checkEntity_p(entity, false))){
        if(head == NULL){
            head = new listaPro;
            head->prev = NULL;
            head->e = entity;
            head->next = NULL;
        }
        else{
            while(headTemp->next != NULL) headTemp = headTemp->next;
            headTemp->next = new listaPro;
            headTemp->next->prev = headTemp;
            headTemp->next->next = NULL;
            headTemp->next->e = entity;
        }
    }
    else if(!(checkEntity_p(entity, true))){
        if(chead == NULL){
            chead = new listaPro;
            chead->prev = NULL;
            chead->e = entity;
            chead->next = NULL;
        }
        else{
            while(cheadTemp->next!=NULL){
                cheadTemp = cheadTemp->next;
            }
            cheadTemp->next = new listaPro;
            cheadTemp->next->next = NULL;
            cheadTemp->next->prev = cheadTemp;
            cheadTemp->next->e = entity;
        }
    }
}

void ListaProiettili::addEntita(Proiettile *entity){
    addEntita_p(entity, false);
}

bool ListaProiettili::removeEntita_p(Proiettile *entity,bool b, bool deleteEntita){
    bool returnValue = false;
    plistaPro headTemp;
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

bool ListaProiettili::removeEntita(Proiettile *entity, bool deleteEntita) {
    return removeEntita_p(entity, false, deleteEntita);
}


bool ListaProiettili::makecList(Entita *entity){
    // Controlla quali entità sono a contatto con l'entità di input e le aggiungo in chead. Ritorno true se ci sono entita a contatto.

    bool returnValue = false;
    plistaPro headTemp = head;

    while(headTemp != NULL){
        while(!(entity->controllaContatto(headTemp->e))){
            headTemp = headTemp->next;
            returnValue = true;
        }
        addEntita_p(headTemp->e, true);
        headTemp = headTemp->next;
    }
    return returnValue;
};

plistaPro ListaProiettili::getList(){
    return head;
};

plistaPro ListaProiettili::getcList(){
    return chead;
};

void ListaProiettili::deletecList(){
    plistaPro temp = getcList();
    if(temp != NULL) {
        while(temp->next != NULL){
            temp = temp->next;
            removeEntita_p(temp->prev->e, true, false);
        } 
        removeEntita_p(temp->e, true, false);
    }
};

void ListaProiettili::deleteList(){
    plistaPro temp = getList();
    if(temp != NULL) {
        while(temp->next != NULL){
            temp = temp->next;
            removeEntita(temp->prev->e, true);
        } 
        removeEntita(temp->e, true);
    }
};


void ListaProiettili::stampaTutte(int offsetY, int offsetX) {
    plistaPro headTemp = head;
    while(headTemp != NULL) {
        headTemp->e->stampa(offsetY, offsetX);
        headTemp = headTemp->next; 
    }
}


void ListaProiettili::aggiornaEntita(Stanza * stanza, Player * player) {
    plistaPro headTemp = head;
    while(headTemp != NULL) {
        headTemp->e->updateEntita(stanza, player);
        headTemp = headTemp->next; 
    }
}

void ListaProiettili::aggiornaTick() {
    plistaPro headTemp = head;
    while(headTemp != NULL) {
        headTemp->e->toCurrentTick();
        headTemp = headTemp->next; 
    }
}


int ListaProiettili::lengthList(){
    int returnvalue=0;
    listaPro * tmp = this-> head;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

int ListaProiettili::lengthList(bool type){
    int returnvalue=0;
    listaPro * tmp = this-> head;
    while(tmp!=NULL){
        if (!type != tmp->e->isPlayerProjectile()){
            returnvalue+=1;
        }
        tmp = tmp -> next;
    }
    return returnvalue;
}

int ListaProiettili::lengthcList(){
    int returnvalue=0;
    listaPro * tmp = this-> chead;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

int ListaProiettili::lengthcList(bool type){
    int returnvalue=0;
    listaPro * tmp = this-> chead;
    while(tmp!=NULL){
        if (!type != tmp->e->isPlayerProjectile()){
            returnvalue+=1;
        }
        tmp = tmp -> next;
    }
    return returnvalue;
}