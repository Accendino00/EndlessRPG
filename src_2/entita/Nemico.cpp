#include "../generale/libs.hpp"

Nemico::Nemico (int type, int posy, int posx, int tipoStanza) {

    // Impostazione dell'hitbox e della dimensione dello stampabile. 
    // Inoltre il giocatore ha 1 solo frame di stampa
    (*this).h_dimy = 1;
    (*this).h_dimx = 1;
    (*this).s_dimy = 1;
    (*this).s_dimx = 1;
    (*this).currentFrame = 0;

    this->maxLife=100;
    this->currentLife = this->maxLife;
	
    this->stampabile = new cchar_t * [1];
    this->stampabile[0] = new cchar_t [1];

    this->passedActions = 0;
    this->lastTick = gd->getCurrentTick();
    
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
    
    this->y = posy;
    this->x = posx;

    this->ticksForAction = 600;
    this->currentAction = 0;
    this->numActions = 12;
    this->actions = new int[12];
    for (int i = 0; i < 12; i++) this->actions[i] = 0;
    actions[0] = MUOVI_DIREZIONE | DIRECTION_EE;
    actions[1] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_EE;
    actions[2] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_NE;
    actions[3] = MUOVI_DIREZIONE | DIRECTION_NN;
    actions[4] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_NN;
    actions[5] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_NO;
    actions[6] = MUOVI_DIREZIONE | DIRECTION_OO;
    actions[7] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_OO;
    actions[8] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_SO;
    actions[9] = MUOVI_DIREZIONE | DIRECTION_SS;
    actions[10] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_SS;
    actions[11] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO |  AZIONE_SPARA_TERZIARIO | DIRECTION_SE;


    this->damage = 5;

    if(type == NORMAL_ENEMY) {
        int idNemico = ( rand() % 5 );
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
            for(int i = DIRECTION_NN; i <= DIRECTION_NO; i = i << 1) {
                if((azione & i) == i) {
                            // Interazione con il giocatore
                    this->muovi(i,1);
                    if (!player->controllaContatto(this->getX(), this->getY(), this->getDimX(), this->getDimY())) {
                        this->muovi(i,-1);
                        switch(movimentoValido(i, 1, stanza, false)) {
                            case STANZA_ACC_LIBERO:
                                this->muovi(i,1);
                                break;
                            case STANZA_ACC_PROIETTILE_GIOCATORE:
                                stanza->dmgDaProiettiliContactList(true);
                                stanza->cancellaProiettiliSovrapposti(this, false);
                                this->muovi(i,1);
                                break;
                            case STANZA_ACC_PORTA:
                            case STANZA_ACC_MURO:
                                // Sta fermo
                                break;
                            default:
                                // Non si muove
                                break;
                        }
                    } else {
                        this->muovi(i,-1);
                        // Se sono a contatto con il giocatore, non mi muovo
                    }


                }
            }
        }

        

        if( (azione & AZIONE_SPARA_DIREZIONE) == AZIONE_SPARA_DIREZIONE) {
            for(int i = DIRECTION_NN; i <= DIRECTION_NO; i = i << 1) {
                if((azione & i) == i) {
                    // Offset della posizione di creazione degli spari secondari,
                    // A seconda della direzione di quello primario
                    int osX, osY;
                    if( (azione & i) == DIRECTION_NN ) { osX =  1; osY =  0;}
                    if( (azione & i) == DIRECTION_SS ) { osX = -1; osY =  0;}
                    if( (azione & i) == DIRECTION_EE ) { osX =  0; osY = -1;}
                    if( (azione & i) == DIRECTION_OO ) { osX =  0; osY =  1;}
                    if( (azione & i) == DIRECTION_NE ) { osX =  1; osY =  1;}
                    if( (azione & i) == DIRECTION_SE ) { osX =  1; osY = -1;}
                    if( (azione & i) == DIRECTION_SO ) { osX = -1; osY = -1;}
                    if( (azione & i) == DIRECTION_NO ) { osX = -1; osY =  1;}
                    // Parte dal centro del nemico
                    if ((azione & AZIONE_SPARA_PRINCIPALE) == AZIONE_SPARA_PRINCIPALE) {
                        stanza->aggiungiProiettile(new Proiettile(this->y,this->x,false,i,this->damage,stanza->getId()));
                    }
                    // Parte dalla destra della direzione dove si spara 
                    if ((azione & AZIONE_SPARA_SECONDARIO) == AZIONE_SPARA_SECONDARIO) {
                        stanza->aggiungiProiettile(new Proiettile((this->y)+osY,(this->x)+osX,false,i,this->damage,stanza->getId()));
                    }
                    // Parte dalla sinistra della direzione dove si spara 
                    if ((azione & AZIONE_SPARA_TERZIARIO) == AZIONE_SPARA_TERZIARIO) {
                        stanza->aggiungiProiettile(new Proiettile((this->y)-osY,(this->x)-osX,false,i,this->damage,stanza->getId()));
                    }
                }
            }
        }

        // Gestione del movimento pattern 
        /*else if( (azione & MUOVI_PATTERN) == MUOVI_PATTERN ) {
            switch(patternDirezione) {
                case DIRECTION_EE:
                    // if can't move, change direction
                    this->incrementaX(1);
                break;
                case DIRECTION_OO:
                    this->incrementaX(-1);
                break;
                case DIRECTION_NN:
                    this->incrementaY(-1);
                break;
                case DIRECTION_SS:
                    this->incrementaY(1);
                break;
            }
        }*/
        this->currentAction = (this->currentAction + 1) % this->numActions;
        this->passedActions--;
    }
}