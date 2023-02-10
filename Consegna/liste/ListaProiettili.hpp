#pragma once
#include "../generale/libs.hpp"
/**
 * @file ListaProiettili.hpp
 * @author Giuseppe Forciniti
 * @date 2022
 *
 * @brief Questa classe salva le Entita di questo tipo in una struct
 * Lista in modo da permettere alle Entità varie operazioni.
 * Comprende varie funzioni che permettono cose
 * tra cui capire se l'entità e a contatto con qualcosa, aggiungere,
 * rimuovere entità e cancellare la lista. 
 */

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
    bool checkEntity_p(Proiettile *entity, bool contactList);
    void addEntita_p(Proiettile *entity, bool contactList);
    bool removeEntita_p(Proiettile *entity,bool contactList, bool deleteEntita);

public:
    ListaProiettili();
    ~ListaProiettili();

    bool checkEntity(Proiettile *entity);
    void addEntita(Proiettile *entity);
    bool removeEntita(Proiettile *entity);
    void deleteList();
    plistaPro getList();
    int lengthList();
    int lengthList(bool type);

    bool makecList(Entita *entity);
    plistaPro getcList();
    void deletecList();
    void deletecList_fromList(bool type);
    int lengthcList();
    int lengthcList(bool type);

    void stampaTutte(int offsetY, int offsetX);

    void aggiornaEntita(Gioco * gioco);
    void aggiornaTick();

    int dmgDaProiettiliContactList(bool type);
};