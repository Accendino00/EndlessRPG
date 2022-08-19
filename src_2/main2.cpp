#include "./generale/libs.hpp"

/*
    Comandi per compilazione con debug:
        g++ -g -o Gioco Entita.cpp Compatibility.cpp main.cpp -lncursesw
        valgrind --leak-check=full          --show-leak-kinds=all          --track-origins=yes          --verbose          --log-file=valgrind-out.txt          ./Gioco
*/

/**
 * @brief Dati del gioco
 * 
 * gd viene utilizzata in modo globale da tutti
 */
GameData * gd;

int main () {

    // Inizializzazione dei dati di gioco
    gd = new GameData();
    gd->startUp();

    // Start del menu principale
    MenuMain * m_main = new MenuMain();
    m_main->loopMenu();
    delete m_main;      // Quando finisce il loop del menu principale, è perché viene chiuso il gioco


    // Chiusura della finestra stdscr e fine del programma
    endwin();
    return gd->getStatus();
}