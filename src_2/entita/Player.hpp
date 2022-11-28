#pragma once
#include "../generale/libs.hpp"

class Player:public Entita{
private:
    int lastinput;
    int dashDistanceX, dashDistanceY;
    bool attacco_dietro;
    bool attacco_diagonale;
    int difesa;
    bool chiave;

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
    
    void aggiungiDirezioneAttacco(int direzione);
    
    void modificaDifesa(int val);
    void modificaVita(int quantita);
    void modificaSprint(int val);
    void modificaDanno(int danno);

    void setChiave(bool val);
    bool getChiave();

    void inventario();
};