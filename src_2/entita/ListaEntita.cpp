#include "../generale/libs.hpp"

ListaEntita::ListaEntita(){
    this->head = NULL;
}

bool ListaEntita::checkEntity_p(Entita *entity, bool b){

    // Controlla se l'entità è presente nella lista
    plistaE headTemp = head;
    bool returnvalue = false;
    plistaE cheadTemp = chead;

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
}


bool ListaEntita::checkEntity(Entita *entity){
    return checkEntity_p(entity, false);
}


void ListaEntita::addEntita_p(Entita *entity, bool b){

    // aggiunge entita controllando che non sia gia presente

    plistaE headTemp = head;
    plistaE cheadTemp = chead;

    if(!b && !(checkEntity_p(entity, false))){
        plistaE headTemp = head;

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


bool ListaEntita::removeEntita_p(Entita *entity, bool b){
    bool returnValue = false;
    plistaE prevTemp = NULL;
    plistaE nextTemp = NULL;
    if(!b){
        plistaE headTemp = head;

        if(checkEntity_p(entity, false)){
                returnValue = true;
                while(headTemp->e != entity){
                    headTemp = headTemp->next;
                }
                if(headTemp->e == entity){
                    if(headTemp->prev != NULL){
                        if(headTemp->next != NULL){
                            nextTemp = headTemp->next;
                            prevTemp = headTemp->prev;
                            delete headTemp;
                            prevTemp->next = nextTemp;
                            nextTemp->prev = prevTemp;
                            headTemp = head;
                        }
                        else{
                            prevTemp = headTemp->prev;
                            delete headTemp;
                            prevTemp->next = NULL;
                            headTemp = head;
                        }
                    }
                    else{
                        nextTemp = headTemp->next;
                        delete headTemp;
                        nextTemp->prev = NULL;
                        headTemp = head;
                    }
            }
        }
    }
    else{
        plistaE cheadTemp = chead;
        if(checkEntity_p(entity, true)){
                returnValue = true;
                while(cheadTemp->e != entity){
                    cheadTemp = cheadTemp->next;
                }
                if(cheadTemp->e == entity){
                    if(cheadTemp->prev != NULL){
                        if(cheadTemp->next != NULL){
                            nextTemp = cheadTemp->next;
                            prevTemp = cheadTemp->prev;
                            delete cheadTemp;
                            prevTemp->next = nextTemp;
                            nextTemp->prev = prevTemp;
                            cheadTemp = chead;
                        }
                        else{
                            prevTemp = cheadTemp->prev;
                            delete cheadTemp;
                            prevTemp->next = NULL;
                            cheadTemp = chead;
                        }
                    }
                    else{
                        nextTemp = cheadTemp->next;
                        delete cheadTemp;
                        nextTemp->prev = NULL;
                        cheadTemp = chead;
                    }
            }
        }
    }
}

bool ListaEntita::removeEntita(Entita *entity){
    return removeEntita_p(entity, false);
};


bool ListaEntita::makecList(Entita *entity){
    // Controlla quali entità sono a contatto con l'entità di input e le aggiungo in chead. Ritorno true se ci sono entita a contatto.

    bool returnValue = false;
    plistaE headTemp = head;

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

ListaEntita::plistaE ListaEntita::getcList(){
    return chead;

};

void ListaEntita::deletecList(){

    while(chead->next != NULL){
        delete chead->prev->next;
        chead->prev->next = NULL;
        delete chead->prev;
        chead->prev = NULL;
        chead = chead->next;
    } 
    delete chead->prev;
    chead->prev = NULL;
    delete chead;
    chead = NULL;


};

