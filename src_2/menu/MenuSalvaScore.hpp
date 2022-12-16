#pragma once
#include "../generale/libs.hpp"

class MenuSalvaScore : public Menu {
private:
    int score;

public:
    MenuSalvaScore(int score);
    void loopMenu();
    void printAll();
};