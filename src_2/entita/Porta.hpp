#pragma once
#include "../generale/libs.hpp"

#define DIMENSIONE_PORTA_VERTICALE 5
#define DIMENSIONE_PORTA_ORIZZONTALE 10
#define PORTA_NORD  0
#define PORTA_SUD   1
#define PORTA_EST   2
#define PORTA_OVEST 3

class Porta : public Entita {
public:
    Porta(int type, int direzione, bool portaConChiave);

    void updateEntita();
};