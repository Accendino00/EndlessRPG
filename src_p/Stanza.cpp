#include "Entita.hpp"


Stanza::Stanza(Entita * nemici, Entita * porte, Entita * artefatti, WINDOW * schermata_mappa, wchar_t ** matrice_stampabile, int ** matrice_logica){
    (*this).nemici = nemici;
    (*this).porte = porte;
    (*this).artefatti = artefatti;
    (*this).schermata_mappa = schermata_mappa;
    (*this).topologia.matrice_stampabile = matrice_stampabile;
    (*this).topologia.matrice_logica = matrice_logica;
}
bool Stanza::accessibile(int ** mappa, int x, int y){
    int returnbool = false;
    if(x >= 0 && x < 80 && y >= 0 && y < 20 && mappa[x][y] != 1){
        returnbool = true;
    } return returnbool;
}
