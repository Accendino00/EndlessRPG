#pragma once
#include "../generale/libs.hpp"

class MenuMain {
private:
    short selezione;

public:
    MenuMain();

    void loopMenu();

    void manageInput();
    int getSelezione();
    void print();
};