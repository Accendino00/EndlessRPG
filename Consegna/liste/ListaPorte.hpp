#pragma once
#include "../generale/libs.hpp"
/**
 * @file ListaPorte.hpp
 * @author Giuseppe Forciniti
 * @date 2022
 *
 * @brief Questa classe salva le Entita di questo tipo in una struct
 * Lista in modo da permettere alle Entità varie operazioni.
 * Comprende varie funzioni che permettono cose
 * tra cui capire se l'entità e a contatto con qualcosa, aggiungere,
 * rimuovere entità e cancellare la lista. 
 */

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
    bool checkEntity_p(Porta *entity, bool contactList);
    void addEntita_p(Porta *entity, bool contactList);
    bool removeEntita_p(Porta *entity,bool contactList, bool deleteEntita);

public:
    ListaPorte();
    ~ListaPorte();

    bool checkEntity(Porta *entity);
    void addEntita(Porta *entity);
    bool removeEntita(Porta *entity);
    void deleteList(bool conChiave);
    void deleteList();
    plistaP getList();
    int lengthList(bool conChiave);
    int lengthList();

    bool makecList(Entita *entity);
    plistaP getcList();
    void deletecList();
    int lengthcList();

    void stampaTutte(int offsetY, int offsetX);
};