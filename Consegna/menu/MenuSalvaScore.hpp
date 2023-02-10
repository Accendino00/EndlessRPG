/**
 * @file MenuSalvaScore.hpp
 * @author Jacopo Francesco Amoretti
 * @date 2022
 * 
 * @brief 
 *  Classe di MenuSalvaScore, che gestisce il menu per salvare il punteggio.
 *  Il punteggio viene salvato in un file di testo, e viene visualizzato nel menu MenuScore.
 * 
 *  Il punteggio viene salvato scrivendo il nome dell'utente e il punteggio ottenuto.
 *  Il nome viene scelto all'interno di questo menu.
 */

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