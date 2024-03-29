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
    // Inizializzazione dei dati di gioco globali
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