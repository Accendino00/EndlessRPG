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

    // Impostazioni scale factor in base al livello e alla difficoltà
    double scaleFactor = 1.0;
    if (strcmp(gd->getDifficulty(), "Facile") == 0) {
        scaleFactor = 0.75;
    } else if (strcmp(gd->getDifficulty(), "Normale") == 0) {
        scaleFactor = 1.0;
    } else if (strcmp(gd->getDifficulty(), "Difficile") == 0) {
        scaleFactor = 1.5;
    } else if (strcmp(gd->getDifficulty(), "Impossibile") == 0) {
        scaleFactor = 2.0;
    }

    // Il livello aumenta lo scale factor in modo lineare
    scaleFactor = scaleFactor + (numLivello*0.2);


    short color = 0;
    int numOfPatters = 0;

    if(type == NORMAL_ENEMY) {
        int idNemico = ( rand() % 6 );

        // Devo avere un'alta chance di avere nemici di tipo 3, meta per 4 e 5 (si smezzano una chance) e bassa per 0, 1 e 2

        switch(idNemico) {
////////////// Trottola (2x2)
            // idea: si gira e spara in tre direzioni, muovendosi in senso orario (o antiorario) mostrando da dove sta per sparare
            case 0:
                // Statistiche del nemico delineate dallo scale factor calcolato in precedenza
    
                this->damage  =   10 * scaleFactor;
                this->maxVita = 175 * scaleFactor;
                this->vita    = this->maxVita;
                this->punti   = 200;


                // Impostazioni della stampa del nemico

                this->h_dimy = 2;
                this->h_dimx = 2;
                this->s_dimy = 2;
                this->s_dimx = 10;

                this->stampabile = new cchar_t * [s_dimy];
                for(int i = 0; i < s_dimy; i++) {
                    this->stampabile[i] =  new cchar_t [s_dimx];
                }

                color = 0;
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

                for(int j = 0; j < s_dimx/h_dimx; j++) {
                    setcchar(&(this->stampabile[0][(j*2)]),   L"╔", A_NORMAL, color, NULL);
                    setcchar(&(this->stampabile[1][(j*2)]),   L"╚", A_NORMAL, color, NULL);
                    setcchar(&(this->stampabile[0][(j*2)+1]), L"╗", A_NORMAL, color, NULL);
                    setcchar(&(this->stampabile[1][(j*2)+1]), L"╝", A_NORMAL, color, NULL);
                }
                
                setcchar(&(this->stampabile[0][0]), L"▛", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[1][2]), L"▙", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[1][5]), L"▟", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[0][7]), L"▜", A_REVERSE, color, NULL);


                // Impostazioni personalizzate del nemico

                this->velocitaProiettile = 0.45 + (0.2 * scaleFactor);

                strcpy(this->nome, "Prillo");

                this->ticksForAction = 300;
                this->currentAction = 0;
                this->currentFrame = 4;

                this->numActions = 14;
                this->actions = new int[this->numActions];
                for (int i = 0; i < this->numActions; i++) this->actions[i] = 0; // Prima le setto tutte a 0
                actions[0] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_TERZIARIO | DIRECTION_NN;
                actions[1] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | DIRECTION_NO;
                actions[2] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_TERZIARIO | DIRECTION_OO;
                actions[3] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | DIRECTION_OO;
                actions[4] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_SECONDARIO | DIRECTION_SO;
                actions[5] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_SECONDARIO | DIRECTION_SS;
                actions[6] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | DIRECTION_SS;
                actions[7] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | DIRECTION_SE;
                actions[8] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | DIRECTION_EE;
                actions[9] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_SECONDARIO | DIRECTION_EE;
                actions[10] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | DIRECTION_NE;
                actions[11] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | DIRECTION_NN;
                actions[12] = FRAME_PROSSIMO | AZIONE_PAUSA;
                actions[13] = AZIONE_PAUSA;
            break;
////////////// Sputafuoco (1x1)
            // idea: si muove in una direzione e spara nella stessa dierzione (+/- 45 gradi), quando colpisce un muro (accessibile da falso) si gira e ripete
            case 1:
                // Statistiche del nemico delineate dallo scale factor calcolato in precedenza
    
                this->damage  =   5 * scaleFactor;
                this->maxVita = 50 * scaleFactor;
                this->vita    = this->maxVita;
                this->punti   = 150;


                // Impostazioni della stampa del nemico

                this->h_dimy = 1;
                this->h_dimx = 1;
                this->s_dimy = 1;
                this->s_dimx = 1;

                this->stampabile = new cchar_t * [s_dimy];
                for(int i = 0; i < s_dimy; i++) {
                    this->stampabile[i] =  new cchar_t [s_dimx];
                }

                color = 0;
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

                setcchar(&(this->stampabile[0][0]), L"╬", A_REVERSE, color, NULL);


                // Impostazioni personalizzate del nemico
                switch(rand() % 4) {
                    case 0:
                        this->patternDirezione = DIRECTION_NN;
                    break;
                    case 1:
                        this->patternDirezione = DIRECTION_SS;
                    break;
                    case 2:
                        this->patternDirezione = DIRECTION_EE;
                    break;
                    case 3:
                        this->patternDirezione = DIRECTION_OO;
                    break;
                }

                this->velocitaProiettile = 0.6 + (0.2 * scaleFactor);

                strcpy(this->nome, "Sputafuoco");

                this->ticksForAction = 100;
                this->currentAction = 0;
                this->currentFrame = 0;

                this->numActions = 3;
                this->actions = new int[this->numActions];
                for (int i = 0; i < this->numActions; i++) this->actions[i] = 0; // Prima le setto tutte a 0
                actions[0] = AZIONE_SPARA_SPUTAFUOCO;
                actions[1] = MUOVI_PATTERN | AZIONE_SPARA_SPUTAFUOCO;
                actions[2] = AZIONE_SPARA_SPUTAFUOCO;
            break;
////////////// Bombardiere (3x3)
            // idea: carica un colpo per 2 frame e poi spara in tutte le direzioni usando tutti i cannoni (9*8 = 72 colpi)
            case 2:
                // Statistiche del nemico delineate dallo scale factor calcolato in precedenza
    
                this->damage  =  10 * scaleFactor;
                this->maxVita = 250 * scaleFactor;
                this->vita    = this->maxVita;
                this->punti   = 300;


                // Impostazioni della stampa del nemico

                this->h_dimy = 3;
                this->h_dimx = 3;
                this->s_dimy = 3;
                this->s_dimx = 9;

                this->stampabile = new cchar_t * [s_dimy];
                for(int i = 0; i < s_dimy; i++) {
                    this->stampabile[i] =  new cchar_t [s_dimx];
                }

                color = 0;
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



                // Primo frame
                for(int i = 0; i < h_dimy; i++) {
                    for(int j = 0; j < h_dimx; j++) {
                        setcchar(&(this->stampabile[i][j]), L"░", A_NORMAL, color, NULL);
                    }
                }
                
                // Secondo frame
                for(int i = 0; i < h_dimy; i++) {
                    for(int j = 0; j < h_dimx; j++) {
                        setcchar(&(this->stampabile[i][j+3]), L"▒", A_NORMAL, color, NULL);
                    }
                }
                

                // Terzo frame
                for(int i = 0; i < h_dimy; i++) {
                    for(int j = 0; j < h_dimx; j++) {
                        setcchar(&(this->stampabile[i][j+6]), L"█", A_NORMAL, color, NULL);
                    }
                }

                for (int j = 0; j < this->s_dimx/this->h_dimx; j++) {
                    setcchar(&(this->stampabile[0][(j*this->h_dimx)+0]), L"╔", A_REVERSE, color, NULL);
                    setcchar(&(this->stampabile[2][(j*this->h_dimx)+0]), L"╚", A_REVERSE, color, NULL);
                    setcchar(&(this->stampabile[0][(j*this->h_dimx)+2]), L"╗", A_REVERSE, color, NULL);
                    setcchar(&(this->stampabile[2][(j*this->h_dimx)+2]), L"╝", A_REVERSE, color, NULL);
                }

                // Impostazioni personalizzate del nemico

                this->velocitaProiettile = 0.3 + (0.2 * scaleFactor);

                strcpy(this->nome, "Bombardiere");

                this->ticksForAction = 750;
                this->currentAction = 0;
                this->currentFrame = 0;

                this->numActions = 4;
                this->actions = new int[this->numActions];
                for (int i = 0; i < this->numActions; i++) this->actions[i] = 0; // Prima le setto tutte a 0
                actions[0] = AZIONE_PAUSA;
                actions[1] = FRAME_PROSSIMO | AZIONE_PAUSA;
                actions[2] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO
                            | 0b11111111; // Per indicare tutte le direzioni, piuttosto che fare l'OR bitwise di tutte
                actions[3] = FRAME_PROSSIMO | AZIONE_PAUSA;
            break;
////////////// Soldato semplice (1x1)
            // idea: tra una pausa e un altra spara verso il giocatore
            case 3:
                // Statistiche del nemico delineate dallo scale factor calcolato in precedenza
    
                this->damage  =  15 * scaleFactor;
                this->maxVita = 150 * scaleFactor;
                this->vita    = this->maxVita;
                this->punti   = 100;


                // Impostazioni della stampa del nemico

                this->h_dimy = 1;
                this->h_dimx = 1;
                this->s_dimy = 1;
                this->s_dimx = 1;

                this->stampabile = new cchar_t * [s_dimy];
                for(int i = 0; i < s_dimy; i++) {
                    this->stampabile[i] =  new cchar_t [s_dimx];
                }

                color = 0;
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
                setcchar(&(this->stampabile[0][0]), L"╳", A_REVERSE, color, NULL);


                // Impostazioni personalizzate del nemico

                this->velocitaProiettile = 0.9 + (0.35 * scaleFactor);

                strcpy(this->nome, "Soldato");

                this->ticksForAction = 750;
                this->currentAction = 0;
                this->currentFrame = 0;

                this->numActions = 2;
                this->actions = new int[this->numActions];
                for (int i = 0; i < this->numActions; i++) this->actions[i] = 0; // Prima le setto tutte a 0
                actions[0] = AZIONE_PAUSA;
                actions[1] = AZIONE_SPARA_GIOCATORE | AZIONE_SPARA_PRINCIPALE;
            break;
////////////// Bruco (orizzontale) (2x1)
            // idea: si muove a pattern da sinistra a destra e spara sopra e sotto, in modo alternato
            case 4:
                // Statistiche del nemico delineate dallo scale factor calcolato in precedenza
    
                this->damage  =  10 * scaleFactor;
                this->maxVita = 100 * scaleFactor;
                this->vita    = this->maxVita;
                this->punti   = 100;


                // Impostazioni della stampa del nemico

                this->h_dimy = 1;
                this->h_dimx = 2;
                this->s_dimy = 1;
                this->s_dimx = 2;

                this->stampabile = new cchar_t * [s_dimy];
                for(int i = 0; i < s_dimy; i++) {
                    this->stampabile[i] =  new cchar_t [s_dimx];
                }

                color = 0;
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
                setcchar(&(this->stampabile[0][0]), L"▚", A_NORMAL, color, NULL);
                setcchar(&(this->stampabile[0][1]), L"▚", A_NORMAL, color, NULL);


                // Impostazioni personalizzate del nemico
                
                // Inizia ad andare casualmente a destra o a sinistra
                this->patternDirezione = (rand() % 2 == 0) ? (DIRECTION_EE) : (DIRECTION_OO);

                this->velocitaProiettile = 0.9 + (0.35 * scaleFactor);

                strcpy(this->nome, "Bruco");

                this->ticksForAction = 400;
                this->currentAction = 0;
                this->currentFrame = 0;

                this->numActions = 4;
                this->actions = new int[this->numActions];
                for (int i = 0; i < this->numActions; i++) this->actions[i] = 0; // Prima le setto tutte a 0
                actions[0] = MUOVI_PATTERN;
                actions[1] = MUOVI_PATTERN | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_TERZIARIO | DIRECTION_NN;
                actions[2] = MUOVI_PATTERN;
                actions[3] = MUOVI_PATTERN | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | DIRECTION_SS;
            break;
////////////// Bruco (verticale) (1x2)
            // idea: si muove a pattern da sopra a sotta spara a destra e a sinistra, in modo alternato
            case 5:
                // Statistiche del nemico delineate dallo scale factor calcolato in precedenza
    
                this->damage  =  10 * scaleFactor;
                this->maxVita = 100 * scaleFactor;
                this->vita    = this->maxVita;
                this->punti   = 100;


                // Impostazioni della stampa del nemico

                this->h_dimy = 2;
                this->h_dimx = 1;
                this->s_dimy = 2;
                this->s_dimx = 1;

                this->stampabile = new cchar_t * [s_dimy];
                for(int i = 0; i < s_dimy; i++) {
                    this->stampabile[i] =  new cchar_t [s_dimx];
                }

                color = 0;
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
                setcchar(&(this->stampabile[0][0]), L"▞", A_NORMAL, color, NULL);
                setcchar(&(this->stampabile[1][0]), L"▞", A_NORMAL, color, NULL);


                // Impostazioni personalizzate del nemico
                
                // Inizia ad andare casualmente a destra o a sinistra
                this->patternDirezione = (rand() % 2 == 0) ? (DIRECTION_NN) : (DIRECTION_SS);

                this->velocitaProiettile = 0.9 + (0.35 * scaleFactor);

                strcpy(this->nome, "Bruco");

                this->ticksForAction = 400;
                this->currentAction = 0;
                this->currentFrame = 0;

                this->numActions = 4;
                this->actions = new int[this->numActions];
                for (int i = 0; i < this->numActions; i++) this->actions[i] = 0; // Prima le setto tutte a 0
                actions[0] = MUOVI_PATTERN;
                actions[1] = MUOVI_PATTERN | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | DIRECTION_EE;
                actions[2] = MUOVI_PATTERN;
                actions[3] = MUOVI_PATTERN | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_TERZIARIO | DIRECTION_OO;
            break;
        }
    } else if (type == BOSS_ENEMY) {
        // Per i boss, le chance sono 1/3 per ogni tipo di boss
        int idNemico = ( rand() % 2 );

        switch(idNemico) {
////////////// Super trottola (3x3) 
            // Spara tanto mentre si gira, e casualmente cambia la velocità e la direzione (quando la cambia sta fermo per un po')
            case 0:
                // Statistiche del nemico delineate dallo scale factor calcolato in precedenza
    
                this->damage  =   10 * scaleFactor;
                this->maxVita = 1000 * scaleFactor;
                this->vita    = this->maxVita;
                this->punti   = 5000;


                // Impostazioni della stampa del nemico

                this->h_dimy = 3;
                this->h_dimx = 3;
                this->s_dimy = 3;
                this->s_dimx = 27;

                this->stampabile = new cchar_t * [s_dimy];
                for(int i = 0; i < s_dimy; i++) {
                    this->stampabile[i] =  new cchar_t [s_dimx];
                }

                color = 0;
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

                for(int j = 0; j < s_dimx/h_dimx; j++) {
                    setcchar(&(this->stampabile[0][(j*3)]),   L"╔", A_NORMAL, color, NULL);
                    setcchar(&(this->stampabile[2][(j*3)]),   L"╚", A_NORMAL, color, NULL);
                    setcchar(&(this->stampabile[0][(j*3)+2]), L"╗", A_NORMAL, color, NULL);
                    setcchar(&(this->stampabile[2][(j*3)+2]), L"╝", A_NORMAL, color, NULL);

                    setcchar(&(this->stampabile[1][(j*3)]),   L"╟", A_NORMAL, color, NULL);
                    setcchar(&(this->stampabile[1][(j*3)+2]),   L"╢", A_NORMAL, color, NULL);
                    setcchar(&(this->stampabile[0][(j*3)+1]),     L"╤", A_NORMAL, color, NULL);
                    setcchar(&(this->stampabile[2][(j*3)+1]),   L"╧", A_NORMAL, color, NULL);
                    
                    setcchar(&(this->stampabile[1][(j*3)+1]),   L"┼", A_NORMAL, color, NULL);
                }
                
                setcchar(&(this->stampabile[0][1]),  L"▀", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[0][3]),  L"▛", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[1][6]),  L"▌", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[2][9]),  L"▙", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[2][13]), L"▄", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[2][17]), L"▟", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[1][20]), L"▐", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[0][23]), L"▜", A_REVERSE, color, NULL);


                // Impostazioni personalizzate del nemico

                this->velocitaProiettile = 1 + (0.2 * scaleFactor);

                strcpy(this->nome, "Super Prillo");

                this->ticksForAction = 60;
                this->currentAction = 0;
                this->currentFrame = 8;

                this->numActions = 14;
                this->actions = new int[this->numActions];
                for (int i = 0; i < this->numActions; i++) this->actions[i] = 0; // Prima le setto tutte a 0
                actions[0 ] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_NN;
                actions[1 ] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_NO;
                actions[2 ] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_OO;
                actions[3 ] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_SO;
                actions[4 ] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_SS;
                actions[5 ] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_SE;
                actions[6 ] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_EE;
                actions[7 ] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_NE;
                actions[8 ] = FRAME_PROSSIMO | AZIONE_PAUSA;
                actions[9 ] = AZIONE_PAUSA;
                actions[10] = AZIONE_PAUSA;
                actions[11] = AZIONE_PAUSA;
                actions[12] = AZIONE_PAUSA;
                actions[13] = AZIONE_PAUSA;

                numOfPatters = 10;
                this->numActions = 24*numOfPatters;
                this->actions = new int[this->numActions];
                for (int i = 0; i < this->numActions; i++) this->actions[i] = 0; // Prima le setto tutte a 0
                for(int i = 0; i < numOfPatters; i++) {
                    int dir = 1 << (rand() % 8); 
                    for (int j = 0; j < 10; j++) {
                        actions[ j+(i*24)] = MUOVI_DIREZIONE | dir;
                    }
                    actions[10+(i*24)] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_NN;
                    actions[11+(i*24)] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_NO;
                    actions[12+(i*24)] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_OO;
                    actions[13+(i*24)] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_SO;
                    actions[14+(i*24)] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_SS;
                    actions[15+(i*24)] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_SE;
                    actions[16+(i*24)] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_EE;
                    actions[17+(i*24)] = FRAME_PROSSIMO | AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | DIRECTION_NE;
                    actions[18+(i*24)] = FRAME_PROSSIMO | AZIONE_PAUSA;
                    actions[19+(i*24)] = AZIONE_PAUSA;
                    actions[20+(i*24)] = AZIONE_PAUSA;
                    actions[21+(i*24)] = AZIONE_PAUSA;
                    actions[22+(i*24)] = AZIONE_PAUSA;
                    actions[23+(i*24)] = AZIONE_PAUSA;
                }
            break;
////////////// Alternatore (3x3)
            // Si muove per un numero casuale di step (~10) in una direzione casuale, poi si ferma per un frame e poi 
            // inizia a sparare in tutte le direzioni usando tutti i cannoni (non insieme, ma casualemnte uno alla volta)
            // Si illumina la direzione dove ha appena sparato (forse, se ho voglia di farlo)
            case 1:
                // Statistiche del nemico delineate dallo scale factor calcolato in precedenza
    
                this->damage  =   10 * scaleFactor;
                this->maxVita = 1000 * scaleFactor;
                this->vita    = this->maxVita;
                this->punti   = 5000;


                // Impostazioni della stampa del nemico

                this->h_dimy = 3;
                this->h_dimx = 3;
                this->s_dimy = 3;
                this->s_dimx = 6;

                this->stampabile = new cchar_t * [s_dimy];
                for(int i = 0; i < s_dimy; i++) {
                    this->stampabile[i] =  new cchar_t [s_dimx];
                }

                color = 0;
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

                setcchar(&(this->stampabile[0][0]), L"╔", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[2][0]), L"╚", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[0][2]), L"╗", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[2][2]), L"╝", A_REVERSE, color, NULL);

                setcchar(&(this->stampabile[1][0]), L"╟", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[1][2]), L"╢", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[0][1]), L"╤", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[2][1]), L"╧", A_REVERSE, color, NULL);
                    
                setcchar(&(this->stampabile[1][1]), L"┼", A_REVERSE, color, NULL);


                setcchar(&(this->stampabile[0][3]), L"╳", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[2][3]), L"╳", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[0][5]), L"╳", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[2][5]), L"╳", A_REVERSE, color, NULL);

                setcchar(&(this->stampabile[1][3]), L"╳", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[1][5]), L"╳", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[0][4]), L"╳", A_REVERSE, color, NULL);
                setcchar(&(this->stampabile[2][4]), L"╳", A_REVERSE, color, NULL);
                    
                setcchar(&(this->stampabile[1][4]), L"╳", A_REVERSE, color, NULL);


                // Impostazioni personalizzate del nemico

                this->velocitaProiettile = 1 + (0.2 * scaleFactor);

                strcpy(this->nome, "Alternatore");

                this->ticksForAction = 100;
                this->currentAction = 0;
                this->currentFrame = 1;

                numOfPatters = 10;
                this->numActions = 65*numOfPatters;
                this->actions = new int[this->numActions];
                for (int i = 0; i < this->numActions; i++) this->actions[i] = 0; // Prima le setto tutte a 0
                for(int i = 0; i < numOfPatters; i++) {
                    int dir = 1 << (rand() % 8); 
                    actions[ 0+(i*65)] = FRAME_PROSSIMO | MUOVI_DIREZIONE | dir;
                    for (int j = 1; j < 10; j++) {
                        actions[ j+(i*65)] = MUOVI_DIREZIONE | dir;
                    }
                    for (int j = 10; j < 15; j++) {
                        actions[ j+(i*65)] = AZIONE_PAUSA;
                    }
                    actions[15+(i*65)] = FRAME_PROSSIMO | AZIONE_PAUSA;
                    for (int j = 16; j < 65; j++) {
                        dir = 1 << (rand() % 8);
                        switch(rand()%3) {
                            case 0:
                                actions[j+(i*65)] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | dir;
                            break;
                            case 1:
                                actions[j+(i*65)] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO  | dir;
                                break;
                            case 2:
                                actions[j+(i*65)] = AZIONE_SPARA_DIREZIONE | AZIONE_SPARA_PRINCIPALE | AZIONE_SPARA_SECONDARIO | AZIONE_SPARA_TERZIARIO | dir;
                            break;
                        }
                    }
                }
            break;
        }
    }
    this->x -= (int) (((float)this->h_dimx-0.5)/2);
    this->y -= (int) (((float)this->h_dimy-0.5)/2);
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

        if( (azione & AZIONE_SPARA_SPUTAFUOCO) == AZIONE_SPARA_SPUTAFUOCO) {
            // capisce la direzione del giocatore rispetto al proiettile usando le coordinate
            int dir = patternDirezione;

            // Per come sono scritte le direzioni, shift bitwise di 1 a sinistra 
            // è uguale a ruotare di 45 gradi in senso orario.
            // Usando questo fatto, scelgo tra il fare un bitwise shift a destra o a sinistra
            // oppure nessuno a partire dalla direzione del pattern.

            switch (rand() % 3) {
                case 0: // Non faccio shift
                break;
                case 1: // Shift a sinistra
                    if(dir == DIRECTION_NO) {
                        dir = DIRECTION_NN;
                    } else {
                        dir = dir << 1;
                    }
                break;
                case 2: // Shift a destra
                    if(dir == DIRECTION_NN) {
                        dir = DIRECTION_NO;
                    } else {
                        dir = dir >> 1;
                    }
                break;
            }

            sparaProiettile(dir,0,stanza);
        }

        if ( (azione & FRAME_PROSSIMO) == FRAME_PROSSIMO ) {
            this->nextFrame();
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

    this->muovi(direzione,val);
    bool contattoGiocatore = player->controllaContatto(this->getX(), this->getY(), this->getDimX(), this->getDimY());
    this->muovi(direzione,-val);
    if (!contattoGiocatore) {
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
            case STANZA_ACC_PROIETTILE_NEMICO:
            case STANZA_ACC_ARTEFATTO:
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

    osX = osX + (int) ((float)this->h_dimx/2);
    osY = osY + (int) ((float)this->h_dimy/2);

    stanza->aggiungiProiettile(new Proiettile((this->y)+osY,(this->x)+osX,false,dir,this->damage,stanza->getId(), this->velocitaProiettile));
}


void Nemico::stampa(int offsetY, int offsetX) {
    Entita::stampa(offsetY, offsetX);
    if (this->type == BOSS_ENEMY) {
        stampaVita(70);
    }
}

/**
 * @brief Stampa la vita del nemico
 * 
 * La vita viene stampata in basso, a distanza di 5 dalla parte inferiore
 * del terminale. Viene inoltre stampato il nome del nemico e una corince
 * 
 * @param blocchi Il numero di blocchi di vita del nemico
 *                I nemici normali hanno 40 blocchi
 *                I boss hanno           70 blocchi
 */
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

int Nemico::getPunti() {
    return this->punti;
}