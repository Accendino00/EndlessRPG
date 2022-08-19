#pragma once
#include "../generale/libs.hpp"

class MenuMain : public Menu {
public:
    MenuMain();

    void loopMenu();
    void printAll();
    void printTitle();
};