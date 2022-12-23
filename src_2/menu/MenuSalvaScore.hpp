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