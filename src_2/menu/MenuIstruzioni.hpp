#pragma once
#include "../generale/libs.hpp"

class MenuIstruzioni : public Menu {
public:
    MenuIstruzioni();
    void loopMenu();
    void printAll();
    void printIstruzioni();
};