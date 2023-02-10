/**
 * @file Porta.hpp
 * @author Petru Marcel Marincas
 * @date 2022
 * 
 * @brief Contiene la classe Porta, che rappresenta una porta.
 * Estende la classe Entita. Viene creata dalle stanze, in base
 * alle stanze che hanno adiacenti.
 * 
 * Nel costruttore si specifica la direzione della porta, se è
 * con chiave o meno, e le dimensioni della stanza in cui si
 * trova. Questo permette di centrarla correttamente nella stanza. 
 */
#pragma once
#include "../generale/libs.hpp"

#define DIMENSIONE_PORTA_VERTICALE 5
#define DIMENSIONE_PORTA_ORIZZONTALE 10

#define PORTA_NORD  0
#define PORTA_SUD   1
#define PORTA_EST   2
#define PORTA_OVEST 3

class Porta : public Entita {
private:
    bool portaConChiave;
public:
    Porta(int direzione, bool portaConChiave, int dimstanzay, int dimstanzax);

    void updateEntita();
    bool isPortaConChiave();
};