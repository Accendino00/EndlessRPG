#include "../generale/libs.hpp"

Gioco::Gioco(){
    this->player = new Player(0,0, 50);
}

void Gioco::gameLoop() {
    bool gameOver = false;
    Proiettile * pr = NULL;
    gd->resetTicks();

    Stanza * lamammadiPetru = new Stanza();

    do {
        gd->frameStart();

        // SCHERMATA INIZIALE
        // Il menu principale
        gd->getInput();
        erase();
        
        // Calcola logica

        this->player->manageInput();

        lamammadiPetru -> stampa_stanza();

        this->player->stampa(gd->getTerminalY()/2, gd->getTerminalX()/2);
        this->player->stampaHUDplayer();

        if(gd->checkInput('q')) {
            gameOver = true;
        }

        if(gd->checkInput(KEY_RIGHT)) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_EE);
        }
        if(gd->checkInput(KEY_DOWN)) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_SS);
        }
        if(gd->checkInput(KEY_LEFT)) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_OO);
        }
        if(gd->checkInput(KEY_UP)) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_NN);
        }
        if(gd->checkInput('i')) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_NE);
        }
        if(gd->checkInput('k')) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_SE);
        }
        if(gd->checkInput('j')) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_SO);
        }
        if(gd->checkInput('u')) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_NO);
        }
        
        gd->manageTicks();

        if(pr != NULL) {
            pr->stampa(gd->getTerminalY()/2, gd->getTerminalX()/2);
            pr->updateProjectile();
        }

        gd->frameFinish();
        refresh();
    } while (! (gameOver) );
}