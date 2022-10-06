#include "../generale/libs.hpp"

Gioco::Gioco(){
    player = new Player(0,0, 50);
    
    this->gameOver = false;
}

Gioco::~Gioco() {
    delete this->player;
    // delete this->proiettili; e tutte le altre liste
}



void Gioco::gameLoop() {
    // Imposto i ticket a 0 quando inizia il gioco
    gd->resetTicks();

    
    /* 
    
    Stanza * stanzaProva = new Stanza(ID_STANZA_NORMALE);
    stanzaProva -> imposta_porte(true, false, false, true);
    stanzaProva -> da_logica_a_stampabile();
    stanzaProva -> stampa_stanza();

    */
    
    Livello * livello = new Livello();
    
    nemici.addEntita(new Nemico(0));

    plistaE tempProiettili, tempNemici, tempPorte, tempArtefatti;

    do {
        // Inizio del frame, aggiornamento dei tick, lettura input e erase dello schermo
        gd->frameStart();
        gd->manageTicks();
        gd->getInput();
        erase(); 
        
        /*** Gestione degli input ***/

        this->player->manageInput(&(this->proiettili));

        if(gd->checkInput('q')) {
            gameOver = true;
        }
        if(gd->checkInput('p')) {
            // Pause menu
        }

        /*** Calcolo della logica ***/

        tempProiettili = this->proiettili.getList();
        while(tempProiettili != NULL) {
            ((Proiettile*)tempProiettili->e)->updateEntita();
            tempProiettili = tempProiettili->next;
        }

        // updateAll(), una volta chiamato, chiama updateEntita per tutti gli elementi della lista

        tempNemici = this->nemici.getList();
        while(tempNemici != NULL) {
            ((Nemico*)tempNemici->e)->updateEntita(player, &(this->proiettili));
            tempNemici = tempNemici->next;
        }


        /*** Stampa ***/

        /* TEMP */
    
        livello -> stampa();
    


        // Stampa di tutto
        this->proiettili.stampaTutte(livello->offsetY(), livello->offsetX());
        this->nemici.stampaTutte(livello->offsetY(), livello->offsetX());
        this->player->stampa(livello->offsetY(), livello->offsetX());
        this->player->stampaHUDplayer();

        // Fine del frame e refresh dello schermo
        gd->frameFinish();
        refresh();
    } while (! (gameOver) );
}