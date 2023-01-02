#pragma once
#include "../generale/libs.hpp"

class MenuSalvaScore : public Menu {
private:
    int score;
    char letter; // Lettera dell'alfabeto selezionata
    int x_offset;

public:
    MenuSalvaScore(int score);
    void loopMenu();
    void printAll();
    void printGameOver();
};

/*
Logica:
In pratica quando l'utente salva il il suo username 
succede che se è il primissimo giocatore scrive subito il 
nome in testa al file. Se invece ci sono altri nomi
devo scorrerli finché non arrivo in fondo al file
e lì lo posso aggiungere in coda.
A questo punto in entrambi i casi faccio partire
il metodo salva_carica_score del MenuScore il quale
stampa nel menù punteggi il nome e il punteggio
*/