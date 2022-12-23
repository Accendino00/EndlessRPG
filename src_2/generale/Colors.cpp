#include "../generale/libs.hpp"

void initializeColors() {
    init_color(MENU_TEXT, 960 , 960 , 960 );
    init_color(MENU_BACKGROUND, 0, 0, 0);
    init_color(MENU_HL_TEXT, 0, 0, 0);
    init_color(MENU_HL_BACKGROUND, 1000, 1000, 1000);
    init_color(DEFAULT, 0, 0, 0);

    // Per poter convertire da 1000 1000 1000 a 255 255 255, uso questa costante per moltiplicare
    double CC = 1000 / 255;
    
    // Generico
    init_color(GAME_BACKGROUND,         0   * CC,   0   * CC,   0   * CC);
    
    // Menu
    init_color(MAIN_TITLE_TEXT,         255 * CC,   255 * CC,   51  * CC);
    init_color(MAIN_TITLE_BACKGROUND,   0  * CC,   0  * CC,   0 * CC);
    init_color(GAME_OVER_TEXT,          255 * CC,   0 * CC,   0  * CC);
    init_color(GAME_OVER_BACKGROUND,    0  * CC,   0  * CC,   0 * CC);
    init_pair(MENU_NORMAL,          MENU_TEXT,              MENU_BACKGROUND);
    init_pair(MENU_HIGHLIGHT,       MENU_HL_TEXT,           MENU_HL_BACKGROUND);
    init_pair(MAIN_TITLE,           MAIN_TITLE_TEXT,        MAIN_TITLE_BACKGROUND);
    init_pair(GAME_OVER,            GAME_OVER_TEXT,         GAME_OVER_BACKGROUND);

    // Per la mappa, ogni stanza ha colori diversi
    // I caratteri sono i muri, mentre il background e' lo spazio vuoto
    init_color(MAP_SPAWN_EMPTY,         19  * CC,   80  * CC,   95  * CC);
    init_color(MAP_NORMAL_EMPTY,        51  * CC,   19  * CC,   92  * CC);
    init_color(MAP_BOSS_EMPTY,          17  * CC,   29  * CC,   94  * CC);

    init_color(MAP_SPAWN_WALL,          0   * CC,   250 * CC,   171 * CC);
    init_color(MAP_NORMAL_WALL,         120 * CC,   66  * CC,   230 * CC);
    init_color(MAP_BOSS_WALL,           199 * CC,   0   * CC,   57  * CC);

    init_pair(MAP_SPAWN_PAIR,       MAP_SPAWN_WALL,         MAP_SPAWN_EMPTY);
    init_pair(MAP_NORMAL_PAIR,      MAP_NORMAL_WALL,        MAP_NORMAL_EMPTY);
    init_pair(MAP_BOSS_PAIR,        MAP_BOSS_WALL,          MAP_BOSS_EMPTY);


    // Colori per la minimappa: caratteri neri / come lo sfondo del gioco
    // Mentre il background ha lo stesso colore della stanza

    init_pair(MINIMAP_SPAWN_PAIR,   GAME_BACKGROUND,        MAP_SPAWN_EMPTY);
    init_pair(MINIMAP_NORMAL_PAIR,  GAME_BACKGROUND,        MAP_NORMAL_EMPTY);
    init_pair(MINIMAP_BOSS_PAIR,    GAME_BACKGROUND,        MAP_BOSS_EMPTY);
    init_color(MINIMAP_UNKNOWN_GREY,    50 * CC,   50   * CC,   50  * CC);
    init_pair(MINIMAP_UNKNOWN_PAIR, GAME_BACKGROUND,        MINIMAP_UNKNOWN_GREY);
    init_pair(MINIMAP_UNKNOWN_PAIR_TEXT, COLOR_WHITE,       MINIMAP_UNKNOWN_GREY);


    // Giocatore e nemici generici - da notare che hanno 3 bg diversi per le diverse stanze
    init_color(PLAYER_COLOR,            180 * CC,   230 * CC,   40  * CC);
    init_color(PLAYER_BULLET_COLOR,     90  * CC,   205 * CC,   255 * CC);
    init_color(ENEMY_BULLET_COLOR,      255 * CC,   90  * CC,   100 * CC);

    init_pair(PLAYER_COLOR_PAIR_E,  PLAYER_COLOR,           MAP_SPAWN_EMPTY);
    init_pair(PLAYER_COLOR_PAIR_N,  PLAYER_COLOR,           MAP_NORMAL_EMPTY);
    init_pair(PLAYER_COLOR_PAIR_B,  PLAYER_COLOR,           MAP_BOSS_EMPTY);
    init_pair(PLAYER_BULLET_PAIR_E, PLAYER_BULLET_COLOR,    MAP_SPAWN_EMPTY);
    init_pair(PLAYER_BULLET_PAIR_N, PLAYER_BULLET_COLOR,    MAP_NORMAL_EMPTY);
    init_pair(PLAYER_BULLET_PAIR_B, PLAYER_BULLET_COLOR,    MAP_BOSS_EMPTY);
    init_pair(ENEMY_BULLET_PAIR_E,  ENEMY_BULLET_COLOR,     MAP_SPAWN_EMPTY);
    init_pair(ENEMY_BULLET_PAIR_N,  ENEMY_BULLET_COLOR,     MAP_NORMAL_EMPTY);
    init_pair(ENEMY_BULLET_PAIR_B,  ENEMY_BULLET_COLOR,     MAP_BOSS_EMPTY);

    // HUD
    init_color(HEARTS,                  255 * CC,   0   * CC,   0   * CC);
    init_pair(HEARTS_PAIR,          HEARTS,                 GAME_BACKGROUND);

    // Porte
    init_color(DOOR_BACKGROUND,         222 * CC,   56  * CC,   200 * CC);
    init_color(DOOR_KEY_BACKGROUND,     18  * CC,   243 * CC,   156 * CC);
    init_color(DOOR_FOREGROUND,         222 * CC,   56  * CC,   200 * CC);
    init_color(DOOR_KEY_FOREGROUND,     18  * CC,   243 * CC,   156 * CC);
    
    init_pair(DOOR_PAIR,            DOOR_FOREGROUND,        DOOR_BACKGROUND);
    init_pair(DOOR_KEY_PAIR,        DOOR_KEY_FOREGROUND,    DOOR_KEY_BACKGROUND);
    

    // Artefatti
    init_color(ARTEFATTO_CUORE,          255 * CC,   0   * CC,   0   * CC);
    init_color(ARTEFATTO_POTENZIAMENTO,  0   * CC,   255 * CC,   100 * CC);
    init_color(ARTEFATTO_STATISTICHE,    0   * CC,   255 * CC,   255 * CC);
    init_color(ARTEFATTO_CHIAVE,         255 * CC,   255 * CC,   0   * CC);

    init_pair(ARTEFATTO_CUORE_PAIR_E,   ARTEFATTO_CUORE,    MAP_SPAWN_EMPTY);
    init_pair(ARTEFATTO_CUORE_PAIR_N,   ARTEFATTO_CUORE,    MAP_NORMAL_EMPTY);
    init_pair(ARTEFATTO_CUORE_PAIR_B,   ARTEFATTO_CUORE,    MAP_BOSS_EMPTY);

    init_pair(ARTEFATTO_POTENZIAMENTO_PAIR_E,   ARTEFATTO_POTENZIAMENTO,    MAP_SPAWN_EMPTY);
    init_pair(ARTEFATTO_POTENZIAMENTO_PAIR_N,   ARTEFATTO_POTENZIAMENTO,    MAP_NORMAL_EMPTY);
    init_pair(ARTEFATTO_POTENZIAMENTO_PAIR_B,   ARTEFATTO_POTENZIAMENTO,    MAP_BOSS_EMPTY);

    init_pair(ARTEFATTO_STATISTICHE_PAIR_E,   ARTEFATTO_STATISTICHE,    MAP_SPAWN_EMPTY);
    init_pair(ARTEFATTO_STATISTICHE_PAIR_N,   ARTEFATTO_STATISTICHE,    MAP_NORMAL_EMPTY);
    init_pair(ARTEFATTO_STATISTICHE_PAIR_B,   ARTEFATTO_STATISTICHE,    MAP_BOSS_EMPTY);

    init_pair(ARTEFATTO_CHIAVE_PAIR_E,   ARTEFATTO_CHIAVE,    MAP_SPAWN_EMPTY);
    init_pair(ARTEFATTO_CHIAVE_PAIR_N,   ARTEFATTO_CHIAVE,    MAP_NORMAL_EMPTY);
    init_pair(ARTEFATTO_CHIAVE_PAIR_B,   ARTEFATTO_CHIAVE,    MAP_BOSS_EMPTY);

    init_pair(ARTEFATTO_CUORE_PAIR_PAUSA,           ARTEFATTO_CUORE,            GAME_BACKGROUND);
    init_pair(ARTEFATTO_POTENZIAMENTO_PAIR_PAUSA,   ARTEFATTO_POTENZIAMENTO,    GAME_BACKGROUND);
    init_pair(ARTEFATTO_STATISTICHE_PAIR_PAUSA,     ARTEFATTO_STATISTICHE,      GAME_BACKGROUND);
    init_pair(ARTEFATTO_CHIAVE_PAIR_PAUSA,          ARTEFATTO_CHIAVE,           GAME_BACKGROUND);
}