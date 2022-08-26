#pragma once
#include "../generale/libs.hpp"

struct listaE{
    listaE *prev;
    Entita *e;
    listaE *next;
}; typedef listaE *plistaE;

class ListaEntita : public Entita{
private:
    plistaE head;
    plistaE chead;

    // bool:
    // false = head, 
    // true = chead
    bool checkEntity_p(Entita *entity, bool b);
    void addEntita_p(Entita *entity, bool b);
    bool removeEntita_p(Entita *entity,bool b, bool deleteEntita);

public:
    ListaEntita();
    ~ListaEntita();

    bool checkEntity(Entita *entity);
    void addEntita(Entita *entity);
    bool removeEntita(Entita *entity, bool deleteEntita);
    void deleteList();
    plistaE getList();

    bool makecList(Entita *entity);
    plistaE getcList();
    void deletecList();

    void stampaTutte(int offsetY, int offsetX);
};