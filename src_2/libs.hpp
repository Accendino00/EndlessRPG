#ifdef __linux__ 
    #include <ncurses.h>
#elif _WIN32
    #include <ncursesw/ncurses.h>
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

//Inclusione degli header
#include "Entita.hpp"

#include "Compatibility.cpp"