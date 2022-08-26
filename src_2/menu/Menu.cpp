#include "../generale/libs.hpp"


Menu::Menu(int selezione, int numOfOptions, int lineOffset) {
    this->selezione = selezione;
    this->numOfOptions = numOfOptions;
    this->lineOffset = lineOffset;
}

void Menu::manageInput() {
    int i = 0;
    while(i < gd->getNumOfPressedKeys()) {
        switch(gd->getKey(i)) {
            case KEY_UP:
            case L'w':
            case L'W':
                selezione = (selezione -1 + numOfOptions) % numOfOptions;
                break;
            case KEY_DOWN:
            case L's':
            case L'S':
                selezione = (selezione + 1) % numOfOptions;
                break;
        }
        i++;
    }
}

int Menu::getSelezione() {
    return this->selezione;
}

void Menu::printLine(const char * text, int id) {
    attron(COLOR_PAIR(MENU_NORMAL));
    int centerY = gd->getTerminalY()/2;
    int centerX = gd->getTerminalX()/2;
    if (this->getSelezione() == id) {
        attron(COLOR_PAIR(MENU_HIGHLIGHT));
        mvprintw(lineOffset+centerY+(2*(id+1)),centerX-4,">");
    }
    mvprintw(lineOffset+centerY+(2*(id+1)),centerX-2,"%s",text);
    if (this->getSelezione() == id) {
        attroff(COLOR_PAIR(MENU_HIGHLIGHT));
    }
    attroff(COLOR_PAIR(MENU_NORMAL));
}