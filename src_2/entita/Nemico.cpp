#include "../generale/libs.hpp"

Nemico::Nemico (int type, int posy, int posx, int tipoStanza, int numLivello) {


    // Impostazioni di base
    this->currentFrame  = 0;
    this->passedActions = 0;
    this->lastTick      = gd->getCurrentTick();
    this->tickOfLastHit = gd->getCurrentTick();
    
    this->type = type;
    this->mostraVita = false;

    this->y = posy;
    this->x = posx;

    // Impostazioni variabili in base alla difficoltà ed al livello

    double scaleFactor = 1.0;
    if (strcmp(gd->getDifficulty(), "Facile") == 0) {
        scaleFactor = 0.5;
    } else if (strcmp(gd->getDifficulty(), "Normale") == 0) {
        scaleFactor = 1.0;
    } else if (strcmp(gd->getDifficulty(), "Difficile") == 0) {
        scaleFactor = 1.5;
    } else if (strcmp(gd->getDifficulty(), "Impossibile") == 0) {
        scaleFactor = 2.0;
    }

    scaleFactor = scaleFactor + (numLivello*0.2);

    this->damage  =   5 * scaleFactor;
    this->maxVita = 100 * scaleFactor;
    this->vita    = this->maxVita;


    // Impostazioni della stampa del nemico


    this->h_dimy = 1;
    this->h_dimx = 1;
    this->s_dimy = 1;
    this->s_dimx = 1;

    this->stampabile = new cchar_t * [s_dimy];
    for(int i = 0; i < s_dimy; i++) {
        this->stampabile[i] =  new cchar_t [s_dimx];
    }

    short color = 0;
    switch(tipoStanza){
        case ID_STANZA_SPAWN:
            color = (ENEMY_BULLET_PAIR_E);
        break;
        case ID_STANZA_NORMALE:
            color = (ENEMY_BULLET_PAIR_N);
        break;
        case ID_STANZA_BOSS:
            color = (ENEMY_BULLET_PAIR_B);
        break;
    }
    setcchar(&(this->stampabile[0][0]), L"N", A_NORMAL, color, NULL);

    // Impostazioni personalizzate del nemico
    
    this->velocitaProiettile = 0.9 + (0.5 * scaleFactor);

    strcpy(this->nome, "Nemico");

    this->ticksForAction = 600;
    this->currentAction = 0;

    this->numActions = 12;
    this->actions = new int[this->numActions];
    for (int i = 0; i < this->numActions; i++) this->actions[i] = 0;
    actions[0] = MUOVI_DIREZIONE | DIRECTION_EE;
    actions[1] = AZIONE_SPARA_GIOCATORE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO;
    actions[2] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_NE;
    actions[3] = MUOVI_DIREZIONE | DIRECTION_NN;
    actions[4] = AZIONE_SPARA_GIOCATORE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO;
    actions[5] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_NO;
    actions[6] = MUOVI_DIREZIONE | DIRECTION_OO;
    actions[7] = AZIONE_SPARA_GIOCATORE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO;
    actions[8] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_SO;
    actions[9] = MUOVI_DIREZIONE | DIRECTION_SS;
    actions[10] = AZIONE_SPARA_GIOCATORE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO;
    actions[11] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_SE;



    if(type == NORMAL_ENEMY) {
        int idNemico = ( rand() % 7 );
        switch(idNemico) {
            // Trottola (2x2)
            // idea: si gira e spara in tre direzioni, muovendosi in senso orario (o antiorario) mostrando da dove sta per sparare
            case 0:

            break;
            // Cannoniere (3x3)
            // idea: mira al giocatore, mostra dove vuole sparare e poi spara usando tutti e tre i cannoni, (destro e sinistro fanno dopo il centrale)
            // così c'è un effeto tipo "formazione dei jet"
            case 1:

            break;
            // Sputafuoco (1x1)
            // idea: si muove in una direzione e spara nella direzione opposta (usando un cannone a caso), quando colpisce un muro (accessibile da falso) si gira e ripete
            case 2:

            break;
            // Bombardiere (3x3)
            // idea: carica un colpo per 2 frame e poi spara in tutte le direzioni usando tutti i cannoni (9*8 = 72 colpi)
            // dopo che ha finito di caricare il colpo, cambia il timeforaction in modo casuale
            case 3:

            break;
            // Soldato semplice (1x1)
            // idea: tra una pausa e un altra spara verso il giocatore
            case 4:

            break;
            // Verme (orizzontale) (2x1)
            // idea: si muove a pattern da sinistra a destra e spara sopra e sotto, in modo alternato
            case 5:

            break;
            // Verme (verticale) (1x2)
            // idea: si muove a pattern da sopra a sotta spara a destra e a sinistra, in modo alternato
            case 6:

            break;
        }
    } else if (type == BOSS_ENEMY) {
        // Per i boss, le chance sono 1/3 per ogni tipo di boss
        int idNemico = ( rand() % 3 );

        switch(idNemico) {
            // Super trottola (3x3) 
            // Spara tanto mentre si gira, e casualmente cambia la velocità e la direzione (quando la cambia sta fermo per un po')
            case 0:
                // 4 frame per orientazione, 2 frame per attesa idle
                /* 
                int nf = 2 + 4;
                (*this).h_dimy = 3;
                (*this).h_dimx = 3;
                (*this).s_dimy = 3;
                (*this).s_dimx = 3 * nf;  
                (*this).currentFrame = 0;

                this->maxLife=100;
                this->currentLife = this->maxLife;
                
                this->stampabile = new cchar_t * [1];
                this->stampabile[0] = new cchar_t [1];

                this->passedActions = 0;
                this->lastTick = gd->getCurrentTick();
                */


            break;
            // Super cannoniere (5x5) (ha una cornice tipo le mappe, e un cannone che fuoriesce dal centro 3x3)
            // idea: mira al giocatore per un paio di frame, poi inizia a sparare per diverse volte usando tutti i cannoni 
            // nella direzione del giocatore (cambiandola mentre il giocatore si muove)
            // Il caricamento è come se aumentasse il calore del cannone centrale (quindi diventa sempre più giallo fino ad essere chiaro quasi bianco)
            // sta fermo per più a lungo rispetto alla super trottola
            case 1:

            break;
            // Alternatore (3x3)
            // Si muove per un numero casuale di step (~10) in una direzione casuale, poi si ferma per un frame e poi 
            // inizia a sparare in tutte le direzioni usando tutti i cannoni (non insieme, ma casualemnte uno alla volta)
            // Si illumina la direzione dove ha appena sparato (forse, se ho voglia di farlo)
            case 2:

            break;
        }
    }
}

Nemico::~Nemico() {
    
    delete[] this->actions;
}

void Nemico::updateEntita(Stanza * stanza, Player * player) {
    this->Entita::updateEntita();
    while (this->passedActions > 0) {
        int azione = this->actions[this->currentAction];
        
    
        // Gestione del movimento con direzione
        if( (azione & MUOVI_DIREZIONE) == MUOVI_DIREZIONE ) {
            // Faccio un for che guarda tutte le direzioni in modo orario (vedere GameData.hpp per le define)
            for(int dir = DIRECTION_NN; dir <= DIRECTION_NO; dir = dir << 1) {
                if((azione & dir) == dir) { // Se la direzione è proprio quella richiesta allora fa dei controlli
                    muoviNemico(dir, 1, stanza, player); // Se non si muove, non c'è problema, non fa nulla
                }
            }
        }

        
        // Gestione del movimento pattern -> se non si può muovere, inverte la sua direzione
        else if( (azione & MUOVI_PATTERN) == MUOVI_PATTERN ) {
            switch(patternDirezione) {
                case DIRECTION_EE:
                    if(!muoviNemico(DIRECTION_EE, 1, stanza, player)) {
                        patternDirezione = DIRECTION_OO;
                    }
                break;
                case DIRECTION_OO:
                    if(!muoviNemico(DIRECTION_OO, 1, stanza, player)) {
                        patternDirezione = DIRECTION_EE;
                    }
                break;
                case DIRECTION_NN:
                    if(!muoviNemico(DIRECTION_NN, 1, stanza, player)) {
                        patternDirezione = DIRECTION_SS;
                    }
                break;
                case DIRECTION_SS:
                    if(!muoviNemico(DIRECTION_SS, 1, stanza, player)) {
                        patternDirezione = DIRECTION_NN;
                    }
                break;
            }
        }

        if( (azione & AZIONE_SPARA_DIREZIONE) == AZIONE_SPARA_DIREZIONE) {
            for(int dir = DIRECTION_NN; dir <= DIRECTION_NO; dir = dir << 1) {
                if((azione & dir) == dir) {
                    if ((azione & AZIONE_SPARA_PRINCIPALE) == AZIONE_SPARA_PRINCIPALE) {
                        sparaProiettile(dir,0,stanza);
                    }
                    if ((azione & AZIONE_SPARA_SECONDARIO) == AZIONE_SPARA_SECONDARIO) {
                        sparaProiettile(dir,1,stanza);
                    }
                    if ((azione & AZIONE_SPARA_TERZIARIO) == AZIONE_SPARA_TERZIARIO) {
                        sparaProiettile(dir,-1,stanza);
                    }
                }
            }
        }

        if( (azione & AZIONE_SPARA_GIOCATORE) == AZIONE_SPARA_GIOCATORE) {
            // capisce la direzione del giocatore rispetto al proiettile usando le coordinate
            int dir = DIRECTION_NN;
            if(player->getY() < this->y) {
                if(player->getX() < this->x) {
                    dir = DIRECTION_NO;
                } else if(player->getX() > this->x) {
                    dir = DIRECTION_NE; 
                } else {
                    dir = DIRECTION_NN;
                }
            } else if(player->getY() > this->y) {
                if(player->getX() < this->x) {
                    dir = DIRECTION_SO;
                } else if(player->getX() > this->x) {
                    dir = DIRECTION_SE; 
                } else {
                    dir = DIRECTION_SS;
                }
            } else {
                if(player->getX() < this->x) {
                    dir = DIRECTION_OO;
                } else if(player->getX() > this->x) {
                    dir = DIRECTION_EE; 
                }
            }

            if ((azione & AZIONE_SPARA_PRINCIPALE) == AZIONE_SPARA_PRINCIPALE) {
                sparaProiettile(dir,0,stanza);
            }
            if ((azione & AZIONE_SPARA_SECONDARIO) == AZIONE_SPARA_SECONDARIO) {
                sparaProiettile(dir,1,stanza);
            }
            if ((azione & AZIONE_SPARA_TERZIARIO) == AZIONE_SPARA_TERZIARIO) {
                sparaProiettile(dir,-1,stanza);
            }

            
        }

        this->currentAction = (this->currentAction + 1) % this->numActions;
        this->passedActions--;
    }
}

/**
 * @brief Muove il nemico nella derizione e per una quantità messi come parametro
 * Se si può muovere, e quindi si è mosso, allora ritorna vero. In caso contrario
 * ritorna falso.
 * 
 * @param direzione     Direzione in cui si vuole muovere
 * @param val           Valore di quanto si vuole muovere
 * @param stanza        Stanza in cui si trova il nemico
 * @param player        Giocatore
 * @return true         Se si è mosso
 * @return false        Se non si è mosso
 */
bool Nemico::muoviNemico( int direzione, int val, Stanza * stanza, Player * player ) {
    bool returnValue = false;
    if (!player->controllaContatto(this->getX(), this->getY(), this->getDimX(), this->getDimY())) {
        switch(movimentoValido(direzione, val, stanza, false)) {
            case STANZA_ACC_LIBERO:
                this->muovi(direzione,val);
                returnValue = true;
                break;
            case STANZA_ACC_PROIETTILE_GIOCATORE:
                this->modificaVita(-stanza->dmgDaProiettiliContactList(true));
                stanza->cancellaProiettiliSovrapposti(this, false);
                this->muovi(direzione,val);
                returnValue = true;
                break;
            case STANZA_ACC_PORTA:
            case STANZA_ACC_MURO:
            default:
                // Se ha incontrato cose bloccanti, allora ritorna falso
                returnValue = false;
                break;
        }
    }
    return returnValue;
}

void Nemico::sparaProiettile(int dir, int offset, Stanza * stanza) {
            int osX, osY;
            if( dir == DIRECTION_NN ) { osX =  offset; osY =  0;}
            if( dir == DIRECTION_SS ) { osX = -offset; osY =  0;}
            if( dir == DIRECTION_EE ) { osX =  0;      osY = -offset;}
            if( dir == DIRECTION_OO ) { osX =  0;      osY =  offset;}
            if( dir == DIRECTION_NE ) { osX =  offset; osY =  offset;}
            if( dir == DIRECTION_SE ) { osX =  offset; osY = -offset;}
            if( dir == DIRECTION_SO ) { osX = -offset; osY = -offset;}
            if( dir == DIRECTION_NO ) { osX = -offset; osY =  offset;}

            stanza->aggiungiProiettile(new Proiettile((this->y)+osY,(this->x)+osX,false,dir,this->damage,stanza->getId(), this->velocitaProiettile));
}


void Nemico::stampa(int offsetY, int offsetX) {
    Entita::stampa(offsetY, offsetX);
    if (this->type == BOSS_ENEMY) {
        stampaVita(50);
    }
}

void Nemico::stampaVita (int blocchi) {
    int vita = this->getVita();
    int maxVita = this->getMaxVita();
    int negOffsetY = 5;

    int blocchiVita = ((float)vita * blocchi) / maxVita;
    int blocchiVitaMancanti = blocchi - blocchiVita;


    mvprintw(gd->getTerminalY() - negOffsetY+2, (gd->getTerminalX()/2) - (blocchi/2), "VITA : %d / %d", vita, maxVita);


    attron(COLOR_PAIR(HEARTS_PAIR));


    // Stampa dei blocchi di vita
    for(int i = 0; i < blocchiVita; i++) {
        mvprintw(gd->getTerminalY() - negOffsetY, (gd->getTerminalX()/2) - (blocchi/2) + i, "█");
    }

    // Stampa della parte rimanente (con spazi per indicare che avrà il carattere dello sfondo, ovvero nero)
    for(int i = 0; i < blocchiVitaMancanti; i++) {
        mvprintw(gd->getTerminalY() - negOffsetY, (gd->getTerminalX()/2) - (blocchi/2) + blocchiVita + i, " ");
    }

    // Stampa dei parziali blocchi di vita ad incrementi di 1/8
    // usando i cosiddetti "ASCII block elements"
    if(         ((((float)vita) / maxVita) * blocchi) - blocchiVita < 1. 
                && ((((float)vita) / maxVita) * blocchi) - blocchiVita > 7/8. )
        mvprintw(gd->getTerminalY() - negOffsetY, gd->getTerminalX()/2 - blocchi/2 + blocchiVita, "█");
    else if(    ((((float)vita) / maxVita) * blocchi) - blocchiVita < 7/8. 
                && ((((float)vita) / maxVita) * blocchi) - blocchiVita > 6/8. )
        mvprintw(gd->getTerminalY() - negOffsetY, gd->getTerminalX()/2 - blocchi/2 + blocchiVita, "▇");
    else if(    ((((float)vita) / maxVita) * blocchi) - blocchiVita < 6/8. 
                && ((((float)vita) / maxVita) * blocchi) - blocchiVita > 5/8. )
        mvprintw(gd->getTerminalY() - negOffsetY, gd->getTerminalX()/2 - blocchi/2 + blocchiVita, "▆");
    else if(    ((((float)vita) / maxVita) * blocchi) - blocchiVita < 5/8. 
                && ((((float)vita) / maxVita) * blocchi) - blocchiVita > 4/8. )
        mvprintw(gd->getTerminalY() - negOffsetY, gd->getTerminalX()/2 - blocchi/2 + blocchiVita, "▅");
    else if(    ((((float)vita) / maxVita) * blocchi) - blocchiVita < 4/8. 
                && ((((float)vita) / maxVita) * blocchi) - blocchiVita > 3/8. )
        mvprintw(gd->getTerminalY() - negOffsetY, gd->getTerminalX()/2 - blocchi/2 + blocchiVita, "▄");
    else if(    ((((float)vita) / maxVita) * blocchi) - blocchiVita < 3/8. 
                && ((((float)vita) / maxVita) * blocchi) - blocchiVita > 2/8. )
        mvprintw(gd->getTerminalY() - negOffsetY, gd->getTerminalX()/2 - blocchi/2 + blocchiVita, "▃");
    else if(    ((((float)vita) / maxVita) * blocchi) - blocchiVita < 2/8. 
                && ((((float)vita) / maxVita) * blocchi) - blocchiVita > 1/8. )
        mvprintw(gd->getTerminalY() - negOffsetY, gd->getTerminalX()/2 - blocchi/2 + blocchiVita, "▂");
    else if(    ((((float)vita) / maxVita) * blocchi) - blocchiVita < 1/8. 
                && ((((float)vita) / maxVita) * blocchi) - blocchiVita > 0 )
        mvprintw(gd->getTerminalY() - negOffsetY, gd->getTerminalX()/2 - blocchi/2 + blocchiVita, "▁");
        

    /* 
        Stampa questa cornice per i blocchi della salute, dove BOSS viene sostituito
        con il nome nemico di cui si sta stampando la salute.

        ╔BOSS═══════╗
        ║███████▄   ║
        ╚═══════════╝
    */

    mvprintw(gd->getTerminalY() - negOffsetY - 1, gd->getTerminalX()/2 - blocchi/2 - 1, "╔");
    mvprintw(gd->getTerminalY() - negOffsetY,     gd->getTerminalX()/2 - blocchi/2 - 1, "║");
    mvprintw(gd->getTerminalY() - negOffsetY + 1, gd->getTerminalX()/2 - blocchi/2 - 1,  "╚");
    for(int i = 0; i < blocchi; i++) {
        mvprintw(gd->getTerminalY() - negOffsetY - 1, gd->getTerminalX()/2 - blocchi/2 + i, "═");
        mvprintw(gd->getTerminalY() - negOffsetY + 1, gd->getTerminalX()/2 - blocchi/2 + i, "═");    
    }
    mvprintw(gd->getTerminalY() - negOffsetY - 1, gd->getTerminalX()/2 + blocchi/2, "╗");
    mvprintw(gd->getTerminalY() - negOffsetY,     gd->getTerminalX()/2 + blocchi/2, "║");
    mvprintw(gd->getTerminalY() - negOffsetY + 1, gd->getTerminalX()/2 + blocchi/2,  "╝");
    mvprintw(gd->getTerminalY() - negOffsetY - 1, gd->getTerminalX()/2 - blocchi/2, "%s", this->nome);
    attroff(COLOR_PAIR(HEARTS_PAIR));
}

void Nemico::modificaVita(int quantita) {
    this->mostraVita = true;
    this->tickOfLastHit = gd->getCurrentTick();
    Entita::modificaVita(quantita);
}

int Nemico::getTickOfLastHit() {
    return this->tickOfLastHit;
}


int Nemico::getType() {
    return this->type;
}


bool Nemico::isMostrabile() {
    return this->mostraVita;
}