#pragma once
#include "../generale/libs.hpp"

struct listaA{
    listaA *prev;
    Artefatto *e;
    listaA *next;
}; typedef listaA *plistaA;

class ListaArtefatti {
private:
    plistaA head;
    plistaA chead;

    // bool:
    // false = head, 
    // true = chead
    bool checkEntity_p(Artefatto *entity, bool b);
    void addEntita_p(Artefatto *entity, bool b);
    bool removeEntita_p(Artefatto *entity,bool b, bool deleteEntita);

public:
    ListaArtefatti();
    ~ListaArtefatti();

    bool checkEntity(Artefatto *entity);
    void addEntita(Artefatto *entity);
    bool removeEntita(Artefatto *entity, bool deleteEntita);
    void deleteList();
    plistaA getList();
    int lengthList();

    bool makecList(Entita *entity);
    plistaA getcList();
    void deletecList();
    int lengthcList();

    void stampaTutte(int offsetY, int offsetX);
};