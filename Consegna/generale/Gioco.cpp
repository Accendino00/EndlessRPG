/**
 * @file Gioco.cpp
 * @author Petru Marcel Marincas
 * @date 2022
 * 
 * @brief Classe che gestisce il Gioco.
 * 
 * Per più informazioni leggere la documentazione delle funzioni 
 * oppure il commento iniziale di Gioco.hpp.
 */

#include "../generale/libs.hpp"

Gioco::Gioco(){
    this->gameOver = false;
    this->popupShow = false;
    this->livello_counter = 0;
}

Gioco::~Gioco() {
    delete this->player;
    delete livello_corrente;
}


// GETTERS & SETTERS

Player * Gioco::getPlayer(){
    return this->player;
}
Livello * Gioco::getLivello() {
    return this->livello_corrente;
}
int Gioco::getLivelloCounter() {
    return this->livello_counter;
}

void Gioco::setPlayer(Player * player) {
    this->player = player;
}
void Gioco::setLivello(Livello * livello) {
    this->livello_corrente = livello;
}
void Gioco::setLivelloCounter(int livello_counter) {
    this->livello_counter = livello_counter;
}

/**
 * @brief Funzione che crea un artefatto alle coordinate specificate.
 * Non lo crea sempre, bensì usa un droprate per decidere se crearlo o meno.
 * 
 * Il tipo di artefatto che crea è casuale, tranne nel caso in cui non ci siano
 * più nemici, e in quel caso crea sempre una chiave.
 * 
 * @param y 
 * @param x 
 */
void Gioco::spawnArtefatto(int y, int x) {
    
    // Bool per capire se e' stato spawnato un artefatto
    // In quanto al massimo se ne puo' spawnare uno
    bool spawn = false;

    /////////// CHIAVE

    // SPAWN DELLA CHIAVE
    if(!(getPlayer()->getChiave()) && !livello_corrente->haArtefatto(TIPOART_CHIAVE)){
        float keyDroprate;
        if(this->livello_corrente->getNumNemici() != 0){
            // Il droprate della chiave, se ci sono ancora dei nemici è deciso usando la funzione:
            // y = -1/3x + 15, dove x è il numero di nemici e y è il droprate risultante.
            //   Questo vuol dire che inizierà a poter fare spawn la chiave quando ci sono meno di 45 nemici,
            //   e avrà sempre un droprate inferiore al 15%, finchè ci sono ancora nemici.
            keyDroprate = ((-1/3.0f)*this->livello_corrente->getNumNemici())+15;
        }
        else{
            // Se invece non ci sono più nemici, devo spawnare la chiave, quindi il droprate è 100%
            keyDroprate = 100;
        }
        if(rand() % 100 < keyDroprate){
            this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_CHIAVE, this->livello_corrente->getStanza()->getId()));
            spawn = true;
        }
    }

    /////////// POTENZIAMENTI

    // SPAWN DELL'ATTACCO DIETRO
    float atkDietroDroprate = 5.0;
    if(!(getPlayer()->getAttacks(1)) && !livello_corrente->haArtefatto(TIPOART_ATTACCO_DIETRO)
    && !(spawn) && rand() % 100 < atkDietroDroprate){
        this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_ATTACCO_DIETRO, this->livello_corrente->getStanza()->getId()));
        spawn = true;
    }
    
    // SPAWN DELL'ATTACCO DIAGONALE 
    float atkDiagonaleDroprate = 3.0;
    if(!(getPlayer()->getAttacks(2)) && !livello_corrente->haArtefatto(TIPOART_ATTACCO_DIAGONALE)
    && !(spawn) && rand() % 100 < atkDiagonaleDroprate){
        this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_ATTACCO_DIAGONALE, this->livello_corrente->getStanza()->getId()));
        spawn = true;
    }

    // SPAWN DELL'AUMENTO DELLO SPRINT DEL GIOCATORE
    float aumentaSprintDroprate = 5.0;
    if(getPlayer()->getSprint() < 6 && !livello_corrente->haArtefatto(TIPOART_AUMENTA_SPRINT)
    && !(spawn) && rand() % 100 < aumentaSprintDroprate){
        this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_AUMENTA_SPRINT, this->livello_corrente->getStanza()->getId()));
        spawn = true;
    }

    // SPAWN DELL'AUMENTO DELLA VELOCITA' DEI PROIETTILI DEL GIOCATORE
    float aumentaVelProiettiliDroprate = 5.0;
    if(getPlayer()->getVelProiettile() < 2.5 && !livello_corrente->haArtefatto(TIPOART_VEL_PROIETTILI)
    && !(spawn) && rand() % 100 < aumentaVelProiettiliDroprate){
        this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_VEL_PROIETTILI, this->livello_corrente->getStanza()->getId()));
        spawn = true;
    }

    // SPAWN DELL'ATTACCO SHOTGUN
    float atkShotgunDroprate= 3.0;
    if(!(getPlayer()->getAttacks(3)) && !livello_corrente->haArtefatto(TIPOART_ATTACCO_SHOTGUN)
    && !(spawn) && rand() % 100 < atkShotgunDroprate){
        this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_ATTACCO_SHOTGUN, this->livello_corrente->getStanza()->getId()));
        spawn = true;
    }



    /////////// STATISTICHE

    // SPAWN DELL'AUMENTO DEL DANNO DEL GIOCATORE
    float aumentaAttaccoDroprate = 8.0;
    if(!(spawn) && rand() % 100 < aumentaAttaccoDroprate){
        this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_AUMENTA_ATTACCO, this->livello_corrente->getStanza()->getId()));
        spawn = true;
    }

    // SPAWN DELL'AUMENTO DELLA DIFESA DEL GIOCATORE
    float aumentaDifesaDroprate = 10.0;
    if(!(spawn) && rand() % 100 < aumentaDifesaDroprate){
        this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_AUMENTA_DIFESA, this->livello_corrente->getStanza()->getId()));
        spawn = true;
    }


    // SPAWN DELL'AUMENTO DELLA VITA DEL GIOCATORE
    float aumentaMaxHPDroprate = 5.0;
    if(getPlayer()->maxVita < 300 && !(spawn) && rand() % 100 < aumentaMaxHPDroprate){
        this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_AUMENTA_MAX_HP, this->livello_corrente->getStanza()->getId()));
        spawn = true;
    }



    /////////// HP

    // SPAWN DELLA VITA DEL GIOCATORE
    float aumentaHPDroprate = 15.0;
    if(!(spawn) && rand() % 100 < aumentaHPDroprate){
        this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,TIPOART_AUMENTA_HP, this->livello_corrente->getStanza()->getId()));
        spawn = true;
    }
}

/**
 * @brief Mostro un popup quando il giocatore sconfigge il boss.
 * 
 * Questo popup compare 1 secondo dopo aver sconfitto il boss e dura 2 secondi.
 * Questa funzione modifica anche lvlcleared a true, in modo da non far apparire più volte il popup.
 */
void Gioco::bossPopup(){
    if (!this->popupShow) {
        this->popupBoss = gd->getCurrentTick();
        this->popupShow = true;
    }
    if(this->popupShow && gd->getCurrentTick() - popupBoss > 1000 && gd->getCurrentTick() - popupBoss < 3000) {
        mvprintw((gd->getTerminalY()/2)-1, ((gd->getTerminalX()/2) - 15), "╔══════════════════════════════╗");
        mvprintw((gd->getTerminalY()/2),   ((gd->getTerminalX()/2) - 15), "║ 🎉 Hai sconfitto il Boss! 🎉 ║");
        mvprintw((gd->getTerminalY()/2)+1, ((gd->getTerminalX()/2) - 15), "╚══════════════════════════════╝");
    }
}

/**
 * @brief Cambia il livello quando il giocatore sconfigge tutti i nemici.
 * 
 * Mostra a schermo un popup che permette al giocatore di cambiare livello premendo "l".
 * Si può cambiare livello solo se non si è in una stanza con dei nemici ancora vivi, anche
 * se il boss è stato sconfitto.
 */
void Gioco::cambialivello(){
    if(livello_corrente->getStanza()->getNumNemici()==0){
        mvprintw( 6, 10, "╔══════════════════════════════════╗");
        mvprintw( 7, 10, "║ Premere 'l' per cambiare livello ║");
        mvprintw( 8, 10, "╚══════════════════════════════════╝");
        if(gd->checkInput('l')){
            delete livello_corrente;
            // livello_counter parte da 1, ma il primo livello parte da 0, quindi prima
            // lo passo come parametro e poi lo incremento.
            livello_corrente = new Livello(livello_counter++);
            player->modificaCoordinate((int)DIM_STANZA_SPAWN_Y/2,(int)DIM_STANZA_SPAWN_X/2);
            player->setFrame(FRAME_OF_E);
            player->setChiave(false);
            this->popupShow = false;
        }
    }    
}

/**
 * @brief Getisce il loop di gioco. Per la descrizione a grandi linee,
 * vedere il primo commento in Gioco.hpp.
 */
void Gioco::gameLoop() {
    // Imposto i ticket a 0 quando inizia il gioco
    gd->resetTicks();

    this->player = new Player((int)DIM_STANZA_SPAWN_Y/2,(int)DIM_STANZA_SPAWN_X/2, 50);
    this->livello_corrente = new Livello(this->livello_counter++);

    this->player->toCurrentTick();
    this->livello_corrente -> aggiornaTick();
    
    MenuPause *m_pause;
    MenuSalvaScore *m_salvascore;

    do {
        // Inizio del frame, aggiornamento dei tick, lettura input e erase dello schermo
        gd->frameStart();
        gd->manageTicks();
        gd->getInput();
        erase(); 
        
        /*** Gestione degli input ***/

        if(gd->checkInput('p')) {
            m_pause = new MenuPause();
            gameOver = m_pause->loopMenu();
            delete m_pause;

            // Riporto i tick a quelli attuali
            gd->manageTicks();
            this->livello_corrente -> aggiornaTick();
            this->player->toCurrentTick();
        }

        this->player->manageInput(livello_corrente);


        /*** Calcolo della logica ***/

        livello_corrente -> calcolo_logica(this);
        
        /*** Stampa ***/

        livello_corrente -> stampa();
    
        this->player->stampa(livello_corrente->offsetY(), livello_corrente->offsetX());
        this->player->stampaHUDplayer();
        
        
        if(livello_corrente->Bossisdead()){
            bossPopup();
            cambialivello();
        }

        if(this->player->getVita() <= 0) {
            gameOver = true;
        }

        // Fine del frame e refresh dello schermo
        gd->frameFinish();
        refresh();
    } while (! (gameOver) );

    // Quando il gioco finisce, c'è la schermata di game over e di salvataggio del punteggio
    m_salvascore = new MenuSalvaScore(this->player->getScore());
    m_salvascore->loopMenu();
    delete m_salvascore;
}

