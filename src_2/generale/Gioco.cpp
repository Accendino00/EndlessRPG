#include "../generale/libs.hpp"

Gioco::Gioco(){
    // Viene generato il giocatore al centro della stanza iniziale, con 50 punti vita
    player = new Player((int)DIM_STANZA_SPAWN_Y/2,(int)DIM_STANZA_SPAWN_X/2, 50);
    this->gameOver = false;
}

Gioco::~Gioco() {
    delete this->player;
    delete livello;
}

/*
    Ordine di calcolo della logica:

        input del player
            movimento (eventuali contatti con nemici / eventuale contatto con porta / eventuale contatto con artefatti )
            eventuali contatti con proiettili
            
        logica mappa
            se il player supera i limiti e deve cambiare stanza

        logica nemici
            movimento (eventuali contatti con muri / porte / nemici)
            contatti con proiettili
            m o r t e (eventuale spawn di artefatti / chiavi)

        logica proiettili
            movimento
            contatto
            distruzione

        logica porte (di tutte le stanze, in modo da poter aprirla se si prende una chiave)
            apertura

        -- nota sulle porte:
            Ogni stanza ha una lista di porte normali
            inoltre, nella lista ci sono anche le porte con chiave
            quando si entra in una qualsiasi stanza, vengono generate le porte della stanza in base alle stanze attorno 
                (se di fianco ce una stanza del boss, la porta ha una chiave se la chiave ancora non e' stata collezionata)
            tutte le porte normali vengono cancellate quando si cleara la stanza
            quando si colleziona la chiave, se si colleziona nella stanza dove c'e' la porta con chiave, essa viene distrutta
            senno, essa non verra' generata quando si entra in stanza
            collezionata

    nota:
        proiettili e artefatti sono non bloccanti
        nemici, porte e player sono bloccanti


*/


void Gioco::gameLoop() {
    // Imposto i ticket a 0 quando inizia il gioco
    gd->resetTicks();
    
    livello = new Livello();

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

        livello -> calcolo_logica(this->player);

        /*** Stampa ***/
    
        livello -> stampa(this->player);
    
        this->player->stampa(livello->offsetY(), livello->offsetX());
        this->player->stampaHUDplayer();


        // Fine del frame e refresh dello schermo
        gd->frameFinish();
        refresh();
    } while (! (gameOver) );
}