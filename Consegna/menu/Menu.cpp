#include "../generale/libs.hpp"

/**
 * @brief Costruttore di Menu
 * 
 * @param selezione    La selezione dalla quale partire
 * @param numOfOptions Il numero di opzioni che ha il menu
 * @param lineOffset   Quanto essere spostao rispetto al centro nelle y
 */
Menu::Menu(int selezione, int numOfOptions, int lineOffset) {
    this->selezione = selezione;
    this->numOfOptions = numOfOptions;
    this->lineOffset = lineOffset;
}

/**
 * @brief Gestisce l'input del menu.
 * Se si scende o si sale, allora si cambia la selezione. 
 */
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

/**
 * @brief Stampa la linea i-esima del menu con "text".
 * Se la linea è quella selezionata, la evidenzia.
 * 
 * L'id è un modo per indica l'indice nel quale si trova.
 * Se io ho un menu con 3 opzioni, l'id di queste sarà 0, 1, 2.
 * 
 * @param text Il testo della linea
 * @param id   L'id della linea
 */
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