#pragma once
#include "../generale/libs.hpp"

class Player:public Entita{
    private:

    public:
    Player(int y, int x);

    /*
    Da aggiungere un puntatore alla stanza come parametro di questi due metodi, 
    in modo che non ne creiamo una nuova, ma andiamo a chiamare quella 
    che già esiste in "Game"
    */
   
    void manageInput();
    void movimento(int input);

    void inventario();
};