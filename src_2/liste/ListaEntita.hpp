#pragma once
#include "../generale/libs.hpp"

struct listaE{
    listaE *prev;
    Entita *e;
    listaE *next;
}; typedef listaE *plistaE;

class ListaEntita {
private:
    plistaE head;
    plistaE chead;

    // bool:
    // false = head, 
    // true = chead
    bool checkEntity_p(Entita *entity, bool contactList);
    void addEntita_p(Entita *entity, bool contactList);
    bool removeEntita_p(Entita *entity,bool contactList, bool deleteEntita);

public:
    ListaEntita();
    ~ListaEntita();

    bool checkEntity(Entita *entity);
    void addEntita(Entita *entity);
    bool removeEntita(Entita *entity, bool deleteEntita);
    void deleteList();
    plistaE getList();
    int lengthList();

    bool makecList(Entita *entity);
    plistaE getcList();
    void deletecList();
    int lengthcList();

    void stampaTutte(int offsetY, int offsetX);
};