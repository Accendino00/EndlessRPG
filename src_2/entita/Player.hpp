#pragma once
#include "../generale/libs.hpp"

class Player:public Entita{
private:
    int lastinput;
    int dashDistanceX, dashDistanceY;

public:
    Player(int y, int x, int life);

    /*
    Da aggiungere un puntatore alla stanza come parametro di questi due metodi, 
    in modo che non ne creiamo una nuova, ma andiamo a chiamare quella 
    che già esiste in "Game"
    */
   
    void stampaHUDplayer();

    void manageInput(Livello * livello);
    void gestione_player(int input, Livello * livello);
    void muoviPlayer(int direzione, int val, Livello * livello);
    void aggiungi_vita(Artefatto a);

    void inventario();
};