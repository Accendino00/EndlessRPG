#include "../generale/libs.hpp"

class ListaEntita:public Entita{
private:
    struct listaE{
        listaE *prev;
        Entita *e;
        listaE *next;
    }; typedef listaE *plistaE;

    plistaE head;
public:
    ListaEntita();
    void addEntita(Entita *entity);
    bool removeEntita(Entita *entity);
    ListaEntita *contactList(Entita *entity);

};