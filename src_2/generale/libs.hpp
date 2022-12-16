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
#include "../generale/GameData.hpp"

// La dichiaro qui così dopo non ho problemi con le dipendenze, 
// in quanto questa variabile è contenuta nel main e deve essere globale
extern GameData * gd;

#include "../generale/classDeclares.hpp"

//Inclusione degli header
#include "../entita/Entita.hpp"
#include "../entita/Nemico.hpp"
#include "../entita/Proiettile.hpp"
#include "../entita/Artefatto.hpp"
#include "../entita/Porta.hpp"

// Le liste di Entita varie
#include "../liste/ListaEntita.hpp"
#include "../liste/ListaNemici.hpp"
#include "../liste/ListaProiettili.hpp"
#include "../liste/ListaArtefatti.hpp"
#include "../liste/ListaPorte.hpp"

// Livello e le stanze
#include "../mappa/Stanza.hpp"
#include "../mappa/Livello.hpp"

// Il giocatore (che deve avere riferimento a Livello e, 
// per estensione, alle varie Liste di Entita, pertanto
// viene incluso successivamente alle loro definizioni)
#include "../entita/Player.hpp"

// Menu
#include "../menu/Menu.hpp"
#include "../menu/MenuScore.hpp"
#include "../menu/MenuMain.hpp"
#include "../menu/MenuOptions.hpp"
#include "../menu/MenuCrediti.hpp"
#include "../menu/MenuPause.hpp"
#include "../menu/MenuSalvaScore.hpp"
#include "../menu/MenuIstruzioni.hpp"
#include "../generale/Gioco.hpp"


