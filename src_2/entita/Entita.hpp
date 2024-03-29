#pragma once
#include "../generale/libs.hpp"

class Entita {
public:
    // Punti salute
    int vita;
    int maxVita;

    // Danno fatto con il tocco di questa entità
    int damage;

    // Coordinate dell'angolo in alto a sinistra dell'entita
    int x, y;
    
    int h_dimx, h_dimy; // Dimensioni hitbox
    int s_dimx, s_dimy; // Dimensioni stampabile
    int currentFrame; // Lo stampabile che viene mostrato in un determinato momento

    // Matrice che contiene il contenuto da stampare per rappresentare l'entità
    cchar_t ** stampabile;

    // Per poterlo animare e in generale fargli fare cose ogni n tempo
    long long int lastTick;
    long long int ticksForAction;

    long long int passedActions; // Basato su ticksForAction

public:
    Entita();
    Entita(int life, int y,int x, int dim_y, int dim_x, cchar_t ** stampa);
    ~Entita();

    void stampa(int offsetY, int offsetX);
    
    bool controllaContatto(Entita * entita);
    bool controllaContatto(int x, int y, int h_dimx, int h_dimy);

    void updateEntita();
    void toCurrentTick();
    
    void nextFrame();
    void setFrame(int frame);
    int getMaxFrames();

    int getDamage();

    int getVita();
    void modificaVita(int quantita);
    void setVita(int quantita);

    int getMaxVita();
    void setMaxVita(int quantita);

    void modificaCoordinate(int new_y, int new_x);
    void incrementaX(int amount);
    void incrementaY(int amount);
    int getX();
    int getY();

    int getDimX();
    int getDimY();

    void muovi(int direzione, int val);
    int movimentoValido(int direzione, int val, Stanza * Stanza, bool giocatore);
};