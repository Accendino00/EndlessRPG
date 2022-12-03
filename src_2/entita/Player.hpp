#pragma once
#include "../generale/libs.hpp"

class Player:public Entita{
private:
    // Utils
    int lastinput;

    // Attributi
    int sprintDistance;
    int difesa;
    double velocitaProiettile;

    // Inventario
    bool attacco_dietro;
    bool attacco_diagonale;
    bool chiave;
    bool attacco_shotgun;

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
    void sparaProiettile(int dir, int offset, Stanza * stanza);
    
    void modificaDifesa(int val);
    void modificaVita(int quantita);
    void modificaMaxVita(int quantita);
    void modificaSprint(int val);
    void modificaDanno(int danno);
    void modificaVelProiettile(int val);

    void setChiave(bool val);
    bool getChiave();

    int getSprint();
    int getVelProiettile();

    void inventario();
};