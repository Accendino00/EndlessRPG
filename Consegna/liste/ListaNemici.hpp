#pragma once
#include "../generale/libs.hpp"
/**
 * @file ListaNemici.hpp
 * @author Giuseppe Forciniti
 * @date 2022
 *
 * @brief Questa classe salva le Entita di questo tipo in una struct
 * Lista in modo da permettere alle Entità varie operazioni.
 * Comprende varie funzioni che permettono cose
 * tra cui capire se l'entità e a contatto con qualcosa, aggiungere,
 * rimuovere entità e cancellare la lista. 
 */

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
    bool removeEntita(Gioco * gioco, Nemico *entity);
    bool removeEntita(Nemico *entity);
    void deleteList();
    plistaN getList();
    int lengthList();

    bool makecList(Entita *entity);
    plistaN getcList();
    void deletecList();
    int lengthcList();

    void stampaTutte(int offsetY, int offsetX);

    void aggiornaEntita(Gioco * gioco);
    void aggiornaTick();

    void dmgNemiciContactList(Gioco * gioco, int quantita);
};