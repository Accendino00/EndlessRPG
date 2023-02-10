/**
 * @file Gioco.cpp
 * @author Petru Marcel Marincas
 * @date 2022
 * 
 * @brief Classe che gestisce il Gioco.
 * 
 * In particolare, il Gioco ha dei dati che sono:
 *  - Un puntatore al Player
 *  - Un puntatore al Livello corrente
 *  - Un contatore per il Livello corrente
 *  - Un booleano che indica se il Gioco è finito
 *  - E poi dei dati relativi al popup sull'aver battuto il boss.
 * 
 * All'inizio del gioco, inizializzo diverse variabili utili, come:
 *  - I ticks contati
 *  - Il livello corrente
 *  - Il giocatore
 * 
 * La logica a grandi linee del loop di gioco è la seguente:
 *  1. Gestisco i frame, i tick e prendo gli input.
 *  2. Capisco se ho premuto 'p' per pausare il gioco.
 *  3. Gestisco gli input del giocatore, ovvero capisco se
 *     il giocatore si muove, se attacca o se usa un dash.
 *  4. Calcolo la logica del livello, ovvero muovo i nemici,
 *     faccio attaccare i nemici, faccio muovere i proiettili,
 *     gestisco l'eventuale morte dei nemici (e quindi la richiesta
 *     di far nascere un artefatto), le loro animazioni, l'apertura 
 *     di porte, l'attraversamento di esse e il cambio di stanza del 
 *     giocatore.
 *  5. Passo alla fase di stampa, dove stampo (in questo ordine):
 *      - La stanza
 *      - Le porte
 *      - I proiettili
 *      - I nemici
 *      - Gli artefatti
 *      - La minimappa
 *      - Il giocatore
 *      - L'HUD del giocatore
 *  6. Controllo se il boss è stato sconfitto, in caso di sì, mostro:
 *      - Il popup che indica che il boss è stato sconfitto
 *      - Il popup che indica che il livello è stato completato e 
 *        come passare al prossimo
 *  7. Faccio un controllo sulla vita del giocatore, se è minore di 
 *     0 allora gameover.
 *  8. Gestisco la fine del frame e, dopo l'attesa del frame (vedere
 *     documentazione di gameData->frameFinish()) stampo quello che 
 *     ho aggiunto alla stampa a schermo.
 *  9. Ripeto il loop.
 * 
 * 
 *  Alla fine del gioco, mostro il menu per salvare lo score.
 */

#pragma once
#include "../generale/libs.hpp"

class Gioco {
private:
    Player * player;
    Livello * livello_corrente;
    int livello_counter;

    bool gameOver;
    
    bool popupShow;
    long long int popupBoss;

public:
    Gioco();
    ~Gioco();

    Player * getPlayer();
    Livello * getLivello();
    int getLivelloCounter();

    void setPlayer(Player * player);
    void setLivello(Livello * livello);
    void setLivelloCounter(int livello_counter);

    void spawnArtefatto(int y, int x);

    void bossPopup();
    void cambialivello();

    void gameLoop();
};