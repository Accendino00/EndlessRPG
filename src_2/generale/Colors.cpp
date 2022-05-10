#include "../generale/libs.hpp"

void initializeColors() {
    init_color(MENU_TEXT, 1000, 1000, 1000);
    init_color(MENU_BACKGROUND, 0, 0, 0);
    init_color(MENU_HL_TEXT, 0, 0, 0);
    init_color(MENU_HL_BACKGROUND, 1000, 1000, 1000);
    init_color(DEFAULT, 0, 0, 0);

    // Per poter convertire da 1000 1000 1000 a 255 255 255, uso questa costante per moltiplicare
    double CC = 1000 / 255;
    init_color(MAIN_TITLE_TEXT,         254 * CC,   135 * CC,   93  * CC);
    init_color(MAIN_TITLE_BACKGROUND,   53  * CC,   98  * CC,   136 * CC);

    init_color(MAP_BACKGROUND,          0   * CC,   0   * CC,   0   * CC);
    init_color(PLAYER_COLOR,            180 * CC,   230 * CC,   40  * CC);
    init_color(PLAYER_BULLET_COLOR,     90  * CC,   205 * CC,   255 * CC);
    init_color(ENEMY_BULLET_COLOR,      255 * CC,   90  * CC,   100 * CC);
    init_color(HEARTS,                  255 * CC,   0 * CC,     0 * CC );

    init_pair(MENU_NORMAL,          MENU_TEXT,              MENU_BACKGROUND);
    init_pair(MENU_HIGHLIGHT,       MENU_HL_TEXT,           MENU_HL_BACKGROUND);
    init_pair(MAIN_TITLE,           MAIN_TITLE_TEXT,        MAIN_TITLE_BACKGROUND);
    init_pair(PLAYER_COLOR_PAIR,    PLAYER_COLOR,           MAP_BACKGROUND);
    init_pair(HEARTS_PAIR,          HEARTS,                 DEFAULT);
    init_pair(PLAYER_BULLET_PAIR,   PLAYER_BULLET_COLOR,    MAP_BACKGROUND);
    init_pair(ENEMY_BULLET_PAIR,    ENEMY_BULLET_COLOR,     MAP_BACKGROUND);
       
}