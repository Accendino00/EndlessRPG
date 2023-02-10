/**
 * @file Player.hpp
 * @author Giuseppe Forciniti
 * @date 2022
 * @brief 
 *    Contiene la classe Player che estende la classe Entita.
 *    Il Player è un'entità che si muove a diverse velocità, spara, 
 *    prende artefatti che modificano i suoi attributi, e può essere
 *    sconfitto dai Nemici.
 *     
 *    Le azioni del Player sono determinate dall'input del giocatore,
 *    utilizzando una variabile lastinput, e delle funzioni di gestione
 *    dell'input, tra cui manageInput che controlla il numero di tasti 
 *    premuti e li identifica attraverso GameData, e li passa alla funzione
 *    di gestione del Player, che prende
 *    in input i tasti premuti e muove il Player in una certa direzione,
 *    ad una certa velocità, dentro a un certo livello, oppure compie azioni
 *    come lo sparare Proiettili.
 *    
 *    Per esempio, se il giocatore preme il tasto "W", GameData prende l'input
 *    e lo mette in un array, manageInput entra in un while loop dove finche
 *    non legge tutti gli input aumenta un contatore, e ad ogni passo del loop
 *    passa l'input alla funzione di gestione del player. In questo caso fa solo
 *    1 loop e passa a gestione_player l'input "W", e il Player si muove.
 * 
 *    Ci sono anche varie funzioni per gestire tutti i parametri del Player
 *    che inoltre vengono anche stampati come HUD di gioco. Parametri come
 *    vita, danno, artefatti, difesa, velocità, velocità proiettili e score.
 *
 *    
 * 
 * 
 */







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

    // Lo score del giocatore
    int score;

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
    void modificaVelProiettile(double val);

    void setChiave(bool val);
    bool getChiave();

    int getSprint();
    double getVelProiettile();

    bool getAttacks(int attack);

    void inventario();

    int getScore();
    void modificaScore(int val);
    void setScore(int val);
};