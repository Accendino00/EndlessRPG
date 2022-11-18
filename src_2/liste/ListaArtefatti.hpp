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
    bool checkEntity_p(Artefatto *entity, bool contactList);
    void addEntita_p(Artefatto *entity, bool contactList);
    bool removeEntita_p(Artefatto *entity, bool contactList, bool deleteEntita);

public:
    ListaArtefatti();
    ~ListaArtefatti();

    bool checkEntity(Artefatto *entity);
    void addEntita(Artefatto *entity);
    bool removeEntita(Artefatto *entity);
    void deleteList();
    plistaA getList();
    int lengthList();

    bool makecList(Entita *entity);
    plistaA getcList();
    void deletecList();
    int lengthcList();


    void aggiornaEntita(Gioco * gioco);
    void effettiArtefatti(Player * player);

    void stampaTutte(int offsetY, int offsetX);
};