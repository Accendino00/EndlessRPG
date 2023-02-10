/**
 * @file Proiettile.hpp
 * @author Petru Marcel Marincas
 * @date 2022
 * 
 * @brief 
 *      Contiene la classe Proiettile, che rappresenta un proiettile.
 *      Esso avanza all'interno della stanza fino a quando non incontra
 *      qualcosa: se quella cosa è bloccante, allora il proiettile viene
 *      distrutto (e infligge danni).
 * 
 *      L'insieme dei proiettili che appaiono nelle stanze viene gestito da listaProiettili.
 */

#pragma once
#include "../generale/libs.hpp"

class Proiettile : public Entita {
private:
    bool playerProjectile;
    int direzione;
public:
    Proiettile(int y, int x, bool playerProjectile, int direzione, int danno, int tipoStanza, double velocita);
    void updateEntita(Gioco * gioco);
    bool isPlayerProjectile();
};