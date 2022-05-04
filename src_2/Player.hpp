#pragma once
#include "libs.hpp"

class Player:public Entita{
    private:

    public:
    Player(int y, int x);
    void movimento(int input, Stanza stanza);
    void inventario();

};