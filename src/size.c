#include <sys/ioctl.h>
#include "wish_term.h"

int wish_resize(wish_term* term)
{
    struct winsize ws;

    ioctl(1, TIOCGWINSZ, &ws);
    if (term->size.x != ws.ws_col || term->size.y != ws.ws_row)
    {
        term->size.x = ws.ws_col;
        term->size.y = ws.ws_row;
        wish_frame_resize(&term->frames[0], term->size.x, term->size.y);
        wish_frame_resize(&term->frames[1], term->size.x, term->size.y);
        return 1;
    }
    return 0;
}

void wish_get_size(wish_term* term, wish_size* osize)
{
    *osize = term->size;
}
