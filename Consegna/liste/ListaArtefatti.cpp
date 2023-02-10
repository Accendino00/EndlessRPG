#include "../generale/libs.hpp"


ListaArtefatti::ListaArtefatti(){
    this->head = NULL;
    this->chead = NULL;
}

ListaArtefatti::~ListaArtefatti(){
    this->deletecList();
    this->deleteList();
}

bool ListaArtefatti::checkEntity_p(Artefatto *Artefatto, bool contactList){

    // Controlla se l'entità è presente nella lista
    plistaA headTemp = head;
    bool returnvalue = false;
    plistaA cheadTemp = chead;

    if(!contactList){
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

bool ListaArtefatti::checkEntity(int type) {
    plistaA headTemp = head;
    bool returnvalue = false;
    while(headTemp != NULL && !returnvalue){
            if(headTemp->e->getIDArtefatto() == type) returnvalue = true;
            else headTemp = headTemp->next;
    }
    return returnvalue;
}

/**
 * @brief addEntita_p aggiunge un entita alla lista con un bool per decidere
 * se aggiungere l'entità alla contactList o alla lista normale.
 * 
 * @param Artefatto 
 * @param contactList 
 */


void ListaArtefatti::addEntita_p(Artefatto *Artefatto, bool contactList){

    // aggiunge entita controllando che non sia gia presente

    plistaA headTemp = head;
    plistaA cheadTemp = chead;

    if(!contactList && !(checkEntity_p(Artefatto, false))){
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
/**
 * @brief // Uso removeEntita_p per compattare le funzioni di rimozione e
 * uso 2 booleani per decidere cosa cancellare e da dove.
 * La cancello dalla contactlist senza cancellare l'entita
 *
 * 
 * @param entity 
 * @param contactList La cancello dalla contactlist
 * @param deleteEntita La cancello dalla lista normale
 * @return true 
 * @return false 
 */


bool ListaArtefatti::removeEntita_p(Artefatto *entity, bool contactList, bool deleteEntita){
    bool returnValue = false;
    plistaA headTemp;
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

bool ListaArtefatti::removeEntita(Artefatto *entity) {
    removeEntita_p(entity, true, false); // La cancello dalla contactlist senza cancellare l'entita
    return removeEntita_p(entity, false, true); // La cancello dalla lista normale cancellando l'entita
}


bool ListaArtefatti::makecList(Entita *entity){
    // Controlla quali entità sono a contatto con l'entità di input e le aggiungo in chead. Ritorno true se ci sono entita a contatto.

    deletecList();

    bool returnValue = false;
    plistaA headTemp = head;

    while(headTemp != NULL){
        if (headTemp->e != entity && (entity->controllaContatto(headTemp->e))) {
            addEntita_p(headTemp->e, true);
            returnValue = true;
        }
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

void ListaArtefatti::deleteList(){
    plistaA temp = getList();
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


void ListaArtefatti::stampaTutte(int offsetY, int offsetX) {
    plistaA headTemp = head;
    while(headTemp != NULL) {
        headTemp->e->stampa(offsetY, offsetX);
        headTemp = headTemp->next; 
    }
}

int ListaArtefatti::lengthList(){
    int returnvalue=0;
    listaA * tmp = this-> head;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}

int ListaArtefatti::lengthcList(){
    int returnvalue=0;
    listaA * tmp = this-> chead;
    while(tmp!=NULL){
        returnvalue+=1;
        tmp = tmp -> next;
    }
    return returnvalue;
}
/**
 * @brief Se l'artefatto esiste e quindi ha vita > 0, applica
 * gli effetti degli artefatti chiamando una funzione di Entita
 * e poi cancella l'Artefatto
 * 
 * @param player 
 */
void ListaArtefatti::effettiArtefatti(Player * player){
    listaA * tmp = this->chead;
    while(tmp!=NULL){
        if (tmp->e->getVita() > 0) {
            tmp->e->applicaEffetto(player);
        } 
        removeEntita(tmp->e);
        tmp = this->chead;
    }

}

void ListaArtefatti::aggiornaEntita(Gioco * gioco) {
    plistaA headTemp = head;
    while(headTemp != NULL) {
        if (headTemp->e->getVita() <= 0) {
            removeEntita(headTemp->e);
            headTemp = head;
        } else {
            headTemp->e->updateEntita(gioco->getPlayer());
            if(headTemp->e->getVita() == 0) {
                removeEntita(headTemp->e);
                headTemp = head;
            } else {
                headTemp = headTemp->next;
            }
        }
    }
}