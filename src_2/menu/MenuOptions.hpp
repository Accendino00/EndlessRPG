#pragma once
#include "../generale/libs.hpp"

class MenuOptions {
private:
    short selezione;

public:
    MenuOptions();

    void loopMenu();

    void manageInput();
    int getSelezione();
    void print();
};