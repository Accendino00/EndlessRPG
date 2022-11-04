#pragma once
#include "../generale/libs.hpp"

struct listaN{
    listaN *prev;
    Nemico *e;
    listaN *next;
}; typedef listaN *plistaN;

class ListaNemici {
private:
    plistaN head;
    plistaN chead;

    // bool:
    // false = head, 
    // true = chead
    bool checkEntity_p(Nemico *entity, bool contactList);
    void addEntita_p(Nemico *entity, bool contactList);
    bool removeEntita_p(Nemico *entity,bool contactList, bool deleteEntita);

public:
    ListaNemici();
    ~ListaNemici();

    bool checkEntity(Nemico *entity);
    void addEntita(Nemico *entity);
    bool removeEntita(Nemico *entity, bool deleteEntita);
    void deleteList();
    plistaN getList();
    int lengthList();

    bool makecList(Entita *entity);
    plistaN getcList();
    void deletecList();
    int lengthcList();

    void stampaTutte(int offsetY, int offsetX);

    void aggiornaEntita(Stanza * stanza, Player * player);
    void aggiornaTick();

    void dmgNemiciContactList(int quantita);
};