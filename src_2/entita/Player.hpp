#pragma once
#include "../generale/libs.hpp"

class Player:public Entita{
    private:

    public:
    Player(int y, int x);
    void movimento(int input, Stanza stanza);
    void inventario();

};