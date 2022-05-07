#include "../generale/libs.hpp"

void initializeColors() {
    init_color(MENU_TEXT, 1000, 1000, 1000);
    init_color(MENU_BACKGROUND, 0, 0, 0);
    init_color(MENU_HL_TEXT, 0, 0, 0);
    init_color(MENU_HL_BACKGROUND, 1000, 1000, 1000);

    init_color(MAIN_TITLE_TEXT, 1000 * 254 / 255,1000 * 135 / 255,1000 * 93 / 255);
    init_color(MAIN_TITLE_BACKGROUND, 1000 * 53 / 255,1000 * 98 / 255,1000 * 136 / 255);


    init_pair(MENU_NORMAL, MENU_TEXT, MENU_BACKGROUND);
    init_pair(MENU_HIGHLIGHT, MENU_HL_TEXT, MENU_HL_BACKGROUND);
    init_pair(MAIN_TITLE, MAIN_TITLE_TEXT, MAIN_TITLE_BACKGROUND);
}