#include <ncursesw/ncurses.h>
#include "Entita.hpp"
#include "Stanza.hpp"

class Player:public Entita{
    private:

    public:
    Player(int x,int y, int attr, cchar_t ** stampa, int ** attr_arr):Entita(x, y, attr, stampa, attr_arr);
    void movimento(int input, Stanza stanza);
    void inventario();

}