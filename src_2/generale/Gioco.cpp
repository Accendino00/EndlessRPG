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



    prima faccio l'update degli input del giocatore
        muovo il giocatore fino a quando accessibile mi dice che si puo
            se intercetto qualcosa di diverso da proiettile e artefatto mi blocco
            se intercetto artefatto o proiettile, li distruggo e in base a
                quanti proiettili distruggo, prendo danno
                    quando distruggo la listacontatti (true) c'e' anche l'entita in modo da poterla danneggiare
                quali artefatti distruggo, guadagno cose
                    prima di distruggere un artefatto, in base al suo id e a dei suoi dati, modifico il player
                    come argomento di deletelistaC (true) c'e' anche il player in modo da poterlo potenziare o curare o altro
        genero i proiettili sparando, mettendoli di 1 nella direzione dove sto sparando, i quali verranno aggiornati nella parte successiva

    capisco se il giocatore si deve muovere per andare ad un'altra stanza.

    poi faccio l'update dei proiettili
        muovo il proiettili fino a quando accessibile mi dice che si puo (prima controllo, poi muovo)
        quando accessibile, oppure il controllo del contatto con il giocatore se proiettile dei nemici, mi danno falso, allora vuol dire che sono a contatto con:
            stanza (quindi un muro)
            porta (come se fosse un muro)
            proiettile (come se fosse un muro)
            giocatore (da controllare che tipo di proiettile osno)
            nemico (da controllare che tipo di proiettile sono)
            artefatto (quindi come se fosse vuoto)
        quando incontrolo qualsiasi cosa che non sia un artefatto, il ciclo si ferma e il numero di azioni da fare diventa 0 per il proiettile

    aggiorno la salute del giocatore in caso di contatti con proiettili e li cancello
        se vita inferiore a 0, allora
            schermata gameover, dove si puo' premere un tasto per tornare al menu oppure per salvare lo score
                se si salva lo score, allora si arriva ad un'altra schermata dove si possono scegliere caratteri e viene salvato su file
            si interrompe il ciclo di gameloop e si esce dal gioco
    aggiorno la salute dei nemici in caso di contatto con proiettili e li cancello
    aggiorno la lista nemici, facendo un delete di tutti i nemici che hanno vita inferiore o uguale a 0
        in caso di nemici particolari, genero artefatti (se nemico ha chiave OPPURE se nemico ha casualmente beccato il generare un artefatto)

    poi faccio l'update dei nemici
        poi uso le azioni del nemico e, ogni volta che faccio un movimento, faccio un controllo con accessibile
            se stanza
            oppure porta
            oppure giocatore
            oppure nemico
            allora mi fermo nell'azione di movimento e non la faccio e vado avanti con le azioni

            se invece proiettile, allora continuo con i movimenti ma dannaeggio il nemico
                se vita inferiore a 0, allora smetto di aggiornare il nemico e le sue azioni da fare diventano 0
        poi sparo i proiettili e faccio le sue altre cose, come le animazioni

    aggiorno la salute del giocatore in caso di contatto con proiettili e li cancello
        se vita inferiore a 0, allora
            schermata gameover, dove si puo' premere un tasto per tornare al menu oppure per salvare lo score
                se si salva lo score, allora si arriva ad un'altra schermata dove si possono scegliere caratteri e viene salvato su file
            si interrompe il ciclo di gameloop e si esce dal gioco
    aggiorno la lista nemici, facendo un delete di tutti i nemici che hanno vita inferiore o uguale a 0
        in caso di nemici particolari, genero artefatti (se nemico ha chiave OPPURE se nemico ha casualmente beccato il generare un artefatto)

    poi, infine, faccio il calcolo della logica del livello per capire se devo mantenere le porte, quale porte mantenenre e quale cancellare
*/
#include "../generale/libs.hpp"

Gioco::Gioco(){
    // Viene generato il giocatore al centro della stanza iniziale, con 50 punti vita
    player = new Player((int)DIM_STANZA_SPAWN_Y/2,(int)DIM_STANZA_SPAWN_X/2, 50);
    this->gameOver = false;
}

Gioco::~Gioco() {
    delete this->player;
    delete livello_corrente;
}

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

void Gioco::cambialivello(){
    if(livello_corrente->getStanza()->getNumNemici()==0){
        mvprintw(gd->getTerminalY()/2, (gd->getTerminalX()/2) - 13, "🎉 Hai sconfitto il Boss! 🎉");
        mvprintw( 6, 10, "╔══════════════════════════════════╗");
        mvprintw( 7, 10, "║ Premere 'l' per cambiare livello ║");
        mvprintw( 8, 10, "╚══════════════════════════════════╝");
        if(gd->checkInput('l')){
            delete livello_corrente;
            livello_corrente = new Livello(livello_counter++);
            player->modificaCoordinate((int)DIM_STANZA_SPAWN_Y/2,(int)DIM_STANZA_SPAWN_X/2);
            player->setFrame(FRAME_OF_E);
            player->setChiave(false);
        }
    }    
}

void Gioco::gameLoop() {
    // Imposto i ticket a 0 quando inizia il gioco
    gd->resetTicks();
    
    this->livello_counter = 1;
    livello_corrente = new Livello();

    do {
        // Inizio del frame, aggiornamento dei tick, lettura input e erase dello schermo
        gd->frameStart();
        gd->manageTicks();
        gd->getInput();
        erase(); 
        
        /*** Gestione degli input ***/

        this->player->manageInput(livello_corrente);

        if(gd->checkInput('q')) {
            gameOver = true;
        }
        if(gd->checkInput('p')) {
            // Pause menu
        }

        /*** Calcolo della logica ***/

        livello_corrente -> calcolo_logica(this);
        
        /*** Stampa ***/

        livello_corrente -> stampa();
    
        this->player->stampa(livello_corrente->offsetY(), livello_corrente->offsetX());
        this->player->stampaHUDplayer();
        
        if(livello_corrente->isBossstanza()){
            cambialivello();
        }
        // Fine del frame e refresh dello schermo
        gd->frameFinish();
        refresh();
    } while (! (gameOver) );

    // Quando il gioco finisce, c'è la schermata di game over e di salvataggio del punteggio
}

void Gioco::spawnArtefatto(int y, int x) {
    // #TODO aggiungere le chance di spawnare artefatti;
    this->livello_corrente->getStanza()->aggiungiArtefatto(new Artefatto(y,x,(rand() % TIPOART_MAX) + 1, this->livello_corrente->getStanza()->getId()));
}