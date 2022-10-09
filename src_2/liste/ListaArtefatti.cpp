#include "../generale/libs.hpp"

ListaArtefatti::ListaArtefatti(){
    this->head = NULL;
}

ListaArtefatti::~ListaArtefatti(){
    this->deletecList();
    this->deleteList();
}

bool ListaArtefatti::checkEntity_p(Artefatto *Artefatto, bool b){

    // Controlla se l'entità è presente nella lista
    plistaA headTemp = head;
    bool returnvalue = false;
    plistaA cheadTemp = chead;

    if(!b){
        while(headTemp != NULL && !returnvalue){
                if(headTemp->e == Artefatto)returnvalue = true;
                else headTemp = headTemp->next;
        }
    }
    else{
        while(cheadTemp != NULL && !returnvalue){
                if(cheadTemp->e == Artefatto)returnvalue = true;
                else cheadTemp = cheadTemp->next;
        }
    }

    return returnvalue;
}


bool ListaArtefatti::checkEntity(Artefatto *Artefatto){
    return checkEntity_p(Artefatto, false);
}


void ListaArtefatti::addEntita_p(Artefatto *Artefatto, bool b){

    // aggiunge entita controllando che non sia gia presente

    plistaA headTemp = head;
    plistaA cheadTemp = chead;

    if(!b && !(checkEntity_p(Artefatto, false))){
        plistaA headTemp = head;

        if(head == NULL){
            head = new listaA;
            head->prev = NULL;
            head->e = Artefatto;
            head->next = NULL;
        }
        else{
            while(headTemp->next != NULL) headTemp = headTemp->next;
            headTemp->next = new listaA;
            headTemp->next->prev = headTemp;
            headTemp->next->next = NULL;
            headTemp->next->e = Artefatto;
        }
    }
    else if(!(checkEntity_p(Artefatto, true))){
        if(chead == NULL){
            chead = new listaA;
            chead->prev = NULL;
            chead->e = Artefatto;
            chead->next = NULL;
        }
        else{
            while(cheadTemp->next!=NULL){
                cheadTemp = cheadTemp->next;
            }
            cheadTemp->next = new listaA;
            cheadTemp->next->next = NULL;
            cheadTemp->next->prev = cheadTemp;
            cheadTemp->next->e = Artefatto;
        }
    }
}

void ListaArtefatti::addEntita(Artefatto *Artefatto){
    addEntita_p(Artefatto, false);
}

bool ListaArtefatti::removeEntita_p(Artefatto *Artefatto,bool b, bool deleteEntita){
    bool returnValue = false;
    plistaA headTemp;
    if (b) {
        headTemp = chead;
    } else {
        headTemp = head;
    }

    if(checkEntity_p(Artefatto, b)){
        returnValue = true;
        while(headTemp->e != Artefatto){
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

bool ListaArtefatti::removeEntita(Artefatto *Artefatto, bool deleteEntita) {
    removeEntita_p(Artefatto, false, deleteEntita);
}


bool ListaArtefatti::makecList(Artefatto *Artefatto){
    // Controlla quali entità sono a contatto con l'entità di input e le aggiungo in chead. Ritorno true se ci sono entita a contatto.

    bool returnValue = false;
    plistaA headTemp = head;

    while(headTemp != NULL){
        while(!(Artefatto->controllaContatto(headTemp->e))){
            headTemp = headTemp->next;
            returnValue = true;
        }
        addEntita_p(Artefatto, true);
        headTemp = headTemp->next;
    }
    return returnValue;
};

plistaA ListaArtefatti::getList(){
    return head;
};

plistaA ListaArtefatti::getcList(){
    return chead;
};

void ListaArtefatti::deletecList(){
    plistaA temp = getcList();
    if(temp != NULL) {
        while(temp->next != NULL){
            temp = temp->next;
            removeEntita_p(temp->prev->e, true, false);
        } 
        removeEntita_p(temp->e, true, false);
    }
};

void ListaArtefatti::deleteList(){
    plistaA temp = getList();
    if(temp != NULL) {
        while(temp->next != NULL){
            temp = temp->next;
            removeEntita(temp->prev->e, true);
        } 
        removeEntita(temp->e, true);
    }
};


void ListaArtefatti::stampaTutte(int offsetY, int offsetX) {
    plistaA headTemp = head;
    while(headTemp != NULL) {
        headTemp->e->stampa(offsetY, offsetX);
        headTemp = headTemp->next; 
    }
}