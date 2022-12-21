#pragma once
#include "../generale/libs.hpp"

class MenuSalvaScore : public Menu {
private:
    int score;
    int letter; // Lettera dell'alfabeto selezionata
    char alphabet[27]; // Array con alfabeto

public:
    MenuSalvaScore(int score);
    void loopMenu();
    void printAll();
};