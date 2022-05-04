#include "libs.hpp"

class MainMenu {
private:
    short selezione;

public:
    MainMenu();

    void manageInput(int * inputs, int num_inputs);
    int getSelezione();
    void print();
};