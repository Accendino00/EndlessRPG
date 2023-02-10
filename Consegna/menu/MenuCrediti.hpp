/**
 * @file MenuCrediti.hpp
 * @author Jacopo Francesco Amoretti
 * @date 2022
 * 
 * @brief 
 *  Classe di MenuCrediti. Gestisce il menu dei crediti.
 *  Mostra gli sviluppatori del gioco in ordine alfabetico.
 *  Si può tornare al menu principale.
 */

#pragma once
#include "../generale/libs.hpp"

class MenuCrediti : public Menu{
public:
    MenuCrediti();

    void loopMenu();
    void printAll();
    void printAuthors();
};