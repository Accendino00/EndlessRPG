#ifdef _WIN32
    #include <ncursesw/ncurses.h>

    #define CCHARW_MAX	5
        typedef struct
        {
            attr_t	attr;
            wchar_t	chars[CCHARW_MAX];
        #if 0
        #undef NCURSES_EXT_COLORS
        #define NCURSES_EXT_COLORS 20201114
            int		ext_color;	/* color pair, must be more than 16-bits */
        #endif
        }
        cchar_t;

    // non sono implementate perfettamente uguali a quelle di ncurses normale, ma
    // ciò che non implemento, non lo suo, quindi trovavo superfluo cercare di imitarlo

    int getcchar(  const cchar_t *wcval,
               wchar_t *wch,
               attr_t *attrs,
               short *color_pair,
               void *opts) 
    {
        int returnValue = OK;
        if (wcval != NULL && wch != NULL && attrs != NULL && color_pair != NULL) {
            int index = 0;
            while ((*wcval).chars[index] != L'\0') {
                (*wcval).chars[index] = wch[index];
            }
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
        if (wcval != NULL && wch != NULL && attrs != NULL && color_pair != NULL) {
            int index = 0;
            while ((*wcval).chars[index] != L'\0') {
                (*wcval).chars[index] = wch[index];
            }
            (*wcval).attr = (*attrs);
            (*wcval).ext_color = (*color_pair);
        } else {
            returnValue = ERR;
        }
        return returnValue;
    }

    void mvwadd_wch (WINDOW * win, int y, int x, const cchar_t * c) {
        attr_t attributo;
        wchar_t carattere;
        short colorpair;
        getcchar(c, &carattere, &attributo, &color_pair, NULL);
        wattron(win, attributo | COLOR_PAIR(color_pair));
        mvwprintw(win,y,x,"%lc",carattere);
        wattroff(win, attributo | COLOR_PAIR(color_pair));
    }

#endif


