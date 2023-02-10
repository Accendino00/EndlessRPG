/**
 * @file MenuScore.hpp
 * @author Jacopo Francesco Amoretti
 * @date 2022
 * 
 * @brief 
 *  Classe di MenuScore, che gestisce il menu per visualizzare i punteggi salvati.
 *  I punteggi migliori sono elencati in cima, mentre quelli peggiori saranno in fondo.
 */

#pragma once
#include "../generale/libs.hpp"

struct UserData {
    int score;
    char nome[11];
};

// Dato generico per lo score (punteggio e nome di 3 caratteri)
struct UserDataList {
    UserData data;
    UserDataList *next;
}; typedef UserDataList *pUserData;


class MenuScore : public Menu {
private:
    int scoreCounter;               // Grandezza dell'array    
    UserData * arrayScore;          // Array ordinato con gli score

    int pagina;                     // Numero della pagina visualizzata

public:
    MenuScore();
    ~MenuScore();
    void loopScore();
    void printAll();
};