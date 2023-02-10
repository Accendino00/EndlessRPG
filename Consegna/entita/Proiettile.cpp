#include "../generale/libs.hpp"

/**
 * @brief Costruttore di proiettile.
 *
 * Genera un nuovo proiettile alle coordinate x e y, con la direzione specificata.
 * Inoltre gli vengono impostate diverse caratteristiche, come la velocità e il danno.
 * 
 * Il booleano playerProjectile specifica se il proiettile è stato sparato dal giocatore,
 * e quindi determina a chi il proiettile farà danno.
 * 
 * Il tipoStanza aiuta a specifica il colore dello sfondo del proiettile.
 * Può avere i valori ID_STANZA_SPAWN, ID_STANZA_NORMALE, ID_STANZA_BOSS.
 * 
 * @param y 
 * @param x 
 * @param playerProjectile Vero se il proiettile è stato sparato dal giocatore 
 * @param direzione     Direzione del proiettile, vedere quelle definite in GameData.hpp
 * @param danno         Danno che il proiettile fa al bersaglio
 * @param tipoStanza    ID_STANZA_SPAWN, ID_STANZA_NORMALE, ID_STANZA_BOSS
 * @param velocita      (0,n] - 1 è la velocità base, 2 è il doppio, 0.5 è la metà, etc.
 */
Proiettile::Proiettile(int y, int x, bool playerProjectile, int direzione, int danno, int tipoStanza, double velocita) {
    this->lastTick = gd->getCurrentTick();
    this->x = x;
    this->y = y;
    // Impostazione dell'hitbox e della dimensione dello stampabile. 
    // Inoltre i proiettili hanno 1 solo frame di stampa
    (*this).h_dimy = 1;
    (*this).h_dimx = 1;
    (*this).s_dimy = 1;
    (*this).s_dimx = 1;
    (*this).currentFrame = 0;

    this->direzione = direzione;
    this->passedActions = 0;
    //this->muovi(this->direzione, 1);
    
    this->passedActions = 0;
    this->lastTick = gd->getCurrentTick();

    // Velocità diverse in base alla direzione nella quale viaggiano
    if(this->direzione == DIRECTION_NN || this->direzione == DIRECTION_SS) {
        this->ticksForAction = 50;  
    } else if(this->direzione == DIRECTION_EE || this->direzione == DIRECTION_OO) {
        this->ticksForAction = 40;  
    } else {
        this->ticksForAction = 60;
    }

    // La velocità fa scalare il tempo di attesa tra un movimento e l'altro
    // Velocità 2 vuol dire che va al doppio della velocità rispetto alla "base" di 1. 
    this->ticksForAction = (long long int) ((double)this->ticksForAction * (1.0/velocita));
    
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];

    this->vita = 1;
    this->maxVita = 1;

    this->damage = danno;

    this->playerProjectile = playerProjectile;
    short color = 0;
    switch(tipoStanza){
        case ID_STANZA_SPAWN:
            color = (playerProjectile) ? (PLAYER_BULLET_PAIR_E) : (ENEMY_BULLET_PAIR_E);
        break;
        case ID_STANZA_NORMALE:
            color = (playerProjectile) ? (PLAYER_BULLET_PAIR_N) : (ENEMY_BULLET_PAIR_N);
        break;
        case ID_STANZA_BOSS:
            color = (playerProjectile) ? (PLAYER_BULLET_PAIR_B) : (ENEMY_BULLET_PAIR_B);
        break;
    }
    switch(direzione) {
        case DIRECTION_NN:
            setcchar(&(this->stampabile[0][0]), L"\u21D1", A_NORMAL, color, NULL);
            break;
        case DIRECTION_SS:
            setcchar(&(this->stampabile[0][0]), L"\u21D3", A_NORMAL, color, NULL);
            break;
        case DIRECTION_EE:
            setcchar(&(this->stampabile[0][0]), L"\u21D2", A_NORMAL, color, NULL);
            break;
        case DIRECTION_OO:
            setcchar(&(this->stampabile[0][0]), L"\u21D0", A_NORMAL, color, NULL);
            break;
        case DIRECTION_NE:
            setcchar(&(this->stampabile[0][0]), L"\u21D7", A_NORMAL, color, NULL);
            break;
        case DIRECTION_SE:
            setcchar(&(this->stampabile[0][0]), L"\u21D8", A_NORMAL, color, NULL);
            break;
        case DIRECTION_SO:
            setcchar(&(this->stampabile[0][0]), L"\u21D9", A_NORMAL, color, NULL);
            break;
        case DIRECTION_NO:
            setcchar(&(this->stampabile[0][0]), L"\u21D6", A_NORMAL, color, NULL);
            break;
    }
}

/**
 * @brief Muove il proiettile nella direzione specificata.
 * Inoltre, gestisce le interazioni con gli altri oggetti.
 * 
 * Le interazioni vengono gestite solo se il proiettile ha vita superiore a 0.
 * In caso contrario, il proiettile è considerato "da cancellare".
 * 
 * Le sue interazioni sono:
 *  PER TUTTI I PROIETTILI:
 *    - Nessuna collisione (STANZA_ACC_LIBERO) -> muovi
 *    - Collisione con un muro (STANZA_ACC_MURO) -> imposta vita a 0
 *    - Collisione con una porta (STANZA_ACC_PORTA) -> imposta vita a 0
 *    - Collisione con un artefatto (STANZA_ACC_ARTEFATTO) -> muovi
 *    - Collisione con un proiettile di tipo opposto (STANZA_ACC_PROIETTILE_...) 
 *          -> imposta vita a 0, muovi e cancella anche l'altro proiettile al quale è sovrapposto
 * 
 *  PER I PROIETTILI DEL GIOCATORE:
 *    - Collisione con un nemico (STANZA_ACC_NEMICO) -> imposta vita a 0 e danneggia il nemico.
 *  
 *  PER I PROIETTILI DEL NEMICO:
 *    - Collisione con il giocatore -> imposta vita a 0 e danneggia il giocatore
 * 
 * @param gioco 
 */
void Proiettile::updateEntita(Gioco * gioco) {
    this->Entita::updateEntita();
    while (this->getVita() > 0 && this->passedActions > 0) {
        // Interazione con il giocatore
        this->muovi(this->direzione,1);
        if (!this->isPlayerProjectile()  && gioco->getPlayer()->controllaContatto(this->getX(), this->getY(), this->getDimX(), this->getDimY())) {
            // Per danneggiare il giocatore, modifico la sua vita con il negativo del danno che fa il proiettile
            gioco->getPlayer()->modificaVita(- (this->getDamage())); 
            this->setVita(0);
        } else {
            this->muovi(this->direzione,-1);
        }

        // Interazione con tutte le altre entità / la stanza
        switch(movimentoValido(this->direzione, 1, gioco->getLivello()->getStanza(), false)) {
            case STANZA_ACC_LIBERO:
                this->muovi(this->direzione,1);
                break;
            case STANZA_ACC_NEMICO:
                if (this->isPlayerProjectile()) {
                    gioco->getLivello()->getStanza()
                         ->dmgNemiciContactList(gioco, this->getDamage());
                    this->setVita(0);
                } else{
                    this->muovi(this->direzione,1);
                }
                break;
            case STANZA_ACC_ARTEFATTO:
                this->muovi(this->direzione,1);
                break;
            case STANZA_ACC_PROIETTILE_GIOCATORE:
                this->muovi(this->direzione,1);
                if (!this->isPlayerProjectile()) {
                    gioco->getLivello()->getStanza()->cancellaProiettiliSovrapposti(this, false);
                    this->setVita(0);
                }
                break;
            case STANZA_ACC_PROIETTILE_NEMICO:
                this->muovi(this->direzione,1);
                if (this->isPlayerProjectile()) {
                    gioco->getLivello()->getStanza()->cancellaProiettiliSovrapposti(this, true);
                    this->setVita(0);
                }
                break;
            case STANZA_ACC_PORTA:
            case STANZA_ACC_MURO:
                this->setVita(0);
                break;
            default:
                this->setVita(0);
                break;
        }
        this->passedActions--;
    }
}

/**
 * @brief Ritorna vero se è un proiettile del giocatore
 * 
 * @return true     E' un proiettile del giocatore
 * @return false    E' un proiettile dei nemici
 */
bool Proiettile::isPlayerProjectile(){
    return this->playerProjectile;
}