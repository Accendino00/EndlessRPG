#include "./generale/libs.hpp"

/*

    Comandi per compilazione con debug:
        g++ -g -o Gioco Entita.cpp Compatibility.cpp main.cpp -lncursesw
        valgrind --leak-check=full          --show-leak-kinds=all          --track-origins=yes          --verbose          --log-file=valgrind-out.txt          ./Gioco
*/

GameData * gd;

int main () {

    // Inizializzazione
    gd = new GameData();
    gd->startUp();
    // Menu m_main, m_pause, m_options, m_credits, m_insertName;
    // HighscoreMenu m_score;
    // ConfirmMenu m_confirmExit, m_confirmExitPause;

    MenuMain * m_main = new MenuMain();
    m_main->loopMenu();
    delete m_main;

    endwin();
    return gd->getStatus();
}