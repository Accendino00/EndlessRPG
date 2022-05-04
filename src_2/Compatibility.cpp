#include "libs.hpp"
// non sono implementate perfettamente uguali a quelle di ncurses normale, ma
// ciò che non implemento, non lo uso, quindi trovavo superfluo cercare di imitarlo
int getcchar(  const cchar_t *wcval,
           wchar_t *wch,
           attr_t *attrs,
           short *color_pair,
           void *opts) 
{
    int returnValue = OK;
    if (wcval != NULL && wch != NULL && attrs != NULL && color_pair != NULL) {
        int index = 0;
        while (index < CCHARW_MAX-1 && (*wcval).chars[index] != L'\0') {
            wch[index] = (*wcval).chars[index];
        }
        wch[index] = L'\0';
        (*attrs) = (*wcval).attr;
        (*color_pair) = (*wcval).ext_color;
    } else {
        returnValue = ERR;
    }
    return returnValue;
}
int setcchar(  
           cchar_t *wcval,
           const wchar_t *wch,
           const attr_t attrs,
           short color_pair,
           const void *opts ) 
{
    int returnValue = OK;
    if (wcval != NULL && wch != NULL) {
        int index = 0;
        while (index < CCHARW_MAX-1 && (*wcval).chars[index] != L'\0') {
            (*wcval).chars[index] = wch[index];
        }
        (*wcval).chars[index] = L'\0';
        (*wcval).attr = (attrs);
        (*wcval).ext_color = (color_pair);
    } else {
        returnValue = ERR;
    }
    return returnValue;
}
void mvwadd_wch (WINDOW * win, int y, int x, const cchar_t * c) {
    //attr_t attributo;
    //wchar_t carattere [CCHARW_MAX];
    //short color_pair;
    //getcchar(c, carattere, &attributo, &color_pair, NULL);
    wattron(win, c->attr | COLOR_PAIR(c->ext_color));
    mvwprintw(win,y,x,"%ls",c->chars);
    wattroff(win, c->attr | COLOR_PAIR(c->ext_color));
}