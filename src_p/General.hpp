#ifdef __linux__ 
    #include <ncurses.h>
#elif _WIN32
    #include <ncursesw/ncurses.h>
#else
    #error Errore di compilazione, sistema operativo non supportato
#endif

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>

//Inclusione degli header
#include "Entita.hpp"
#include "Stanza.hpp"
#include "Nemico.hpp"
#include "Livello.hpp"
#include "Player.hpp"

