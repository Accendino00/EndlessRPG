#pragma once
#ifdef __linux__ 
    #include <ncurses.h>
#else
    #error Errore di compilazione, sistema operativo non supportato
#endif

#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <chrono>
#include <stdio.h>
#include <unistd.h>


#include "../generale/Colors.hpp"
#include "../generale/General.hpp"

// La dichiaro qui così dopo non ho problemi con le dipendenze, 
// in quanto questa variabile è contenuta nel main e deve essere globale
extern GameData * gd;

//Menu
#include "../menu/MenuOptions.hpp"
#include "../menu/MenuMain.hpp"

//Inclusione degli header
#include "../entita/Entita.hpp"
#include "../mappa/Stanza.hpp"
#include "../entita/Player.hpp"

