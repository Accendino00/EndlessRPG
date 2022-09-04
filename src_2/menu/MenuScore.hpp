#pragma once
#include "../generale/libs.hpp"

//Dato generico per lo score (punteggio e nome di 3 caratteri)
struct dati {
    int score;
    char [3] nome;
    dati *next;
};
typedef dati *ptrlist;

class MenuScore : public Menu {
private:
    ptrlist head;     //Testa della lista dei punteggi
public:
    MenuScore();
    void caricaScore();
    void loopScore();
    void printAll();

};

/*
idea di dato:
struct dati {
    int score;
    char [3] nome;
}
dati [100] da_leggere;
(^^^^ meglio da implementare dinamicamente ^^^^)
(^^^^ idea: radoppia la dimensione dell'array se hai finito lo spazio ^^^^)

non usare malloc e free, usa solo new e delete

leggere tutti i dati da un file csv del tipo:
    AAA;1231512
    BAS;512
    ...
    ZZZ;323357

ordinare i dati letti in ordine decrescente

stamparne 10 a volta sullo schermo, poi avere un opzione per cambiare pagina
e mostrare i 10 dopo, e così via


ricordati di deallocare tutto con il destructor alla fine (metodo scritto come: ~MenuScore())

 I valori che mostri, dallarray di valori letti, sono da
Arr[numpagina*10]
Fino a
Arr[(numpagina+1)*10]
*/
