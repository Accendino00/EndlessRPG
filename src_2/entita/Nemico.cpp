#include "../generale/libs.hpp"

Nemico::Nemico (int type) {

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
   
    setcchar(&(this->stampabile[0][0]), L"N", A_NORMAL, PLAYER_COLOR_PAIR, NULL);
    
    this->y = 20;
    this->x = 20;

    this->ticksForAction = 250;
    this->currentAction = 0;
    this->numActions = 12;
    this->actions = new int[12];
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


    /*if(type == NORMAL_ENEMY) {
        int idNemico = ( rand() % 5 );
        switch(idNemico) {
            case 0:

            break;
            case 1:

            break;
            case 2:

            break;
            case 3:

            break;
            case 4:

            break;
        }
    } else if (type == BOSS_ENEMY) {
        int idNemico = ( rand() % 3 );
        switch(idNemico) {
            case 0:

            break;
            case 1:

            break;
            case 2:

            break;
        }
    }*/
}

Nemico::~Nemico() {
    endwin();
    std::cout << "Ciao";
    exit(1);
    delete[] this->actions;
}

void Nemico::updateEntita(Player * player, ListaEntita * proiettili /*e altri dati sulla mappa e sui nemici da controllare*/) {
    this->Entita::updateEntita();
    while (this->passedActions > 0) {
        int azione = this->actions[this->currentAction];
        // Gestione del movimento con direzione
        if( (azione & MUOVI_DIREZIONE) == MUOVI_DIREZIONE ) {
            for(int i = DIRECTION_NN; i <= DIRECTION_NO; i = i << 1) {
                if((azione & i) == i) {
                    this->muovi(i, 1);
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
                        proiettili->addEntita(new Proiettile(this->y,this->x,false,i));
                    }
                    // Parte dalla destra della direzione dove si spara 
                    if ((azione & AZIONE_SPARA_SECONDARIO) == AZIONE_SPARA_SECONDARIO) {
                        proiettili->addEntita(new Proiettile((this->y)+osY,(this->x)+osX,false,i));
                    }
                    // Parte dalla sinistra della direzione dove si spara 
                    if ((azione & AZIONE_SPARA_TERZIARIO) == AZIONE_SPARA_TERZIARIO) {
                        proiettili->addEntita(new Proiettile((this->y)-osY,(this->x)-osX,false,i));
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