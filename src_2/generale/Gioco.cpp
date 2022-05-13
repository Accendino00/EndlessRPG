#include "../generale/libs.hpp"

Gioco::Gioco(){
    this->player = new Player(0,0, 50);
}

void Gioco::gameLoop() {
    bool gameOver = false;
    Proiettile * pr = NULL;
    do {
        gd->frameStart();

        // SCHERMATA INIZIALE
        // Il menu principale
        gd->getInput();
        erase();
        
        // Calcola logica

        this->player->manageInput();



        this->player->stampa(gd->getTerminalY()/2, gd->getTerminalX()/2);
        this->player->stampaHUDplayer();

        if(gd->checkInput('q')) {
            gameOver = true;
        }

        if(gd->checkInput(KEY_RIGHT)) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_RIGHT);
        }
        if(gd->checkInput(KEY_DOWN)) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_DOWN);
        }
        if(gd->checkInput(KEY_LEFT)) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_LEFT);
        }
        if(gd->checkInput(KEY_UP)) {
            pr = new Proiettile(this->player->y, this->player->x,true,DIRECTION_UP);
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