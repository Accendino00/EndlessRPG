#include "../generale/libs.hpp"

Gioco::Gioco(){
    player = new Player((int)DIM_STANZA_SPAWN_Y/2,(int)DIM_STANZA_SPAWN_X/2, 50);
    this->gameOver = false;
}

Gioco::~Gioco() {
    delete this->player;
    delete livello;
}



void Gioco::gameLoop() {
    // Imposto i ticket a 0 quando inizia il gioco
    gd->resetTicks();
    
    livello = new Livello();
    
    // nemici.addEntita(new Nemico(0));

    // plistaE tempProiettili, tempNemici, tempPorte, tempArtefatti;

    do {
        // Inizio del frame, aggiornamento dei tick, lettura input e erase dello schermo
        gd->frameStart();
        gd->manageTicks();
        gd->getInput();
        erase(); 
        
        /*** Gestione degli input ***/

        this->player->manageInput(livello);

        if(gd->checkInput('q')) {
            gameOver = true;
        }
        if(gd->checkInput('p')) {
            // Pause menu
        }

        /*** Calcolo della logica ***/

        // tempProiettili = this->proiettili.getList();
        // while(tempProiettili != NULL) {
        //     ((Proiettile*)tempProiettili->e)->updateEntita();
        //     tempProiettili = tempProiettili->next;
        // }

        livello -> calcolo_logica(this->player);

        // updateAll(), una volta chiamato, chiama updateEntita per tutti gli elementi della lista

        // tempNemici = this->nemici.getList();
        // while(tempNemici != NULL) {
        //     ((Nemico*)tempNemici->e)->updateEntita(player, &(this->proiettili));
        //     tempNemici = tempNemici->next;
        // }


        /*** Stampa ***/

        /* TEMP */
    
        livello -> stampa(this->player);
    


        // Stampa di tutto
        // this->proiettili.stampaTutte(livello->offsetY(), livello->offsetX());
        // this->nemici.stampaTutte(livello->offsetY(), livello->offsetX());
        this->player->stampa(livello->offsetY(), livello->offsetX());
        this->player->stampaHUDplayer();

        // Fine del frame e refresh dello schermo
        gd->frameFinish();
        refresh();
    } while (! (gameOver) );
}