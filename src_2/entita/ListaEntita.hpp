#pragma once
#include "../generale/libs.hpp"

class ListaEntita:public Entita{
private:
    struct listaE{
        listaE *prev;
        Entita *e;
        listaE *next;
    }; typedef listaE *plistaE;



    plistaE head;
    // Lista mega contatti ( attento !)
    plistaE chead;

    // bool:
    // false = head, 
    // true = chead
    bool checkEntity_p(Entita *entity, bool b);
    void addEntita_p(Entita *entity, bool b);
    bool removeEntita_p(Entita *entity, bool b);

public:
    ListaEntita();
    bool checkEntity(Entita *entity);
    void addEntita(Entita *entity);
    bool removeEntita(Entita *entity);
    bool makecList(Entita *entity);
    plistaE getcList();
    void deletecList();


};