#pragma once
#include "../generale/libs.hpp"

struct listaPro{
    listaPro *prev;
    Proiettile *e;
    listaPro *next;
}; typedef listaPro * plistaPro;

class ListaProiettili {
private:
    plistaPro head;
    plistaPro chead;

    // bool:
    // false = head, 
    // true = chead
    bool checkEntity_p(Proiettile *entity, bool b);
    void addEntita_p(Proiettile *entity, bool b);
    bool removeEntita_p(Proiettile *entity,bool b, bool deleteEntita);

public:
    ListaProiettili();
    ~ListaProiettili();

    bool checkEntity(Proiettile *entity);
    void addEntita(Proiettile *entity);
    bool removeEntita(Proiettile *entity, bool deleteEntita);
    void deleteList();
    plistaPro getList();
    int lengthList();
    int lengthList(bool type);

    bool makecList(Entita *entity);
    plistaPro getcList();
    void deletecList();
    int lengthcList();
    int lengthcList(bool type);

    void stampaTutte(int offsetY, int offsetX);

    void aggiornaEntita(Stanza * stanza, Player * player);
    void aggiornaTick();
};