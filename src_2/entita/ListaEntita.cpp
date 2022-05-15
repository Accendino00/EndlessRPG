#include "../generale/libs.hpp"

ListaEntita::ListaEntita(){
    this->head = NULL;
}

void ListaEntita::addEntita(Entita *entity){

    plistaE headTemp = head;
    plistaE temp = NULL;

    if(head == NULL){
        head = new listaE;
        head->prev = NULL;
        head->e = entity;
        head->next = NULL;
    }
    else{
        if(headTemp->next == NULL){
            headTemp->next = new listaE;
            temp = headTemp->next;
            temp->prev = headTemp;
            temp->e = entity;
            temp->next = NULL;
            headTemp = head;
        }else headTemp = headTemp->next;

    }

}

bool ListaEntita::removeEntita(Entita *entity){

    plistaE headTemp = head;
    plistaE prevTemp = NULL;
    plistaE nextTemp = NULL;
    bool returnvalue = true;

    if(head == NULL){
        returnvalue = false;
    }

    else if(headTemp->e == entity){
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
    else{
        if(headTemp->next != NULL){
            headTemp = headTemp->next;
        }
        else{
            returnvalue = false;
        }
    }
};

ListaEntita *ListaEntita::contactList(Entita *entity){
    
};


