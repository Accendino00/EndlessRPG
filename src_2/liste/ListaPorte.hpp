#pragma once
#include "../generale/libs.hpp"

struct listaP{
    listaP *prev;
    Porta *e;
    listaP *next;
}; typedef listaP *plistaP;

class ListaPorte  {
private:
    plistaP head;
    plistaP chead;

    // bool:
    // false = head, 
    // true = chead
    bool checkEntity_p(Porta *entity, bool b);
    void addEntita_p(Porta *entity, bool b);
    bool removeEntita_p(Porta *entity,bool b, bool deleteEntita);

public:
    ListaPorte();
    ~ListaPorte();

    bool checkEntity(Porta *entity);
    void addEntita(Porta *entity);
    bool removeEntita(Porta *entity, bool deleteEntita);
    void deleteList();
    plistaP getList();

    bool makecList(Porta *entity);
    plistaP getcList();
    void deletecList();

    void stampaTutte(int offsetY, int offsetX);
};