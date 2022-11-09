/**
 * @file main.cpp
 * @date 2022
 * @authors Petru Marcel Marincas, 
 *          Giuseppe Forciniti, 
 *          Davide Donati, 
 *          Jacopo Francesco Amoretti
 * 
 * @brief
 *      File che contiene il main del progetto del corso di Programmazione
 *      dell'università di Bologna, anno 2021 / 2022.
 * 
 *      Si tratta di un gioco platform in grafica ASCII, sviluppato su più livelli,
 *      con un punteggio e con controlli da tastiera. Gli altri requisiti e vincoli
 *      sono presenti sulle slides della presentazione del progetto.
 * 
 *      Abbiamo dato al nostro gioco il nome "".
 */


#include "./generale/libs.hpp"

/* 
    Dati del gioco globali.
    A questi dati vi si può accedere da tutti i file che includono "generale/libs.hpp".
    Non viene mai passato come parametro, tutte le funzioni lo considerano globale.

    Per più dettagli, vedere la classe "GameData" che si trova nella cartella "generale".
*/
GameData * gd;


int main () {

    // Inizializzazione dei dati di gioco
    gd = new GameData();
    gd->startUp();

    // Start del menu principale
    MenuMain * m_main = new MenuMain();
    m_main->loopMenu();
    delete m_main;

    // Chiusura della finestra di ncurses e fine del programma, con restituzione dello status
    // impostato in GameData, che viene impostato in modo particolare in caso di errori.
    endwin();
    return gd->getStatus();
}



/*
    Comandi per compilazione con debug:
        g++ -g -o Gioco Entita.cpp Compatibility.cpp main.cpp -lncursesw
        valgrind --leak-check=full          --show-leak-kinds=all          --track-origins=yes          --verbose          --log-file=valgrind-out.txt          ./Gioco

    Ncurses sembra usare:
    ==48346== HEAP SUMMARY:
    ==48346==     in use at exit: 1,079,082 bytes in 510 blocks
    ==48346==   total heap usage: 572 allocs, 62 frees, 1,174,014 bytes allocated

    // per ora, data 04 / 11 / 22, sembra non avere più memory leak

*/
