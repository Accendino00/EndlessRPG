#include "../generale/libs.hpp"

Gioco::Gioco(){
    this->player = new Player(0,0, 50);
}

void Gioco::gameLoop() {
    bool gameOver = false;
    Proiettile * pr;
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

        //if(gd->checkInput('z')) {
        //    pr = new Proiettile(gd->getTerminalY()/2, gd->getTerminalX()/2,true,DIRECTION_RIGHT);
        //}
//
        //if(pr != NULL) {
        //    pr->updateProjectile();
        //}

        gd->frameFinish();
        refresh();
    } while (! (gameOver) );
}