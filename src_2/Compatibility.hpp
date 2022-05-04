#pragma once
#include "libs.hpp"
    
#define CCHARW_MAX	5
struct cchar_t
{
    attr_t	attr;
    wchar_t	chars[CCHARW_MAX];
#if 1
#undef NCURSES_EXT_COLORS
#define NCURSES_EXT_COLORS 20201114
    int		ext_color;	/* color pair, must be more than 16-bits */
#endif
};
typedef struct cchar_t cchar_t;
int getcchar(  const cchar_t *wcval,
           wchar_t *wch,
           attr_t *attrs,
           short *color_pair,
           void *opts);
int setcchar(  
           cchar_t *wcval,
           const wchar_t *wch,
           const attr_t attrs,
           short color_pair,
           const void *opts );
void mvwadd_wch (WINDOW * win, int y, int x, const cchar_t * c);