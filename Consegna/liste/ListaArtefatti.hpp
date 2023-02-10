#pragma once
#include "../generale/libs.hpp"
/**
 * @file ListaArtefatti.hpp
 * @author Giuseppe Forciniti
 * @date 2022
 *
 * @brief Questa classe salva le Entita di questo tipo in una struct
 * Lista in modo da permettere alle Entità varie operazioni.
 * Comprende varie funzioni che permettono cose
 * tra cui capire se l'entità e a contatto con qualcosa, aggiungere,
 * rimuovere entità e cancellare la lista. 
 */


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
    bool checkEntity(int type);
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