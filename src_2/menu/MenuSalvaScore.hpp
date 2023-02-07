#pragma once
#include "../generale/libs.hpp"

class MenuSalvaScore : public Menu {
private:
    int score;
    char letter; // Lettera dell'alfabeto selezionata
    char nome_utente[11];

public:
    MenuSalvaScore(int score);
    void loopMenu();
    void printAll();
    void printGameOver();
};

/*
Logica:
In pratica quando l'utente salva il suo username 
viene aggiunto in coda ai nomi precedeneti (se ci sono)
I metodi di MenuScore fanno poi si che il punteggio sia aggiornato nella rispettiva
sezione del menù
*/