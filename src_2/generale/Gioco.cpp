#include "../generale/libs.hpp"

Gioco::Gioco(){
    this->player = new Player(0,0);
}

void Gioco::gameLoop() {
    bool gameOver = false;
    do {
        gd->frameStart();

        // SCHERMATA INIZIALE
        // Il menu principale
        gd->getInput();
        erase();

        this->player->manageInput();

        if(gd->checkInput('q')) {
            gameOver = true;
        }

        this->player->stampa(gd->getTerminalY()/2, gd->getTerminalX()/2);

        gd->frameFinish();
        refresh();
    } while (! (gameOver) );
}