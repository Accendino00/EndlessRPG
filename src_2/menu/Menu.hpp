#pragma once
#include "../generale/libs.hpp"

class Menu {
private:
    short selezione;
    int numOfOptions;
    int lineOffset;

public:
    Menu(int selezione, int numOfOptions, int lineOffset);

    // void loopMenu();

    void manageInput();
    int getSelezione();
    
    // void printAll();
    void printLine(const char * text, int id);
};